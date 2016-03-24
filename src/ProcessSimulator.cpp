#include "ProcessSimulator.h"
#include <fstream>
#include <iostream>
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
        multiProcessMode ? RunSJFQuadCoreSimulation() : RunSJFSimulation();
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

void ProcessSimulator::WriteReportFile() const
{
    std::ofstream reportFile;

    switch(this->currentAlgorithim)
    {
    case RoundRobin: 
        multiProcessMode ? reportFile.open("round-robin-quad-core.csv") : reportFile.open("round-robin-single-core.csv");
        break;
    case FIFO:
        multiProcessMode ? reportFile.open("fifo-quad-core.csv") : reportFile.open("fifo-single-core.csv");
        break;
    case SJF:
        multiProcessMode ? reportFile.open("sjf-quad-core.csv") : reportFile.open("sjf-single-core.csv");
        break;
    default: break;
    }

    // if for some reason we could not open the file just report. Don't attempt to write it
    if (!reportFile.is_open())
        return;

    // Column Header information
    reportFile << "Process Id, Wait Time\n";

    // write the csv report file. 
    // first is the process id, and second is the process wait time
    for(auto process : processWaitingTimes)
    {
        reportFile << process.first << ", " << process.second << std::endl;
    }
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
                processWaitingTimes.insert(std::make_pair(currentProcess.processId, waitingTime));
            }
            else {
                totalCycleNumber = (currentProcess.arrivalTime + currentProcess.numberCycles);
            }

        }
        // No waiting time since this is the first process
        else {
            totalCycleNumber = currentProcess.numberCycles;
            iProcess++;
            // first process didn't have any wait time
            processWaitingTimes.insert(std::make_pair(currentProcess.processId, 0));
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
    // first process has no waiting time
    processWaitingTimes.insert(std::make_pair(scheduledProcesses.FirstProcess().processId, 0));
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
            processWaitingTimes.insert(std::make_pair(waitingProcess.processId, waitingTime));

            // we now should have one less process scheduled
            scheduledProcesses.PopProcess();

        }
        // either we don't have a processor waiting or their isn't a process that has arrived
        else
        {
            // loop through all the processes that are currently running on all the processors
            for (unsigned int i = 0; i < runningProcesses.size(); i++)
            {
                // do we have a process that has completedProcessesed up?
                if (runningProcesses[i].numberCycles <= 0)
                {
                    // make a processor avaliable
                    processorsLeft++;
                    
                    // context penalty since processor has to do some work to get ready for next process
                    totalPenalty += contextPenalty;

                    // we are completedProcessesed with this proces remove it from the set
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
    int numberOfRemainingProcesses = scheduledProcesses.GetNumberProcesses();
    int totalNumberOfProcess = numberOfRemainingProcesses;

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
                        processWaitingTimes.insert(std::make_pair(ProcessSet.at(i).processId, 0));
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
                    processWaitingTimes.insert(std::make_pair(ProcessSet.at(i).processId, waitingTime));

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
    processWaitingTimes.insert(std::make_pair(processSet.front().processId, 0));
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
            // assign this process to some processor so it can do some work
            processorsLeft--;
            runningProcesses.push_back(waitingProcess);

            // we need to calculate the waiting time that this process had to wait for an open processor
            waitingTime += (totalCycles - waitingProcess.arrivalTime);
            processWaitingTimes.insert(std::make_pair(waitingProcess.processId, waitingTime));

            // we now should have one less process scheduled
            processSet.erase(processSet.begin() + 0);
            
        }
        // either we don't have a processor waiting or their isn't a process that has arrived
        else
        {
            // loop through all the processes that are currently running on all the processors
            for (unsigned int i = 0; i < runningProcesses.size(); i++)
            {
                // do we have a process that has completedProcessesed up?
                if (runningProcesses[i].numberCycles <= 0)
                {
                    // make a processor avaliable
                    processorsLeft++;
                    
                    // context penalty since processor has to do some work to get ready for next process
                    totalPenalty += contextPenalty;
                    
                    // we are completedProcessesed with this proces remove it from the set
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
    // Quantum time of 50 cycles, should be fixed
       const int quantumTime = 50;
       int time = 0;
       int isProcessDone = 0; // should be a bool...
       
    // set remaining procs to number of procs currently in queue
    int numberOfRemainingProcesses = scheduledProcesses.GetNumberProcesses();
    
    // total becomes remaining
    int totalNumberOfProcess = numberOfRemainingProcesses;
       
    // create a new process array object called processSet
    // populate with the total number of procs
       Process *processSet = new Process[totalNumberOfProcess];
    
    // Populate remaining time, completedProcesses or "complete" processes, and waiting processes
    // with total # of procs
    
    // Dynamically allocate remaining time; quick and dirty fix to the potential CSE machine
    // problem related to predefined sizing of arrays in C++   
    int *remainingTime;   
    remainingTime = new int [totalNumberOfProcess];

    // after checking it will compile on the CSE machines
    // since these are just arrays, we could just switch to using vectors since this is what they are for...
       int completedProcesses[totalNumberOfProcess];
       int wait[totalNumberOfProcess];
       
    // init counter var and cycle time to 0. Assuming that totCycletime is
    // going to be used in updating the CSP when this algo runs every iteration
    int count = 0;
    int totalCycleTime = 0;

       processWaitingTimes.insert(std::make_pair(scheduledProcesses.FirstProcess().processId, 0));
    
       // Pass the processes in queue into an array. This makes the whole thing easier.
    // Check while there's still scheduled procs in the queue...
       while(scheduledProcesses.GetNumberProcesses() > 0)
       {
           // create new process object and feed it the first scheduled proc
           Process newProcess = scheduledProcesses.FirstProcess();
           
           // update process set with counter for index, and set = to above object
           processSet[count] = newProcess;
           
           // increment totalCycletime by # cycles of the newProcess object
           totalCycleTime += newProcess.numberCycles;
           
           // rem. time array gets updated with counter for index, set
           // equal to the # of cycles
           remainingTime[count] = newProcess.numberCycles;
           
           // completedProcesses is a array keeping track of complete procs. We populate with count and set
           // == to zero
           completedProcesses[count] = 0;
           
           // locally update count 
           count++; 
           
           // decrement process from sched queue
           scheduledProcesses.PopProcess();
       }
    
    //  //-----------------------------------------------------------
    //     for(int i = 0; numberOfRemainingProcesses != 0;)
    //     {
    //             // check if the rem time for the current proc is < quantum
    //         if((remainingTime[i] <= quantumTime) && (remainingTime[i] > 0))
    //         {
    
    //             time += remainingTime[i];
    //             remainingTime[i] = 0;
    //             isProcessDone = 1;
    //         }
    //         else if(remainingTime[i] > 0)
    //         {
    //             remainingTime[i] -= quantumTime;
    //             time += quantumTime;
    //         }
    
    //         // If rem time for the current process is zero,
    //            // and process is done
    //         if((remainingTime[i] == 0) && (isProcessDone == 1))
    //            {
    //             numberOfRemainingProcesses--;
    //          //   std::cout << time - processSet[i].arrivalTime - processSet[i].numberCycles << std::endl;
    //             waitingTime += (time - processSet[i].arrivalTime - processSet[i].numberCycles);
    //             isProcessDone = 0;
    //         }
    
    //         if(i == (totalNumberOfProcess - 1))
    //         {
    //             i = 0;
    //         }
       
    //            else if (processSet[i+1].arrivalTime <= time)
    //         {
    //             i++;
    //         }
       
    //            else
    //         {
    //             i = 0;
    //         }
    //     }
    // //---------------------------------------------------

       // we set our proc time to 0
       int processingTime = 0;
    
       for(time = 0; time < totalCycleTime;) // traverse from 0 to totCycleTime
       {
           // as long as we are less than all procs
           for(int i = 0; i < totalNumberOfProcess;i++)
           {
               //
               if((processSet[i].arrivalTime <= time) && (completedProcesses[i] == 0))
               {
                   if(remainingTime[i] < quantumTime)
                   {
                       processingTime = remainingTime[i];
                   }
                   else
                   {
                       processingTime = quantumTime;
                   }
                   
                   remainingTime[i] = remainingTime[i] - processingTime;
                   
                   if(remainingTime[i] == 0)
                   {
                       completedProcesses[i] = time; // (c) http://stackoverflow.com/questions/1491281completedProcesses/round-robin-scheduling-program
                   }
                   for (int j = 0; j < totalNumberOfProcess; j++)
                   {
                       // check for our inner counter != outer counter
                       // and if uncompletedProcessesed and if the arrival time is
                       // less than or equal to the current time
                       if(j != i && completedProcesses[j] == 0 && processSet[j].arrivalTime <= time)
                       {
                           // Update the waiting time
                           waitingTime += processingTime;
                           processWaitingTimes.insert(std::make_pair(processSet[j].processId, waitingTime));
                           
                           // update contextSwitchPenalty with the global total penalty
                           totalPenalty += contextPenalty;
                       }
                   }
                   time = time + processingTime;
               }
           }
       }
       
       // manual cleanup, bad practice (not RAII) but its quick and dirty for just one variable
       delete remainingTime;
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