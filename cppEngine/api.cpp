#include "api.h"
#include "httplib.h"
#include "json.hpp"
#include "transaction.h"
#include <iostream>
using json = nlohmann::json;
using namespace std;
using namespace httplib;
bool sendTransaction(const transactionDetail& transaction){
    json transactionJson;
    transactionJson["name"] = transaction.name;
    transactionJson["phoneNumber"] = transaction.phoneNumber;
    transactionJson["vehicleNumber"] = transaction.vehicleNumber;
    transactionJson["vehicleType"] = transaction.vehicleType;
    transactionJson["material"] = transaction.material;
    transactionJson["ratePerKG"] = transaction.ratePerKG;
    transactionJson["grossWeight"] = transaction.grossWeight;
    transactionJson["tareWeight"] = transaction.tareWeight;
    transactionJson["netWeight"] = transaction.netWeight;
    transactionJson["price"] = transaction.price;
    transactionJson["dateTime"] = transaction.dateTime;
    transactionJson["location"] = transaction.location;
    string statusStr;
    switch(transaction.status) {
        case transactionStatus::CREATED:
                statusStr = "CREATED";
                break;
        case transactionStatus::GROSS_CAPTURED: 
                statusStr = "GROSS_CAPTURED";
                break;
        case transactionStatus::COMPLETED:
                statusStr = "COMPLETED";    
                break;
        default:
                statusStr = "UNKNOWN";
                break;
    }
    transactionJson["status"] = statusStr;




    string jsonString = transactionJson.dump();
    Client client("localhost", 3000);
    auto res = client.Post("/api/transactions", jsonString, "application/json");

    if (res && res->status == 200) {
        cout << "Transaction sent successfully!" << endl;
        return true;
    } else {
        cout << "Failed to send transaction. Status: " << (res ? res->status : 0) << endl;
        return false;
    }
}

