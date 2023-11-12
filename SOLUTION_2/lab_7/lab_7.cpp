#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <map>
#include <set>
#include <conio.h>
#include <unordered_map>
#include <unordered_set>


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

	friend std::ostream& operator<<(std::ostream& os, Transport& transport)
	{
		os << "Название транспорта: " << transport.nameOfTransport << std::endl;
		os << "Марка: " << transport.mark << std::endl;
		os << "Номер: " << transport.number << std::endl;
		os << "Макс. скорость: " << transport.maxSpeed << " км/ч" << std::endl;
		os << "Дата выпуска: " << transport.date << std::endl;
		return os;
	}

	static void printSet(std::set<Transport>& t);
	static void printMap(std::map<int, Transport>& t);
	static void printMultimap(std::multimap<int, Transport>& t);
	static void printMultiset(std::multiset<Transport>& t);
	static void printUnorderedMap(std::unordered_map<int, Transport>& t);
	static void printUnorderedSet(std::unordered_set<Transport>& t);
	static void printUnorderedMultimap(std::unordered_multimap<int, Transport>& t);
	static void printUnorderedMultiset(std::unordered_multiset<Transport>& t);

	static Transport addTransport();

	static void findMark(std::set<Transport> t, std::string mark)
	{
		for (auto it = t.begin(); it != t.end(); ++it)
		{
			if (it->mark == mark)
			{
				Transport tran = *it;
				std::cout << tran << std::endl;
				return;
			}
		}
		std::cout << "\nТакой марки транспорта нет\n";
	}
	static void findNameOfTransport(std::set<Transport> t, std::string name)
	{
		for (auto it = t.begin(); it != t.end(); ++it)
		{
			if (it->nameOfTransport == name)
			{
				Transport tran = *it;
				std::cout << tran << std::endl;
				return;
			}
		}
		std::cout << "\nТакого вида транспорта нет\n";
	}
	static void findNumber(std::set<Transport> t, int number)
	{
		for (auto it = t.begin(); it != t.end(); ++it)
		{
			if (it->number == number)
			{
				Transport tran = *it;
				std::cout << tran << std::endl;
				return;
			}
		}
		std::cout << "\nТакого номера транспорта нет\n";
	}
	static void findMaxSpeed(std::set<Transport> t, double maxSpeed)
	{
		for (auto it = t.begin(); it != t.end(); ++it)
		{
			if (it->maxSpeed == maxSpeed)
			{
				Transport tran = *it;
				std::cout << tran << std::endl;
				return;
			}
		}
		std::cout << "\nТакой скорости транспорта нет\n";
	}

	bool operator<(const Transport& other) const 
	{
		return number < other.number;
	}
	bool operator==(const Transport& other) const 
	{
		return number == other.number;
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
			std::cout << "\n -!!!- ПОПРОБУЙТЕ СНОВА -!!!-\n";
			std::cin.clear();
			std::cin.ignore();
		}
	}
}

void Transport::printSet(std::set<Transport>& t)
{
	for (auto transport : t)
	{
		std::cout << transport << std::endl;
	}
}
void Transport::printMap(std::map<int, Transport>& t)
{
	for (auto& pair : t)
	{
		std::cout << "Ключ: " << pair.first << std::endl;
		std::cout << pair.second << std::endl;
	}
}
void Transport::printMultimap(std::multimap<int, Transport>& t) 
{
	for (auto it = t.begin(); it != t.end(); ++it) 
	{
		std::cout << "Название транспорта: " << it->second.nameOfTransport << std::endl;
		std::cout << "Марка: " << it->second.mark << std::endl;
		std::cout << "Номер: " << it->second.number << std::endl;
		std::cout << "Макс. скорость: " << it->second.maxSpeed << " км/ч" << std::endl;
		std::cout << "Дата выпуска: " << it->second.date << std::endl;
	}
}
void Transport::printMultiset(std::multiset<Transport>& tr) 
{
	for (auto t : tr) 
	{
		std::cout << t << std::endl;
	}
}
void Transport::printUnorderedMap(std::unordered_map<int, Transport>& t) 
{
	for (const auto& pair : t) 
	{
		std::cout << "Название транспорта: " << pair.second.nameOfTransport << std::endl;
		std::cout << "Марка: " << pair.second.mark << std::endl;
		std::cout << "Номер: " << pair.second.number << std::endl;
		std::cout << "Макс. скорость: " << pair.second.maxSpeed << " км/ч" << std::endl;
		std::cout << "Дата выпуска: " << pair.second.date << std::endl;
	}
}
void Transport::printUnorderedSet(std::unordered_set<Transport>& tr) 
{
	for (auto t : tr)
	{
		std::cout << t << std::endl;
	}
}
void Transport::printUnorderedMultimap(std::unordered_multimap<int, Transport>& t) 
{
	for (auto it = t.begin(); it != t.end(); ++it)
	{
		std::cout << "Название транспорта: " << it->second.nameOfTransport << std::endl;
		std::cout << "Марка: " << it->second.mark << std::endl;
		std::cout << "Номер: " << it->second.number << std::endl;
		std::cout << "Макс. скорость: " << it->second.maxSpeed << " км/ч" << std::endl;
		std::cout << "Дата выпуска: " << it->second.date << std::endl;
	}
}
void Transport::printUnorderedMultiset(std::unordered_multiset<Transport>& tr) 
{
	for (auto t : tr) 
	{
		std::cout << t << std::endl;
	}
}

Transport Transport::addTransport()
{
	Transport t;
	std::string name, mark, date;
	int number, day, month, year;
	double maxSpeed;

	std::cout << "\nВведите название вида транспорта:  ";
	std::cin >> name;
	t.setName(name);
	std::cout << "Введите производителя транспорта:  ";
	std::cin >> mark;
	t.setMark(mark);
	std::cout << "Введите номер транспорта:  ";
	std::cin >> number;
	t.setNumber(number);
	std::cout << "Введите макс. скорость:  ";
	std::cin >> maxSpeed;
	t.setMaxSpeed(maxSpeed);
	std::cout << "Введите дату выпуска:  ";
	std::cin >> day;
	std::cout << "Введите месяц выпуска:  ";
	std::cin >> month;
	std::cout << "Введите год выпуска:  ";
	std::cin >> year;
	t.changeToDate(day, month, year);
	return t;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");

	std::set<Transport> transportSet;
	std::map<int, Transport> transportMap;
	std::multimap<int, Transport> transportMultimap;
	std::multiset<Transport> transportMultiset;

	Transport t = Transport::addTransport();
	int number = t.getNumber();

	transportMap[number] = t;
	transportMultimap.insert(std::make_pair(number, t));

	transportSet.insert(t);
	transportMultiset.insert(t);

	t = Transport::addTransport();
	number = t.getNumber();

	transportMap[number] = t;
	transportMultimap.insert(std::make_pair(number, t));

	transportSet.insert(t);
	transportMultiset.insert(t);

	std::cout << "\n--------- УСПЕШНО ДОБАВЛЕНО ---------\n\n";

	Transport::printSet(transportSet);
	
	transportMap.erase(--transportMap.end());
	transportSet.erase(--transportSet.end());
	
	std::cout << "\n--------- УСПЕШНО УДАЛЕНО ---------\n\n";

	Transport::printMap(transportMap);

	Transport::findNameOfTransport(transportSet, "Автобус");
	Transport::findMark(transportSet, "Audi");
	Transport::findNumber(transportSet, 1234);
	Transport::findMaxSpeed(transportSet, 330);
	
	char ch = _getch();
	return 0;
}