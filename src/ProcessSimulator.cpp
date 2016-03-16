#include "ProcessSimulator.h"



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
int ProcessSimulator::GetAverageWaitTime() const
{
	return (waitingTime / numberProcesses);
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

	// while we still have processes scheduled to run
	while(scheduledProcesses.GetNumberProcesses() > 0)
	{
		// get a reference to the current scheduled process
		Process currentProcess = scheduledProcesses.FirstProcess();
		runningQueue.AddProcess(currentProcess);
		// increase the total time by how long this process needs to run
		totalRunningTime += currentProcess.numberCycles;
		// calculate the time this process hade to wait and add it to the total waiting time
		waitingTime += currentProcess.arrivalTime;
		totalPenalty += contextPenalty;
		totalRunningTime += contextPenalty;
		scheduledProcesses.PopProcess();

	}
}
