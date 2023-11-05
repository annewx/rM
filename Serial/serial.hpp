//
// Created by anne on 10/28/23.
//
#include <iostream>
#include <libserialport.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string>
#include "../Detect/detect.hpp"
#include "../Pnp/pnp.hpp"


#ifndef ARMOR_SERIAL_HPP
#define ARMOR_SERIAL_HPP


class serial {
public:
    detect *serial_detect;
    pnp *serial_pnp;

    bool sp_ret;
    std::string  data;
    char buf[25];
    struct sp_port *serPort;
    serial(class detect &detect,class pnp &pnp);
    bool open();
    //发送数据
    [[noreturn]] bool send();

    //接受数据
    [[noreturn]] bool receive();



};





#endif //ARMOR_SERIAL_HPP
