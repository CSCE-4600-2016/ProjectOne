/*
* Group Members: 
* Chad Smith
* Jimmy Yeung
* Asad Waheed 
*/
#include <iostream>
#include <random>
#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>

struct Process
{
	int processId;
	int cycles;
	int memoryFootprint;
};

std::queue<Process> GenerateNormalDistribution(std::mt19937& randEngine, const int processCount);
std::queue<Process> GeneratePoissonDistribution(std::mt19937& randEngine, const int processCount);
std::queue<Process> GenerateUniformDistribution(std::mt19937& randEngine, const int processCount);

int main(int argc, char* argv[])
{
	// random distribution needed variables
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937 gen_engine(static_cast<unsigned int>(seed));
	std::queue<Process> processQueue;

	// we didn't have arguments for how many processes to generate
	if(argc < 2)
	{
		std::cout << "ERROR: Must run with how many processes to generate\n";
		return -1;
	}
	int processCount = std::stoi(argv[1]);
	std::string distributionType = argv[2];

	if(distributionType == "normal")
	{
		processQueue = GenerateNormalDistribution(gen_engine, processCount);
	}
	else if(distributionType == "uniform")
	{
		processQueue = GenerateUniformDistribution(gen_engine, processCount);
	}
	else if(distributionType == "poisson")
	{
		processQueue = GeneratePoissonDistribution(gen_engine, processCount);
	}
	else
	{
		std::cout << "ERROR: Must enter the distribution to generate\n";
		return -1;
	}


	return 0;
}

std::queue<Process> GenerateNormalDistribution(std::mt19937& randEngine, const int processCount)
{
	std::normal_distribution<> cyclesDistribution(6000, 6000);
	std::normal_distribution<> memoryDistribution(20, 20);
	std::queue<Process> processQueue;
	std::vector<double> cycles;
	std::vector<double> memoryFootprints;
	std::ofstream processCsv;
	processCsv.open("process-normal-distribution.csv");

	for (int i = 0; i < processCount * 2; i++)
	{
		double cycle = std::round(cyclesDistribution(randEngine));
		double memory = std::round(memoryDistribution(randEngine));

		if ((cycle >= 1000) && (cycle <= 11000))
		{
			cycles.push_back(cycle);
		}
		if ((memory >= 1) && (memory <= 100))
		{
			memoryFootprints.push_back(memory);
		}
	}

	for (int i = 0; i < processCount * 2; i++)
	{
		double cycle = std::round(cyclesDistribution(randEngine));
		double memory = std::round(memoryDistribution(randEngine));

		if ((cycle >= 1000) && (cycle <= 11000))
		{
			cycles.push_back(cycle);
		}
		if ((memory >= 1) && (memory <= 100))
		{
			memoryFootprints.push_back(memory);
		}
	}

	for (int i = 0; i < processCount; i++)
	{
		Process newProcess;
		newProcess.processId = i;
		newProcess.cycles = static_cast<int>(cycles[i]);
		newProcess.memoryFootprint = static_cast<int>(memoryFootprints[i]);
		processQueue.push(newProcess);
		// write the data to the csv files to easily generate the distrubtion
		processCsv << newProcess.processId << "," << newProcess.cycles << "," << newProcess.memoryFootprint << std::endl;
	}
	processCsv.close();

	return processQueue;
}

std::queue<Process> GeneratePoissonDistribution(std::mt19937& randEngine, const int processCount)
{
	std::poisson_distribution<> cyclesDistribution(6000);
	std::poisson_distribution<> memoryDistribution(20);
	std::queue<Process> processQueue;
	std::vector<double> cycles;
	std::vector<double> memoryFootprints;
	std::ofstream processCsv;
	processCsv.open("process-poisson-distribution.csv");

	for (int i = 0; i < processCount * 2; i++)
	{
		double cycle = std::round(cyclesDistribution(randEngine));
		double memory = std::round(memoryDistribution(randEngine));

		if ((cycle >= 1000) && (cycle <= 11000))
		{
			cycles.push_back(cycle);
		}
		if ((memory >= 1) && (memory <= 100))
		{
			memoryFootprints.push_back(memory);
		}
	}

	for (int i = 0; i < processCount * 2; i++)
	{
		double cycle = std::round(cyclesDistribution(randEngine));
		double memory = std::round(memoryDistribution(randEngine));

		if ((cycle >= 1000) && (cycle <= 11000))
		{
			cycles.push_back(cycle);
		}
		if ((memory >= 1) && (memory <= 100))
		{
			memoryFootprints.push_back(memory);
		}
	}

	for (int i = 0; i < processCount; i++)
	{
		Process newProcess;
		newProcess.processId = i;
		newProcess.cycles = static_cast<int>(cycles[i]);
		newProcess.memoryFootprint = static_cast<int>(memoryFootprints[i]);
		processQueue.push(newProcess);
		// write the data to the csv files to easily generate the distrubtion
		processCsv << newProcess.processId << "," << newProcess.cycles << "," << newProcess.memoryFootprint << std::endl;
	}
	processCsv.close();

	return processQueue;
}

std::queue<Process> GenerateUniformDistribution(std::mt19937& randEngine, const int processCount)
{
	const double cycleLambda = 1 / 6000;
	const double memoryLambda = 1 / 20;
	std::uniform_int_distribution<> cyclesDistribution(1000, 11000);
	std::uniform_int_distribution<> memoryDistribution(1, 100);
	std::queue<Process> processQueue;
	std::vector<double> cycles;
	std::vector<double> memoryFootprints;
	std::ofstream processCsv;
	processCsv.open("process-uniform-distribution.csv");

	for (int i = 0; i < processCount ; i++)
	{
		int cycle = std::round(cyclesDistribution(randEngine));
		int memory = std::round(memoryDistribution(randEngine));

		if ((cycle >= 1000) && (cycle <= 11000))
		{
			cycles.push_back(cycle);
		}
		if ((memory >= 1) && (memory <= 100))
		{
			memoryFootprints.push_back(memory);
		}
	}

	for (int i = 0; i < processCount; i++)
	{
		int cycle = std::round(cyclesDistribution(randEngine));
		int memory = std::round(memoryDistribution(randEngine));

		if ((cycle >= 1000) && (cycle <= 11000))
		{
			cycles.push_back(cycle);
		}
		if ((memory >= 1) && (memory <= 100))
		{
			memoryFootprints.push_back(memory);
		}
	}

	for (int i = 0; i < processCount; i++)
	{
		Process newProcess;
		newProcess.processId = i;
		newProcess.cycles = static_cast<int>(cycles[i]);
		newProcess.memoryFootprint = static_cast<int>(memoryFootprints[i]);
		processQueue.push(newProcess);
		// write the data to the csv files to easily generate the distrubtion
		processCsv << newProcess.processId << "," << newProcess.cycles << "," << newProcess.memoryFootprint << std::endl;
	}
	processCsv.close();

	return processQueue;
}
