/*
	File: Algorithms.cpp
	Desc: The required algorithms will be implemented here
	Notes: Algorithms are:
		- Round Robin
		- Shortest Job First
		- Priority Queue
		- Shortest Remaining Time
*/

class degreeOfMultiProgramming
{

};

// Essential struct for Scheduler class functions and data
struct SchedAlgoParams
{
	SchedAlgoParams(int m) : degreeOfMultiprogramming(m) {}
	int iCurrentTime;
	int iCsp;
	int iQuantum;
	int iInContextSwitch;
	int iCountNewReadyProcesses;
	int iOverHead;
	std::vector<PCB> swappedProcesses;
	//DegreeOfMultiprogramming degreeOfMultiprogramming;
	bool bRecentNewProcess;
};		