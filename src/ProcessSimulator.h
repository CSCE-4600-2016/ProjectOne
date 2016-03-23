#ifndef PROCESS_SIMULATOR_H_
#define PROCESS_SIMULATOR_H_

#include <map>

#include "Helpers.h"
#include "ProcessSet.h"

/// <summary>
/// Represents a simulation of a process scheduling algorithm
/// </summary>
class ProcessSimulator
{
public:	
	ProcessSimulator();	
	/// <summary>
	/// Initializes a new instance of the <see cref="ProcessSimulator" /> class.
	/// </summary>
	/// <param name="algorithim">The algorithim.</param>
	/// <param name="contextSwitch">The context switch.</param>
	/// <param name="processSet">The process set.</param>
	/// <param name="multiProcessMode">if set to <c>true</c> [multi process mode].</param>
	ProcessSimulator(SchedulingAlgorithim algorithim, unsigned int contextSwitch, const ProcessSet& processSet, bool multiProcessMode = false);
	
	/// <summary>
	/// Runs the simulation.
	/// </summary>
	void RunSimulation();

	/// <summary>
	/// Gets the average wait time.
	/// </summary>
	/// <returns></returns>
	float GetAverageWaitTime() const;
	
	/// <summary>
	/// Gets the total penalty.
	/// </summary>
	/// <returns></returns>
	int GetTotalPenalty() const;
	

private:
	// Driver Methods for the individual simulation types
	void RunFifoSimulation();
		
	void RunFifoQuadCoreSimulation();

	void RunRRSimulation();
	
	void RunSJFSimulation();
    
    void RunSJFQuadCoreSimulation();
	

	/// <summary>
	/// The process waiting times
	/// key: processId
	/// value: process waiting time
	/// </summary>
	std::map<int, int> processWaitingTimes;

	unsigned int waitingTime;
	unsigned int totalRunningTime;
	SchedulingAlgorithim currentAlgorithim;
	unsigned int contextPenalty;
	unsigned int totalPenalty;
	ProcessSet scheduledProcesses;
	unsigned int numberProcesses;
	bool multiProcessMode;

};

#endif
