/*5. ����������� ����� ������� (������� 5 �������) �� ���������� �������
������������� ��������������. ���������� ��������� ������
��������� ������� �����. ������������� ������� ���� �����
�������������� ��������. ����������� ��������������� ��������������
��������. ������������� ������� ���� �������������� �������� �
���������� new. ������� �������������� �������� � ������������ �
������������������ ����� ������������� � ������������. ������
����������� ������� ����������. ������� ����������� (����������������)
����� ����������, ������������� ���������� ����� ���� � ���������� ���.*/


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
			std::cout << "\n -!!!- ���������� ����� -!!!-\n";
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
		std::cout << "\n������� �������������: \n";
		std::cin >> pr;
		std::cout << "\n������� ���������: \n";
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
		std::cout << "\n������������� ���������: " << get_pr();
		std::cout << "\n����: " << get_cost();
		std::cout << "\n���� ���������: " << color;
	}
};

class Pen: public Stationery
{
	std::string ink_color;
public:
	Pen(): Stationery()
	{
		std::cout << "\n������� ���� ������: ";
		std::cin >> ink_color;
	}
	void showProduct() 
	{
		std::cout << "\n������������� �����: " << get_pr();
		std::cout << "\n����: " << get_cost();
		std::cout << "\n���� ������ �����: " << ink_color;
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
			std::cout << "\n�������� ���������� " << exept.what() << std::endl;
		}
	}
	void addPensils() 
	{
		std::cout << "\n������� ���� ���������: \n";
		std::string color;
		double weight;
		std::cin >> color ;
		std::cout << "\n������� ��� ���������: \n";
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
			std::cout << "\n������� ������������� ����������: \n";
			std::cin >> pr;
			if (obj.get_pr() != pr) 
			{
				throw std::runtime_error("");
			}
			std::cout << "\n���������� �������" << std::endl;
			return;
		}
		catch (std::runtime_error) 
		{
			std::cout << "\n���������� �� �������" << std::endl;
			std::cout << "\n������ ����������?\n1 - ��\n2 - ���" << std::endl;
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
	std::cout << "\n���������� ���������" << std::endl;
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
		std::cout << "\n������� �������������� �������� ������������" << std::endl;
		std::cin.clear();
		std::cin.ignore();
	}
	Pencil p("Green", 50);
	p.showProduct();
	std::cin.ignore();
	Pen pens;
	std::cout << "\n�����" << std::endl;
	find(pens);
	Order order;
	order.addPensils();
	order.addPens();
	order.showInfo();
}