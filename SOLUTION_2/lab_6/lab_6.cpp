/* В каждом индивидуальном задании необходимо создать контейнеры
list, vector, array, которые будут хранить объекты классов по предметной
области - транспортная техника. Для контейнера реализовать добавление, удаление,
вывод содержимого контейнера на экран и в файл, поиск и сортировку элементов. 
Необходимо создать удобное пользовательское меню. 

Предметная область: транспортная техника */

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include<iomanip>

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

	std::string getDate() { return date; }

	void changeToDate(int day, int month, int year)
	{
		date = std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
	}
};

class Transport: public Date
{
protected:

	std::string nameOfTransport{};
	std::string mark{};
	int number{};
	double maxSpeed{};

public:

	Transport(): nameOfTransport(""), mark(""), number(0), maxSpeed(0) {}
	~Transport() {}

	void setName(std::string& nameOfTransport) { this->nameOfTransport = nameOfTransport; }
	void setMark(std::string& mark) { this->mark = mark; }
	void setNumber(int& number) { this->number = number; }
	void setMaxSpeed(double& maxSpeed) { this->maxSpeed = maxSpeed; }

	std::string getName() { return nameOfTransport; }
	std::string getMark() { return mark; }
	int getNumber() { return number; }
	double getMxSpeed() { return maxSpeed; }

	static Transport search(std::vector<Transport>& vect, int number);

	friend std::ostream& operator<<(std::ostream& os, const Transport& tr)
	{
		os << tr.nameOfTransport << "\t" << tr.mark 
			<< "\t" << tr.number << "\t" << tr.maxSpeed << "\t" << tr.date;
		return os;
	}

	template<typename Container>
	friend std::ostream& operator<<(std::ostream& os, const Container& tr)
	{
		for (int i = 0; i < tr.size(); i++)
		{
			os << tr.at(i).nameOfTransport << "\t" << tr.at(i).mark << "\t" << tr.at(i).number
				<< "\t" << tr.at(i).maxSpeed << "\t" << tr.at(i).date << std::endl;
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Transport& tr)
	{
		is >> tr.nameOfTransport >> tr.mark
		   >> tr.number >> tr.maxSpeed >> tr.date;
		return is;
	}
};

class Menu
{
public:

	static void showMenu();
	static int checkInt();
	static int choice();
	static void showData(std::vector<Transport> vect);
	static void show(Transport tr);

	template<typename Container>
	static void addInFile(std::string filename, Container& cont)
	{
		std::ofstream fout(filename, std::ios::out);
		if (!fout.is_open())
		{
			std::cout << "-!!!- ОШИБКА ОТКРЫТИЯ ФАЙЛА -!!!-";
			exit(1);
		}

		fout.seekp(0, std::ios::end);
		fout << cont << std::endl;
		fout.flush();
	}

	template<typename Container>
	static Container getFromFile(std::string filename, Container& cont)
	{
		std::fstream file;
		file.open(filename, std::ios::in | std::ios::out | std::ios::app);
		if (!file.is_open())
		{
			std::cout << "\n-!!!- ОШИБКА ОТКРЫТИЯ ФАЙЛА -!!!-\n";
			exit(1);
		}

		file.seekg(0, std::ios::beg);

		Transport tr;
		Container transport;
		while (file >> tr && !file.eof()) { transport.push_back(tr); }

		return transport;
	}

	static bool compareByCarNumber(Transport& tr1, Transport& tr2);
};


Transport Transport::search(std::vector<Transport>& vect, int number)
{
	Transport transport;

	for (int i = 0; i < vect.size(); i++)
	{
		if (vect.at(i).getNumber() == number)
		{
			transport = vect.at(i);
		}
	}
	return transport;
}

void Menu::showMenu()
{
	std::cout << "\n------------------- МЕНЮ -------------------";
	std::cout << "\n| 1) Добавление транспортного средства     |";
	std::cout << "\n| 2) Удаление транспортного средства       |";
	std::cout << "\n| 3) Показать транспортные средства        |";
	std::cout << "\n| 4) Поиск                                 |";
	std::cout << "\n| 5) Сортировка                            |";
	std::cout << "\n| 6) Выход                                 |";
	std::cout << "\n--------------------------------------------\n";
}

int Menu::checkInt()
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

int Menu::choice()
{
	while (1)
	{
		std::cout << "\nВАШ ВЫБОР->  ";
		int choice = checkInt();

		switch (choice)
		{
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		case 4:
			return 4;
		case 5:
			return 5;
		case 6:
			system("cls");
			exit(0);
		default:
			std::cout << "\n !!! ТАКОГО ВЫБОРА НЕ СУЩЕСТВУЕТ !!!";
			std::cout << "\n          ПОПРОБУЙТЕ СНОВА          \n";
			break;
		}
	}
}

void Menu::showData(std::vector<Transport> vect)
{
	std::cout << "\n+-----------------------------------------------------------------------------+\n";
	std::cout << "|                             БАЗА ДАННЫХ ТРАНСПОРТА                          |\n";
	std::cout << "+-----------------------------------------------------------------------------+\n";
	std::cout << "|  №  |      Название        |   Производитель  |     Номер     |     Дата    |\n";
	std::cout << "|     |     транспорта       |                  |   транспорта  |    выпуска  |\n";
	std::cout << "+-----------------------------------------------------------------------------+";

	for (int i = 0; i < vect.size(); i++)
	{
		std::cout << "\n| " << std::setw(4) << std::left << (i + 1)
			<< "| " << std::setw(21) << std::left << vect.at(i).getName() << "| "
			<< std::setw(17) << std::left << vect.at(i).getMark() << "| "
			<< std::setw(14) << std::left << vect.at(i).getNumber() << "| "
			<< std::setw(12) << std::left << vect.at(i).getDate() << "| ";
		std::cout << std::endl << "+-----------------------------------------------------------------------------+";
	}
	std::cout << std::endl;
}

void Menu::show(Transport tr)
{
	std::cout << "\n+-----------------------------------------------------------------------------+\n";
	std::cout << "|                             БАЗА ДАННЫХ ТРАНСПОРТА                          |\n";
	std::cout << "+-----------------------------------------------------------------------------+\n";
	std::cout << "|            Название        |   Производитель  |     Номер     |     Дата    |\n";
	std::cout << "|           транспорта       |                  |   транспорта  |    выпуска  |\n";
	std::cout << "+-----------------------------------------------------------------------------+";

	std::cout << "\n| " << std::setw(27) << std::left << tr.getName() << "| "
			<< std::setw(17) << std::left << tr.getMark() << "| "
			<< std::setw(14) << std::left << tr.getNumber() << "| "
			<< std::setw(12) << std::left << tr.getDate() << "| ";
	std::cout << std::endl << "+-----------------------------------------------------------------------------+";
	std::cout << std::endl;
}

bool Menu::compareByCarNumber(Transport& tr1, Transport& tr2)
{
	return tr1.getNumber() < tr2.getNumber();
}




int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");

	std::fstream file;
	std::string filename = "transport.txt";
	file.open(filename, std::ios::in | std::ios::out | std::ios::app);

	if (!file.is_open())
	{
		std::cerr << "\n-!!!- ОШИБКА ОТКРЫТИЯ ФАЙЛА -!!!-\n" << std::endl;
	}

	std::list<Transport> listTransport = Menu::getFromFile(filename, listTransport);
	std::vector<Transport> vectorTransport = Menu::getFromFile(filename, vectorTransport);
	std::array<Transport, 1> arrayTransport;

	Transport t;
	std::string name, mark, date;
	int number, day, month, year, choice;
	double maxSpeed;

	while (1)
	{
		Menu::showMenu();
		choice = Menu::choice();
		if (choice == 1)
		{
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

			listTransport.push_back(t);

			vectorTransport.push_back(t);

			if(arrayTransport.empty())
				arrayTransport = {t};

			Menu::addInFile(filename, vectorTransport);


			std::cout << "\n--------- УСПЕШНО ДОБАВЛЕНО ---------\n";
		}
		else if (choice == 2)
		{
			Menu::showData(vectorTransport);
			std::cout << "\nВведите № транспорта, который хотите удалить->  ";
			int number = Menu::checkInt();

			vectorTransport.erase(vectorTransport.begin() + number - 1);

			listTransport.pop_back();
			
			Menu::addInFile(filename, vectorTransport);

			std::cout << "\n--------- УСПЕШНО УДАЛЕНО ---------\n";
		}
		else if (choice == 3)
		{
			Menu::showData(vectorTransport);
		}
		else if (choice == 4)
		{
			std::cout << "\nВведите номер транспорта, который хотите найти->  ";
			std::cin >> number;

			Transport t = Transport::search(vectorTransport, number);
			if(t.getNumber() != 0)
					Menu::show(t);
			else std::cout << "\n-!!!- ТАКОГО ТРАНСПОРТА НЕТ В ФАЙЛЕ -!!!-\n";

		}
		else if (choice == 5)
		{
			std::sort(vectorTransport.begin(), vectorTransport.end(), Menu::compareByCarNumber);
			Menu::showData(vectorTransport);
		}
	}
}