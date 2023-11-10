//
// Created by anne on 10/28/23.
//
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "serial.hpp"
#include "../Detect/detect.hpp"
#include "../Pnp/pnp.hpp"



serial::serial(detect &detect,pnp &pnp){
    serial_detect = &detect;
    serial_pnp =&pnp;
    sp_ret = open();

}

bool serial::open(){
    sp_return ret = sp_get_port_by_name("/dev/ttyACM0", &serPort);
    if(ret != SP_OK)sp_get_port_by_name("/dev/ttyUSB0", &serPort);
    ret = sp_open(serPort,SP_MODE_READ_WRITE);
    if(ret != SP_OK) return false;
    sp_set_baudrate(serPort,115200);
    sp_set_bits(serPort, 8);
    sp_set_parity(serPort,SP_PARITY_NONE);
    sp_set_stopbits(serPort, 1);
    cout<<"open"<<endl;
    return true;
}

[[noreturn]] bool serial::send(){
    while (true) {
        if (!sp_ret) {
            data = "NULL";
            serial_detect->serData = data;
            sp_ret = open();
        } else {
            
            if(serial_detect->list != 0){
                data = "A";
                data += "Y";
                if (serial_pnp->yaw > 0)data += "+";
                else data += "-";
                data += cv::format("%06.2f", abs(serial_pnp->yaw));
                data += "P";
                if (serial_pnp->pitch_off > 0)data += "+";
                else data += "-";
                data += cv::format("%06.2f", abs(serial_pnp->pitch_off));
                if (abs(serial_pnp->yaw) < 5 && abs(serial_pnp->pitch_off) < 5) data += "F";
                else data += "N";
                data += "E";
                sp_blocking_write(serPort, data.c_str(), 19, 0);
                serial_detect->serData = data;
                cout<<data<<endl;
            }
            else{
                data = "AY+000.00P+000.00NE";
                sp_blocking_write(serPort,data.c_str(),19,0);
                serial_detect->serData = data;
            }

        }

    }

}

[[noreturn]] bool serial::receive() {
    while(true){
        char sign;
        sp_nonblocking_read(serPort,&sign,1);
        if(sign=='A'){
            sp_nonblocking_read(serPort,&buf,24);
            if(buf[23]=='E' && buf[1]=='Y' && buf[9]=='P' && buf[17]=='S'){
                serial_detect->enemyColor = buf[0]=='B' ? "blue":"red";
                float selfYaw,selfPitch,shootSpeed;
                std::string strbuffer = buf;
                selfYaw=std::stof(strbuffer.substr(2,7));
                selfPitch=std::stof(strbuffer.substr(10,7));
                shootSpeed=std::stof(strbuffer.substr(18,5));
                serial_pnp->v=shootSpeed;
                serial_detect->readData = 'A'+strbuffer;
            }
        }
        else{
            serial_detect->readData = "NULL";
        }
    }
}
