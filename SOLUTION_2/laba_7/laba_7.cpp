#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <map>
#include <set>

class Date
{
private:

	int day{};
	int month{};
	int year{};

protected:

	std::string date{};

public:

	Date() : day(0), month(0), year(0) {}
	~Date() {}

	void setDate(std::string date) { this->date = date; }

	std::string getDate() const { return date; }

	void changeToDate(int day, int month, int year)
	{
		date = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
	}
};

class Transport : public Date
{
protected:

	std::string nameOfTransport{};
	std::string mark{};
	int number{};
	double maxSpeed{};

public:

	Transport() : nameOfTransport(""), mark(""), number(0), maxSpeed(0) {}
	~Transport() {}

	void setName(std::string& nameOfTransport) { this->nameOfTransport = nameOfTransport; }
	void setMark(std::string& mark) { this->mark = mark; }
	void setNumber(int& number) { this->number = number; }
	void setMaxSpeed(double& maxSpeed) { this->maxSpeed = maxSpeed; }

	std::string getName() { return nameOfTransport; }
	std::string getMark() { return mark; }
	int getNumber() { return number; }
	double getMxSpeed() { return maxSpeed; }

	bool operator<(const Transport& other) const 
	{
		return number < other.number;
	}

	friend std::ostream& operator<<(std::ostream& os, const Transport& transport)
	{
		os << "�������� ����������: " << transport.nameOfTransport << std::endl;
		os << "�����: " << transport.mark << std::endl;
		os << "�����: " << transport.number << std::endl;
		os << "����. ��������: " << transport.maxSpeed << " ��/�" << std::endl;
		os << "���� �������: " << transport.date << std::endl;
		return os;
	}
};

int checkInt()
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
			std::cout << "\n -!!!- ���������� ����� -!!!-\n";
			std::cin.clear();
			std::cin.ignore();
		}
	}
}

void addToSet(std::set<Transport>& mySet, const Transport& obj) 
{
	mySet.insert(obj);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");

	std::set<Transport> transportSet;
	std::map<int, Transport> transportMap;

	Transport t;
	std::string name, mark, date;
	int number, day, month, year;
	double maxSpeed;

	std::cout << "\n������� �������� ���� ����������:  ";
	std::cin >> name;
	t.setName(name);
	std::cout << "������� ������������� ����������:  ";
	std::cin >> mark;
	t.setMark(mark);
	std::cout << "������� ����� ����������:  ";
	std::cin >> number;
	t.setNumber(number);
	std::cout << "������� ����. ��������:  ";
	std::cin >> maxSpeed;
	t.setMaxSpeed(maxSpeed);
	std::cout << "������� ���� �������:  ";
	std::cin >> day;
	std::cout << "������� ����� �������:  ";
	std::cin >> month;
	std::cout << "������� ��� �������:  ";
	std::cin >> year;
	t.changeToDate(day, month, year);

	transportMap[number] = t;
	addToSet(transportSet, t);

	std::cout << "\n--------- ������� ��������� ---------\n";

}