#include<iostream>
#include<conio.h>


using namespace std;

class triangle
{
	int st_1{}, st_2{}, st_3{};
	string type{};
public:
	triangle()
	{
		st_1 = 0;
		st_2 = 0;
		st_3 = 0;
		type = "";
	}
	triangle(int st_1, int st_2, int st_3, string type)
	{
		this->st_1 = st_1;
		this->st_2 = st_2;
		this->st_3 = st_3;
		this->type = type;
	}

	triangle(const triangle& obj)
	{
		this->st_1 = obj.st_1;
		this->st_2 = obj.st_2;
		this->st_3 = obj.st_3;
		this->type = obj.type;
	}
	int getSt()
	{
		return st_1;
	}
};

int main()
{
	triangle first();
	cout << first.getSt();
	char a = _getch();
}