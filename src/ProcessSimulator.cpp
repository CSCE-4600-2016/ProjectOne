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
	int waitingTimeSum = 0;
	for (auto iter = processWaitingTimes.begin(); iter != processWaitingTimes.end(); ++iter)
	{
		// set a temporary iter at the end and go back one to get the final iter
		auto finalIter = processWaitingTimes.end();
		--finalIter;
		// we don't need to calculate the very last one because their was no processes after it so nothing waited
		if(iter != finalIter)
		{
			waitingTimeSum += iter->second;
		}
	}

	return waitingTimeSum / processWaitingTimes.size();
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
		auto currentProcess = scheduledProcesses.FirstProcess();
		runningQueue.AddProcess(currentProcess);

		// increase the total time by how long this process needs to run
		totalRunningTime += (currentProcess.numberCycles + contextPenalty);

		// calculate the time this process hade to wait and add it to the total waiting time
		// 50 is because this process came in 50 cycles later
		waitingTime += (currentProcess.numberCycles + contextPenalty) - 50;
		processWaitingTimes.insert(std::pair<int, int>(currentProcess.processId, waitingTime));

		totalPenalty += contextPenalty;
		scheduledProcesses.PopProcess();

	}
}
