#include "Process.h"


Process::Process(): processId(0), numberCycles(0), memoryFootprint(0)
{
}

/// <summary>
/// Initializes a new instance of the <see cref="Process"/> struct.
/// </summary>
/// <param name="processId">The process identifier.</param>
/// <param name="numberCycles">The number cycles.</param>
/// <param name="memoryFootprint">The memory footprint.</param>
/// <param name = "arrivalTime">The arrival time.< / param>
Process::Process(unsigned int processId, unsigned int numberCycles, unsigned int memoryFootprint, unsigned int arrivalTime) : 
	processId(processId), numberCycles(numberCycles), memoryFootprint(memoryFootprint), arrivalTime(arrivalTime)
{

}
