# ReadMe -- Project 1: Process Scheduler
 - Delete or modify  if you want
----------------------------------------
# Given information: 

CSCE 4600.003
Spring 2016
Project #1
Due: March 23, 2016 at 11:59pm via Blackboard Learn
------------------------------------------------------------------------------
For this project you will be working in groups of two or three. Each member of your group must sign up on the
corresponding project sheet in order to receive a grade. Your task is to develop a simulation of different
scheduling disciplines that allocate a set of processes to available processors.
Using the process generator that you developed in Homework #2, generate a set of 50 processes with different
runtime requirements (i.e., cycles). You may assume that the processes arrive in the system every 50 cycles (e.g.,
at times 0, 50,100, 150, 200, …etc.)

- [ ] 1. Develop a simulation of Round-Robin Scheduling with a quantum of 50 cycles, and schedule your set of
processes. Assuming a context switch penalty of 10 cycles (for the scheduler to switch between
processes), compute the average waiting time and the total penalty for the set of processes. Repeat the
experiment over different sets of processes. You should document (graphically) the distribution of cycle
times for your set of processes.

- [ ] 2. Repeat the experiment above for 2 additional scheduling disciplines chosen from (SRT, SJF, FIFO,
LRT).

- [ ] 3. Assuming that you have a multi-processor system with 4 processors. Repeat the above experiments and
calculate the average waiting time and total context-switch penalty.
NOTE: To analyze the performance of your scheduling strategies, you must conduct multiple experiments over
different sets of processes (with different process characteristics).

---------------------------------------------------------------------

## Deliverables: 
Write a minimum 5-page report that highlights the performance and differences of the scheduling
algorithms. You must discuss all the limitations and assumptions. In detail, show how you analyzed the
performance (i.e., average waiting time) and present your results. You must submit well-documented code along
with specification of any special compilation procedures. The code must compile and execute properly on the
CSE Linux machines to receive credit. Include in the report the list of team members who participated. Only one
person needs to submit the required files form each team.
Have FUN!!

---------------------------------------------

# About This Project:

### Compiles with: make
### Runs with: make run
### Current status: Filling out function bodies for the Scheduler class-functions
