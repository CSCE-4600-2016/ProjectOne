

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

	return 0;
}