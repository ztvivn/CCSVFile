#include <iostream>
#include <fstream>
#include <vector>

class CFile
{
    public:
    virtual void Seek(const std::string value) = 0;
    virtual std::string Read(int line_number) = 0;
    virtual void Write(std::string value) = 0;
    // virtual void GetPosition() = 0;
    // virtual void GetLength() = 0;
};

class CCSVFile : public CFile
{
    std::fstream file;
    std::string nameFile; 
    const std::string format = ".csv";

    public:
    CCSVFile(std::string nameFile) : nameFile(nameFile)
    {
        nameFile += format;
        file.open(nameFile);

        if(!file) std::cout << "Не удалось открыть файл\n";
    }
    ~CCSVFile()
    {
        if(file) file.close();
    }

    void Seek(const std::string value);//вывод номера строки в которой находиться параметр valu
    std::string Read(const int line_number);//считываем строку с номеров line_number
    void Write(std::string value);
};

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

int main()
{
    CCSVFile file("pr");

    file.Seek("Ivan");
    std::cout << file.Read(4) << "\n";
    file.Write("6, Anton, 23, 56");
    file.Write("7, Anton, 26, 55");
    std::cout << file.Read(6) << "\n";


    return 0;
}
