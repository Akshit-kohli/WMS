#include "transaction.h"
#include <string>
#include <ctime>
#include <iostream>
using namespace std;

string getCurrentDateTime(){
    time_t now = time(0);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", localtime(&now));
    return string(buffer);
}

transactionDetail createTransaction(
    string name,
    string phoneNumber,
    string vehicleNumber,
    string vehicleType,
    string material,
    double ratePerKG,
    string location
){
    transactionDetail transaction;

    transaction.name = name;
    transaction.phoneNumber = phoneNumber;
    transaction.vehicleNumber = vehicleNumber;
    transaction.vehicleType = vehicleType;
    transaction.material = material;
    transaction.ratePerKG = ratePerKG;
    transaction.location = location;
    transaction.dateTime = getCurrentDateTime();
    transaction.status = transactionStatus::CREATED;
    transaction.grossWeight = 0.0;
    transaction.tareWeight = 0.0;
    transaction.netWeight = 0.0;
    transaction.price = 0.0;

    return transaction; 
}

void captureGrossWeight(transactionDetail &transaction, double grossWeight){
    transaction.grossWeight = grossWeight;
    transaction.status = transactionStatus::GROSS_CAPTURED;
}

void captureTareWeight(transactionDetail &transaction, double tareWeight){
    transaction.tareWeight = tareWeight;
    transaction.netWeight = transaction.grossWeight - transaction.tareWeight;
    transaction.price = transaction.netWeight * transaction.ratePerKG;
    transaction.status = transactionStatus::TARE_CAPTURED;
}
