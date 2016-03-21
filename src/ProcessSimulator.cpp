#include "ProcessSimulator.h"
#include <iostream>
#include <vector>

using namespace std;
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
	case RoundRobin:
        RunRRSimulation();
        break;
	case FIFO:
		RunFifoSimulation();
		break;
	case SRT:
        break;
	case SJF:
        RunSJFSimulation();
        break;
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
        
		// Increase the total time by how long this process needs to run
		totalRunningTime += currentProcess.numberCycles;
        
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
        // No waiting time since this is the first process
        else {
            totalCycleNumber = currentProcess.numberCycles;
            iProcess++;
        }
        
		totalPenalty += contextPenalty;
		scheduledProcesses.PopProcess();
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
    
    int perviousCycle = 0;
    
    int currentProcessingIndex = 0;
    int nextArrivalTime = 0;
    
    
    // Pass the processes in queue into an array. This makes the whole thing easier.
    while(scheduledProcesses.GetNumberProcesses() > 0)
    {
        Process newProcess = scheduledProcesses.FirstProcess();
        ProcessSet.push_back(newProcess);
        scheduledProcesses.PopProcess();
    }
    
    // Sort the vector so we always get SJ Process
    sort(ProcessSet.begin(),ProcessSet.end());

    // SJF
    while(ProcessSet.size() > 0)
    {
        
        if(firstProcess)
        {
            // Find the first process with arrival time = 0
            for(int i = 0 ; i<ProcessSet.size(); i++) {
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
            for(int i = 0 ; i < ProcessSet.size(); i++) {
                // get the process that has shortest cycle but also arrived
                if(ProcessSet.at(i).arrivalTime <= perviousCycle)
                {
                    //waitingTime += perviousCycle - ProcessSet.at(i).arrivalTime;
                    
                    cout << "waiting time = " << waitingTime << endl;
                    perviousCycle = perviousCycle + ProcessSet.at(i).numberCycles;
                    
                    // perviousCycle is still less than
                    if(perviousCycle < nextArrivalTime) {
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

void ProcessSimulator::RunRRSimulation()
{
    // Quantum time of 50 cycles
    int quantumTime = 50;
    int time = 0;
    int isProcessDone = 0;
    
    int remainProcess = scheduledProcesses.GetNumberProcesses();
    int totalNumberOfProcess = remainProcess;
    
    Process *processSet = new Process[totalNumberOfProcess];
    int remainingTime[totalNumberOfProcess];
    int finish[totalNumberOfProcess];
    int wait[totalNumberOfProcess];
    int count = 0;
    int totalCycleTime = 0;

    // Pass the processes in queue into an array. This makes the whole thing easier.
    while(scheduledProcesses.GetNumberProcesses() > 0)
    {
        Process newProcess = scheduledProcesses.FirstProcess();
        processSet[count] = newProcess;
        totalCycleTime += newProcess.numberCycles;

        remainingTime[count] = newProcess.numberCycles;
        
        
        finish[count] = 0;
        count++;
        scheduledProcesses.PopProcess();
    }
    
//    for(int i = 0; remainProcess != 0;)
//    {
//        if(remainingTime[i] <= quantumTime && remainingTime[i] > 0)
//        {
//            time += remainingTime[i];
//            remainingTime[i] = 0;
//            isProcessDone = 1;
//        }
//        else if(remainingTime[i] > 0)
//        {
//            remainingTime[i] -= quantumTime;
//            time += quantumTime;
//        }
//        
//        // If current process is done
//        if(remainingTime[i] == 0 && isProcessDone == 1) {
//            remainProcess--;
//            std::cout << time - processSet[i].arrivalTime - processSet[i].numberCycles << std::endl;
//            waitingTime += (time - processSet[i].arrivalTime - processSet[i].numberCycles);
//            isProcessDone = 0;
//        }
//        
//        if(i == (totalNumberOfProcess - 1))
//        {
//            i = 0;
//        }
//        else if (processSet[i+1].arrivalTime <= time)
//        {
//            i++;
//        }
//        else
//        {
//            i = 0;
//        }
//    }
    int dec = 0;
    for(time = 0; time < totalCycleTime;)
    {
        for(int i = 0; i < totalNumberOfProcess;i++)
        {
            if(processSet[i].arrivalTime <= time && finish[i] == 0)
            {
                if(remainingTime[i] < quantumTime)
                {
                    dec = remainingTime[i];
                }
                else
                {
                    dec = quantumTime;
                }
                
                remainingTime[i] = remainingTime[i] - dec;
                if(remainingTime[i] == 0) {
                    finish[i] = 1;
                }
                for (int j = 0; j < totalNumberOfProcess; j++) {
                    if(j!=i && finish[j] == 0 && processSet[j].arrivalTime <= time)
                    {
                        waitingTime += dec;
                    }
                }
                time = time + dec;
            }
        }
    }
    
}
