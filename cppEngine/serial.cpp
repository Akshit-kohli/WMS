#include "serial.h"
#include "config.h"
#include <iostream>
using namespace std;
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int openSerialPort(const char* portName, int baudRate){
    int fd = open(portName, O_RDWR | O_NOCTTY);

    if (fd == -1){
        cout << "Failed to open the serial port: " << portName << endl;
        return -1;   
    }
    struct termios options;

    if(tcgetattr(fd, &options) != 0){
        cout << "Failed to get serial port attributes" << endl;
        close(fd);
        return -1;
    }
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    if(tcsetattr(fd, TCSANOW, &options) != 0){
        cout << "Failed to set serial port attributes" << endl;
        close(fd);
        return -1;
    }

    return fd;
}




int readFromSerial(int fd, char* buffer, int bufferSize){
    int bytesRead = read(fd, buffer, bufferSize -1);

    if (bytesRead == -1){
        cout << "Failed to read from serial port" << endl;
        return -1;
    }

    buffer[bytesRead] = '\0'; 
    return bytesRead;
}

void closeSerialPort(int fd){
    if(fd != -1){
        close(fd);
        cout << "Serial port is closed" << endl;
    }
}