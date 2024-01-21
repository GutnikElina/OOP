#include<iostream>
#include<string>
#include<vector>
#include<windows.h>
#include<fstream>

class Person 
{
	std::string name{};
	std::string surname{};
	std::string patronomic{};
	int age;
public:
	std::string get_name()
	{
		return name;
	}

	std::string get_patronomic()
	{
		return patronomic;
	}

	std::string get_surname()
	{
		return surname;
	}

	int get_age()
	{
		return age;
	}

	void set_age()
	{
		std::cin >> age;
	}

	void set_age(int a)
	{
		age = a;
	}

	void set_name()
	{
		std::cin >> name;
	}

	void set_name(std::string n)
	{
		name = n;
	}

	void set_surname()
	{
		std::cin >> surname;
	}

	void set_surname(std::string s)
	{
		surname = s;
	}

	void set_patronomic()
	{
		std::cin >> patronomic;
	}

	void set_patronomic(std::string p)
	{
		patronomic = p;
	}
};

class Equipment
{
	std::string equipment{};
public:
	std::string get_equipment()
	{
		return equipment;
	}

	void set_equipment()
	{
		std::cin >> equipment;
	}

	void set_equipment(std::string e)
	{
		equipment = e;
	}
};

class Student: public Person
{
	int course{};
	double average_mark{};
public:
	int get_course()
	{
		return course;
	}

	double get_average_mark()
	{
		return average_mark;
	}

	void set_course()
	{
		std::cin >> course;
	}

	void set_course(int c)
	{
		course = c;
	}

	void set_average_mark()
	{
		std::cin >> average_mark;
	}

	void set_average_mark(double m)
	{
		average_mark = m;
	}
};

class Audience : public Equipment
{
	int number_of_equipments{};
	int number_of_audiences{};
public:
	int get_number_of_equipments()
	{
		return number_of_equipments;
	}

	int get_number_of_audiences()
	{
		return number_of_audiences;
	}

	void set_number_of_equipments()
	{
		std::cin >> number_of_equipments;
	}

	void set_number_of_equipments(int e)
	{
		number_of_equipments = e;
	}

	void set_number_of_audiences()
	{
		std::cin >> number_of_audiences;
	}

	void set_number_of_audiences(int i)
	{
		number_of_audiences = i;
	}
};

class University : private Student, public Audience
{
	std::string name_of_university{};
	std::string address{};
	int number_of_buildings{};
	int number_of_students{};
public:
	int get_number_of_students()
	{
		return number_of_students;
	}

	int get_number_of_buildings()
	{
		return number_of_buildings;
	}

	std::string get_name_of_university()
	{
		return name_of_university;
	}

	std::string get_address()
	{
		return address;
	}

	void set_name_of_university()
	{
		std::cin >> name_of_university;
	}

	void set_name_of_university(std::string o)
	{
		name_of_university = o;
	}

	void set_number_of_buildings()
	{
		std::cin >> number_of_buildings;
	}

	void set_number_of_buildings(int b)
	{
		number_of_buildings = b;
	}

	void set_address()
	{
		std::cin >> address;
	}

	void set_address(std::string a)
	{
		address = a;
	}

	void set_number_of_students()
	{
		std::cin >> number_of_students;
	}

	void set_number_of_students(int t)
	{
		number_of_students = t;
	}
};

void menu()
{
	std::cout << std:: endl << "================== MENU ==================" << std::endl;
	std::cout << "| 1. Check information about university  |" << std::endl;
	std::cout << "| 2. Add new students                    |" << std::endl;
	std::cout << "| 3. Check information about students    |" << std::endl;
	std::cout << "| 4. Exit                                |" << std::endl;
	std::cout << "==========================================" << std::endl;
	std::cout << "YOUR CHOICE:" << std::endl;
}

void readFromFileUniversity(University& u)
{
	std::ifstream outFile("university.txt", std::ios::in);
	std::string name_of_university;
	std::string address;
	int number_of_students;
	int number_of_buildings;

	if (!outFile.is_open())
	{
		system("cls");
		std::cout << "-!!!- FILE OPENING ERROR  -!!!-" << std::endl;
		exit(1);
	}
	else
	{
		while (true)
		{
			if (!(outFile >> name_of_university >> address >> number_of_buildings >> number_of_students))
				break;
			u.set_name_of_university(name_of_university);
			u.set_address(address);
			u.set_number_of_buildings(number_of_buildings);
			u.set_number_of_students(number_of_students);
		}
		outFile.close();
	}
}

void readFromFileStudent(std::vector<Student> &s)
{
	std::ifstream outFile("students.txt", std::ios::in);
	Student student;
	std::string surname;
	std::string name;
	std::string patronomic;
	int age;
	int course;
	double average_mark;

	if (!outFile.is_open())
	{
		system("cls");
		std::cout << "-!!!- FILE OPENING ERROR  -!!!-" << std::endl;
		exit(1);
	}
	else
	{
		while (true)
		{
			if (!(outFile >> surname >> name >> patronomic >> age >> course >> average_mark))
				break;
			student.set_surname(surname);
			student.set_name(name);
			student.set_patronomic(patronomic);
			student.set_age(age);
			student.set_course(course);
			student.set_average_mark(average_mark);

			s.push_back(student);
		}
		outFile.close();
	}
}

void readFromFileAudience(Audience& u)
{
	std::ifstream outFile("audiences.txt", std::ios::in);
	int number_of_equipments;
	int number_of_audiences;
	std::string equipment;

	if (!outFile.is_open())
	{
		system("cls");
		std::cout << "-!!!- FILE OPENING ERROR  -!!!-" << std::endl;
		exit(1);
	}
	else
	{
		while (true)
		{
			if (!(outFile >> number_of_equipments >> number_of_audiences >> equipment))
				break;
			u.set_number_of_equipments(number_of_equipments);
			u.set_number_of_audiences(number_of_audiences);
			u.set_equipment(equipment);
		}
		outFile.close();
	}
}

int check(std::string ch)
{
	int chislo = 0;
	bool isbreak = false;
	char line[30]{};
	for (int i = 0; i < ch.length(); i++)
	{
		if ((ch[i] < 48 || ch[i] > 57) && ch[i] != 43)
			isbreak = true;
	}
	if (isbreak)
	{
		std::cout << "\n-!!!- The entered choice isn't valid.Try again -!!!-\n\n";
		chislo = 999;
		return chislo;
	}
	else
	{
		for (int i = 0; i < ch.length(); i++)
		{
			line[i] = ch[i];
		}
		chislo = atoi(line);
	}
	return chislo;
}

void show_university(University university)
{
	std::cout << "\nThe name of university: " << university.get_name_of_university();
	std::cout << "\nThe address of university: " << university.get_address();
	std::cout << "\nThe number of buildings: " << university.get_number_of_buildings();
	std::cout << "\nThe number of students: " << university.get_number_of_students();
	std::cout << "\nThe number of audiencies: " << university.get_number_of_audiences();
	std::cout << "\nThe number of equipments: " << university.get_number_of_equipments();
	std::cout << "\nThe equipments: " << university.get_equipment() << std::endl;
}

void show_students(std::vector<Student> student)
{
	for (int i = 0; i < student.size(); i++)
	{
		std::cout << std::endl << "----------------------------------------" << std::endl;
		std::cout << "|               Student                |" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Surname: " << student.at(i).get_surname() << std::endl;
		std::cout << "Name: " << student.at(i).get_name() << std::endl;
		std::cout << "Patronomic: " << student.at(i).get_patronomic() << std::endl;
		std::cout << "Age: " << student.at(i).get_age() << std::endl;
		std::cout << "Course: " << student.at(i).get_course() << std::endl;
		std::cout << "Average mark: " << student.at(i).get_average_mark() << std::endl;
	}
}

void saveStudent(std::vector<Student> s)
{
	std::ofstream fout("students.txt", std::ios::out);

	for (int i = 0; i < s.size(); i++)
	{
		if (i != 0) fout << std::endl;
		fout << s.at(i).get_surname()
			<< "\t" << s.at(i).get_name()
			<< "\t" << s.at(i).get_patronomic()
			<< "\t" << s.at(i).get_age()
			<< "\t" << s.at(i).get_course()
			<< "\t" << s.at(i).get_average_mark();
	}
	fout.close();
}

void add_new_student(std::vector<Student>& s)
{
	Student student;
    std:: cout << "Enter surname: ";
	std::string surname{};
	std::cin >> surname;
	student.set_surname(surname);
	std::cout << "Enter name: ";
	std::string name{};
	std::cin >> name;
	student.set_name(name);
	std::cout << "Enter patronomic: ";
	std::string patronomic{}; 
	std::cin >> patronomic;
	student.set_patronomic(patronomic);
	std::cout << "Enter age: ";
	int age; {};
	std::cin >> age;
	student.set_age(age);
	std::cout << "Enter course: ";
	int course{};
	std::cin >> course;
	student.set_course(course);
	std::cout << "Enter average mark: ";
	double average_mark{};
	std::cin >> average_mark;
	student.set_average_mark(average_mark);
	
	s.push_back(student);
	saveStudent(s);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	University university;
	std::vector<Student> student;
	std::vector<Audience> audience;

	readFromFileUniversity(university);
	readFromFileStudent(student);
	readFromFileAudience(audience);

	int choice{};
	std::string line{};
	do
	{
		do
		{
			menu();
			std::cin >> line;
			choice = check(line);
		} while (choice == 999);

		switch (choice)
		{
		case 1:
			show_university(university);
			break;
		case 2:
			add_new_student(student);
			break;
		case 3:
			show_students(student);
			break;
		case 4:
			break;
		default:
			std::cout << "\n-!!!- The entered choice isn't valid.Try again -!!!-\n\n";
			break;
		}

	} while (choice != 4);
	return 0;
}
