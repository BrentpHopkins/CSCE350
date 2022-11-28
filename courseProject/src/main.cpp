#include <iostream>
#include <chrono>
#include <cmath>
using namespace std;
using namespace std::chrono;

int HoarePartition(double arr[], int low, int high)
{
    int pivot = arr[low];
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

double QuickSort(double arr[], int low, int high)
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

int main()
{
    double arr[] = {-1, 5, 7, 12, 5.5, 4.5, 12, 5, 2, 1, -5, 12, 15};
    int high = sizeof(arr) / sizeof(arr[0]) - 1;
    std::cout << QuickSort(arr, 0, high) << std::endl;
    return 0;
}