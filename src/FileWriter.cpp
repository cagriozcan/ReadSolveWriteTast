#include "FileWriter.h"



FileWriter::FileWriter()
{
}


FileWriter::~FileWriter()
{
}

bool FileWriter::WriteVectorsetToFile(std::vector<std::string> dataSet)
{
	std::ofstream writer("taskOutput");
	if (!writer) {
		std::cout << "TaskOutPut file cannot create !!!";
		return false;
	}
	else {
		//Tum gercek datasetteki satirlari dosyaya yazd�r.
		for (const auto &e : dataSet) writer << e << "\n";

		//Output dosyas�n� kapat
		writer.close();
		return true;
	}
}
