/*
Реализуйте стратегию выбора опорного элемента “случайный элемент”. 
Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
*/



#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>
#include <cstring>
#include <ctime>


template< typename T, typename Comparator = std::less<T >>
int partition( T* arr, int l, int r, Comparator cmp = Comparator() ) {
    std::srand( std::time( nullptr ));
    int randomIndex = l + ( std::rand() % (r - l + 1 ));

    std::swap( arr[ randomIndex ], arr[r] );
    T pivot = arr[r];

    int i = r;
    int j = r - 1;

    while( j >= l )
    {
        if( !cmp( arr[j], pivot ))
        {
            --i;
            std::swap( arr[i], arr[j] );
        }
        --j;
    }

    std::swap( arr[i], arr[r] );
    return i;
}


template< typename T, typename Comparator = std::less<T >>
T kth_statistics( T* arr, int k, int l, int r, Comparator cmp = Comparator() ) {
    while( true ) {
        int pivot_pos = partition( arr, l, r, cmp );
        
        if( pivot_pos == k )
        {
            return arr[ pivot_pos ];
        } else if( pivot_pos > k )
        {
            r = pivot_pos - 1;
        } else {
            l = pivot_pos + 1;
        }
    }
}


void run(std::istream& in, std::ostream& out)
{
    int n = 0;
    in >> n;

    int* arr = new int [n];
    for (int i = 0; i < n; i++)
        in >> arr[i];
    
    int k10 = 0.1 * n;
    int k50 = 0.5 * n;
    int k90 = 0.9 * n;

    out << kth_statistics(arr, k10, 0, n - 1) << "\n";
    out << kth_statistics(arr, k50, 0, n - 1) << "\n";
    out << kth_statistics(arr, k90, 0, n - 1) << "\n";

    delete[] arr; 
}


void testLogic() {
    {
        int arr[] = {44};
        int n = 1;
        int k10 = 0;
        int k50 = 0;
        int k90 = 0;
        
        assert(kth_statistics(arr, k10, 0, n - 1) == 44);
        assert(kth_statistics(arr, k50, 0, n - 1) == 44);
        assert(kth_statistics(arr, k90, 0, n - 1) == 44 );
    }
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int n = 10;
        int k10 = 1;
        int k50 = 5;
        int k90 = 9;
        
        assert(kth_statistics(arr, k10, 0, n - 1) == 2);
        assert(kth_statistics(arr, k50, 0, n - 1) == 6);
        assert(kth_statistics(arr, k90, 0, n - 1) == 10);
    }
    {
        int arr[] = {5, 3, 9, 1, 7, 2, 8, 4, 6, 0};
        int n = 10;
        int k10 = 1;
        int k50 = 5;
        int k90 = 9;
        
        assert(kth_statistics(arr, k10, 0, n - 1) == 1);
        assert(kth_statistics(arr, k50, 0, n - 1) == 5);
        assert(kth_statistics(arr, k90, 0, n - 1) == 9);
    }
    {
        int arr[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
        int n = 10;
        int k10 = 1;
        int k50 = 5;
        int k90 = 9;
        
        assert(kth_statistics(arr, k10, 0, n - 1) == 2);
        assert(kth_statistics(arr, k50, 0, n - 1) == 2);
        assert(kth_statistics(arr, k90, 0, n - 1) == 2);
    }
    {
        int arr[] = {5, 3, 8, 1, 9, 2, 7};
        int n = 7;
        int k10 = 0;
        int k50 = 3;
        int k90 = 6;
        
        assert(kth_statistics(arr, k10, 0, n - 1) == 1);
        assert(kth_statistics(arr, k50, 0, n - 1) == 5);
        assert(kth_statistics(arr, k90, 0, n - 1) == 9);
    }
}


int main( int argc, const char *argv[] )
{
    run(std::cin, std::cout);
    //testLogic();
    return 0;
}
