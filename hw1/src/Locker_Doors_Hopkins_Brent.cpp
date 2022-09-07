/**
 * @file Locker_Doors_Hopkins_Brent.cpp
 * @author Brent Hopkins
 * @version 0.1
 * @date 2022-09-07
 *
 * @copyright Copyright (c) 2022 Brent Peter Hopkins
 *
 */
#include <iostream>
#include <array>
#include <vector>

using namespace std;
/**
 * @brief Checks if arguments are valid positive ints
 *
 * @param args argv
 * @param argcount argc
 * @return true the arguments passed are valid non negative ints
 * @return false the arguments passed are not ints or negative ints
 */
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
/**
 * @brief Prints the status of each locker and the number of open lockers
 *
 * @param data Lokcers vector containing boolean values for each locker
 */
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