

#include <iostream>

#include "ProcessSet.h"
#include "ProcessSimulator.h"


int main(int argc, char** argv)
{
	ProcessSet process_set;
	process_set.BuildProcessSet(std::cin);
	// build a simulator for a fifo scheduler, with a context switch penalty of 10
	ProcessSimulator simulator(SchedulingAlgorithim::FIFO, 10, process_set);

	std::cout << "Total Processes: " << process_set.GetNumberProcesses() << std::endl;
	simulator.RunSimulation();
	
	std::cout << "Average Wait Time: " << simulator.GetAverageWaitTime() << std::endl;
	std::cout << "Total Penalty For Context Switching: " << simulator.GetTotalPenalty() << std::endl;
    
//    // RR
//    process_set.BuildProcessSet(std::cin);
//    // build a simulator for a fifo scheduler, with a context switch penalty of 10
//    ProcessSimulator simulatorRR(SchedulingAlgorithim::RoundRobin, 10, process_set);
//    
//    std::cout << "Total Processes: " << process_set.GetNumberProcesses() << std::endl;
//    simulatorRR.RunSimulation();
//    
//    std::cout << "Average Wait Time: " << simulatorRR.GetAverageWaitTime() << std::endl;
//    std::cout << "Total Penalty For Context Switching: " << simulatorRR.GetTotalPenalty() << std::endl;
    
    process_set.BuildProcessSet(std::cin);
    // build a simulator for a fifo scheduler, with a context switch penalty of 10
    ProcessSimulator simulatorSJF(SchedulingAlgorithim::SJF, 10, process_set);
    
    std::cout << "Total Processes: " << process_set.GetNumberProcesses() << std::endl;
    simulatorSJF.RunSimulation();
    
    std::cout << "Average Wait Time: " << simulatorSJF.GetAverageWaitTime() << std::endl;
    std::cout << "Total Penalty For Context Switching: " << simulatorSJF.GetTotalPenalty() << std::endl;

	return 0;
}