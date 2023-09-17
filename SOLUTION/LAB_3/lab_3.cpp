#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class String {
    char* str;

public:
    String() {
        str = new char[1];
        str[0] = '\0';
    }

    String(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    String(const String& s) {
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    }

    ~String() {
        delete[] str;
    }

    char* getStr() const { return str; }

    void operator=(const String& s) {
        delete[] str;
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    }

    void operator+=(const String& s) {
        char* tmp = new char[strlen(str) + strlen(s.str) + 1];
        strcpy(tmp, str);
        strcat(tmp, s.str);
        delete[] str;
        str = tmp;
    }

    friend ostream& operator<<(ostream& os, const String& s) {
        os << s.str;
        return os;
    }

    friend istream& operator>>(istream& is, String& s) {
        char* tmp = new char[100];
        is >> tmp;
        s = String(tmp);
        delete[] tmp;
        return is;
    }
};

int main() {
    String s1;
    String s2("Hello");
    String s3 = s2;
    String s4;

    s4 = "World";
    s1 += s2;
    s1 += s3;
    s1 += s4;

    cout << s1 << endl;

    cout << "Enter a string: ";
    cin >> s1;
    cout << "You entered: " << s1 << endl;

    return 0;
}