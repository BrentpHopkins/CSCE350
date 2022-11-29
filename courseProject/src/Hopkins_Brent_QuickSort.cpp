#include <iostream>
#include <random>
#include <chrono>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;
using namespace std::chrono;

int HoarePartition(vector<double> &arr, int low, int high)
{
    double pivot = arr[low];
    int i = low - 1;
    int j = high + 1;

    while (true)
    {

        do
        {
            i++;
        } while (arr[i] < pivot);

        do
        {
            j--;
        } while (arr[j] > pivot);
        if (i >= j)
        {
            return j;
        }
        iter_swap(arr.begin() + i, arr.begin() + j);
    }
}

double QuickSort(vector<double> &arr, int low, int high)
{
    auto start = high_resolution_clock::now();
    if (low < high)
    {
        int s = HoarePartition(arr, low, high);
        QuickSort(arr, low, s);
        QuickSort(arr, s + 1, high);
    }
    auto end = high_resolution_clock::now();
    duration<double, std::milli> duration = end - start;

    return duration.count();
}

vector<double> readFile(string filename)
{
    vector<double> rv;
    ifstream input(filename);
    string line = "";

    if (input.is_open())
    {
        getline(input, line);
        char strArray[line.length() + 1];
        strcpy(strArray, line.c_str());
        char *tokenValue = strtok(strArray, " ");
        while (tokenValue != NULL)
        {
            rv.push_back(stod(tokenValue));
            tokenValue = strtok(NULL, " ");
        }
    }
    else
    {
        cout << "Error opening inputfile: Please provide a valid file path " << filename << endl;
    }
    input.close();
    return rv;
}

void writetoFile(string outputfile, vector<double> &arr, double executionTime)
{
    ofstream output(outputfile);
    string outString = to_string(arr[0]);
    for (int i = 1; i < arr.size(); i++)
    {
        outString = outString + " " + to_string(arr[i]);
    }
    if (output.is_open())
    {
        output << outString << endl;
        output << to_string(arr.size()) + "\t" + to_string(executionTime) << endl;
    }
    else
    {
        cout << "Error opening output folder: Please provide a valid file path " << outputfile << endl;
    }
    output.close();
}

int main(int argc, char *argv[])
{
    vector<double> arr;
    string input = "../data/input.txt";
    string outPut = "../data/output.txt";
    double exeTime;
    arr = readFile(input);
    exeTime = QuickSort(arr, 0, arr.size() - 1);
    writetoFile(outPut, arr, exeTime);
    return 0;
}