#include<iostream>
#include "serial.h"
#include "config.h"
#include "weight.h"
#include "transaction.h"
#include "receipt.h"
#include <string>
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
    int choice;

    while(true){
        cout << "--------------------- MENU ---------------------" << endl;
        cout << "1. New Transaction" << endl;
        cout << "2. Exit" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "\n" << endl;
        cout << "Enter your choice: " ;
        cin >> choice;
        
        switch (choice) {
            case 2:
                cout << "Exiting the program." << endl;
                closeSerialPort(fd);
                return 0;
            case 1:
                transactionDetail transaction;
                cout << "Enter Customer Name: ";
                cin >> transaction.name;
                cout << "Enter Phone Number: ";
                cin >> transaction.phoneNumber;
                cout << "Enter Vehicle Number: ";
                cin >> transaction.vehicleNumber;
                cout << "Enter Vehicle Type: ";
                cin >> transaction.vehicleType;
                cout << "Enter Material: ";
                cin >> transaction.material;
                cout << "Enter Rate per KG: ";
                cin >> transaction.ratePerKG;
                cout << "Enter Location: ";
                cin >> transaction.location;
                transaction.dateTime = getCurrentDateTime();


                while(true){
                    cout << "Place loaded vehicle on scale. Waiting for gross weight.." << endl;
                    int bytesRead = readFromSerial(fd , buffer, BUFFER_SIZE);
                    double gross = parseWeight(buffer);

                    if(bytesRead > 0){
                        if(gross != 0 && isValidWeight(gross)){
                            captureGrossWeight(transaction, gross);
                            cout << "Gross weight captured: " << transaction.grossWeight << " KG" << endl;
                            break;
                        }
                        else{
                            cout << "Failed to capture gross weight" << endl;
                        }       
                    }
                }

                while(true){
                    cout << "Place empty vehicle on scale. Waiting for tare weight.." << endl;
                    int bytesRead = readFromSerial(fd , buffer, BUFFER_SIZE);
                    double tare = parseWeight(buffer);
                    if(bytesRead > 0){
                        if(tare != 0 && isValidWeight(tare)){
                            captureTareWeight(transaction, tare);
                            cout << "Tare weight captured: " << transaction.tareWeight << " KG" << endl;
                            break;
                        }
                        else{
                            cout << "Failed to capture tare weight" << endl;
                        }
                    }
                }

                printReceipt(transaction);
        }
    }

    closeSerialPort(fd);
    return 0;
}