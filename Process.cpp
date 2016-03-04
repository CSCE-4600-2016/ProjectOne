//
//  main.cpp
//  ProcessSims
//
//  Created by Ho Ting Jimmy Yeung on 2/11/16.
//
//  Usage: The program will generate K processes, and each process will have a unique ID, number of cycles and size of memory
//          footprint. The program will store each process into a resizeable array which becomes a set of processes.
//          Finally, the program will loop through the set of processes array and print out each process's information.
//
//  Argruments: CYCLE_STANDARD_DEVIATION is the standard deviation for normal distrubution. Default value is the same as mean which is 6000.
//              FOOTPRINT_STANDARD_DEVIATION is the standard deviation for normal distrubution. Default value is the same as mean which is 20.
//              K_PROCESSES is the number of processes that you want the program generates.
//
//  Compile: Use the following commend to compile the program:  "   g++ main.cpp -std=c++0x    "
//
//

#include <iostream>
#include <random>
#include <vector>
using namespace std;

const int CYCLE_STANDARD_DEVIATION = 6000;      //Customize the ST DEV for the normal distribution for generateing random #
const int FOOTPRINT_STANDARD_DEVIATION = 20;
const int K_PROCESSES = 20;                    //Set the number of processes you want to generate

class Process {
    private:
    int processID;                      //A unique process ID
    int numberOfCycles;                 //Interval ranging from <1,000, 11,000> with a mean of 6,000
    int sizeOfMemoryFootprint;          //Ranging of 1KB to 100KB with a mean of 20KB
    
    public:
    Process(int psID);                          //Constructor
    void printProcessID() {
        cout << "Process ID = " << processID << endl;
    }
    void printNumberOfCycles() {
        cout << "Number of Cycles = " << numberOfCycles << endl;
    }
    void printSizeOfMemoryFootprint() {
        cout << "Size of memory footprint = " << sizeOfMemoryFootprint << "KB" << endl;
    }
};

//Constructor: Generate random numbers for number of Cycles and Size of memory footprint
//Arg:         The Process's id
Process::Process(int psID) {
    
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

int main(int argc, const char * argv[]) {
    vector<Process> setOfProcesses;
    
    //Create K processes and store each process into a resizeable Array which is a set of processes
    for(int i = 1; i <= K_PROCESSES; i++) {
        Process p(i);
        setOfProcesses.push_back(p);
    }

    //Print out the infomation of each process
    for(int i = 0; i < setOfProcesses.size(); i++) {
        setOfProcesses[i].printProcessID();
        setOfProcesses[i].printNumberOfCycles();
        setOfProcesses[i].printSizeOfMemoryFootprint();
        cout << endl;
    }
    return 0;
}
