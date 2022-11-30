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

class result
{
public:
    int count;
    double time;
};
/**
 * @brief HoarePartiton
 *
 * @param arr the vector of doubles being partitioned
 * @param low the start index of the vector
 * @param high the end index of the vector
 * @return int the index of the partition
 */
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

        swap(arr[i], arr[j]);
    }
}
/**
 * @brief picks a random index between low and high and swaps it with low
 *
 * @param arr a vector of doubles
 * @param low the start index of the vector
 * @param high the end index of the vector
 * @return int the partition found using the random pivot value
 */
int partition_r(vector<double> &arr, int low, int high)
{

    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(arr[random], arr[low]);
    return HoarePartition(arr, low, high);
}

/**
 * @brief randomized quicksort
 *
 * @param arr the vector of doubles being sorted
 * @param low the starting index of the vector
 * @param high the end index of the vector
 */
void QuickSort(vector<double> &arr, int low, int high)
{
    if (low < high)
    {
        int s = partition_r(arr, low, high);
        QuickSort(arr, low, s);
        QuickSort(arr, s + 1, high);
    }
}
/**
 * @brief tracks the execution time of quicksort
 *
 * @param arr the vector of doubles being sorted
 * @param low the start index of the vector
 * @param high the end index of the vector
 * @return double the execution time in ms
 */
double TimedQuickSort(vector<double> &arr, int low, int high)
{
    auto start = high_resolution_clock::now();
    QuickSort(arr, low, high);
    auto end = high_resolution_clock::now();
    duration<double, std::milli> duration = end - start;
    return duration.count();
}

/**
 * @brief reads in double values from a given input file
 *
 * @param filename the file being read
 * @return vector<double> the double values from the input file
 */
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
/**
 * @brief writes to a file
 *
 * @param outputfile the file being written to
 * @param outString the string being written to the file
 */
void writetoFile(string outputfile, string outString)
{
    ofstream output(outputfile);
    if (output.is_open())
    {
        output << outString << endl;
    }
    else
    {
        cout << "Error opening output folder: Please provide a valid file path " << outputfile << endl;
    }
    output.close();
}
/**
 * @brief generates a string containing the values in arr and the execution time
 *
 * @param arr the values being placed in the string
 * @param executionTime the execution time being placed in the string
 * @return string contains the values from arr and the time taken to sort them
 */
string GenerateSortedString(vector<double> &arr, double executionTime)
{
    string out = to_string(arr[0]);

    for (int i = 1; i < arr.size(); i++)
    {
        out = out + " " + to_string(arr[i]);
    }
    out = out + "\n Inputs:" + to_string(arr.size());
    out = out + "    Execution Time:" + to_string(executionTime);
    return out;
}
/**
 * @brief generates a string containing the input size and execution time for each result in the provided vector
 *
 * @param arr the results being converted to a string representation
 * @return string contains the data from every result in arr
 */
string GenerateExecutionTimeString(vector<result> arr)
{
    string out = "";
    for (int i = 0; i < arr.size(); i++)
    {
        out = out + to_string(arr[i].count) + "    " + to_string(arr[i].time) + "\n";
    }
    return out;
}
/**
 * @brief avgs the exection times for a vector of results and returns the result as a string
 *
 * @param arr the results being averaged
 * @return string the average of the results in arr
 */
string GenerateExecutionAverageString(vector<result> arr)
{
    double avg;

    for (int i = 0; i < arr.size(); i++)
    {
        avg = avg + arr[i].time;
    }
    avg = avg / arr.size();
    return to_string(avg);
}
/**
 * @brief applies quicksort to the 25 input files generated for the specified input size
 *
 * @param arr a vector of results for each input file
 * @param inputsize the input size for the files being processed
 */
void QuickSortInputFiles(vector<result> &arr, string inputsize)
{
    for (int i = 0; i < 25; i++)
    {
        result r;
        vector<double> values;
        values = readFile("../data/Input_" + inputsize + "_" + to_string(i) + ".txt");
        r.time = TimedQuickSort(values, 0, values.size() - 1);
        r.count = values.size();
        writetoFile("../data/output" + inputsize + "_" + to_string(i) + ".txt", GenerateSortedString(values, r.time));
        arr.push_back(r);
    }
}

/**
 * @brief applies quick sort to the files created by the input file generator and outputs execution time stats
 *
 */
void BulkSort()
{
    vector<result> tenInputs;
    vector<result> hundredInputs;
    vector<result> thousandInputs;
    string executionTimes = "Input Size\tExecution Time\n";
    string executionTimeAVGS = "\nInput Size\tExecution Time(AVG)\n";

    QuickSortInputFiles(tenInputs, "10");
    QuickSortInputFiles(hundredInputs, "100");
    QuickSortInputFiles(thousandInputs, "1000");
    executionTimes = executionTimes + GenerateExecutionTimeString(tenInputs);
    executionTimes = executionTimes + GenerateExecutionTimeString(hundredInputs);
    executionTimes = executionTimes + GenerateExecutionTimeString(thousandInputs);
    executionTimeAVGS = executionTimeAVGS + "\n10    " + GenerateExecutionAverageString(tenInputs);
    executionTimeAVGS = executionTimeAVGS + "\n100    " + GenerateExecutionAverageString(hundredInputs);
    executionTimeAVGS = executionTimeAVGS + "\n1000    " + GenerateExecutionAverageString(thousandInputs);

    writetoFile("../data/Hopkins_Brent_executionTime.txt", executionTimes);
    writetoFile("../data/Hopkins_Brent_averageExecutionTime.txt", executionTimeAVGS);
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        vector<double> arr;
        string input = argv[1];
        string outPut = argv[2];
        double exeTime;
        arr = readFile(input);
        exeTime = TimedQuickSort(arr, 0, arr.size() - 1);
        writetoFile(outPut, GenerateSortedString(arr, exeTime));
    }
    else
    {
        BulkSort();
    }
    return 0;
}