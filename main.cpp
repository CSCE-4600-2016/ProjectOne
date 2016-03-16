/*
 * main.cpp
 * Date Modified: 3/3/2016
 * Team members: Ho Ting Jimmy Yeung, Asad Waheed, Chad Smith
 *
 *
 *
 */

#include <iostream>
#include <vector>
#include "ProcessGenerator.h"
#include "ProcessTable.h"

using namespace std;
const int NUMBER_OF_PROCESS = 50;

int main(int argc, const char * argv[]) {
    vector<PCB> setOfProcesses;
    
    // Logic: We will first create 50 PCBs using ProcessGenerator and ProcessTable, each of them will have 50 Cycles time more than the pervious process based on the project requirment. So process 1 will have 0 arrival time, process 2 will have 50, then 100,etc. We then apply our Algorithms and get the results.
    
    // BY Jimmy
    // Note: The below code has not been tested since I am not sure if I am using the PCB struct correctly
    
    
    //Create 50 processes and PCBs, save them in vector
    for(int i = 1; i <= NUMBER_OF_PROCESS; i++) {
        
        // This will be the arrvial time of each process. Increment by 50 each time
        int arrivalAndWaitTime = 50 * (i - 1);
        
        // Obtain a new process
        ProcessGenerator p(i);
        
        // Create a new PCB based on the prcoess's
        PCB pcb = PCB(p.getProcessID(), arrivalAndWaitTime, 0, 50 * i,NOT_LOADED, 0);
        
        // Push the new PCB into a list of PCB
        setOfProcesses.push_back(pcb);
    }
    
    // TODO: We now need to work on implementing the Algorithms
    
    return 0;
}