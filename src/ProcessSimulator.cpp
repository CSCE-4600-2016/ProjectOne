#include "ProcessSimulator.h"
#include <iostream>


/// <summary>
/// Initializes a new instance of the <see cref="ProcessSimulator"/> class.
/// </summary>
ProcessSimulator::ProcessSimulator()
{
}

/// <summary>
/// Initializes a new instance of the <see cref="ProcessSimulator"/> class.
/// </summary>
/// <param name="algorithim">The algorithim.</param>
/// <param name="contextSwitch">The context switch.</param>
/// <param name="processSet">The process set.</param>
ProcessSimulator::ProcessSimulator(SchedulingAlgorithim algorithim, unsigned contextSwitch, const ProcessSet& processSet): 
	waitingTime(0), totalRunningTime(0), currentAlgorithim(algorithim), contextPenalty(contextSwitch), totalPenalty(0), scheduledProcesses(processSet)
{
	numberProcesses = scheduledProcesses.GetNumberProcesses();
}

/// <summary>
/// Runs the simulation.
/// </summary>
void ProcessSimulator::RunSimulation()
{
	switch(currentAlgorithim)
	{
	case RoundRobin: break;
	case FIFO:
		RunFifoSimulation();
		break;
	case SRT: break;
	case SJF: break;
	case LRT: break;
	default: break;
	}
}

/// <summary>
/// Gets the average wait time.
/// </summary>
/// <returns></returns>
float ProcessSimulator::GetAverageWaitTime() const
{
	return ((float)waitingTime / (float)numberProcesses);
}

/// <summary>
/// Gets the total penalty.
/// </summary>
/// <returns></returns>
int ProcessSimulator::GetTotalPenalty() const
{
	return totalPenalty;
}

void ProcessSimulator::RunFifoSimulation()
{
	ProcessSet runningQueue;
    int iProcess = 1;
    int totalCycleNumber = 0;

	// while we still have processes scheduled to run
	while(scheduledProcesses.GetNumberProcesses() > 0)
	{

		Process currentProcess = scheduledProcesses.FirstProcess();
        
		runningQueue.AddProcess(currentProcess);
        
		// increase the total time by how long this process needs to run
		totalRunningTime += currentProcess.numberCycles;
        
		// calculate the time this process hade to wait and add it to the total waiting time
		//waitingTime += currentProcess.arrivalTime;
        
        // If this is the first process, we simply ignore calcuating the waiting time, but we will
        // store the current process running cycle to totalCycleNumber var. Next,
        // if this is not the first process, we will first compare the totalCycleNumber to current process
        // arrival Time. If this is true, we have a waiting time, and we also need to update the totoal cycle number. It it's false, we don't have the waiting time.
        // (waiting time = 0)
        
        if(iProcess != 1) {
            if (totalCycleNumber > currentProcess.arrivalTime) {
                waitingTime += (totalCycleNumber - currentProcess.arrivalTime);
                totalCycleNumber += currentProcess.numberCycles;
            }
            else {
                totalCycleNumber = (currentProcess.arrivalTime + currentProcess.numberCycles);
            }
            
        }
        else {
            totalCycleNumber = currentProcess.numberCycles;
            iProcess++;
        }
        
		totalPenalty += contextPenalty;
		scheduledProcesses.PopProcess();
	}
}
