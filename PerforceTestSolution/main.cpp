/*********************************************************************
 * @file  main.cpp
 * @copyright
 * Copyright 2024 Vivek Gawari.
 *
 * @brief Implementation of the source code.
 *********************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

/**@brief
 *  Parses a time string (HH:MM) into an integer representation (minutes since midnight).
 *
 * This function takes a time string in the format HH:MM (e.g., "09:00") and extracts it
 * into an integers representing hours and minutes respectively and
 * then convers it into seconds.
 *
 * @param timeStr The time string to parse.
 * @return The time in seconds.
 */
int parseTime(const std::string& timeStr)
{
	int hours, minutes;
	std::stringstream ss(timeStr);
	char delimiter;

	ss >> hours >> delimiter >> minutes;

	return hours * 60 + minutes;
}

/**@brief
 *  Reads visitor data from a file.
 *
 * This function reads visitor data from a text file. Each line in the file
 * should contain two comma-separated values: the entry time and exit time of a visitor,
 * both formatted in HH:MM. The function parses these times and stores them in a vector of pairs.
 *
 * @param filename The name of the file to read.
 * @return A vector of pairs, where each pair represents the entry and exit time of a visitor at the peak period.
 */
std::vector<std::pair<int, int>> readVisitorData(const std::string& fileName)
{
	std::ifstream file(fileName);
	std::vector<std::pair<int, int>> data;
	std::string line;

	if (!file.is_open())
	{
		throw std::runtime_error("Error: Could not open file " + fileName);
	}

	while (getline(file, line))
	{
		std::stringstream ss(line);
		std::string entryTimeStr, exitTimeStr;
		int entryTime, exitTime;

		getline(ss, entryTimeStr, ',');
		getline(ss, exitTimeStr);

		entryTime = parseTime(entryTimeStr);
		exitTime = parseTime(exitTimeStr);

		data.emplace_back(entryTime, exitTime);
	}

	file.close();
	return data;
}

/**@brief
 * Finds the time period with the most visitors.
 *
 * This function takes a vector of visitor entries (pairs of entry and exit times)
 * and finds the time period with the most visitors present at any given moment.
 * It sorts them into two different vectors and uses merge functionaity
 *
 * @param visitorData A vector of pairs representing visitor entry and exit times.
 * @param max_person Resultant number of maximum people present at the peak period
 * @return A pair representing the start and end time of the peak period (in seconds).
 */
std::pair<int, int> findPeakPeriod(const std::vector<std::pair<int, int>>& visitorData, int& maxPerson)
{
	std::vector<int> entry, exit;
	entry.reserve(visitorData.size());
	exit.reserve(visitorData.size());

	for (const auto& val : visitorData)
	{
		entry.emplace_back(val.first);
		exit.emplace_back(val.second);
	}

	std::sort(entry.begin(), entry.end());
	std::sort(exit.begin(), exit.end());

	int in_guests = 1;

	std::pair<int, int> res_time{ entry[0], exit[0] };
	int i = 1, j = 0, n = visitorData.size();

	while (i < n && j < n)
	{
		if (entry[i] <= exit[j])
		{
			++in_guests;
			if (in_guests > maxPerson)
			{
				++maxPerson;
				res_time.first = entry[i];
				res_time.second = exit[j];
			}
			++i;
		}
		else
		{
			--in_guests;
			++j;
		}
	}

	return res_time;
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
		return 1;
	}

	try
	{
		std::string fileName = argv[1];
		std::vector<std::pair<int, int>> visitorData = readVisitorData(fileName);

		int maxPerson = 1;
		std::pair<int, int> peakPeriod = findPeakPeriod(visitorData, maxPerson);

		std::cout << (peakPeriod.first / 60) << ":" << (peakPeriod.first % 60) << "-"
			<< (peakPeriod.second / 60) << ":" << (peakPeriod.second % 60) << ";"
			<< maxPerson << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}