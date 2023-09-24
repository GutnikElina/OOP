#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <locale>
#include <cmath>

using namespace std;

int generateRand(int min, int max) {
	srand(unsigned(time(0)));
	return rand() % (max - min) + min;
}
int chooseByArrows(string* options, int amountOfOptions, string title) {
	int choice = 0, i;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		cout << "\t   " << title << endl;
		for (i = 0; i < choice; i++) {
			cout << "\t" << options[i] << endl;
		}
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
		cout << "\t" << "> " << options[i++] << " <" << endl;
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		for (; i < amountOfOptions; i++) {
			cout << "\t" << options[i] << endl;
		}

		switch (_getch()) {
		case 27:
			system("cls");
			delete[] options;
			return 0;
		case 72: //Вверх
			if (choice == 0) choice = amountOfOptions - 1;
			else choice--;
			break;
		case 80: //Вниз
			if (choice == (amountOfOptions - 1)) choice = 0;
			else choice++;
			break;
		case '\r':
			system("cls");
			delete[] options;
			return choice + 1;
		}

		system("cls");
	}
}
int enterByArrows(int min, string title) {
	string tab;
	for (int i = 1; i < (title.size() / 2); i++) {
		tab += " ";
	}
	int choice = min;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		cout << title << endl;
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
		cout << tab + "/\\\n" << tab << choice << "\n" + tab + "\\/ " << endl;
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		switch (_getch()) {
		case 27:
			system("cls");
			return 0;
		case 72: //Вверх
			++choice;
			break;
		case 80: //Вниз
			if (choice != min) --choice;
			break;
		case '\r':
			system("cls");
			return choice;
		}

		system("cls");
	}
}
int chooseByArrows(vector<string> options, string title) {
	int choice = 0, i;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		cout << "\t   " << title << endl;
		for (i = 0; i < choice; i++) {
			cout << "\t" << options[i] << endl;
		}
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
		cout << "\t" << "> " << options[i++] << " <" << endl;
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		for (; i < options.size(); i++) {
			cout << "\t" << options[i] << endl;
		}

		switch (_getch()) {
		case 27:
			system("cls");
			return 0;
		case 72: //Вверх
			if (choice == 0) choice = options.size() - 1;
			else choice--;
			break;
		case 80: //Вниз
			if (choice == (options.size() - 1)) choice = 0;
			else choice++;
			break;
		case '\r':
			system("cls");
			return choice + 1;
		}

		system("cls");
	}
}
bool askIsUserSure(string question) {
	string options[2]{ "Да", "Отмена" };
	int choice = 0, i;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (true)
	{
		cout << "\t   " << question << endl;
		for (i = 0; i < choice; i++) {
			cout << "\t" << options[i] << endl;
		}
		SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN);
		cout << "\t" << "> " << options[i++] << " <" << endl;
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		for (; i < 2; i++) {
			cout << "\t" << options[i] << endl;
		}

		switch (_getch()) {
		case 27:
			system("cls");
			return false;
		case 72: //Вверх
			if (choice == 0) choice = 1;
			else choice--;
			break;
		case 80: //Вниз
			if (choice == 1) choice = 0;
			else choice++;
			break;
		case '\r':
			system("cls");
			return !choice;
		}

		system("cls");
	}
}
double typeDouble(string massage) {
	double number;
	cin >> number;
	while (cin.fail() || number < 0) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Какая-то белиберда" << endl;
		}
		else cout << massage << endl;
		cin >> number;
	}

	cin.ignore(100, '\n');
	return number;
}
int typeInt(string massage) {//заставляет ввести пользователя число больше 0
	int number;
	cin >> number;
	while (cin.fail() || number < 0) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Некоректные данные" << endl;
		}
		else cout << massage << endl;
		cout << "Попробуйте заново: ";
		cin >> number;
	}

	cin.ignore(100, '\n');
	return number;
}

template <class T>
class Transaction {
	shared_ptr<T> currentState, prevState;
public:
	Transaction() : currentState(std::make_shared<T>()), prevState(nullptr) {}
	Transaction(const T& trans) {
		currentState = make_shared<T>(trans);
		prevState = nullptr;
	}
	~Transaction() {}
	shared_ptr<T> operator->() { return currentState; }
	void commitTransaction() {
		prevState = nullptr;
	}
	bool startTransaction();
	void cancelTransaction();
};

template<class T>
bool Transaction<T>::startTransaction() {
	prevState = currentState;
	currentState = make_shared<T>(*prevState);

	if (!currentState) {
		cout << "Ошибка! Операция отменена" << endl;
		return false;
	}
	return true;
}

template<class T>
void Transaction<T>::cancelTransaction() {
	currentState = prevState;
	prevState = nullptr;
}

class Money {
	float sum;
	string currency;
	void exchangeToUSD() {
		if (currency == "BYN") {
			sum *= 0.3051f;
		}
		else if (currency == "RUB") {
			sum *= 0.0095f;
		}
		else if (currency == "EUR") {
			sum *= 1.0704f;
		}
		currency = "USD";
	}
public:
	Money() : sum(0), currency("USD") {}
	Money(float sum, string currency) :sum(sum), currency(currency) {}

	void exchange(string newCurrency) {
		if (newCurrency == "USD") {
			exchangeToUSD();
		}
		else if (newCurrency == "BYN") {
			exchangeToUSD();
			sum *= 3.277f;
			currency = "BYN";
		}
		else if (newCurrency == "RUB") {
			sum *= 97.9061f;
			currency = "RUB";
		}
		else if (newCurrency == "EUR") {
			sum *= 0.9342f;
			currency = "EUR";
		}
	}
	float showSum() { return round(sum * 100) / 100; }
	void setMoney(float sum) { this->sum = sum; }
	void addMoney(float add) { sum += add; }
	string showCurrency() { return currency; }
};

class Date {
	int month, year;
public:
	Date() : month(12), year(99) {}
	Date(int month, int year) : month(month), year(year) {}
	string showDate() {
		return to_string(month) + "/" + to_string(year);
	}
};

class PayCard : public Money {
	string cardNumber;
	Date date;
	string CVC;
public:
	PayCard() : cardNumber(generateCardNumber()), Money(), date(Date(12, 99)), CVC(generateCVC()) {}
	static string generateCardNumber() {
		return to_string(generateRand(10000000, 100000000));//8 символов
	}
	static string generateCVC() {
		return to_string(generateRand(100, 1000));//3 символа
	}
	PayCard(int month, int year) : cardNumber(generateCardNumber()), Money(), date(Date(month, year)), CVC(generateCVC()) {	}
	string showInfo() {
		return "  Номер: " + cardNumber + "\n  Дата: " + date.showDate() + "\tCVC: " + CVC;
	}
	void Translate(PayCard& another, float sum) {
		Transaction<PayCard> this_tr(*this);
		Transaction<PayCard> another_tr(another);
		if (this_tr.startTransaction() && another_tr.startTransaction()) {
			this_tr->addMoney(-sum);
			Money sum_m(sum, showCurrency());
			if (showCurrency() != another.showCurrency())
				sum_m.exchange(showCurrency());
			another_tr->addMoney(sum_m.showSum());
			if (generateRand(1, 10) % 2) {
				system("cls");
				cout << "    О нет, транзакция отменена 0_0" << endl;
				_getch();
				this_tr.cancelTransaction();
				another_tr.cancelTransaction();
			}
			else {
				this_tr.commitTransaction();
				another_tr.commitTransaction();
			}
			setMoney(this_tr->showSum());
			another.setMoney(another_tr->showSum());
		}
		else {
			this_tr.cancelTransaction();
			another_tr.cancelTransaction();
		}
	}
	void cardInterface(vector<PayCard>& cards) {
		while (true) {
			switch (chooseByArrows(new string[5]{ "Информация","Конвертировать валюту","Совершить перевод", "Оформить кредит", "Удалить карту" }, 5, "Меню карты")) {
			case 1:
				cout << showInfo() << endl;
				cout << "  Хабар: " << showSum() << " " << showCurrency() << endl;
				_getch();
				break;
			case 2:
			{
				vector<string> options{ "BYN","RUB","EUR","USD" };
				for (int i = 0; i < 4; i++) {
					if (options[i] == showCurrency()) {
						options.erase(options.begin() + i);
						break;
					}
				}
				int choice = chooseByArrows(options, "Выберите валюту");
				if (choice != 0) {
					exchange(options[choice - 1]);
					cout << "Успех =)" << endl;
					_getch();
				}
				break;
			}
			case 3:
				do {
					cout << "Введите номер карты: ";
					int anotherCard = typeInt("Номер карты не может быть отрицательным\nПопробуйте снова:");
					float sum = -1;
					for (int i = 0; i < cards.size(); i++) {
						if (cards[i].cardNumber == to_string(anotherCard)) {
							cout << "Какую сумму?(" << cards[i].showCurrency() << ")" << endl;
							sum = float(typeDouble("Так нельзя -_-"));
							while (sum > showSum()) {
								cout << "У вас нет таких средств. Попробуй ещё: ";
								sum = float(typeDouble("Так нельзя -_-"));
							}
							Translate(cards[i], sum);
							break;
						}
					}
					if (sum != -1) break;
				} while (askIsUserSure("Такой карты нет"));
				break;
			case 4:
				cout << "На какую сумму хотите оформить кредит?" << endl;
				addMoney(typeDouble("Нам не нужны ваши копейки"));
				break;
			case 5:
				if (askIsUserSure("Вы точно хотите это сделать?")) {
					int i = 0;
					for (; i < cards.size(); i++)
						if (cardNumber == cards[i].cardNumber) {
							cards.erase(cards.begin() + i);
							return;
						}
				}
				break;
			case 0: return;
			}
			system("cls");
		}
	}
};

class Menu {
	vector<PayCard> cards{};
public:
	void cardMenu() {
		vector<string> options{ "Создать карту" };
		for (int i = 0; i < cards.size(); i++)
			options.push_back("Карта " + to_string(i + 1));
		int choice;

		while (true) {
			switch (choice = chooseByArrows(options, "Выбор карты")) {
			case 1:
			{
				int years = enterByArrows(1, "На сколько лет оформляем карту?");
				if (years != 0) {
					cards.push_back(PayCard(9, 23 + years));
					options.push_back("Карта " + to_string(cards.size()));
				}
			}
			break;
			case 0:
				if (askIsUserSure("Хотите выйти из программы?")) {
					return;
				}
				break;
			default:
				cards[choice - 2].cardInterface(cards);
				if ((cards.size() + 1) != options.size())
					options.erase(options.begin() + choice - 1);
				break;
			}
		}
	}
};
int main() {
	setlocale(LC_ALL, "RUS");
	Menu menu;
	menu.cardMenu();
}