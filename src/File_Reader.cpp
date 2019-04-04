#include "File_Reader.h"

using namespace boost::interprocess;

FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}


void FileReader::ReadAllFile(const char* filePath, std::map<int, int> &dataSet)
{
    int i = 0;
    double data1 = 0, data2 = 0;
    const std::size_t FileSize = 10000;

    //Filebuffer yaratýyoruz.
    std::filebuf fbuf;
    fbuf.open(filePath, std::ios_base::binary);
    //Boyutu set ediyoruz.
    fbuf.pubseekoff(FileSize - 1, std::ios_base::beg);
    fbuf.sputc(0);

    //Dosyayý map ediyoruz.
    file_mapping m_file(filePath, read_only);
    mapped_region region(m_file, read_only);

    //Map olmuþ alanýn adresini alýyoruz.
    void * addr = region.get_address();
    const char* map = static_cast<char*>(addr);
    size_t size = region.get_size();

    std::map<int, int> *temp = new std::map<int, int>();

    while (i <= size)
    {
        //Bütün dosyayý 8-bitlik data'yi 2 tane 4 bitlik data seti halinde okuyup tutuyoruz
        memcpy(&data1, map + i, sizeof(int));
        memcpy(&data2, map + (i + 4), sizeof(int));

        int myint = *(int*)&map[i];
        int myint1 = *(int*)&map[i + 4];

        dataSet.insert(std::map<int, int>::value_type(myint, myint1));

        i += 8;
    }

    //Buffer kapatýlýr.
    fbuf.close();
}

void FileReader::ReadRealValue(const char *filePath, std::map<int, int> &semidataset)
{
    int firstValue, secondValue, result = 0;
    const std::size_t FileSize = 10000;

    //Filebuffer yaratýyoruz.
    std::filebuf fbuf;
    fbuf.open(filePath, std::ios_base::binary);
    //Boyutu set ediyoruz.
    fbuf.pubseekoff(FileSize - 1, std::ios_base::beg);
    fbuf.sputc(0);

    //Dosyayý map ediyoruz.
    file_mapping m_file(filePath, read_only);
    mapped_region region(m_file, read_only);

    //Map olmuþ alanýn adresini alýyoruz.
    void * addr = region.get_address();
    const char* map = static_cast<char*>(addr);
    size_t size = region.get_size();

    std::map<int, int>::iterator it = semidataset.begin();

    //TaskIndex icinden okunan offset verileri ile gercek datalarý bulup saklýyoruz.
    while (it != semidataset.end())
    {
        secondValue = it->second;
        result = *(int*)&map[secondValue];

        it->second = result;

        it++;
    }

    return;
}

char * FileReader::MappedFiletoMemory(const char* filePath, size_t& size)
{
    const std::size_t FileSize = 10000;
    char* map = new char;
    //Filebuffer yaratýyoruz.
    std::filebuf fbuf;
    fbuf.open(filePath, std::ios_base::binary);
    //Boyutu set ediyoruz.
    fbuf.pubseekoff(FileSize - 1, std::ios_base::beg);
    fbuf.sputc(0);

    //Dosyayý map ediyoruz.
    file_mapping m_file(filePath, read_only);
    mapped_region region(m_file, read_only);

    //Map olmuþ alanýn adresini alýyoruz.
    void * addr = region.get_address();
    map = static_cast<char*>(addr);
    size = region.get_size();

    //Buffer kapatýlýr.
    fbuf.close();

    return map;
}