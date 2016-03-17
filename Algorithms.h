/*
	File: Algorithms.h
	Desc: The required algorithms will be defined here
	Notes: Algorithms are:
		- Round Robin
		- Shortest Job First
		- Priority Queue
		- Shortest Remaining Time
*/

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <deque>
#include "ProcessTable.h"

// Iterators for Ready Processes and Runnable Processes
typedef std::vector<PCB>::iterator ReadyProcItr;
typedef std::deque<PCB>::iterator RunnableProcItr;		

/* Desc: This class controls the insertion of processes into the runnable queue
   and will only do so as long as the degree has not been reached, meaning that 
   memory is still available 
   */
class DegreeOfMultiProgramming
{
	private:

		// These are to be hidden from external classes
		int degree;
		std::deque<ProcessControlBlock> runnableProcesses;


	public: 
		
		/* Constructor, params: degree of multiprogramming, m */
		degreeOfMultiprogramming(int m): degree(m)
		{

		}

		/* isRunnable 
			Desc: This function figures out if there's sufficient mem in the queue 
			to store additional processes. Returns a boolean value */
		bool isRunnable()	
		{
			return runnableProcesses.size() < degree;

		}

		/* Insert
			Desc: a wrapper function for the push_back method
			of the queue. 
			Params: takes in a process and inserts into the queue
		*/
		void Insert( PCB &runbleProcesses )
		{
			runnableProcesses.push_back(runbleProcesses);
		}

		/* Rotate 
			Desc: Moves next process in line to the front
			Params: none
		*/
		void Rotate()
		{
			if(runnableProcesses.size() > 1)
			{
				Insert(*(runnableProcesses.begin()));
				runnableProcesses.pop_front();
			}	
		}	

		/* Remove: 
		    Desc: Deletes process at the front of the queue;
		    returns a copy of the removed process for later calculations
		    Note: If there's nothing inside the queue, it'll return a
			default process control block (with everything initialized to zero) 
			*/
		PCB Remove()
		{
			PCB taskBlock;
			if(runnableProcesses.size() > 0)
			{
				taskBlock = *(runnableProcesses.begin());
				runnableProcesses.pop_front();
				return taskBlock;	
			}	
			return taskBlock;
		}

		/* Size */
		int Size(){ return runnableProcesses.size();}

		/* GetRunnableProcesses 
			Desc: Getter to fetch the queue for external processing
			aka processing outside this class 
		*/

		std::deque<PCB> & GetRunnableProcesses() { return runnableProcesses; }			
					
};

/*
	Struct SchedulingAlgorithmParamters 
	This struct contains params required for process scheduler
	and the algorithms and concepts being simulated, i.e. context switch, etc. 
*/

struct SchedAlgoParams
{
	SchedAlgoParams(int m):
	degreeOfMultiprogramming(m) {}

	/* The members of this struct 
	get initialized in the Scheduler-class constructor 
	*/

	int iCurrentTime;
	int iCsp;
	int iQuantum;
	int iInContextSwitch;
	int iCountNewReadyProcesses;
	int iOverHead;
	std::vector<ProcessControlBlock> swappedProcesses;
	DegreeOfMultiprogramming degreeOfMultiprogramming;
	bool bRecentNewProcess;
};

/* class SchedulingAlgorithms 
	Here we formally define the base class for RR, SJF, and whatever
	other algorithms we're using on this program 
*/
class SchedulingAlgorithm
{
	protected:

		/* OnProcessComplete
			Desc: sets all members of the process once
			it completes. 
			Params: Takes in a iterator of PCB's and a SchedAlgoParams-type object*/
		void OnProcessComplete(std::vector<PCB>::iterator itr, SchedAlgoParams &params)
		{
			itr -> state = COMPLETED;			
			params.iInContextSwitch = params.iCsp;
			itr -> iEndTime = params.iCurrentTime+1;
			itr -> iActualStartTime = (itr -> iEndTime - itr -> iTotalRunTime);
			itr -> iTurnAroundTime = (itr -> iWaitTime + itr -> iTotalRunTime);
			//(itr) -> iTotalRunTime = (itr) -> iTotalRunTime - (itr) -> iCurrentRunningTime;
			params.iOverHead++;
		}

		/* 
		ProcessCompleted
		
		Desc: boolean function that takes/checks ProcessTable
		to see if all the processes for the simulation have been completed 
		
		Params: Takes in a ProcessTable-type object
		
		*/
		bool ProcessesCompleted(ProcessTable &processTable)
		{
			for (ReadyProcItr itrTable = processTable.Processes.begin(); 
				itrTable != processTable.Processes.end(); 
				++itrTable)
			{
				if (itrTable -> state != COMPLETED)
					return false;
			}
			return true;
		}	

		/*
		UpdateProcesses
		
		Desc: Takes in a ProcessTable and PCB vector to
		update completed process information in the 
		vector and sends it to the ProcessTable

		*/
		void UpdateProcesses(ProcessTable &processTable, std::vector<PCB> &readyProcesses)
		{
			for (ReadyProcItr itrTable = processTable.vectProcesses.begin(); itrTable != processTable.Processes.end(); ++itrTable)
			{
				for (ReadyProcItr itrList = readyProcesses.begin(); itrList != readyProcesses.end(); ++itrList)
				{
					if (itrTable -> iProcessID == itrList -> iProcessID)
					{
						*itrTable = *itrList;
						break;
					}
				}
			}
		}
		
	public:

		/*
			RunAlgorithm
	
			Every algorithm sits in a child class of this class, 
			so the virtual function allows flexibility in how the 
			algorithms run by going off of this virtual base-class function. 
			
			Think of it as an initializer function that gets passed around and used by
			child classes. It also takes the load off of this class by 
			not having to redefine this function inside this class for each algorithm, which can be a headache when trying to get RR, or for that matter any algorithm 
			to run as expected. 

		*/
		virtual void RunAlgorithm(ProcessTable &processTable, SchedAlgoParams &params, std::vector<PCB> &readyProcesses) = 0;

		/*
			GetNewlyReadyProcesses
			Desc: Pure vitual method that all derived algorithms must define as well.  This is simply because
		    every algorithm has their own (sick) tastes in how they get the next ready process from the process table at the
		    time they were submitted.  This takes in a ProcessTable, SchedulingAlgorithmParameters and a vector
		    of control blocks.  Should return an integer value representing the number of ready processes that were
		    submitted at that tick. 

		*/
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedAlgoParams 
			&params, std::vector<PCB> &readyProcesses) = 0;

		/*
			ContextSwitch
			This function is optionally overriden in child classes,
			allowing more flexibility in their respective functions
		*/
		virtual void ContextSwitch(SchedAlgoParams &params, std::vector<PCB> &readyProcesses)
		{
			if(params.iInContextSwitch)
			{
				--params.iInContextSwitch;
				for (ReadyProcItr itr = readyProcesses.begin(); itr != readyProcesses.end(); itr++)
					itr -> iWaitTime ++;
			}
		}

};

/* Now for the algorithms. Each will be defined 
   as a class inheriting members/functions from SchedulingAlgorithm above.
*/

/*----------------------------------
	First-In-First-Out
------------------------------------*/
class FIFO:public SchedulingAlgorithm
{
	public:
		virtual void RunAlgorithm(ProcessTable &processTable, SchedAlgoParams &params, std::vector<PCB> &readyProcesses);
		
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedAlgoParams 
			&params, std::vector<PCB> &readyProcesses);

		virtual void ContextSwitch(SchedAlgoParams &params, std::vector<PCB> &readyProcesses)
		{
			if(params.iInContextSwitch)
			{
				itrReadyProcesses itrPro = readyProcesses.begin();
				for (;itrPro != readyProcesses.end(); itrPro++)
					itrPro -> iWaitTime ++;

				--params.iInContextSwitch;
				for (RunnableProcItr itr = params.degreeOfMultiprogramming.GetRunnableProcesses().begin(); 
					itr != params.degreeOfMultiprogramming.GetRunnableProcesses().end(); itr++)
						if (itr -> state == READY)
						itr -> iWaitTime ++;
			}
		}
};   

/*----------------------------------
	Shortest-Job-First
------------------------------------*/
class SJF:public SchedulingAlgorithm
{
	virtual void RunAlgorithm(ProcessTable &processTable, SchedAlgoParams &params, std::vector<PCB> &readyProcesses);
		
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedAlgoParams 
			&params, std::vector<PCB> &readyProcesses);
};

/*----------------------------------
	Shortest-Remaining-Time
------------------------------------*/
class SRT:public SchedulingAlgorithm
{
	virtual void RunAlgorithm(ProcessTable &processTable, SchedAlgoParams &params, std::vector<PCB> &readyProcesses);
		
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedAlgoParams 
			&params, std::vector<PCB> &readyProcesses);
};

/*----------------------------------
	Round-Robin
------------------------------------*/
class RoundRobin:public SchedulingAlgorithm
{
	virtual void RunAlgorithm(ProcessTable &processTable, SchedAlgoParams &params, std::vector<PCB> &readyProcesses);
		
		virtual int GetNewlyReadyProcesses(ProcessTable &processTable, SchedAlgoParams 
			&params, std::vector<PCB> &readyProcesses);

	virtual void ContextSwitch(SchedAlgoParams &params, std::vector<PCB> &readyProcesses)
		{
			if(params.iInContextSwitch)
			{
				ReadyProcItr itrPro = readyProcesses.begin();
				for (itrPro != readyProcesses.end(); itrPro++)
					itrPro -> iWaitTime ++;

				--params.iInContextSwitch;
				for (RunnableProcItr itr = params.degreeOfMultiprogramming.GetRunnableProcesses().begin(); itr != params.degreeOfMultiprogramming.GetRunnableProcesses().end(); itr++)
						if (itr -> state == READY)
							itr -> iWaitTime ++;
			}
		}	

};

#endif		
