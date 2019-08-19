#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream in("test.txt");
    int count = 0;
    if (in.is_open())
    {
        while (in.peek() != EOF)
        {
            string line;
            std::getline(in, line);

            string world;
            istringstream instrstream(line);
            while (instrstream >> world)
            {
                if (!world.empty())
                    ++count;
            }
        }
        in.close();
    }

    cout << "total words: " << count << std::endl;

    return 0;
}