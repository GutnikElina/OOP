/*5. ����������� ����� ������� (������� 5) �� �++ �� ���� �����������
��������. ��������� ����������� ����� ����� ��������. ������������
smart-��������� ��� �������� ��������� ����� ���������� ����������
�������� � �������� ���������� ��������� ����� (�������� ��������
�������, ���������� �������� ��������������, ������ ������� � �.�.)
���������� �������� � ���� �� ���. ����������� �������� ����������,
������� �������� ���������� ���������, ���� �������� ��������� �������
(��������, ����������� ������� ������� �� ����� ������, ��� �� ��� �������,
������� ������� ������ � ��������). ��������� ������ ������������ �����
���������� � ���������� ���������� �������� ������ �� ������� �������. �
������������� ������ ������� ������ ���� ���� �� ���� ��������� �����.
��� ������ ������ ����� ������ ��������� � ��������� �������� �����.
������������ ����������� � �����������, ����������� ��� ����������,
����������� �����������, ����������.*/

#include<iostream>
#include<string>
#include<vector>
#include<conio.h>
#include<memory>

using namespace std;

int check_int() 
{
	int number;
	cin >> number;
	while (cin.fail() || number < 0) 
	{
		cout << "-!!!- �� ����� ������������ ������ -!!!- " << endl;
		cout << "            ���������� �����\n";
		cin >> number;
	}
	return number;
}

string generate_card_number() 
{
	srand(unsigned(time(0)));
	int a, b;
	a = rand() % 9999 + 999;
	b = rand() % 9999 + 999;
	return to_string(a) + to_string(b);
}

string generate_CVC() 
{
	srand(unsigned(time(0)));
	int a;
	a = rand() % 999 +100;
	return to_string(a);
}

int continue_or_not()
{
	int ch{};
	while (1)
	{
		cout << "----------------------------------------------------" << endl;
		cout << "|                ������ ����������?                |" << endl;
		cout << "|    ���� ��, ������� - 1; ���� ���, ������� - 0.  |" << endl;
		cout << "----------------------------------------------------" << endl;
		ch = check_int();
		if (ch == 1 || ch == 0)
		{
			if (ch == 1)
				return 1;
			else if (ch == 0)
				return 0;
		}
	}
}

class Money
{
	float sum{};
	string currency{};
	void exchange_to_USD() 
	{
		if (currency == "BYN") 
		{
			sum *= 0.3051f;
		}
		else if (currency == "RUB") 
		{
			sum *= 0.0095f;
		}
		else if (currency == "EUR") 
		{
			sum *= 1.0704f;
		}
		currency = "USD";
	}
public:
	Money() : sum(0), currency("USD") {}
	Money(float sum, string currency) : sum(sum), currency(currency) {}

	void exchange(string newCurrency) 
	{
		if (newCurrency == "USD") 
		{
			cout << " === ����������� ������ ������ ������� === \n";
			cout << show_sum() << " " << currency << " ���������� �: ";
			exchange_to_USD();
			cout << show_sum() << " " << currency;
		}
		else if (newCurrency == "BYN") 
		{
			cout << " === ����������� ������ ������ ������� === \n";
			cout << show_sum() << " " << currency << " ���������� �: ";
			if (currency != "BYN")
			{
				exchange_to_USD();
				sum *= 3.051f;
				currency = "BYN";
			}
			cout << show_sum() << " " << currency;
		}
		else if (newCurrency == "RUB") 
		{
			cout << " === ����������� ������ ������ ������� === \n";
			cout << show_sum() << " " << currency << " ���������� �: ";
			if (currency != "RUB")
			{
				exchange_to_USD();
				sum *= 95,81;
				currency = "RUB";
			}
			cout << show_sum() << " " << currency;
		}
		else if (newCurrency == "EUR") 
		{
			cout << " === ����������� ������ ������ ������� === \n";
			cout << show_sum() << " " << currency << " ���������� �: ";
			if (currency != "EUR")
			{
				exchange_to_USD();
				sum *= 0.9342f;
				currency = "EUR";
			}
			cout << show_sum() << " " << currency;
		}
	}
	float show_sum() { return round(sum); }
	void set_money(float sum) { this->sum = sum; }
	void add_money(float add) { sum += add; }
	string show_currency() { return currency; }
};


class Date 
{
	int month{}, year{};
public:
	Date() : month(0), year(0) {}
	Date(int month, int year) : month(month), year(year) {}
	string show_date() 
	{
		return to_string(month) + "/" + to_string(year);
	}
};

template <class T>
class Transaction
{
	shared_ptr<T> currentState, prevState;
public:
	Transaction() : currentState(std::make_shared<T>()), prevState(nullptr) {}
	Transaction(const T& trans)
	{
		currentState = make_shared<T>(trans);
		prevState = nullptr;
	}
	~Transaction() {}
	shared_ptr<T> operator->() { return currentState; }
	void commitTransaction()
	{
		prevState = nullptr;
	}
	bool startTransaction()
	{
		prevState = currentState;
		currentState = make_shared<T>(*prevState);

		if (!currentState)
		{
			cout << " -!!!- ��������� ������. ���������� ����� -!!!- " << endl;
			return false;
		}
		return true;
	}
	void cancelTransaction()
	{
		currentState = prevState;
		prevState = nullptr;
	}
};

class PayCard : public Money
{
	string card_number;
	Date date;
	string CVC;
public:
	PayCard() : card_number(generate_card_number()), Money(), date(Date(3, 28)), CVC(generate_CVC()) {}
	
	PayCard(int month, int year) : card_number(generate_card_number()), CVC(generate_CVC()), Money(), date(Date(month, year)) {}

	string show_card_number() { return card_number; }

	string showInfo() 
	{
		return "����� �����: " + card_number + "\n����: " + date.show_date() + "\nCVC: " + CVC;
	}

	void Translate(PayCard& another, float sum) 
	{
		Transaction<PayCard> this_s(*this);
		Transaction<PayCard> another_s(another);
		if (this_s.startTransaction() && another_s.startTransaction())
		{
			this_s->add_money(-sum);
			Money sum_m(sum, show_currency());
			if (show_currency() != another.show_currency())
				sum_m.exchange(show_currency());
			another_s->add_money(sum_m.show_sum());
			set_money(this_s->show_sum());
			another.set_money(another_s->show_sum());
		}
		else 
		{
			this_s.cancelTransaction();
			another_s.cancelTransaction();
		}
	}

	void card_interface(vector<PayCard>& cards) 
	{
		char a{};
		bool flag = true;
		while (flag) 
		{
			int choice{};
			system("cls");
			cout << "\n === ���� ������ � ������ === ";
			cout << "\n1) ���������� � ����� \n2) �������� ������ \n3) �������������� ������ \n4) ��������� �������";
			cout << "\n5) ������� ����� \n6) �������� ����� \n7) �����\n";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				system("cls");
				cout << showInfo() << endl;
				cout << "����: " << show_sum() << " " << show_currency() << endl;
				a = _getch();
				break;
			}
			case 2:
			{
				system("cls");
				cout << "�� ����� ����� ������ �������� ������? (USD)" << endl;
				add_money(float(check_int()));
				break;

			}
			case 3:
			{
				system("cls");
				vector<string> options{ "BYN", "RUB", "EUR", "USD" };

				cout << "�������� ������: \n1) BYN \n2) RUB \n3) EUR \n4) USD\n";
				int choice_of_currency{};
				cin >> choice_of_currency;
				exchange(options[choice_of_currency - 1]);
				a = _getch();
				break;
			}
			case 4:
			{
				do 
				{
					system("cls");
					for (int i = 0; i < cards.size(); i++)
					{
						if (cards[i].show_card_number() != card_number)
						{
							cout << "\n����� �" << i + 1 << "(" << cards[i].show_card_number() << ")";
						}
					}
					cout << "\n������� ����� �����: ";
					int anotherCard = check_int();
					float sum = -1;
					for (int i = 0; i < cards.size(); i++) 
					{
						if (cards[i].card_number == to_string(anotherCard))
						{
							cout << "����� ����� �� ������ ���������? (" << cards[i].show_currency() << ")" << endl;
							sum = float(check_int());
							while (sum > show_sum()) 
							{
								cout << "� ��� ��� ����� �������. ���������� �����! ";
								sum = float(check_int());
							}
							Translate(cards[i], sum);
							break;
						}
					}
					if (sum != -1) break;
				} while (continue_or_not());
				break;
			}
			case 5:
			{
				if (continue_or_not())
				{
					int i = 0;
					for (; i < cards.size(); i++)
						if (card_number == cards[i].card_number)
						{
							cards.erase(cards.begin() + i);
						}
					return;
				}
				break;
			}
			case 6:
			{
				int choice_1{};
				for (int i = 0; i < cards.size(); i++)
				{
					if (card_number != cards[i].show_card_number())
						cout << "\n����� �" << i + 1 << "(" << cards[i].show_card_number() << ")";
				}
				cout << "\n������� �����, � ������� ������ ���������� ������: ";
				choice_1 = check_int();
				cards[choice_1 - 1].card_interface(cards);
				break;
			}
			case 7:
			{
				exit(0);
			}
			system("cls");
			}
		}
	}
};

class Menu 
{
public:
	int choose_number_card(vector<PayCard> cards)
	{
		do
		{
			for (int i = 0; i < cards.size(); i++)
			{
				cout << "\n����� �" << i + 1 << "(" << cards[i].show_card_number() << ")";
			}
			cout << "\n�������� �����, � ������� ������ ������ ������: \n";
			int choice_card{};
			choice_card = check_int();
			if (choice_card > 0 && choice_card <= cards.size() + 1)
				return choice_card;
		} while (1);
	}
	void cardMenu(vector<PayCard> cards)
	{
		system("cls");
		cout << " ============ �������� ����� ============= \n\n�� ������� ��� ������ �������� �����? \n";
		int years = check_int();
		if (years != 0)
		{
			cards.push_back(PayCard(9, 23 + years));
		}
		if (continue_or_not())
		{
			cardMenu(cards);
		}
		system("cls");
		cout << " === �� ������� ������� " << cards.size() << " ����(�) === \n";
		cards[choose_number_card(cards) - 1].card_interface(cards);
	}
};


int main() 
{
	setlocale(LC_ALL, "rus");
	Menu menu;
	vector<PayCard> cards{};
	menu.cardMenu(cards);
}