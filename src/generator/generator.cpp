#include <iostream>
#include <random>
#include <queue>
#include <string>
#include <fstream>
#include <vector>

struct Process
{
	int processId;
	int cycles;
	int memoryFootprint;
};

int main(int argc, char* argv[])
{
	// random normal distribution needed variables
	std::default_random_engine engine;
	std::normal_distribution<> cyclesDistribution(6000, 2500);
	std::normal_distribution<> memoryDistribution(20, 24.5);
	std::queue<Process> processQueue;
	std::vector<int> cycles;
	std::vector<int> memoryFootprints;

	std::ofstream processCsv;
	processCsv.open("process.csv");

	// we didn't have arguments for how many processes to generate
	if(argc < 2)
	{
		std::cout << "ERROR: Must run with how many processes to generate\n";
		return -1;
	}
	int processCount = std::stoi(argv[1]);
	int cyclesMean = 0;
	int memoryMean = 0;


	for (int i = 0; i < processCount * 2; i++)
	{
		int cycle = cyclesDistribution(engine);
		int memory = memoryDistribution(engine);

		if((cycle >= 1000) && (cycle <= 11000))
		{
			cycles.push_back(cycle);
		}
		if((memory >= 1) && (memory <= 100))
		{
			memoryFootprints.push_back(memory);
		}
	}

	for (int i = 0; i < processCount; i++)
	{
		Process newProcess;
		newProcess.processId = i;
		newProcess.cycles = cycles[i];
		newProcess.memoryFootprint = memoryFootprints[i];
		processQueue.push(newProcess);
		cyclesMean = cyclesMean + newProcess.cycles;
		memoryMean = memoryMean + newProcess.memoryFootprint;
		// write the data to the csv files to easily generate the distrubtion
		processCsv << newProcess.processId << "," << newProcess.cycles << "," << newProcess.memoryFootprint << std::endl;
	}
	processCsv.close();

	cyclesMean = cyclesMean / processCount;
	memoryMean = memoryMean / processCount;


	std::cout << "Generated a set of " << processCount << " processes." << std::endl;
	std::cout << "CPU Cycles Mean: " << cyclesMean << std::endl;
	std::cout << "Memory Footprint Mean: " << memoryMean << "kb" << std::endl;

	return 0;
}