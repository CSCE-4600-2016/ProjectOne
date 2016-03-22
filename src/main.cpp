

#include <iostream>

#include "ProcessSet.h"
#include "ProcessSimulator.h"


int main(int argc, char** argv)
{
	ProcessSet process_set;
	process_set.BuildProcessSet(std::cin);
	
	// FIFO
	// build a simulator for a fifo scheduler, with a context switch penalty of 10
	ProcessSimulator simulator(SchedulingAlgorithim::FIFO, 10, process_set);
  std::cout << "FIFO\n\n";
	std::cout << "Total Processes: " << process_set.GetNumberProcesses() << std::endl;
	simulator.RunSimulation();
	
	std::cout << "Average Wait Time: " << simulator.GetAverageWaitTime() << std::endl;
	std::cout << "Total Penalty For Context Switching: " << simulator.GetTotalPenalty() << std::endl;
    
	
	process_set.BuildProcessSet(std::cin);
	// Round Robin
	// build a simulator for a RR scheduler, with a context switch penalty of 10
	std::cout << "RR\n\n";
	ProcessSimulator simulatorRR(SchedulingAlgorithim::RoundRobin, 10, process_set);
	
	std::cout << "Total Processes: " << process_set.GetNumberProcesses() << std::endl;
	simulatorRR.RunSimulation();
	
	std::cout << "Average Wait Time: " << simulatorRR.GetAverageWaitTime() << std::endl;
	std::cout << "Total Penalty For Context Switching: " << simulatorRR.GetTotalPenalty() << std::endl;
	
	
	process_set.BuildProcessSet(std::cin);
	// SJF
	// build a simulator for a SJF scheduler, with a context switch penalty of 10
	ProcessSimulator simulatorSJF(SchedulingAlgorithim::SJF, 10, process_set);
	std::cout << "SJF\n\n";
	std::cout << "Total Processes: " << process_set.GetNumberProcesses() << std::endl;
	simulatorSJF.RunSimulation();
	
	std::cout << "Average Wait Time: " << simulatorSJF.GetAverageWaitTime() << std::endl;
	std::cout << "Total Penalty For Context Switching: " << simulatorSJF.GetTotalPenalty() << std::endl;

	return 0;
	
}

/// Sample Output

//FIFO

//Total Processes: 5
//Average Wait Time: 11676.2
//Total Penalty For Context Switching: 50
//RR

//Total Processes: 5
//Average Wait Time: 23007.8
//Total Penalty For Context Switching: 1730
//SJF

//Total Processes: 5
//Average Wait Time: 11501.8
//Total Penalty For Context Switching: 40
