#pragma once
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <string>


/*bind socket return fd if success*/
int socketBind(int port);//可能需要参数IP

/*send content to the router on port, return 0 if success*/
int socketSend(int fd, int port, std::string IP, std::string content);

/*receive content, return port number if success, else return -1*/
int socketReceive(int fd, std::string &content, std::string &IP);

#endif