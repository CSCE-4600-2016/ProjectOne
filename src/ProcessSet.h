#ifndef PROCESS_SET_H_
#define PROCESS_SET_H_

#include <vector>

#include "Process.h"
/// <summary>
/// Defines a set of processes
/// </summary>
class ProcessSet
{
public:	

	ProcessSet(unsigned int numberProcesses);	
	~ProcessSet();
	
	unsigned int GetNumberProcesses() const;
private:
	std::vector<Process> processSet;
};

#endif

