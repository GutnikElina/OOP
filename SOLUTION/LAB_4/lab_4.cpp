/* Разработать связи между классами «Часы», «Механические часы»,
«Электронные часы», «Циферблат», «Источник энергии».Все классы
должны содержать методы получения и изменения всех полей.Написать
программу, позволяющую получать сведения о часах.Использовать
конструктор с параметрами, конструктор без параметров, конструктор
копирования.В класс добавить необходимый набор полей и методов
(минимум два поля и два метода) на свое усмотрение. Предусмотреть метод
для записи полученных данных в файл. Выводить на экран информацию о
часах, имеющих наибольшую стоимость. */

#include <iostream>
#include <cstring>
#include <fstream>
#include<string>
#include<vector>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
       
class EnergySource
{
private:
    string sourceType{};
public:
    EnergySource() {}

    EnergySource(string sourceType)
    {
        this->sourceType = sourceType;
    }
    string getSourceType()
    {
        return sourceType;
    }
    void setSourceType(string s)
    {
        sourceType = s;
    }
};

class Clock               
{        
private:
    string brandName{};
    double price{};
public:
    Clock() {}

    Clock(string brandName, double price)
    {
        this->brandName = brandName;
        this->price = price;
    }
    string getBrandName()
    {
        return brandName;
    }
    void setBrandName(string br)
    {
        brandName = br;
    }
    double getPrice()
    {
        return price;
    }
    void setPrice(double pr)
    {
        price = pr;
    }
};

class MechanicalClock : public Clock  
{
private:
    string type{};
public:
    MechanicalClock() {}

    MechanicalClock(string brandName, int price, string type) : Clock (brandName, price)
    {
        this->type = type;
    }
    virtual string getType()
    {
        return type;
    }
    void setType(string t)
    {
        type = t ;
    }
};

class ElectronicClock : public Clock, public EnergySource    
{
private:
    string type{};
public:
    ElectronicClock() {}

    ElectronicClock(string brandName, int price, string type, string sourceType) : Clock(brandName, price), EnergySource(sourceType)
    {
        this->type = type;
    }
    string getType()
    {
        return type;
    }
    void setType(string t)
    {
        type = t;
    }
};
            
class Dial : public Clock         
{
private:
    string numberStyle{};
    string dialColor{};
public:
   Dial() {}

    Dial(string brandName, int price, int numberStyle, int dialColor) : Clock(brandName, price)
    {
        this->numberStyle = numberStyle;
        this->dialColor = dialColor;
    }
    string getNumberStyle()
    {
        return numberStyle;
    }
    void setNumberStyle(string n)
    {
        numberStyle = n;
    }
    string getDialColor()
    {
        return dialColor;
    }
    void setDialColor(string d)
    {
        dialColor = d;
    }
};

int check(string);
void menuChoice(void);
void findByCost(vector<ElectronicClock> eclock, vector<MechanicalClock> mclock, vector<Dial> dclock);
void menu(void);
void addNew(vector<ElectronicClock>& eclock, vector<MechanicalClock>& mclock, vector<Dial>& dclock);
void readFromFileEclock(vector<ElectronicClock>& e);
void readFromFileMclock(vector<MechanicalClock>& m);
void readFromFileDclock(vector<Dial>& d);
void show(vector<ElectronicClock> eclock, vector<MechanicalClock> mclock, vector<Dial> dclock);

int main() 
{
    vector<ElectronicClock> eclock;
    vector<MechanicalClock> mclock;
    vector<Dial> dclock;

    readFromFileEclock(eclock);
    readFromFileMclock(mclock);
    readFromFileDclock(dclock);

    int choice{};
    string line{};
    do 
    {
        do
        {
            menu();
            cin >> line;
            choice = check(line);
        } while (choice == 999);

       switch (choice)
       {
       case 1:
           addNew(eclock, mclock, dclock);
           break;
       case 2:
           show(eclock, mclock, dclock);
           break;
       case 3:
           findByCost(eclock, mclock, dclock);
           break;
       case 4: 
           break;
       default:
           cout << "\n-!!!- The entered choice isn't valid.Try again -!!!-\n\n";
           break;
       }

    } while(choice!=4);

    return 0;
}

void menu(void)
{
    cout <<  endl << "================== MENU ==================" << endl;
    cout << "| 1. Add new information                 |" << endl;
    cout << "| 2. Check information about all clocks  |" << endl;
    cout << "| 3. Check the most expensive clocks     |" << endl;
    cout << "| 4. Exit                                |" << endl;
    cout << "==========================================" << endl;
    cout << "YOUR CHOICE:" << endl;
}

void menuChoice(void)
{
    cout << endl << "What you want to add?" << endl;
    cout << "--- 1. Electronic clock --- " << endl;
    cout << "--- 2. Mechanical clock --- " << endl;
    cout << "--- 3. Dial --- " << endl;
    cout << "YOUR CHOICE:" << endl;
}

void saveEclock(vector<ElectronicClock> e)
{
    ofstream fout("eclock_info.txt", ios::out);

    for (int i = 0; i < e.size(); i++)
    {
        if (i != 0) fout << endl;
        fout << e.at(i).getBrandName()
            << "\t" << e.at(i).getPrice()
            << "\t" << e.at(i).getType()
            << "\t" << e.at(i).getSourceType();
    }
    fout.close();
}

void saveMclock(vector<MechanicalClock> m)
{
    ofstream fout("mclock_info.txt", ios::out);

    for (int i = 0; i < m.size(); i++)
    {
        if (i != 0) fout << endl;
        fout << m.at(i).getBrandName()
            << "\t" << m.at(i).getPrice()
            << "\t" << m.at(i).getType();
    }
    fout.close();
}

void saveDclock(vector<Dial> d)
{
    ofstream fout("dclock_info.txt", ios::out);

    for (int i = 0; i < d.size(); i++)
    {
        if (i != 0) fout << endl;
        fout << d.at(i).getBrandName()
            << "\t" << d.at(i).getPrice()
            << "\t" << d.at(i).getDialColor()
            << "\t" << d.at(i).getNumberStyle();
    }
    fout.close();
}

void readFromFileEclock(vector<ElectronicClock>&e)
{
    ifstream outFile("eclock_info.txt", ios::in);
    ElectronicClock temp;
    string brandName{}, type{}, sourceType{};
    double price{};

    if (!outFile.is_open())
    {
        system("cls");
        cout << "-!!!- ОШИБКА ОТКРЫТИЯ ФАЙЛА -!!!-" << endl;
        exit(1);
    }
    else
    {
        while (true)
        {
            if (!(outFile >> brandName >> price >> type >> sourceType))
                break;
            temp.setBrandName(brandName);
            temp.setPrice(price);
            temp.setType(type);
            temp.setSourceType(sourceType);
            e.push_back(temp);
        }
        outFile.close();
    }
}


void readFromFileMclock(vector<MechanicalClock>& m)
{
    ifstream file("mclock_info.txt", ios::in);
    MechanicalClock mclock;
    string mbrandName{}, mtype{};
    double mprice{};

    if (!file.is_open())
    {
        system("cls");
        cout << "-!!!- ОШИБКА ОТКРЫТИЯ ФАЙЛА -!!!-" << endl;
        exit(1);
    }
    else
    {
        while (true)
        {
            if (!(file >> mbrandName >> mprice >> mtype))
                break;
            mclock.setBrandName(mbrandName);
            mclock.setPrice(mprice);
            mclock.setType(mtype);
            m.push_back(mclock);
        }
        file.close();
    }
}

void readFromFileDclock(vector<Dial>& d)
{
    ifstream File("dclock_info.txt", ios::in);
    Dial dclock;
    string dbrandName{}, color{}, numberStyle{};
    double dprice{};

    if (!File.is_open())
    {
        system("cls");
        cout << "-!!!- ОШИБКА ОТКРЫТИЯ ФАЙЛА -!!!-" << endl;
        exit(1);
    }
    else
    {
        while (true)
        {
            if (!(File >> dbrandName >> dprice >> color >> numberStyle))
                break;
            dclock.setBrandName(dbrandName);
            dclock.setPrice(dprice);
            dclock.setDialColor(color);
            dclock.setNumberStyle(numberStyle);
            d.push_back(dclock);
        }
        File.close();
    }
}

void addNew(vector<ElectronicClock>& eclock, vector<MechanicalClock>& mclock, vector<Dial>& dclock)
{
    int choice1{};
    string line1{};

    do
    {
        menuChoice();
        cin >> line1;
        choice1 = check(line1);
    } while (choice1 == 999);

    switch (choice1)
    {
    case 1:
    {
        ElectronicClock newClock;
        cout << "Enter brandname: ";
        string brandName{};
        cin >> brandName;
        newClock.setBrandName(brandName);
        cout << "Enter price ($$): ";
        double price{};
        cin >> price;
        newClock.setPrice(price);
        cout << "Enter type of the electronic clock (digital/combined/smart): ";
        string type{};
        cin >> type;
        newClock.setType(type);
        cout << "Enter source type of energy (battery/sun): ";
        string sourceType{};
        cin >> sourceType;
        newClock.setSourceType(sourceType);

        eclock.push_back(newClock);

        saveEclock(eclock);

        break;
    }
    case 2:
    {
        MechanicalClock newMClock;
        cout << "Enter brandname: ";
        string brandName{};
        cin >> brandName;
        newMClock.setBrandName(brandName);
        cout << "Enter price ($$): ";
        double price{};
        cin >> price;
        newMClock.setPrice(price);
        cout << "Enter type of the mechanical clock (auto/manual): ";
        string type{};
        cin >> type;
        newMClock.setType(type);

        mclock.push_back(newMClock);

        saveMclock(mclock);

        break;
    }
    case 3:
    {

        Dial newDClock;
        cout << "Enter brandname: ";
        string brandName{};
        cin >> brandName;
        newDClock.setBrandName(brandName);
        cout << "Enter price ($$): ";
        double price{};
        cin >> price;
        newDClock.setPrice(price);
        cout << "Enter dial color: ";
        string color{};
        cin >> color;
        newDClock.setDialColor(color);
        cout << "Enter number style (Arabic/Roman): ";
        string numberStyle{};
        cin >> numberStyle;
        newDClock.setNumberStyle(numberStyle);

        dclock.push_back(newDClock);

        saveDclock(dclock);

        break;
    }
    case 4:
        break;
    default:
        cout << "\n-!!!- The entered choice isn't valid.Try again -!!!-\n\n";
    }
}

void show(vector<ElectronicClock> eclock, vector<MechanicalClock> mclock, vector<Dial> dclock)
{
    for (int i = 0; i < eclock.size(); i++)
    {
        cout << endl << "----------------------------------------" << endl;
        cout << "|           Electronic clock           |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Brand name: " << eclock.at(i).getBrandName() << endl;
        cout << "Price ($$): " << eclock.at(i).getPrice() << endl;
        cout << "Type: " << eclock.at(i).getType() << endl;
        cout << "Source type of energy: " << eclock.at(i).getSourceType() << endl;
    }
    for (int i = 0; i < mclock.size(); i++)
    {
        cout << endl << "----------------------------------------" << endl;
        cout << "|           Mechanical clock           |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Brand name: " << mclock.at(i).getBrandName() << endl;
        cout << "Price ($$): " << mclock.at(i).getPrice() << endl;
        cout << "Type: " << mclock.at(i).getType() << endl;
    }
    for (int i = 0; i < dclock.size(); i++)
    {
        cout << endl << "----------------------------------------" << endl;
        cout << "|              Dial clock              |" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Brand name: " << dclock.at(i).getBrandName() << endl;
        cout << "Price ($$): " << dclock.at(i).getPrice() << endl;
        cout << "Dial color: " << dclock.at(i).getDialColor() << endl;
        cout << "Number style: " << dclock.at(i).getNumberStyle() << endl;
    }
}

void findByCost(vector<ElectronicClock> eclock, vector<MechanicalClock> mclock, vector<Dial> dclock)
{
    ElectronicClock emax;
    emax.setBrandName(eclock.at(0).getBrandName());
    emax.setPrice(eclock.at(0).getPrice());
    emax.setType(eclock.at(0).getType());
    emax.setSourceType(eclock.at(0).getSourceType());

    for (int i = 0; i < eclock.size(); i++)
    {
        if (emax.getPrice() < eclock.at(i).getPrice())
        {
            emax.setBrandName(eclock.at(i).getBrandName());
            emax.setPrice(eclock.at(i).getPrice());
            emax.setType(eclock.at(i).getType());
            emax.setSourceType(eclock.at(i).getSourceType());
        }
    }

    cout << endl << "----------------------------------------" << endl;
    cout << "|  The most expensive electronic clock |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Brand name: " << emax.getBrandName() << endl;
    cout << "Price ($$): " << emax.getPrice() << endl;
    cout << "Type: " << emax.getType() << endl;
    cout << "Source type of energy: " << emax.getSourceType() << endl;

    MechanicalClock mmax;
    mmax.setBrandName(eclock.at(0).getBrandName());
    mmax.setPrice(mclock.at(0).getPrice());
    mmax.setType(mclock.at(0).getType());

    for (int i = 0; i < mclock.size(); i++)
    {
        if (mmax.getPrice() < mclock.at(i).getPrice())
        {
            mmax.setBrandName(eclock.at(i).getBrandName());
            mmax.setPrice(mclock.at(i).getPrice());
            mmax.setType(mclock.at(i).getType());
        }
    }

    cout << endl << "----------------------------------------" << endl;
    cout << "|  The most expensive mechanical clock |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Brand name: " << mmax.getBrandName() << endl;
    cout << "Price ($$): " << mmax.getPrice() << endl;
    cout << "Type: " << mmax.getType() << endl;

    Dial dmax;
    dmax.setBrandName(dclock.at(0).getBrandName());
    dmax.setPrice(dclock.at(0).getPrice());
    dmax.setDialColor(dclock.at(0).getDialColor());
    dmax.setNumberStyle(dclock.at(0).getNumberStyle());

    for (int i = 0; i < dclock.size(); i++)
    {
        if (dmax.getPrice() < dclock.at(i).getPrice())
        {
            dmax.setBrandName(dclock.at(i).getBrandName());
            dmax.setPrice(dclock.at(i).getPrice());
            dmax.setDialColor(dclock.at(i).getDialColor());
            dmax.setNumberStyle(dclock.at(i).getNumberStyle());

        }
    }

    cout << endl << "----------------------------------------" << endl;
    cout << "|  The most expensive dial clock |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Brand name: " << dmax.getBrandName() << endl;
    cout << "Price ($$): " << dmax.getPrice() << endl;
    cout << "Dial color: " << dmax.getDialColor() << endl;
    cout << "Number style: " << dmax.getNumberStyle() << endl;
}

int check(string ch)
{
    int chislo = 0;
    bool isbreak = false;
    char line[30]{};
    for (int i = 0; i < ch.length(); i++)
    {
        if ((ch[i] < 48 || ch[i] > 57) && ch[i] != 43)
            isbreak = true;
    }
    if (isbreak)
    {
        cout << "\n-!!!- The entered choice isn't valid.Try again -!!!-\n\n";
        chislo = 999;
        return chislo;
    }
    else
    {
        for (int i = 0; i < ch.length(); i++)
        {
            line[i] = ch[i];
        }
        chislo = atoi(line);
    }
    return chislo;
}
