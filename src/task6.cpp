/*
Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/


#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>
#include <cstring>


template< typename T, typename Comparator = std::less<T>>
int partition( T *arr, int l, int r, Comparator cmp = Comparator())
{
    T pivot = arr[l]; //случайный

    int i = l + 1;
    int j = r;

    while(1)
    {
        while(i <= r && cmp(arr[i], pivot))
            ++i;
        while(cmp(pivot, arr[j]))
            --j;
        
        if (i >= j)
        {
            std::swap(arr[l], arr[j]);
            return j;
        }

        std::swap(arr[i], arr[j]);
        ++i;
        --j;
    }
}


template< typename T, typename Comparator = std::less<T>>
T kth_statistics( T *arr, int k, int l, int r, Comparator cmp = Comparator() )
{
    //итеративно
    int pivot_pos = partition(arr, l, r, cmp);

    if (pivot_pos == k)
        return arr[pivot_pos];
    
    if (pivot_pos > k)
        return kth_statistics(arr, k, l, pivot_pos - 1, cmp);
    
    return kth_statistics(arr, k, pivot_pos + 1, r, cmp);
}


int main( int argc, const char *argv[] )
{
    int n = 0;
    std::cin >> n;

    int* arr = new int [n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    for (int i = 0; i < n; i++)
    {
        std::cout << kth_statistics(arr, i, 0, n - 1) << " ";
    }
    std::cout << "\n";

    delete[] arr;
    
    return 0;
}
