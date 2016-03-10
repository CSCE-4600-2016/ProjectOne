/*
	File: ProcessTable.h
	Desc: Defining ProcessControlBlock and ProcessTable objects
*/

#include <vector>


/* ProcessState enum: describes state of a process */
enum ProcessState{ READY, RUNNING, NOT_LOADED, DONE };


/* Here we create the PCB (Process Control Block) and provide 
 all necessary members. Credit to Alphanso Walker here for showing
 me what all goes inside of a PCB! */

 struct PCB
 {
 	PCB(int procID = 0, int iArrv = 0, int iTotlRun =0,
 		int iWait = 0, ProcessState st = NOT_LOADED, 
 		int et, int currRunTime = 0, int iTurnAround = 0,
 		int actStart = 0)
 			: iProcessID, iTimeSubmitted(iArrv), 
 			iTotalRunTime(iTotlRun), iWaitTime(Wait), state(st),
 			iEndTime(et), iCurrentRunningTime(currRunTime),
 			iTurnAroundTime(iTurnAround), iQuantum(0), 
 			iTrueTotRunTime(iTotlRun) 
 			{}

 	int iProcessID;
	int iTimeSubmitted;
	int iTotalRunTime;
	int iActualStartTime;
	int iWaitTime;
	int iQuantum;
	int iEndTime;
	ProcessState state;
	int iCurrentRunningTime;
	int iTurnAroundTime;
	int iTrueTotalRunTime;	

 };

 struct ProcessTable{ std::vector<PCB>Processes;};
 