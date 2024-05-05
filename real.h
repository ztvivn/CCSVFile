#include <iostream>
#include <fstream>
#include <vector>
#pragma once


class CFile
{
    public:
    void Seek(const std::string value) {};
    std::string Read(int line_number) {return "";};
    void Write(std::string value) {};
    // virtual void GetPosition() = 0;
    // virtual void GetLength() = 0;
};

class CCSVFile : public CFile
{
    std::fstream file;
    std::string nameFile; 
    const std::string format = ".csv";

    public:
    CCSVFile(std::string nameFile);
    ~CCSVFile();

    void Seek(const std::string value);//вывод номера строки в которой находиться параметр valu
    std::string Read(const int line_number);//считываем строку с номеров line_number
    void Write(std::string value);
};

class CBinFile {
private:
    std::fstream file;
    std::string nameFile;
    const std::string format = ".bin";

    struct People {
        int index;
        int age;
        int height;
    };

public:
    CBinFile(std::string nameFile);

    ~CBinFile();

    void Write(int name, int age, int height);

    void Read(int number);
};

