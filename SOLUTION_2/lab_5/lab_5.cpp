/*На основе разработанной иерархии классов, реализованной в
лабораторной работе «ОБРАБОТКА ИСКЛЮЧИТЕЛЬНЫХ СИТУАЦИЙ В
ЯЗЫКЕ С++», реализовать программу для работы с данными, используя
потоки файлового ввода-вывода. Реализовать функций
1. добавления данных в файл,
2. удаления данных из файла,
3. редактирования данных в файле,
4. просмотра данных из файла,
5. поиска данных по необходимым параметрам в файле.
Использовать функции open(), is_open(), bad(), good(), close(), eof(), fail()
для анализа состояния файла, перегрузить операторы вывода в поток << и
считывания из потока >>, использовать функции seekg(), seekp(), tellg().*/

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>

using namespace std;

class Stationery 
{
private:
    string name;
    double price = 0;
public:
    Stationery() {}
    Stationery(const string& name, double price) : name(name), price(price) {}

    std::string getName() { return name; }
    double getPrice() { return price; }
    void setName(const string& n) { this->name = n; }
    void setPrice(double p) { this->price = p; }

    friend ostream& operator<<(ostream& os, const Stationery& item) 
    {
        os << item.name << "\t" << item.price;
        return os;
    }

    friend istream& operator>>(istream& is, Stationery& item) 
    {
        is >> item.name >> item.price;
        return is;
    }
};

class FileSystem 
{
private:

    fstream file;
    string filename;

public:

    FileSystem(const string& filename) 
    {
        this->filename = filename;
        file.open(filename, ios::in | ios::out | ios::app);

        if (!file.is_open())
        {
            cerr << "\nОшибка при открытии файла: " << filename << endl;
        }
    }

    ~FileSystem() 
    {
        if (isOpen())
        {
            file.close();
        }
    }

    bool isOpen() { return file.is_open(); }
    bool hasError() { return file.bad(); }
    bool isGood() { return file.good(); }
    bool isEOF() { return file.eof(); }
    bool isFail() { return file.fail(); }

    void addData(const Stationery& item);
    void removeData(const string& name);
    void editData(const string& name, double newPrice);
    void viewData();
    void searchData(const string& param);
};

bool operator==(const Stationery& item_1, const Stationery& item_2)
{
    return item_1 == item_2;
}

bool operator!=(const Stationery& item_1, const Stationery& item_2)
{
    return item_1 != item_2;
}

void FileSystem::addData(const Stationery& item)
{
    if (!isOpen())
    {
        cerr << "\nОшибка! Файл не открыт." << endl;
        return;
    }

    file.seekp(0, ios::end);
    file << item << endl;
    file.flush();

    cout << "\nДанные успешно добавлены в файл." << endl;
}

void FileSystem::removeData(const string& name)
{
    if (isOpen())
    {
        string line;
        fstream outfile("temp.txt");
        while (getline(file, line))
        {
            if (line != name)
            {
                outfile << line << endl;
            }
        }
        outfile.close();
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Данные успешно удалены из файла." << endl;

        this->viewData();
    }
    else 
    {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

void FileSystem::editData(const string& name, double newPrice)
{
    if (!isOpen())
    {
        cerr << "\nОшибка! Файл не открыт." << endl;
        return;
    }

    fstream tempFile("temp.txt", ios::out);
    if (!tempFile.is_open()) 
    {
        cerr << "\nОшибка! Невозможно создать временный файл." << endl;
        return;
    }

    Stationery item;
    while (file >> item) 
    {
        if (item.getName() == name) 
        {
            item.setPrice(newPrice);
        }
        tempFile << item << endl;
    }

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "\nДанные успешно отредактированы в файле." << endl;
}

void FileSystem::viewData() 
{
    if (!isOpen()) 
    {
        cerr << "\nОшибка! Файл не открыт." << endl;
        return;
    }

    file.seekg(0, std::ios::beg);

    Stationery item;
    while (file >> item && !file.eof()) 
    {
        cout << item << endl;
    }
}

void FileSystem::searchData(const string& param) 
{
    if (!file.is_open()) 
    {
        cerr << "\nОшибка! Файл не открыт." << endl;
        return;
    }

    file.seekg(0, std::ios::beg);

    Stationery item;
    bool found = false;

    while (file >> item && !file.eof()) 
    {
        if (item.getName() == param) 
        {
            cout << item << endl;
            found = true;
        }
    }

    if (!found) 
    {
        cout << "\nДанные с указанным параметром не найдены." << endl;
    }
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");

    FileSystem fs("stationery.txt");

    Stationery item1("Ручка", 10.5);
    fs.addData(item1);

    Stationery item2("Карандаш", 5.75);
    fs.addData(item2);

    Stationery item3("Стерка", 3.05);
    fs.addData(item3);

    fs.viewData();

    fs.removeData("Карандаш");

    fs.editData("Ручка", 15.0);

    fs.searchData("Стерка");

    return 0;
}