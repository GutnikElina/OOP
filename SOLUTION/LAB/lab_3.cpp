/*Создать классы «Транспортное средство», «Самолет», «Поезд»,
«Автомобиль» с необходимым набором полей и методов. Создать массив
объектов базового класса и заполнить этот массив объектами базового и
производных классов. Определить время и стоимость перевозки для
указанных расстояний. Вывести данные о наиболее быстрой и
экономичной поездке на экран. Классы должны содержать методы
получения и изменения значений всех полей. Все поля классов должны быть
объявлены с атрибутами private или protected.*/

#define _XM_NO_INTRINSICS_
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<iomanip>
#include<conio.h>


using namespace std;

class transport {
private:
	double distance;
	double pricePerKm;
	double speed;
public:
	transport() : distance(distance = 0), pricePerKm(pricePerKm = 0), speed(speed = 0) {}

	void setDistance()
	{
		cin >> distance;
	}

	void setDist(double dist)
	{
		distance = dist;
	}

	double getDistance()
	{
		return distance;
	}

	void setSpeed(double speed) 
	{
		this->speed = speed;
	}

	void setPricePerKm(double price)
	{
		this->pricePerKm = price;
	}

	double getPricePerKm()
	{
		return pricePerKm;
	}

	double getTime()
	{
		return distance / speed;
	}

	double getPrice()
	{
		return distance * pricePerKm;
	}
};

class plane: public transport {
	bool businessClass;
public:
	plane() : businessClass(businessClass = false), transport() {}

	void setClass()
	{
		cin >> businessClass;
	}

	double getPricePlane()
	{
		if (businessClass)
			return 3.45 * transport::getPrice();
		else return transport::getPrice();
	}
};

class train: public transport {
	bool type;
public:
	train() : type(type=false), transport() {}

	void setType()
	{
		cin >> type;
	}

	bool getType()
	{
		return type;
	}

	double getPriceTrain()
	{
		if (type)
			return 1.25 * transport::getPrice();
		else return transport::getPrice();
	}
};

class car: public transport {
	int passengers;
public:
	car() : passengers(passengers = 0), transport() {}

	void setPassengers()
	{
		cin >> passengers;
	}

	double getPriceCar()
	{
		return transport::getPrice() / passengers;
	}
};

int main() 
{
	plane flight;
	train trip;
	car ride;

	//distance
	cout << "Enter the distance: ";
	flight.setDistance();
	trip.setDist(flight.getDistance());
	ride.setDist(flight.getDistance());

	//price
	flight.setPricePerKm(0.18);
	trip.setPricePerKm(0.06);
	ride.setPricePerKm(0.28);

	//other characteristics
	cout << "\nChoose the class of the flight on the plane:  ";
	cout << "\n1 - business-class\n0 - economy-class\n";
	flight.setClass();

	cout << "\nEnter the type of the train: ";
	cout << "\n1 - speeding;\n0 - not speeding\n";
	trip.setType();

	cout << "\nEnter the number of the passengers in the car: \n";
	ride.setPassengers();

	//speed
	flight.setSpeed(600);

	if (trip.getType())
		trip.setSpeed(120);
	else trip.setSpeed(60);

	ride.setSpeed(75);

	//the  results
	cout << "\n\n The information of the travel on your distance by different types of the transport ";
	cout << "\n-----------------------------------------------------------------------------------";
	cout << "\n THE TYPE OF TRANSPORT" << setw(10) << "PRICE" << setw(15) << "TIME";
	cout << "\n-----------------------------------------------------------------------------------";
	cout << "\n    Plane " << setw(22) << flight.getPricePlane() << " $" << setw(15) << flight.getTime() << " h";
	cout << "\n    Train " << setw(22) << trip.getPriceTrain() << " $" << setw(15) << trip.getTime() << " h";
	cout << "\n    Car   " << setw(22) << ride.getPriceCar() << " $" << setw(15) << ride.getTime() << " h\n";
	cout << "\n-----------------------------------------------------------------------------------\n\n";

	cout << "\nThe fastest type of the transport is ";
	if (flight.getTime()<trip.getTime() && flight.getTime() < ride.getTime())
		cout << "plane. " << "\n    Plane " << setw(22) << flight.getPricePlane() << " $" << setw(15) << flight.getTime() << " h";
	else if (trip.getTime() < flight.getTime() && trip.getTime() < ride.getTime())
		cout << "train. " << "\n    Train " << setw(22) << trip.getPriceTrain() << " $" << setw(15) << trip.getTime() << " h";
	else if (ride.getTime() < flight.getTime() && ride.getTime() < trip.getTime())
		cout << "car. " << "\n    Car   " << setw(22) << ride.getPriceCar() << " $" << setw(15) << ride.getTime() << " h\n";

	
	cout << "\n\nThe most economical type of the transport is ";
	if (flight.getPricePlane() < trip.getPriceTrain() && flight.getPricePlane() < ride.getPriceCar())
		cout << "plane. " << "\n    Plane " << setw(22) << flight.getPricePlane() << " $" << setw(15) << flight.getTime() << " h\n";
	else if (trip.getPriceTrain() < flight.getPricePlane() && trip.getPriceTrain() < ride.getPriceCar())
		cout << "train. " << "\n    Train " << setw(22) << trip.getPriceTrain() << " $" << setw(15) << trip.getTime() << " h\n";
	else if (ride.getPriceCar() < flight.getPricePlane() && ride.getPriceCar() < trip.getPriceTrain())
		cout << "car. " << "\n    Car   " << setw(22) << ride.getPriceCar() << " $" << setw(15) << ride.getTime() << " h\n";

	char a = _getch();
	return 0;
}
