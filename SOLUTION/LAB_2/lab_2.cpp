/*Реализовать класс String для работы со строками. Создать методы
доступа к полям класса. Перегрузить операторы «=» (присваивание
значения), «+=» (сложение строки и объекта другого класса). Реализовать
конструкторы (по умолчанию, с параметрами, копирования), деструктор.
Реализовать friend-функции для операторов ввода/вывода в поток для
созданного класса.*/

#define _XM_NO_INTRINSICS_
#define _CRT_SECURE_NO_WARNINGS
#define BUFFER 255
#include<iostream>
#include<string>

using namespace std;

class String
{
	int size{};
	char* line{};
public:
	String() 
	{
		line = new char[2];
		line[0] = ' ';
		line[1] = '\0';
	}

	String(const char* str)
	{
		line = new char[strlen(str) + 1];
		strcpy(line, str);
	}

	String(const String& other)
	{
		line = new char[strlen(other.line) + 1];
		strcpy(line, other.line);
	}

	~String()
	{
		delete[] line;
	}

	void operator=(const String& obj) {
		delete[] line;
		line = new char[strlen(obj.line) + 1];
		strcpy(line, obj.line);
	}

	void operator+=(const String& obj) {
		char* tmp = new char[strlen(line) + strlen(obj.line) + 1];
		strcpy(tmp, line);
		strcat(tmp, obj.line);
		delete[] line;
		line = tmp;
	}

	friend ostream& operator<<(ostream& cout, String& obj);

	friend istream& operator>>(istream& cout, String& obj);
};

ostream& operator<<(ostream& cout, String& obj)
{
	cout << obj.line;
	return cout;
}

istream& operator>>(istream& cin, String& obj)
{
	char* tmp = new char[100];
	cin >> tmp;
	obj = String(tmp);
	delete[] tmp;
	cin >> obj.line;
	return cin;
}

int menu()
{
	int choice;
	do
	{
		cout << "\nChoose what you want to do: \n" << "1. s3 = s1 \n";
		cout << "2. s3 = s2 \n" << "3. s3 += s1 \n";
		cout << "4. s3 += s2 \n" << "5. Exit \n";
		cin >> choice;
	} while (choice < 48 && choice > 57);
	return choice;
}

int main()
{
	int size;
	char line_1[BUFFER]{}, line_2[BUFFER]{};
	int ch;

	cout << "Write the first string: ";
	cin >> line_1;

	cout << "Write the second string: ";
	cin >> line_2;

	String s1(line_1);
	String s2(line_2);
	String s3;

	do
	{
		ch = menu();
		switch (ch)
		{
		case 1:
		{
			cout << "The third string before: " << s3 << endl;
			s3 = s1;
			cout << "The third string = the second string: " << s3 << endl;
			break;
		}
		case 2:
		{
			cout << "The string before the change: " << s3 << endl;
			s3 = s2;
			cout << "The string after the change: " << s3 << endl << endl;
			break;
		}
		case 3:
		{
			cout << "The string before the change: " << s3 << endl;
			s3 += s1;
			cout << "The string after the change: " << s3 << endl;
			break;
		}
		case 4:
		{
			cout << "The string before the change: " << s3 << endl;
			s3 += s2;
			cout << "The string after the change: " << s3 << endl;
			break;
		}
		case 5:
		{
			return 0;
			break;
		}
		default:
			cout << " -!!!- The entered choice doesn't exist. Please try again! -!!!-";
			break;
		}
	} while (ch != 5);

}