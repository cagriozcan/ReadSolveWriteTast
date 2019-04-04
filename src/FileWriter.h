#pragma once

#ifndef _FileWriter_
#define _FileWriter_

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

class FileWriter
{
public:
	FileWriter();
	~FileWriter();

	bool WriteVectorsetToFile(std::vector<std::string> dataSet);

};

#endif