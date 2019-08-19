#include <iostream>
#include <vector>

#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void test_write();
void test_read();

int main()
{
    test_write();
    test_read();

    return 0;
};

struct Person
{
    int age;
    float money;
};

#define FILE_NAME "del.txt"

void test_write()
{
    vector<Person> rgPersons {
        {.age=1, .money=11.11},
        {.age=2, .money=22.22},
        {.age=3, .money=33.33}
    };

    ofstream out(FILE_NAME);
    if (out.is_open()) {
        for (auto& item : rgPersons) {
            out << item.age << " " << item.money << endl;
        }

        out.close();
    }
    cout << "write end." << endl;
}

void test_read()
{
    ifstream in(FILE_NAME);
    if (in.is_open())
    {
        while (in.peek() != EOF) {
            string line;
            std::getline(in, line);
            istringstream istrstream(line);
            Person data;
            istrstream >> data.age >> data.money;
            
            cout << data.age << " " << data.money << endl;
        }

        in.close();
    }
    cout << "read over." << endl;
}