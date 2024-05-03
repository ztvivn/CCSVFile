#include <iostream>
#include <fstream>
#include <vector>

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
    CBinFile(std::string nameFile) : nameFile(nameFile + ".bin") {
        file.open(this->nameFile, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл!\n";
        }
    }

    ~CBinFile() {
        if (file.is_open())
            file.close();
    }

    void Write(int name, int age, int height) {
        People people;
        people.index = name;
        people.age = age;
        people.height = height;

        file.write(reinterpret_cast<char*>(&people), sizeof(People));
    }

    void Read(int number) {
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
};

int main() {
    CCSVFile file("info");

    file.Seek("Ivan");
    std::cout << file.Read(4) << "\n";
    file.Write("6, Anton, 23, 56");
    file.Write("7, Anton, 26, 55");
    std::cout << file.Read(6) << "\n";

    CBinFile file1("Br");
    file1.Write(3, 22, 179);

    file1.Read(0);

    return 0;
}
