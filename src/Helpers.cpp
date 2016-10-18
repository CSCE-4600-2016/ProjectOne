
#include <sstream>

#include "Helpers.h"

/// <summary>
/// Splits the string.
/// </summary>
/// <param name="string">The string.</param>
/// <param name="delim">The delimiter.</param>
/// <returns></returns>
std::vector<std::string> SplitString(const std::string& string, char delim)
{
	std::istringstream stream(string);
	std::string tempLine;
	std::vector<std::string> tokens;

	while(std::getline(stream, tempLine, delim))
	{
		if(!tempLine.empty())
		{
			tokens.push_back(tempLine);
		}
	}

	return tokens;
}
