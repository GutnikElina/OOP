/*Разработать набор классов (минимум 5 классов) по предметной области
«Канцелярские принадлежности». Реализовать функций просмотра, добавления, удаления,
сортировки, поиска данных по необходимым параметрам.
Использовать минимум 5 флагов форматирования. Сформировать табличный
вывод всех данных. Использовать функции setf() и unsetf() для установки и
сбрасывания флагов. Использовать функции eof(), fail(), good(), bad(), clear()
для провеки состояния потока.*/


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include<stdexcept>
#include <Windows.h>

class Stationery 
{
    std::string name;
    double price;
public:
    Stationery() {}

    std::string getName() const { return name;}
    double getPrice() const { return price; }
    void setName(std::string n) { this->name = n; }
    void setPrice(double p) { this->price = p; }

    virtual void showProduct() const  = 0; 
};

class Pencil : public Stationery 
{
    std::string color;
public:
    Pencil(): Stationery() {}

    std::string getColor() const { return color; }
    void setColor(std::string c) { this->color = c; }

    void showProduct() const
    {
        std::cout << "Название: " << std::left << std::setw(10) << getName()
            << "Цена: " << std::left << std::setw(8) << getPrice()
            << "Цвет: " << std::left << getColor() << std::endl;
    }
};

class Pen : public Stationery 
{
    std::string inkColor;
public:
    Pen(): Stationery() {}

    std::string getInkColor() const { return inkColor; }
    void setInkColor(std::string i) { this->inkColor = i; }

    void showProduct() const
    {
        std::cout << "Название: " << std::left << std::setw(10) << getName()
            << "Цена: " << std::left << std::setw(8) << getPrice()
            << "Цвет чернил: " << std::left << inkColor << std::endl;
    }
};

class Eraser : public Stationery 
{
public:
    Eraser(): Stationery() {}

    void showProduct() const
    {
        std::cout << "Название: " << std::left << std::setw(10) << getName()
            << "Цена: " << std::left << std::setw(8) << getPrice() << std::endl;
    }
};

class Sharpener : public Stationery 
{
public:
    Sharpener(): Stationery() {}

    void showProduct() const
    {
        std::cout << "Название: " << std::left << std::setw(10) << getName()
            << "Цена: " << std::left << std::setw(8) << getPrice() << std::endl;
    }
};

int correct()
{
    while (1)
    {
        try
        {
            int num;
            std::cin >> num;
            if (std::cin.fail())
            {
                throw 1;
            }
            return num;
        }
        catch (int)
        {
            std::cout << "\n -!!!- ПОПРОБУЙТЕ СНОВА -!!!-\n";
            std::cin.clear();
            std::cin.ignore();
        }
    }
}

void showAllProducts(std::vector<Pen>& p, std::vector<Pencil>& pencils, std::vector<Eraser>& e, std::vector <Sharpener>& sh)
{
    if (p.empty() && pencils.empty() && e.empty() && sh.empty())
    {
        std::cout << "Нет принадлежностей" << std::endl;
    }
    else
    {
        std::cout << "======== Список принадлежностей в заказе ========" << std::endl;
        for (int i = 0; i < p.size(); i++)
        {
            p.at(i).showProduct();
        }
        std::cout << "=================================================" << std::endl;
        for (int i = 0; i < pencils.size(); i++)
        {
            pencils.at(i).showProduct();
        }
        std::cout << "=================================================" << std::endl;
        for (int i = 0; i < e.size(); i++)
        {
            e.at(i).showProduct();
        }
        std::cout << "=================================================" << std::endl;
        for (int i = 0; i < sh.size(); i++)
        {
            sh.at(i).showProduct();
        }
        std::cout << "=================================================" << std::endl;

    }
}

void menuChoice()
{
    std::cout << "========== ВЫБЕРИТЕ С ЧЕМ ХОТИТЕ ПРОДОЛЖИТЬ РАБОТУ =======\n";
    std::cout << "  1 - Карандаши";
    std::cout << "  2 - Ручки";
    std::cout << "  3 - Ластики";
    std::cout << "  4 - Точилки";
}

void menu()
{
    std::cout << "============= МЕНЮ =============\n";
    std::cout << " 1) Просмотр данных\n";
    std::cout << " 2) Добавление записи\n";
    std::cout << " 3) Удаление последней записи\n";
    std::cout << " 4) Сортировка записей\n";
    std::cout << " 5) Выход\n";
}

void addNew(std::vector<Pen>& p, std::vector<Pencil>& pencils, std::vector<Eraser>& e, std::vector <Sharpener>& sh)
{
    menuChoice();
    int choice = correct();
    std::string color;
    double price;
    Pencil p1;
    p1.setName("Карандаш");
    Pen p2;
    p2.setName("Ручка");
    Eraser er;
    er.setName("Ластик");
    Sharpener s;
    s.setName("Точилка");

    switch (choice)
    {
    case 1:
        std::cout << "Введите цену карандаша: \n";
        std::cin >> price;
        std::cout << "Введите цвет карандаша: \n";
        std::cin >> color;
        p1.setPrice(price);
        p1.setColor(color);
        pencils.push_back(p1);
        break;
    case 2:
        std::cout << "Введите цену ручки: \n";
        std::cin >> price;
        std::cout << "Введите цвет чернил: \n";
        std::cin >> color;
        p2.setPrice(price);
        p2.setInkColor(color);
        p.push_back(p2);
        break;
    case 3:
        std::cout << "Введите цену ластика: \n";
        std::cin >> price;
        er.setPrice(price);
        e.push_back(er);
        break;
    case 4:
        std::cout << "Введите цену точилки: \n";
        std::cin >> price;
        s.setPrice(price);
        sh.push_back(s);
        break;
    default:
        std::cout << "\n - !!!- НЕПРАВИЛЬНЫЙ ВВОД ДАННЫХ.ПОПРОБУЙТЕ СНОВА - !!!- \n\n";
        break;
    }
}

void remove(std::vector<Pen>& p, std::vector<Pencil>& pencils, std::vector<Eraser>& e, std::vector <Sharpener>& sh)
{
    menuChoice();
    int choice = correct();

    switch (choice)
    {
    case 1:
        pencils.erase(pencils.end());
        std::cout << "Удаление последней записи прошло успешно! \n";
        break;
    case 2:
        p.erase(p.end());
        std::cout << "Удаление последней записи прошло успешно! \n";
        break;
    case 3:
        e.erase(e.end());
        std::cout << "Удаление последней записи прошло успешно! \n";
        break;
    case 4:
        sh.erase(sh.end());
        std::cout << "Удаление последней записи прошло успешно! \n";
        break;
    default:
        std::cout << "\n - !!!- НЕПРАВИЛЬНЫЙ ВВОД ДАННЫХ.ПОПРОБУЙТЕ СНОВА - !!!- \n\n";
        break;
    }
}

void sorting(std::vector<Pen>& p, std::vector<Pencil>& pencils, std::vector<Eraser>& e, std::vector <Sharpener>& sh)
{
    menuChoice();
    int choice = correct();

    switch (choice)
    {
    case 1:
        sort(pencils.begin(), pencils.end());
        for (int i = 0; i < pencils.size(); i++)
        {
            pencils.at(i).showProduct();
        }
        std::cout << "Сортировка записей прошла успешно! \n";
        break;
    case 2:
        sort(p.begin(), p.end());
        for (int i = 0; i < p.size(); i++)
        {
            p.at(i).showProduct();
        }
        std::cout << "Сортировка записей прошла успешно! \n";
        break;
    case 3:
        sort(e.begin(), e.end());
        for (int i = 0; i < e.size(); i++)
        {
            e.at(i).showProduct();
        }
        std::cout << "Сортировка записей прошла успешно! \n";
        break;
    case 4:
        sort(sh.begin(), sh.end());
        for (int i = 0; i < sh.size(); i++)
        {
            sh.at(i).showProduct();
        }
        std::cout << "Сортировка записей прошла успешно! \n";
        break;
    default:
        std::cout << "\n - !!!- НЕПРАВИЛЬНЫЙ ВВОД ДАННЫХ.ПОПРОБУЙТЕ СНОВА - !!!- \n\n";
        break;
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");

    std::vector<Pencil> pn;
    std::vector<Pen> p;
    std::vector<Eraser> er;
    std::vector<Sharpener> sh;
    
    Pencil pencils;
    pencils.setName("Карандаш");
    pencils.setPrice(2);
    pencils.setColor("Красный");
    pn.push_back(pencils);

    Pen pens;
    pens.setName("Ручка");
    pens.setPrice(3);
    pens.setInkColor("Черный");
    p.push_back(pens);

    Eraser e;
    e.setName("Ластик");
    e.setPrice(1);
    er.push_back(e);

    Sharpener s;
    s.setName("Точилка");
    s.setPrice(2.5);
    sh.push_back(s);

    std::cout.setf(std::ios::right);
    std::cout.width(50);

    int choice;

    do
    {
        menu();
        choice = correct();

        switch (choice)
        {
        case 1:
            showAllProducts(p, pn, er, sh);
            break;
        case 2:
            addNew(p, pn, er, sh);
            break;
        case 3:
            remove(p, pn, er, sh);
            break;
        case 4:
            sorting(p, pn, er, sh);
            break;
        case 5:
            std::cout << "======== ДОСВИДАНИЯ ========";
            break;
        default:
            std::cout << "\n-!!!- НЕПРАВИЛЬНЫЙ ВВОД ДАННЫХ. ПОПРОБУЙТЕ СНОВА -!!!-\n\n";
            break;
        }

    } while (choice != 5);

    return 0;
}