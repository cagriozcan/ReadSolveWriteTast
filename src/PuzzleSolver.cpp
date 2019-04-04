#include "PuzzleSolver.h"
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <sstream>

ATMSP<double> parser;
ATMSB<double> byteCode;

using namespace boost::interprocess;

PuzzleSolver::PuzzleSolver(const map &a) : puzzleSet(a)
{
}

PuzzleSolver::~PuzzleSolver()
{
}

std::vector<std::string> PuzzleSolver::ReadLines(const char * filePath)
{
	int i = 0, firstValue, secondValue, result = 0;
	const std::size_t FileSize = 10000;
	std::vector<std::string> allline;


	//Create a file
	std::filebuf fbuf;
	fbuf.open(filePath, std::ios_base::in | std::ios_base::trunc);
	//Set the size
	fbuf.pubseekoff(FileSize - 1, std::ios_base::beg);
	fbuf.sputc(0);

	//Create a file mapping
	file_mapping m_file(filePath, read_only);

	//Map the whole file with read-write permissions in this process
	mapped_region region(m_file, read_only);

	//Get the address of the mapped region
	void * addr = region.get_address();
	const char *map = static_cast<char*>(addr);
	std::size_t size = region.get_size();

	while (i < size)
	{
		std::string line;

		while (map[i] != '\n')
		{
			line += map[i];
			i++;
		}

		allline.push_back(line);


		i++;

	}

	//Close filebuf
	fbuf.close();

	return allline;

}

std::vector<std::string> PuzzleSolver::ReplaceAllLinesWithRealValue(const std::vector<std::string>& vector)
{
	std::string realDataLine;
	std::vector<std::string> realDataSet;
	std::vector<std::string> dataofLine;
	double result;
	auto it = vector.begin();

	for (int i = 0; i < vector.size(); i++)
	{
		ParseStrings(it[i], ' ', dataofLine);

		realDataLine = ReplaceLineWithRealValue(dataofLine);

		// dataSetteki sifreli verileri gercek degerleri ile degistir ve vektorde tut.Islem sonuclarınıda hesaplar.
		parser.parse(byteCode, realDataLine, "");
		result = byteCode.run();
		realDataLine = realDataLine + " = " + std::to_string(result);
		realDataSet.push_back(realDataLine);

		dataofLine.clear();
	}

	return realDataSet;
}

std::string PuzzleSolver::ReplaceLineWithRealValue(const std::vector<std::string>& vector)
{
	int crypto, realvalue;
	std::string realstring;
	auto it = vector.begin();

	for (int i = 0;  i < vector.size(); i++)
	{
		crypto = std::stoi(it[i]);
		realvalue = (puzzleSet.find(crypto))->second;

		if (realvalue == -1 || realvalue == -2 || realvalue == -3 || realvalue == -4)
		{
			realstring += GetOperationSyntax(realvalue);
		}
		else {
			realstring += std::to_string(realvalue);
		}

		realstring += " ";
	}
	return realstring;
}

std::string PuzzleSolver::GetOperationSyntax(int val)
{
	if (val == -1)
	{
		return "+";
	}
	else if (val == -2)
	{
		return "-";
	}
	else if (val == -3)
	{
		return "*";
	}
	else if (val == -4)
	{
		return "/";
	}
	else
	{
		std::cout << "Invalid STRING to convert math operation" << std::endl;
		return "****";
	}
}

void PuzzleSolver::ParseStrings(const std::string &s, char delim, std::vector<std::string>&  result)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		result.push_back(item);
	}
}