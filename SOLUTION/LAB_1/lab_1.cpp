/*Создать класс Employee (сотрудник), одно из полей которого хранит «порядковый номер» созданного объекта, 
т.е. для первого созданного объекта значение этого поля равно 1, для второго − 2 и т. д. В классе 
разработать метод, который для объекта будет выводить на экран его порядковый номер, 
например: «Мой порядковый номер: 2». В программу добавить необходимый набор полей и методов 
(минимум два поля и два метода) на свое усмотрение.*/

#include<iostream>
#include<string>
using namespace std;

int check_data(char*, int);
int continue_or_not();

class employee
{
	int number;
	static int count;   
public:
	employee()
	{
		count++;
		number = count;
	}

	void print_the_number() 
	{ 
		cout << "The number of the created object: " << number << endl; 
	}
};

int employee::count = 0;

int main()
{
	int exit;
	do
	{
		employee c1, c2, c3;
		c1.print_the_number();
		c2.print_the_number();
		c3.print_the_number();

		exit = continue_or_not();
	} while (exit);
}

int check_data(char* x, int y)
{
	int amount = 0;
	for (int i = 0; (i < y - 1) && (amount == 0); i++)
		if (x[i] <= 48 || x[i] >= 57)
			amount++;
	if (amount != 0)
		return 1;
	else return 2;
}

int continue_or_not()
{
	int exit = 1;
	int MAX;
	char choice[15];
	string line;
	do
	{
		cout << "---------------------\n" << "\tDo you want to continue?\nIf yes, then click - 1; if no, click - 0.\n";
		cin >> line;
		MAX = line.length();
		for (int i = 0; i < MAX - 1; i++)
			choice[i] = line[i];
		exit = check_data(choice, MAX);
		if (exit == 1)
			cout << "\n -!!!- The entered choice doesn't exit.Try again  -!!!-\n";
		else if (exit == 2)
		{
			exit = 0;
			if (MAX == 1 && line[0] == '1')
				return 1;
			else if (MAX == 1 && line[0] == '0')
			{
				cout << "\n\======= THANK'S FOR THE WORK ;)) =======" << endl;
				return 0;
			}
		}
	} while (exit);
}
