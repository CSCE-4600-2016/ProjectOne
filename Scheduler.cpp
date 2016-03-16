/*
	File: Scheduler.cpp
	Desc: Implmenting Scheduler class functions
*/

#include "Scheduler.h"
#include <fstream>
#include <iostream>
#include <cstring>	

/* Our PCB-type vector iterator for the Ready Process Queue */
typedef std::std::vector<PCB>::iterator ReadyProcItr;	

/* Constructor; takes the algo name, and required params */

Scheduler::Scheduler(const std::string &AlgorithmName, int contextSwitchPenalty, int quantum, int degree):algoParams(degree)
{
	// Init all data members of the class

	algorithmParams.iCsp = contextSwitchPenalty;
	algorithmParams.iOverHead = 0;
	algorithmParams.iQuantum = quantum;
	algorithmParams.iCurrentTime = 0;
	algorithmParams.iInContextSwitch = 0;
	algorithmParams.bRecentNewProcess = false;
	algorithm = CreateAlgorithm(AlgorithmName);
}
Scheduler::~Scheduler()
{
	// Free up memory on the heap after we're done 
	// with our algorithm
	delete algorithm;
}

/* LoadFile method, if we are taking in processes from a file */
void Scheduler::LoadFile(const std::string &FileName)
{
	std::ifstream in(strFilename.c_str()); 
	if(in.fail())
	{
		std::cerr <<"Failed to open file\n";
		exit(1);
	}

	ProcessControlBlock taskBlock;
	while( in >> taskBlock.iProcessID >> taskBlock.iTimeSubmitted >> taskBlock.iTotalRunTime )
	{
		taskBlock.iTrueTotalRunTime = taskBlock.iTotalRunTime;
		processTable.vectProcesses.push_back(taskBlock);
	}
}

/* CreateAlgorithm, private function that will generate algorithm based on
	a simple if-block */
SchedulingAlgorithm *Scheduler::CreateAlgorithm(const std::string &AlgorithmName)
{
	_strlwr(const_cast<char *>(strAlgorithmName.c_str()));
	if( strAlgorithmName == "sjf" )	// shortest job first
		return new ShortestJobFirst;
	else if( strAlgorithmName == "srtf" ) // shortest remaining time-first
		return new ShortestTimeRemaingNext;
	else if( strAlgorithmName == "rr" )   // round-robin
		return new RoundRobin;

	return new FirstComeFirstServe; // otherwise default to FIFO, or FCFS
}


/* RunProcesses */
void Scheduler::RunProcesses()
{
	algorithm->RunAlgorithm(processTable, algorithmParams, readyProcesses);	
	algorithmParams.iOverHead = (algorithmParams.iOverHead-1) * algorithmParams.iCsp;
}

