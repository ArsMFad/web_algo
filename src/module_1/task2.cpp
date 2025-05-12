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


void testExponentialSearch()
{
    {
        int array[] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
        assert(exponentialSearch( array, 9 ) == std::make_pair( 4, 8 ));
    }
    {
        int array[] = { 1, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        assert( exponentialSearch( array, 10 ) == std::make_pair( 1, 2 ) );
    }
    {
        int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        assert( exponentialSearch( array, 19 ) == std::make_pair( 8, 16 ) );
    }
    {
        int array[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
        assert( exponentialSearch( array, 9 ) == std::make_pair( 4, 8 ) );
    }

    std::cout << "ALL EXPONENTIAL SEARCH TESTS DONE" << std::endl;
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


void testBinarySearch()
{
    {
        int array[] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
        assert( binarySearch( array, 4, 8 ) == 4 );
    }
    {
        int array[] = { 1, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        assert( binarySearch( array, 1, 2 ) == 1 );
    }
    {
        int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        assert( binarySearch( array, 8, 16 ) == 9 );
    }
    {
        int array[] = { 1, 2, 3, 4, 5, 4, 3, 2, 1 };
        assert( binarySearch( array, 4, 8 ) == 4 );
    }

    std::cout << "ALL BINARY SEARCH TESTS DONE" << std::endl;
}


void testLogic()
{
    {
        int array[] = { 1, 3, 5, 7, 9, 8, 6, 4, 2 };
        std::pair< int, int > borders = exponentialSearch( array, 9 );
        assert(binarySearch( array, borders.first, borders.second ) == 4 );
    }
    {
        int array[] = { 1, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        std::pair< int, int > borders = exponentialSearch( array, 10 );
        assert( binarySearch( array, borders.first, borders.second ) == 1 );
    }
    {
        int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        std::pair< int, int > borders = exponentialSearch( array, 19 );
        assert( binarySearch( array, borders.first, borders.second ) == 9 );
    }
    {
        int array[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
        std::pair< int, int > borders = exponentialSearch(array, 9);
        assert( binarySearch( array, borders.first, borders.second ) == 4 );
    }

    std::cout << "ALL TESTS DONE" << std::endl;
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

    delete A;

    return;
}


int main( int argc, const char *argv[] )
{
    run( std::cin, std::cout );
    //testExponentialSearch();
    //testBinarySearch();
    //testLogic();

    return 0;
}
