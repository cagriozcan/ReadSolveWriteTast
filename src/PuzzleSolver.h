#pragma once

#ifndef _PuzzleSolver_
#define _PuzzleSolver_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "atmsp.h"

typedef std::map<int, int> map;

class PuzzleSolver
{
private:
	map const puzzleSet;

public:

	PuzzleSolver(const map & a);
	~PuzzleSolver();

	std::vector<std::string> ReadLines(const char * filePath);

	std::vector<std::string> ReplaceAllLinesWithRealValue(const std::vector<std::string>& vector);

private:
	std::string ReplaceLineWithRealValue(const std::vector<std::string>& vector);

	std::string GetOperationSyntax(int val);

	void ParseStrings(const std::string &s, char delim, std::vector<std::string>&  result);

};

#endif