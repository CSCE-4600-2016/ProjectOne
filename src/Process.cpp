#include "Process.h"


/// <summary>
/// Initializes a new instance of the <see cref="Process"/> struct.
/// </summary>
/// <param name="processId">The process identifier.</param>
/// <param name="numberCycles">The number cycles.</param>
/// <param name="memoryFootprint">The memory footprint.</param>
Process::Process(unsigned int processId, unsigned int numberCycles, unsigned int memoryFootprint) : 
	processId(processId), numberCycles(numberCycles), memoryFootprint(memoryFootprint)
{

}
