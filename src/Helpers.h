#ifndef HELPERS_H_
#define HELPERS_H_

#include <vector>
#include <string>

/// <summary>
/// The Scheudling algorithim that will be used
/// </summary>
enum SchedulingAlgorithim
{
	RoundRobin,
	FIFO,
	SRT,
	SJF,
	LRT
};

std::vector<std::string> SplitString(const std::string& string, char delim);

#endif


