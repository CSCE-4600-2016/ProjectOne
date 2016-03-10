// File: Scheduler.h
// Description: A base class sechduler that all the algorithms can derive from as subclasses
// Adding more headers for the two that are commented out right now 

// #include "ProcessTable.h"
// #include "ProcessAlgorithms.h"
#include <string>
#include <vector>

#ifndef SCHEDULER_H
#define SCHEDULER_H
class Scheduler
{
	private:

		// Data/variables
		ProcessTable processTable;
		SchedulingAlgorithm *algorithm;
		SchedAlgoParams algoParams;
		std::std::vector<PCB> readyProcesses;
		//Functions
		SchedulingAlgorithm *CreateAlgorithm(const std::string &AlgorithmName);
		

	public:

		/* Takes the algo name, and required params*/
		Scheduler(const std::string &AlgorithmName, int csp, int quantum = 0, int m = 0);
		~Scheduler();	

		/* LoadFile method, if we are taking in processes from a file */
		void LoadFile(const std::string &FileName);

		/* RunProcesses */
		void RunProcesses();

		/* Getter for the ProcessTable */
		/* ProcessTable *GetProcessTable(){ return &processTable } */

		/* Getter for the algorithm paramters */
		/* SchedAlgoParams *GetSchedAlgoParams(){ return &algoParams }*/

};

#endif // SCHEDULER_H