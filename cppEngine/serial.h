#pragma once

int openSerialPort(const char* portName, int baudRate);

int readFromSerial(int fd, char* buffer, int bufferSize);

void closeSerialPort(int fd);
