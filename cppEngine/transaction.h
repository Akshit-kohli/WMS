#pragma once 
#include <string>
using namespace std;

enum class transactionStatus{
        CREATED,
        GROSS_CAPTURED,
        COMPLETED
};

struct transactionDetail{
    string name;
    string phoneNumber;
    string vehicleNumber;
    string vehicleType;
    string material;
    double grossWeight;
    double tareWeight;
    double netWeight;
    double price;
    string dateTime;
    string location;
    transactionStatus status;
};

transactionDetail createTransaction(
    string name,
    string phoneNumber,
    string vehicleNumber,
    string vehicleType,
    string material,
    string location
);

void captureGrossWeight(transactionDetail &transaction, double grossWeight);

void captureTareWeight(transactionDetail &transaction, double weight, double ratePerKG);
string getCurrentDateTime();
