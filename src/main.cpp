

#include <iostream>
#include <locale>

#include "ProcessSet.h"
#include "ProcessSimulator.h"


int main(int argc, char** argv)
{
    
	// set cout locale to use the system locale so we can get numbers formatted since
	std::cout.imbue(std::locale(""));
	ProcessSet process_set;
    
    /*
     *  FIFO
     */
	process_set.BuildProcessSet(std::cin);
    
	// build a simulator for a fifo scheduler, with a context switch penalty of 10
	ProcessSimulator simulator(SchedulingAlgorithim::FIFO, 10, process_set);
    
	std::cout << "Fifo Single Core: Total Processes: " << process_set.GetNumberProcesses() << std::endl;
	simulator.RunSimulation();
	
	std::cout << "Fifo Single Core: Average Wait Time: " << simulator.GetAverageWaitTime() << std::endl;
	std::cout << "Fifo Single Core: Total Penalty For Context Switching: " << simulator.GetTotalPenalty() << std::endl;
    
    // build a simulator for a multiprocessor fifo scheduler, with a context switch penalty of 10
    ProcessSimulator multiFifo(SchedulingAlgorithim::FIFO, 10, process_set, true);
    std::cout << "\n\nFiFo Quad Core: Total Processes: " << process_set.GetNumberProcesses() << std::endl;
    multiFifo.RunSimulation();
    
    std::cout << "FiFo Quad Core: Average Wait Time: " << multiFifo.GetAverageWaitTime() << std::endl;
    std::cout << "Fifo Quad Core: Total Penalty For Context Switching: " << multiFifo.GetTotalPenalty() << std::endl;
	

//    // RR
    process_set.BuildProcessSet(std::cin);

//    // build a simulator for a fifo scheduler, with a context switch penalty of 10
    ProcessSimulator simulatorRR(SchedulingAlgorithim::RoundRobin, 10, process_set);
//    

    std::cout << "\nRound Robin: Total Processes: " << process_set.GetNumberProcesses() << std::endl;
    simulatorRR.RunSimulation();
//    
    std::cout << "Round Robin: Average Wait Time: " << simulatorRR.GetAverageWaitTime() << std::endl;
    std::cout << "Round Robin: Total Penalty For Context Switching: " << simulatorRR.GetTotalPenalty() << std::endl;

	
    /*
     *  SJF
     */
	process_set.BuildProcessSet(std::cin);
    
	// build a simulator for a SJF scheduler, with a context switch penalty of 10
	ProcessSimulator simulatorSJF(SchedulingAlgorithim::SJF, 10, process_set);
	
	std::cout << "\n\nSJF Single Core: Total Processes: " << process_set.GetNumberProcesses() << std::endl;
	simulatorSJF.RunSimulation();
	
	std::cout << "SFJ Single Core: Average Wait Time: " << simulatorSJF.GetAverageWaitTime() << std::endl;
	std::cout << "SJF Single Core: Total Penalty For Context Switching: " << simulatorSJF.GetTotalPenalty() << std::endl;
    
    // build a simulator for a multiprocessor SJF scheduler, with a context switch penalty of 10
    ProcessSimulator multiSJF(SchedulingAlgorithim::SJF, 10, process_set, true);
    std::cout << "\n\nSJF Quad Core: Total Processes: " << process_set.GetNumberProcesses() << std::endl;
    multiSJF.RunSimulation();
    
    std::cout << "SJF Quad Core: Average Wait Time: " << multiSJF.GetAverageWaitTime() << std::endl;
    std::cout << "SJF Quad Core: Total Penalty For Context Switching: " << multiSJF.GetTotalPenalty() << std::endl;





	return 0;
}