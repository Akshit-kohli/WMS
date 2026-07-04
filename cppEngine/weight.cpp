#include <cstdio>
#include "weight.h"
#include <iostream>
using namespace std;

double parseWeight(const char*rawData){
    double value;
    char unit[4];
    int readParameters = sscanf(rawData, "%lf %s", &value, unit);

    if (readParameters != 2) {
        return -1.0;
    }

    string unitString(unit);
    if (unitString == "kg" || unitString == "KG") {
        return value;
    }
    else if (unitString == "g" || unitString == "G") {
        return value / 1000.0;
    }
    else if (unitString == "lb" || unitString == "LB") {
        return value * 0.453592;
    }
    else {
        return -1.0; 
    }

}

bool isValidWeight(double weight){
    if (weight >100.0 && weight < 60000.0) {
        return true;
    } else {
        return false;
    }
}