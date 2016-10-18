#ifndef PROCESS_SET_H_
#define PROCESS_SET_H_

#include <deque>
#include <istream>

#include "Process.h"
/// <summary>
/// Defines a set of processes
/// </summary>
class ProcessSet
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="ProcessSet"/> class.
	/// </summary>
	ProcessSet();
	~ProcessSet();
	
	/// <summary>
	/// Builds the process set.
	/// </summary>
	/// <param name="csvStream">The CSV stream.</param>
	void BuildProcessSet(std::istream& csvStream);

	/// <summary>
	/// Gets the number processes.
	/// </summary>
	/// <returns></returns>
	unsigned int GetNumberProcesses() const;
	
	/// <summary>
	/// Adds the process to the process set.
	/// </summary>
	/// <param name="process">The process.</param>
	void AddProcess(const Process& process);
		
	/// <summary>
	/// Pops the process from back.
	/// </summary>
	void PopProcessFromBack();

	/// <summary>
	/// Pops the process.
	/// </summary>
	void PopProcess();
	
	/// <summary>
	/// Gets the first process in the process set.
	/// </summary>
	/// <returns></returns>
	Process& FirstProcess();

private:
	std::deque<Process> processSet;
};

#endif

