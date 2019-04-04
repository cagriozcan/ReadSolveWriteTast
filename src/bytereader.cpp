// bytereader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FileReader.h"
#include "PuzzleSolver.h"
#include "FileWriter.h"

int main()
{
	FileReader fileReader;
	FileWriter writer;

	std::map<int, int> dataSet;
	const char* filePath1 = "C:\\taskIndex";
	const char* filePath2 = "C:\\taskFile";
	const char* filePath3 = "C:\\taskList";


	fileReader.ReadAllFile(filePath1, dataSet);
	fileReader.ReadRealValue(filePath2, dataSet);

	PuzzleSolver puzz(dataSet);
	std::vector<std::string> allcrypto = puzz.ReadLines(filePath3);
	std::vector<std::string> realDataSet = puzz.ReplaceAllLinesWithRealValue(allcrypto);

	if (writer.WriteVectorsetToFile(realDataSet))
	{
		std::cout << "Basariliyiz ABIIIIIII" << std::endl;
	}
	return 0;
}

