/*
Группа людей называется современниками если был такой момент, когда
они могли собраться вместе. Для этого в этот момент каждому из них
должно было уже исполниться 18 лет, но ещё не исполниться 80 лет.

Дан список Жизни Великих Людей. Необходимо получить максимальное количество
современников. В день 18летия человек уже может принимать участие в собраниях,
а в день 80летия и в день смерти уже не может.

Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия.
В этих случаях принимать участие в собраниях он не мог. 
*/


#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>
#include <cstring>


struct PersonDate
{
    int id;
    int day;
    int month;
    int year;
    bool isDead;

    PersonDate() : id(0), day(0), month(0), year(0), isDead(false) {}

    PersonDate( int _id, int _day, int _month, int _year, int _isDead ) : id( _id ), day( _day ), month( _month ), year( _year ), isDead( _isDead ) {}
};


bool comparatorPersonDate(const struct PersonDate a, const struct PersonDate b)
{
    if ( a.year != b.year ) return a.year < b.year;
    if ( a.month != b.month ) return a.month < b.month;
    if ( a.day != b.day ) return a.day < b.day;

    return a.isDead < b.isDead;
}


template< typename T, typename Comparator>
void Merge( T* firstArr, int firstLen, T* secondArr, int secondLen, T* resultArr, Comparator comp )
{
    int firstIndex = 0;
    int secondIndex = 0;
    int resultIndex = 0;

    while(( firstIndex < firstLen ) && ( secondIndex < secondLen ))
    {
        if (comp(firstArr[ firstIndex ], secondArr[ secondIndex ]))
        {
            resultArr[ resultIndex++ ] = firstArr[ firstIndex ];
            ++firstIndex;
        } else
        {
            resultArr[ resultIndex++ ] = secondArr[ secondIndex ];
            ++secondIndex;
        }
    }

    while( firstIndex < firstLen )
    {
        resultArr[ resultIndex++ ] = firstArr[ firstIndex++ ];
    }

    while( secondIndex < secondLen )
    {
        resultArr[ resultIndex++ ] = secondArr[ secondIndex++ ];
    }
}


template< typename T, typename Comparator>
void MergeSort( T* arr, int len, Comparator comp )
{
    if ( len <= 1 ) return;

    int firstLen = len / 2;
    int secondLen = len - firstLen;

    MergeSort( arr, firstLen, comp );
    MergeSort( arr + firstLen, secondLen, comp );

    T* temp = new T[ len ];
    Merge( arr, firstLen, arr + firstLen, secondLen, temp, comp );

    memcpy( arr, temp, sizeof( T ) * len );

    delete[] temp;
}


void run( std::istream& in, std::ostream& out )
{
    int K;

    std::cin >> K;
    
    PersonDate* arr = new PersonDate[ K * 2 ];

    int j = 0;
    for( int i = 0; i < K; i++ )
    {
        int _day, _month, _year;

        std::cin >> _day >> _month >> _year;
        arr[j] = PersonDate( i, _day, _month, _year, 0 );
        ++j;

        std::cin >> _day >> _month >> _year;
        arr[j] = PersonDate( i, _day, _month, _year, 1 );
        ++j;
    }

    MergeSort( arr, K*2, comparatorPersonDate );

    int localResult = 0;
    int maxResult = 0;
    for( int i = 0; i < K*2; i++ )
    {
        if ( !arr[i].isDead ) ++localResult;
        else --localResult;

        maxResult = std::max( maxResult, localResult );
    }
    
    std::cout << maxResult << "\n";

    delete arr;
}


int main( int argc, const char *argv[] )
{
    run( std::cin, std::cout );
    return 0;
}
