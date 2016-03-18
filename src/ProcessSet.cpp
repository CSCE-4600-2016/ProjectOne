#include "ProcessSet.h"
#include <string>

#include "Helpers.h"

/// <summary>
/// Initializes a new instance of the <see cref="ProcessSet"/> class.
/// </summary>
ProcessSet::ProcessSet()
{
}


/// <summary>
/// Finalizes an instance of the <see cref="ProcessSet"/> class.
/// </summary>
ProcessSet::~ProcessSet()
{
	processSet.clear();
}

/// <summary>
/// Builds the process set.
/// </summary>
/// <param name="csvStream">The CSV stream.</param>
void ProcessSet::BuildProcessSet(std::istream& csvStream)
{
	std::string row;
	unsigned int arivalTime  = 0;
	// loop through all the rows in the csv file
	// each row signifies a process
	while(std::getline(csvStream, row))
	{
		// split on the comma to get the individual process information
		// processInfo[0] = processId
		// processInfo[1] = cycles
		// processInfo[2] = memoryFootprint
		std::vector<std::string> processInfo = SplitString(row, ',');
		Process tempProcess(std::stoi(processInfo[0]), std::stoi(processInfo[1]), std::stoi(processInfo[2]), arivalTime);
		processSet.push_back(tempProcess);
		arivalTime += 50;
	}
}

/// <summary>
/// Gets the number processes.
/// </summary>
/// <returns></returns>
unsigned ProcessSet::GetNumberProcesses() const
{
	return processSet.size();
}

/// <summary>
/// Adds the process to the process set.
/// </summary>
/// <param name="process">The process.</param>
void ProcessSet::AddProcess(const Process& process)
{
	processSet.push_back(process);
}



/// <summary>
/// Pops the process from back.
/// </summary>
void ProcessSet::PopProcessFromBack()
{
	processSet.pop_back();
}

/// <summary>
/// Pops the process.
/// </summary>
void ProcessSet::PopProcess()
{
	processSet.pop_front();
}

/// <summary>
/// Gets the first process in the process set.
/// </summary>
/// <returns>Reference to the first process</returns>
Process& ProcessSet::FirstProcess()
{
	return processSet.front();

}
