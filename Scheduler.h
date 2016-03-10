// File: Scheduler.h
// Description: A base class sechduler that all the algoorithms
// can derive from as subclasses

// #include "ProcessTable.h"
// #include "ProcessAlgorithms.h"
#include <string>
#include <vector>

#ifndef SCHEDULER_H
#define SCHEDULER_H
class Scheduler
{
	private:

	public:

		/* Takes the algo name, and required params*/
		Scheduler(const std::string &AlgorithmName, int csp,
					int quantum = 0, int m = 0);
		~Scheduler();	

		/* LoadFile method, if we are taking in processes from a file */
		void LoadFile(const std::string &FileName);

		/* RunProcesses */
		void RunProcesses();

		/* Getter for the ProcessTable */
		/* ProcessTable *GetProcessTable(){ return }*/
};



#endif // SCHEDULER_H