#include "receipt.h"
#include <iostream>
using namespace std;

void printReceipt(const transactionDetail& transaction){
    cout << "\n" << endl;
    cout << "-------------------- RECEIPT -------------------" << endl;
    cout << "         BENDOCH WEIGHTBRIDGE SERVICES          " << endl;
    cout << "================================================" << endl;
    cout << "\n" <<endl;
    cout << "Date & Time    : "<< transaction.dateTime << endl;
    cout << "Location       : "<< transaction.location << endl;
    cout << "\n" << endl;
   
    cout << "------------------------------------------------" << endl;
    cout << "   CUSTOMER DETAILS" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Customer Name  : "<< transaction.name << endl;
    cout << "Phone Number   : "<< transaction.phoneNumber << endl;
    cout << "\n" << endl;
   
    cout << "------------------------------------------------" << endl;
    cout << "   VEHICLE AND MATERIAL" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Vehicle Number : "<< transaction.vehicleNumber << endl;
    cout << "Vehicle Type   : "<< transaction.vehicleType << endl;
    cout << "Material       : "<< transaction.material << endl;
    cout << "\n" << endl;
   
    cout << "------------------------------------------------" << endl;
    cout << "   WEIGHT DETAILS" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Gross Weight   : "<< transaction.grossWeight << " KG" << endl;
    cout << "Tare Weight    : "<< transaction.tareWeight << " KG" << endl;
    cout << "Net Weight     : "<< transaction.netWeight << " KG" << endl; 
    cout <<"\n" << endl;

    cout << "------------------------------------------------" << endl;
    cout << "   CHARGES" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Rate per KG    :Rs. "<< transaction.ratePerKG << endl;
    cout << "Total Charges  :Rs. "<< transaction.price << endl;
    cout << "\n" << endl;

    cout << "=================================================" << endl;
    cout << "         Thank you for your business!            " << endl;
    cout << "            Bendoch Pvt. Ltd.                   " << endl;
    cout << "=================================================" << endl;
    cout << "\n" << endl;
}