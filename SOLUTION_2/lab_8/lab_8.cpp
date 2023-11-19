#include <iostream>
#include <queue>
#include <fstream>
#include <stack>
#include <string>
#include <conio.h>
#include <vector>
#include <windows.h>

using namespace std;

class Date
{
private:

	int day{};
	int month{};
	int year{};

protected:

	string date{};

public:

	Date() : day(0), month(0), year(0) {}
	~Date() {}

	void setDate(string date) { this->date = date; }

	string getDate() { return date; }

	void changeToDate(int day, int month, int year)
	{
		date = to_string(day) + "." + to_string(month) + "." + to_string(year);
	}
};

class Transport : public Date
{
protected:

	string nameOfTransport{};
	string mark{};
	int number{};
	double maxSpeed{};

public:

	Transport() : nameOfTransport(""), mark(""), number(0), maxSpeed(0) {}
	~Transport() {}

	void setName(string nameOfTransport) { this->nameOfTransport = nameOfTransport; }
	void setMark(string mark) { this->mark = mark; }
	void setNumber(int number) { this->number = number; }
	void setMaxSpeed(double maxSpeed) { this->maxSpeed = maxSpeed; }

	string getName() { return nameOfTransport; }
	string getMark() { return mark; }
	int getNumber() { return number; }
	double getMxSpeed() { return maxSpeed; }

	void display() 
	{
		cout << "\nÕ‡Á‚‡ÌËÂ: " << nameOfTransport << "\nÃ‡Í‡: " << mark << 
			"\nÕÓÏÂ: " << number << "\nÃ‡ÍÒ. ÒÍÓÓÒÚ¸: " << maxSpeed << "\nƒ‡Ú‡ ‚˚ÔÛÒÍ‡: " << date << endl;
	}

	friend ostream& operator<<(ostream& os, const Transport& tr)
	{
		os << tr.nameOfTransport << "\t" << tr.mark
			<< "\t" << tr.number << "\t" << tr.maxSpeed << "\t" << tr.date;
		return os;
	}

	friend istream& operator>>(istream& is, Transport& tr)
	{
		is >> tr.nameOfTransport >> tr.mark
			>> tr.number >> tr.maxSpeed >> tr.date;
		return is;
	}

	bool operator>(const Transport& other) const
	{
		return number > other.number;
	}
};

queue<Transport> transportQueue;
stack<Transport> transportStack;
priority_queue<Transport, vector<Transport>, greater<Transport>> transportPriorityQueue;

void addToQueue(Transport obj) { transportQueue.push(obj); }
void addToStack(Transport obj) { transportStack.push(obj); }
void addToPriorityQueue(Transport obj) { transportPriorityQueue.push(obj); }

void removeFromQueue() { transportQueue.pop(); }
void removeFromStack() { transportStack.pop(); }
void removeFromPriorityQueue() { transportPriorityQueue.pop(); }

void editObject(queue<Transport>& container, int index, Transport newObj) 
{
	queue<Transport> temp;
	while (!container.empty()) 
	{
		temp.push(container.front());
		container.pop();
	}

	int count = 0;
	while (!temp.empty()) 
	{
		if (count == index) 
		{
			container.push(newObj);
		}
		else 
		{
			container.push(temp.front());
		}
		temp.pop();
		count++;
	}
}

void displayQueue(queue<Transport> container) 
{
	queue<Transport> temp = container;
	while (!temp.empty()) 
	{
		temp.front().display();
		temp.pop();
	}
}

Transport searchByName(queue<Transport> container, string name) 
{
	Transport result;
	queue<Transport> temp = container;
	while (!temp.empty()) 
	{
		if (temp.front().getName() == name) 
		{
			result = temp.front();
		}
		temp.pop();
	}
	return result;
}

int main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");

	Transport car1;
	Transport car2;
	Transport bus1;

	car1.setName("ÀÂ„ÍÓ‚‡ˇ Ï‡¯ËÌ‡");
	car1.setMark("Audi");
	car1.setNumber(1234);
	car1.setMaxSpeed(330);
	car1.setDate("20.03.2015");

	car2.setName("ÀÂ„ÍÓ‚‡ˇ Ï‡¯ËÌ‡");
	car2.setMark("BMW");
	car2.setNumber(4321);
	car2.setMaxSpeed(280);
	car2.setDate("15.05.2011");

	bus1.setName("¿‚ÚÓ·ÛÒ");
	bus1.setMark("Ã¿«");
	bus1.setNumber(5678);
	bus1.setMaxSpeed(90);
	bus1.setDate("12.02.2013");

	addToQueue(car1);
	addToQueue(car2);
	addToQueue(bus1);

	addToStack(car1);
	addToStack(car2);
	addToStack(bus1);

	cout << "\n--- “–¿Õ—œŒ–“ ---\n";
	displayQueue(transportQueue);

	removeFromQueue();

	cout << "\n--- “–¿Õ—œŒ–“ œŒ—À≈ ”ƒ¿À≈Õ»ﬂ ---\n";
	displayQueue(transportQueue);

	Transport taxi1;
	taxi1.setName("“‡ÍÒË");
	taxi1.setMark("Mercedes");
	taxi1.setNumber(3957);
	taxi1.setMaxSpeed(320);
	taxi1.setDate("14.11.2018");

	cout << "\n--- “–¿Õ—œŒ–“ œŒ—À≈ »«Ã≈Õ≈Õ»ﬂ ---\n";
	editObject(transportQueue, 0, taxi1);

	displayQueue(transportQueue);

	Transport s = searchByName(transportQueue, "¿‚ÚÓ·ÛÒ");

	cout << "\n--- Õ¿…ƒ≈ÕÕ€… “–¿Õ—œŒ–“ ---\n\n";
	cout << s;

	char ch = _getch();

	return 0;
}