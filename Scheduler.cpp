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

Scheduler::Scheduler(const std::string &AlgorithmName, int contextSwitchPenalty, int quantum = 0, int degree):algoParams(degree)
{
	algoParams
	algoParams
	algoParams
	algoParams
	algoParams
	algoParams
	algoParams
	algorithm = CreateAlgorithm(AlgorithmName);
}
Scheduler::~Scheduler()
{

}

/* LoadFile method, if we are taking in processes from a file */
void Scheduler::LoadFile(const std::string &FileName)
{

}

/* RunProcesses */
void Scheduler::RunProcesses()
{
	
}

/* Getter for the ProcessTable */
/* ProcessTable *GetProcessTable(){ return &processTable } */

/* Getter for the algorithm paramters */
/* SchedAlgoParams *GetSchedAlgoParams(){ return &algoParams }*/
