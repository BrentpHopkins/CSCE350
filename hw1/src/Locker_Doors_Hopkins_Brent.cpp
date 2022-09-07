#include <iostream>
#include <array>
#include <vector>

using namespace std;

bool ValidInts(char *args[], int argcount)
{
    for (int i = 1; i < argcount; i++)
    {
        if (atoi(args[i]) == 0 || atoi(args[i]) < 0)
        {
            return false;
        }
    }
    return true;
}

void PrintLockerStatus(vector<bool> data)
{
    string status = "";
    int openCount = 0;
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i])
        {
            status = "open";
            openCount++;
        }
        else
        {
            status = "closed";
        }
        cout << "locker " << (i + 1) << " is " << status << endl;
    }
    cout << "there are " << openCount << " open lockers" << endl;
}

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 3 || !ValidInts(argv, argc))
    {
        cout << "Usage: Locker_Doors_Hopkins_Brent <positive # of locker doors> <Positive # of passes>" << endl;
    }
    else
    {
        long unsigned int size = stoi(argv[1]);
        long unsigned int loops = stoi(argv[2]);
        vector<bool> lockers(size);
        fill(lockers.begin(), lockers.end(), false);

        for (size_t i = 1; i <= loops; i++)
        {
            for (size_t j = 0; j < (lockers.size()); j++)
            {
                if ((j + 1) % i == 0)
                {
                    lockers[j] = !lockers[j];
                }
            }
        }
        PrintLockerStatus(lockers);
    }
    return 0;
}