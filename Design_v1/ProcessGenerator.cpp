#include <iostream>
#include <random>
#include <vector>
#include "ProcessGenerator.h"
using namespace std;

const int CYCLE_STANDARD_DEVIATION = 6000;      //Customize the ST DEV for the normal distribution for generateing random #
const int FOOTPRINT_STANDARD_DEVIATION = 20;

//Constructor: Generate random numbers for number of Cycles and Size of memory footprint
//Arg:         The Process's id
ProcessGenerator::ProcessGenerator(int psID) {
    
    processID = psID;
    
    random_device rd;
    mt19937 gen(rd());
    
    //Normal Distribution with mean = 6000, standard deviation = 1000
    normal_distribution<> cycle(6000,CYCLE_STANDARD_DEVIATION);
    int number = round(cycle(gen));
    
    //Set the range of the Process's number of cycles to be with 1000 to 11000
    while(number < 1000 || number > 11000) {
        number = round(cycle(gen));
    }
    numberOfCycles = number;
    
    //Normal Distrubution with mean = 20, standard deviation = 10
    normal_distribution<> footprint(20,FOOTPRINT_STANDARD_DEVIATION);
    number = round(footprint(gen));
    
    //Set the range of the size of memory footprint to be within 1KB to 100KB
    while(number < 1 || number > 100) {
        number = round(footprint(gen));
    }
    
    sizeOfMemoryFootprint = number;
    
}

int ProcessGenerator::getProcessID() {
    return processID;
}
int ProcessGenerator::getNumberOfCycles() {
    return numberOfCycles;
}
int ProcessGenerator::getSizeOfMemoryFootprint() {
    return sizeOfMemoryFootprint;
}

void ProcessGenerator::printProcessID() {
    cout << "Process ID = " << processID << endl;
}
void ProcessGenerator::printNumberOfCycles() {
    cout << "Number of Cycles = " << numberOfCycles << endl;
}
void ProcessGenerator::printSizeOfMemoryFootprint() {
    cout << "Size of memory footprint = " << sizeOfMemoryFootprint << "KB" << endl;
}