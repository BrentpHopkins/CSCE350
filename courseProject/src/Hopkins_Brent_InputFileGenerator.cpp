#include <iostream>
#include <random>
#include <string.h>
#include <cmath>
#include <fstream>
using namespace std;
/**
 * @brief generates a vector of doubles
 *
 * @param count the number of doubles to be generated
 * @return vector<double> a vector containing the random doubles
 */
vector<double> Random(int count)
{
    vector<double> arr;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-1000000, 1000000);

    for (int i = 0; i < count; i++)
    {
        arr.push_back(dis(gen));
    }
    return arr;
}
/**
 * @brief writes a vector of doubles to a provided output file
 *
 * @param outputfile the path of the file being written to
 * @param arr the vector of doubles being written to the file
 */
void writetoFile(string outputfile, vector<double> &arr)
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
    }
    else
    {
        cout << "Error opening outputfile: " << outputfile << endl;
    }
    output.close();
}
/**
 * @brief generates inputs files containing random doubles
 *
 * @param count the numbe of items in the input file being generated
 */
void GenerateFiles(int count)
{
    for (int i = 0; i < 25; i++)
    {
        vector<double> arr = Random(count);
        string filename = "../data/Input_" + to_string(count) + "_" + to_string(i) + ".txt";
        writetoFile(filename, arr);
    }
}

int main(int argc, char *argv[])
{
    GenerateFiles(10);
    GenerateFiles(100);
    GenerateFiles(1000);
    return 0;
}