#ifndef PROCESS_H_
#define PROCESS_H_
/// <summary>
/// Process Struct
/// Represents a process that would be running inside of an operating system
/// </summary>


struct Process
{
public:
	Process();
	// Constructor - Creates a new process with process information
	// processId - simulates the id of the process, as what the OS would use
	// numberCycles - simulates the number or cycles a process uses
	// memoryFootprint - simulates the memory footprint	
	Process(unsigned int processId, unsigned int numberCycles, unsigned int memoryFootprint, unsigned int arrivalTime);
    
    bool operator<(const Process& s2) const {
        return this->numberCycles < s2.numberCycles;
    }
	
	/// <summary>
	/// The process identifier
	/// </summary>
	unsigned int processId;	
	/// <summary>
	/// The number cycles
	/// </summary>
	unsigned int numberCycles;	
	/// <summary>
	/// The memory footprint
	/// </summary>
	unsigned int memoryFootprint;
	
	/// <summary>
	/// The arrival time
	/// </summary>
	unsigned int arrivalTime;

	/// The following are specific to Round Robin Scheduling Algorithm
	unsigned int waitTime;

	unsigned int turnAroundTime;
};

#endif