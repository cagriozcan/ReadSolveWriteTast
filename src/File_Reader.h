#pragma once

#ifndef _FileReader_
#define _FileReader_

///////////////////////////////////////////////////////includes//////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <map>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#ifdef __linux__
#include <sys/mman.h>
#else
#include "windows.h"
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////

class FileReader
{
public:

    FileReader();
    ~FileReader();

    //Butun dosyayi okur.8-bitlik datalari 4'er data setleri icinde map'te tutar.
    void ReadAllFile(const char * filePath, std::map<int, int>& dataSet);

    //Offsetli gercek datalarin bulundugu dosyayi(taskFile) aldigi datasetle cozumleyerek,s�ifreli degerleri ile gercek degerleri saklar.
    //Saklama sekli <sifrelidata , gercekdeger>
    void ReadRealValue(const char * filePath, std::map<int, int>& semidataset);

    //Dosya yolu verilen datayi memory map edip pointer'i doner.
    char * MappedFiletoMemory(const char * filePath, size_t & size);

};

#endif  //_FileReader_