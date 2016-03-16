//
//  ProcessGenerator.h
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

#ifndef ProcessGenerator_h
#define ProcessGenerator_h

class ProcessGenerator {
private:
    int processID;                      //A unique process ID
    int numberOfCycles;                 //Interval ranging from <1,000, 11,000> with a mean of 6,000
    int sizeOfMemoryFootprint;          //Ranging of 1KB to 100KB with a mean of 20KB
    
public:
    
    //Constructor: Generate random numbers for number of Cycles and Size of memory footprint
    //Arg:         The Process's id
    ProcessGenerator(int psID);

    void printProcessID();
    void printNumberOfCycles();
    void printSizeOfMemoryFootprint();
};

#endif /* ProcessGenerator_h */
