#include "ProcessSimulator.h"
#include <vector>
#include <algorithm> //std::sort

using namespace std;

/// <summary>
/// Initializes a new instance of the <see cref="ProcessSimulator"/> class.
/// </summary>
ProcessSimulator::ProcessSimulator()
{
}

/// <summary>
/// Initializes a new instance of the <see cref="ProcessSimulator" /> class.
/// </summary>
/// <param name="algorithim">The algorithim.</param>
/// <param name="contextSwitch">The context switch.</param>
/// <param name="processSet">The process set.</param>
/// <param name="multiProcessMode">if set to <c>true</c> [multi process mode]. Defaults to false</param>
/// <returns></returns>
ProcessSimulator::ProcessSimulator(SchedulingAlgorithim algorithim, unsigned contextSwitch, const ProcessSet& processSet, bool multiProcessMode) :
	waitingTime(0), totalRunningTime(0), currentAlgorithim(algorithim), contextPenalty(contextSwitch),
	totalPenalty(0), scheduledProcesses(processSet), multiProcessMode(multiProcessMode)
{
	numberProcesses = scheduledProcesses.GetNumberProcesses();
}

/// <summary>
/// Runs the simulation.
/// </summary>
void ProcessSimulator::RunSimulation()
{
	switch (currentAlgorithim)
	{
	case RoundRobin:
		RunRRSimulation();
		break;
	case FIFO:
		// if we are in multiProcess mode then run a quad core simulation
		multiProcessMode ? RunFifoQuadCoreSimulation() : RunFifoSimulation();
		break;
	case SJF:
        multiProcessMode? RunSJFQuadCoreSimulation() : RunSJFSimulation();
		break;

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
	unsigned int totalCycleNumber = 0;


	// while we still have processes scheduled to run
	while (scheduledProcesses.GetNumberProcesses() > 0)
	{
		Process currentProcess = scheduledProcesses.FirstProcess();

		runningQueue.AddProcess(currentProcess);

		// Increase the total time by how long this process needs to run
		totalRunningTime += currentProcess.numberCycles;

		// If this is the first process, we simply ignore calcuating the waiting time, but we will
		// store the current process running cycle to totalCycleNumber var. Next,
		// if this is not the first process, we will first compare the totalCycleNumber to current process
		// arrival Time. If this is true, we have a waiting time, and we also need to update the totoal cycle number. It it's false, we don't have the waiting time.
		// (waiting time = 0)


		if (iProcess != 1) {
			if (totalCycleNumber > currentProcess.arrivalTime) {
				waitingTime += (totalCycleNumber - currentProcess.arrivalTime);
				totalCycleNumber += currentProcess.numberCycles;
			}
			else {
				totalCycleNumber = (currentProcess.arrivalTime + currentProcess.numberCycles);
			}

		}
		// No waiting time since this is the first process
		else {
			totalCycleNumber = currentProcess.numberCycles;
			iProcess++;
		}

		totalPenalty += contextPenalty;
		scheduledProcesses.PopProcess();
	}
}

/// <summary>
/// Runs the fifo quad core simulation.
/// </summary>
void ProcessSimulator::RunFifoQuadCoreSimulation()
{
	// how many processors we currently have left to run a process
	unsigned int processorsLeft = 4;
	unsigned int totalCycles = 0;

	// all the processes that are running right now
	std::vector<Process> runningProcesses;

	// start with one running process
	runningProcesses.push_back(scheduledProcesses.FirstProcess());
	scheduledProcesses.PopProcess();

	// for a multiprocess system we are going to treat each time around the loop as one cycle. This way each we always know when to add or remove a process
	while (scheduledProcesses.GetNumberProcesses() > 0)
	{
		// the process that is scheduled next to run
		Process waitingProcess = scheduledProcesses.FirstProcess();
		// if we have an open processor AND we have a process waiting then we give this process to some processor
		if (processorsLeft > 0 && totalCycles >= waitingProcess.arrivalTime)
		{
			// asign this process to some processor so it can do some work
			processorsLeft--;
			runningProcesses.push_back(waitingProcess);
			// we need to calculate the waiting time that this process had to wait for an open processor
			waitingTime += (totalCycles - waitingProcess.arrivalTime);

			// we now should have one less process scheduled
			scheduledProcesses.PopProcess();

		}
		// either we don't have a processor waiting or their isn't a process that has arrived
		else
		{
			// loop through all the processes that are currently running on all the processors
			for (unsigned int i = 0; i < runningProcesses.size(); i++)
			{
				// do we have a process that has finished up?
				if (runningProcesses[i].numberCycles <= 0)
				{
					// make a processor avaliable
					processorsLeft++;
					
					// context penalty since processor has to do some work to get ready for next process
					totalPenalty += contextPenalty;

					// we are finished with this proces remove it from the set
					runningProcesses.erase(runningProcesses.begin() + i);
				}
				// process is not done yet, just keep subtracting the number cycles it has left
				else
				{
					runningProcesses[i].numberCycles--;
				}
			}
		}

		totalCycles++;
	}

}

//bool ProcessSimulator::compare_cycles(const Process &lhs, const Process &rhs)
//{
//    return lhs.numberCycles < rhs.numberCycles;
//}



void ProcessSimulator::RunSJFSimulation()
{
	int remainProcess = scheduledProcesses.GetNumberProcesses();
	int totalNumberOfProcess = remainProcess;

	int firstProcess = true;
	vector<Process> ProcessSet;

	unsigned int perviousCycle = 0;

	unsigned int currentProcessingIndex = 0;
	unsigned int nextArrivalTime = 0;


	// Pass the processes in queue into an array. This makes the whole thing easier.
	while (scheduledProcesses.GetNumberProcesses() > 0)
	{
		Process newProcess = scheduledProcesses.FirstProcess();
		ProcessSet.push_back(newProcess);
		scheduledProcesses.PopProcess();
	}

	// Sort the vector so we always get SJ Process
	sort(ProcessSet.begin(), ProcessSet.end());

	// SJF
	while (ProcessSet.size() > 0)
	{

		if (firstProcess)
		{
			// Find the first process with arrival time = 0
			for (unsigned int i = 0; i < ProcessSet.size(); i++) {
				if (ProcessSet.at(i).arrivalTime == 0)
				{
					// Save the first process cycle
					if (ProcessSet.at(i).numberCycles >= 50)
					{
						perviousCycle = ProcessSet.at(i).numberCycles;
					}
					else
					{
						perviousCycle = 50;
					}

					// Delete the process since we are done with it
					ProcessSet.erase(ProcessSet.begin() + i);

					currentProcessingIndex++;

					break;
				}
			}

			firstProcess = false;
		}
		// Not first process
		else
		{

			nextArrivalTime = (50 * currentProcessingIndex) + 50;

			// Find next process based on next Arrival Time
			for (unsigned int i = 0; i < ProcessSet.size(); i++) {
				// get the process that has shortest cycle but also arrived
				if (ProcessSet.at(i).arrivalTime <= perviousCycle)
				{
					waitingTime += perviousCycle - ProcessSet.at(i).arrivalTime;

					//cout << "waiting time = " << waitingTime << endl;
					perviousCycle = perviousCycle + ProcessSet.at(i).numberCycles;

					// perviousCycle is still less than
					if (perviousCycle < nextArrivalTime) {
						perviousCycle = nextArrivalTime;
					}

					//cout << "pervious = " << perviousCycle << endl;

					// Delete the process since we are done with it
					ProcessSet.erase(ProcessSet.begin() + i);

					//cout << endl;

					currentProcessingIndex++;
					// Update context switch penalty
					totalPenalty += contextPenalty;
					break;
				}

			}
		}
	}

}

void ProcessSimulator::RunSJFQuadCoreSimulation()
{
    vector<Process> processSet;
    
    // Pass the processes in queue into an array. This makes the whole thing easier.
    while (scheduledProcesses.GetNumberProcesses() > 0)
    {
        Process newProcess = scheduledProcesses.FirstProcess();
        processSet.push_back(newProcess);
        scheduledProcesses.PopProcess();
    }
    
    // Sort the vector so we always get SJ Process
    sort(processSet.begin(), processSet.end());
    
    // how many processors we currently have left to run a process
    unsigned int processorsLeft = 4;
    unsigned int totalCycles = 0;
    
    // all the processes that are running right now
    std::vector<Process> runningProcesses;
    
    // start with one running process
    runningProcesses.push_back(processSet.at(0));
    processSet.erase(processSet.begin() + 0);
    
    
    // for a multiprocess system we are going to treat each time around the loop as one cycle. This way each we always know when to add or remove a process
    while (processSet.size() > 0)
    {
        // the process that is scheduled next to run
        Process waitingProcess = processSet.at(0);
        // if we have an open processor AND we have a process waiting then we give this process to some processor
        if (processorsLeft > 0 && totalCycles >= waitingProcess.arrivalTime)
        {
            // asign this process to some processor so it can do some work
            processorsLeft--;
            runningProcesses.push_back(waitingProcess);
            // we need to calculate the waiting time that this process had to wait for an open processor
            waitingTime += (totalCycles - waitingProcess.arrivalTime);
            
            // we now should have one less process scheduled
            processSet.erase(processSet.begin() + 0);
            
        }
        // either we don't have a processor waiting or their isn't a process that has arrived
        else
        {
            // loop through all the processes that are currently running on all the processors
            for (unsigned int i = 0; i < runningProcesses.size(); i++)
            {
                // do we have a process that has finished up?
                if (runningProcesses[i].numberCycles <= 0)
                {
                    // make a processor avaliable
                    processorsLeft++;
                    
                    // context penalty since processor has to do some work to get ready for next process
                    totalPenalty += contextPenalty;
                    
                    // we are finished with this proces remove it from the set
                    runningProcesses.erase(runningProcesses.begin() + i);
                }
                // process is not done yet, just keep subtracting the number cycles it has left
                else
                {
                    runningProcesses[i].numberCycles--;
                }
            }
        }
        
        totalCycles++;
    }
}


// Round Robin
void ProcessSimulator::RunRRSimulation()
{
}


///---------------------------


/// <summary>
/// Simulating 4-core multiprocessors
/// </summary>


/// struct Processor
/// Simulating a 4-core processor by using a vector of processes

struct Processor
{
	std::vector<Process> processList;
	int totalCycleCount;
	int AvailableMemory;
};

/// Create a list of processors  
std::vector<Processor> processorList;

/// Create 4 processors with 4GB of memory each 
void generateProcessors()
{
	int numOfProcessors = 4;
	int i;

	for (i = 0; i < numOfProcessors; i++)
	{
		Processor currentProcessor;
		currentProcessor.totalCycleCount = 0;
		currentProcessor.AvailableMemory = 4000000;
		processorList.push_back(currentProcessor);
	}
}
