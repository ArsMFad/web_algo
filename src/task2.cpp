/*

Дан массив целых чисел А[0..n-1].
Известно, что на интервале [0, m] значения массива строго возрастают,
а на интервале [m, n-1] строго убывают. Найти m за O( log m ).
2 ≤ n ≤ 10000. 

*/


#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>


std::pair<int, int> exponentialSearch( int * array, int n )
{
    int i = 1;

    while( i < n && 
           array[i] > array[i - 1] )
    {
        i <<= 1;
    }

    int left = i >> 1;
    int right = std::min( i, n - 1 );

    return { left, right };
}


int binarySearch( int * array, int left, int right )
{
    int mid;

    while ( left < right ) {
        mid = ( left + right ) / 2;

        if ( array[mid] > array[mid + 1] )
            right = mid;
        else
            left = mid + 1;
    }

    return left;
}


void run( std::istream &in, std::ostream &out )
{
    int n;
    int * A;
    std::pair<int, int> borders;
    
    in >> n;
    A = new int[n];

    for ( int i = 0; i < n; i++ )
    {
        in >> A[i];
    }

    borders = exponentialSearch( A, n );

    out << binarySearch( A, borders.first, borders.second ) << "\n";

    return;
}


int main( int argc, const char *argv[] )
{
    run( std::cin, std::cout );
    //testExponentialSearch();
    //testBinaerySearch();
    //testLogic();

    return 0;
}
