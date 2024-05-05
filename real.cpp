#include "real.h"
#include <iostream>
#include <fstream>
#include <vector>

CCSVFile::CCSVFile(std::string nameFile) : nameFile(nameFile)
    {
        nameFile += format;
        file.open(nameFile);

        if(!file) std::cout << "Не удалось открыть файл\n";
    }

CCSVFile::~CCSVFile()
    {
        if(file) file.close();
    }

void CCSVFile::Seek(const std::string value)
{
    char symbol;
    std::string value_copy;
    int number = 1;
    std::vector<int> matching_lines;

    // Переместить указатель чтения файла в начало
    file.clear(); // Сброс ошибок чтения/записи файла
    file.seekg(0, std::ios::beg); // Установить указатель чтения файла в начало

    while (file.get(symbol))
    {
        if(symbol == '\n') 
        {
            ++number;
            continue;
        }

        if(symbol == ',') 
        {
            if(value_copy == value)
            {
                matching_lines.push_back(number);
            }

            value_copy = "";
            continue;
        }

        value_copy.push_back(symbol);
    }

    if (matching_lines.empty())
    {
        std::cout << "Не найдено совпадений для \"" << value << "\"\n";
    }
    else
    {
        std::cout << "Найдено совпадений для \"" << value << "\" в строках: ";
        for (int line : matching_lines)
        {
            std::cout << line << " ";
        }
        std::cout << '\n';
    }
}

std::string CCSVFile::Read(const int line_number)
{
    if (line_number <= 0)
    {
        std::cout << "Такой строки нет!\n";
        exit(0);
    } 

    file.clear(); // Сброс ошибок чтения/записи файла
    file.seekg(0, std::ios::beg); 

    int current_line_number = 0;
    std::string full_data;

    while (current_line_number != line_number && std::getline(file, full_data))
    {
        ++current_line_number;
    }

    if (current_line_number != line_number)
    {
        std::cout << "Такой строки нет!\n";
        exit(0);
    } 

    return full_data;
}

void CCSVFile::Write(std::string value)
{
    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл для записи\n";
        return;
    }

    file << value << std::endl;
}

CBinFile::CBinFile(std::string nameFile) : nameFile(nameFile + ".bin") {
        file.open(this->nameFile, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл!\n";
        }
    }

CBinFile:: ~CBinFile() {
        if (file.is_open())
            file.close();
    }

void CBinFile::Write(int name, int age, int height) {
        People people;
        people.index = name;
        people.age = age;
        people.height = height;

        file.write(reinterpret_cast<char*>(&people), sizeof(People));
    }
    
void CBinFile::Read(int number) {
        People people;
        file.seekg(number * sizeof(People), std::ios::beg);
        file.read(reinterpret_cast<char*>(&people), sizeof(People));

        if (!file.eof()) {
            std::cout << "Структура №" << number << '\n';
            std::cout << "name = " << people.index << '\n';
            std::cout << "age = " << people.age << '\n';
            std::cout << "height = " << people.height << '\n';
        } else {
            std::cerr << "Достигнут конец файла.\n";
        }
    }