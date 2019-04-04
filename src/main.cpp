#include <string>

#include "File_Reader.h"
#include "PuzzleSolver.h"
#include "FileWriter.h"

#define TASKFILE "Input/taskFile"
#define TASKINDEX "Input/taskIndex"
#define TASKLIST "Input/taskList"


int main(int argc, char *argv[])
{
std::map<int,int> dataSet;
    FileReader file_reader;

    file_reader.ReadAllFile(TASKINDEX,dataSet);
    file_reader.ReadRealValue(TASKFILE, dataSet);

    PuzzleSolver puzzleSolver(dataSet);
    std::vector<std::string> cryptolDataSet = puzzleSolver.ReadLines(TASKLIST);
    FileWriter writer;
    bool oldumuhocam = writer.WriteVectorsetToFile(puzzleSolver.ReplaceAllLinesWithRealValue(cryptolDataSet));
    if(oldumuhocam)std::cout << "BASARDIKKKK ABIIIII" << std::endl;


    return 0;
}

