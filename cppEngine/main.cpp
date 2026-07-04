#include<iostream>
#include "serial.h"
#include "config.h"
using namespace std;

int main() {
    cout << "WeightBridge Management System"<< endl;
    
    cout << "Operating serial port.." << endl;

    int fd = openSerialPort(SERIAL_PORT, BAUD_RATE);

    if (fd == -1){
        cout << "Exiting due to port failure" << endl;
        return -1;
    }

    cout << "Serial port opened successfully" << endl;
    char buffer[BUFFER_SIZE];

    cout <<"Reading data from serial port.. " << endl;
    int bytesRead = readFromSerial(fd , buffer, BUFFER_SIZE);

    if (bytesRead > 0){
        cout << "Recieved: " << buffer << endl;
    }
    closeSerialPort(fd);
    return 0;
}