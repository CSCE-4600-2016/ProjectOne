// File: Scheduler.h
// Description: A base class sechduler that all the algoorithms
// can derive from as subclasses

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>

class Scheduler
{
	private:
		// These vectors will represent our process queues
		std::vector<int> ReadyQueue;
		std::vector<int> WaitQueue;		
		bool isIdle;

	public:
		/* Constructor -- 
		   Desc: Begins the Scheduling simulation 
		   Params: vector input queue, stats, and clock start time  */
		Scheduler(std::vector<int> inputQueue, int[]stats, int clockStartTime );
		
		// Ready functions
		
};











#endif // SCHEDULER_H