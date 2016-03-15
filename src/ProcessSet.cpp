#include "ProcessSet.h"


/// <summary>
/// Initializes a new instance of the <see cref="ProcessSet"/> class.
/// </summary>
/// <param name="numberProcesses">The number processes.</param>
ProcessSet::ProcessSet(unsigned numberProcesses) : processSet(numberProcesses)
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
/// Gets the number processes.
/// </summary>
/// <returns></returns>
unsigned ProcessSet::GetNumberProcesses() const
{
	return processSet.size();
}
