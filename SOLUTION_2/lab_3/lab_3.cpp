/*5. Разработать набор классов (минимум 5 классов) по предметной области
«Канцелярские принадлежности». Функционал программы должен
позволить собрать заказ. Сгенерировать минимум пять типов
исключительных ситуаций. Реализовать перенаправление исключительных
ситуаций. Сгенерировать минимум одну исключительную ситуацию с
оператором new. Создать исключительную ситуацию в конструкторе и
продемонстрировать вызов конструкторов и деструкторов. Задать
собственную функцию завершения. Создать собственный (пользовательский)
класс исключения, сгенерировать исключение этого типа и обработать его.*/


#include <windows.h> 
#include <iostream> 
#include <locale.h>
#include <string>
#include<vector>
#include<stdexcept>

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

class Stationery    
{
	std::string pr;
	int cost;
public:
	Stationery() 
	{
		std::cout << "\nВведите производителя: \n";
		std::cin >> pr;
		std::cout << "\nВведите стоимость: \n";
		cost = correct();
	}
	std::string get_pr()
	{
		return pr;
	}
	int get_cost()
	{
		return cost;
	}
	virtual void showProduct() = 0;
};

class Pencil: public Stationery
{
	std::string color;
	double weight;
public:
	Pencil(std::string color, double weight) : Stationery()
	{
		this->color = color;
		this->weight = weight;
		if (!weight)
		{
			throw 1;
		}
	}
	void showProduct() 
	{
		std::cout << "\nПроизводитель карандаша: " << get_pr();
		std::cout << "\nЦена: " << get_cost();
		std::cout << "\nЦвет карандаша: " << color;
	}
};

class Pen: public Stationery
{
	std::string ink_color;
public:
	Pen(): Stationery()
	{
		std::cout << "\nВведите цвет чернил: ";
		std::cin >> ink_color;
	}
	void showProduct() 
	{
		std::cout << "\nПроизводитель ручки: " << get_pr();
		std::cout << "\nЦена: " << get_cost();
		std::cout << "\nЦвет чернил ручки: " << ink_color;
	}
};

class Order 
{
	std::vector<Pencil> pencils;
	Pen* pens;
	int size = 0;
public:
	Order() 
	{
		try 
		{   
			pens = new Pen[3];
		}
		catch (std::bad_alloc exept) 
		{
			std::cout << "\nВозникло исключение " << exept.what() << std::endl;
		}
	}
	void addPensils() 
	{
		std::cout << "\nВведите цвет карандаша: \n";
		std::string color;
		double weight;
		std::cin >> color ;
		std::cout << "\nВведите вес карандаша: \n";
		std::cin >> weight;
		Pencil p(color, weight);
		pencils.push_back(p);
	}
	void addPens() 
	{
		if (size <= 3) 
		{
			Pen p;
			pens[size] = p;
		}
	}
	void showInfo() 
	{
		for (Pencil p : pencils) 
		{
			p.showProduct();
		}
		for (int i = 0; i < size; i++) 
		{
			pens[i].showProduct();
		}
	}
};

void find(Pen obj)
{                                                 
	while (1) 
	{
		std::string pr;
		try 
		{
			std::cin.ignore();
			std::cout << "\nВведите производителя канцелярии: \n";
			std::cin >> pr;
			if (obj.get_pr() != pr) 
			{
				throw std::runtime_error("");
			}
			std::cout << "\nСовпадение найдено" << std::endl;
			return;
		}
		catch (std::runtime_error) 
		{
			std::cout << "\nСовпадение не найдено" << std::endl;
			std::cout << "\nХотите продолжить?\n1 - да\n2 - нет" << std::endl;
			int choice = correct();
			if (choice == 2) 
			{
				return;
			}
		}
	}
}

void terminateFunc()        
{   
	std::cout << "\nЗавершение программы" << std::endl;
	exit(-1);
}

int main() 
{
	system("chcp 1251");
	system("cls");
	set_terminate(terminateFunc);
	try                      
	{   
		 Pencil p("", 0);
	}
	catch (int) 
	{
		std::cout << "\nВызвана исключительная ситуация конструктора" << std::endl;
		std::cin.clear();
		std::cin.ignore();
	}
	Pencil p("Green", 50);
	p.showProduct();
	std::cin.ignore();
	Pen pens;
	std::cout << "\nПоиск" << std::endl;
	find(pens);
	Order order;
	order.addPensils();
	order.addPens();
	order.showInfo();
}