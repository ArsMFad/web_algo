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

    return a.isDead > b.isDead;
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


int solve( PersonDate* arr, int len )
{
    int localResult = 0;
    int maxResult = 0;

    for( int i = 0; i < len; i++ )
    {
        if ( arr[i].isDead ) --localResult;
        else ++localResult;

        maxResult = std::max( maxResult, localResult );
    }

    return maxResult;
}


void testLogic() {
    {
        PersonDate* arr = new PersonDate[2]
        {
            PersonDate( 0, 2, 5, 1998, false ),
            PersonDate( 0, 2, 5, 2060, true )
        };
        
        assert( arr[0].day == 2 && arr[0].month == 5 && arr[0].year == 1998 && !arr[0].isDead );
        assert( arr[1].day == 2 && arr[1].month == 5 && arr[1].year == 2060 && arr[1].isDead );
        delete[] arr;
    }
    {
        PersonDate* arr = new PersonDate[2]
        {
            PersonDate( 0, 1, 1, 2000, false ),
            PersonDate( 0, 1, 1, 2030, true )
        };
        
        assert( arr[0].day == 1 && arr[0].month == 1 && arr[0].year == 2000 && !arr[0].isDead );
        assert( arr[1].day == 1 && arr[1].month == 1 && arr[1].year == 2030 && arr[1].isDead );

        delete[] arr;
    }
    {
        PersonDate* arr = new PersonDate[2]
        {
            PersonDate( 0, 2, 1, 1938, false ),
            PersonDate( 0, 2, 1, 2000, true )
        };
        
        assert( arr[0].day == 2 && arr[0].month == 1 && arr[0].year == 1938 && !arr[0].isDead );
        assert( arr[1].day == 2 && arr[1].month == 1 && arr[1].year == 2000 && arr[1].isDead );

        delete[] arr;
    }
    {
        PersonDate* arr = new PersonDate[6]
        {
            PersonDate( 0, 2, 1, 1938, false ),
            PersonDate( 1, 1, 1, 2000, false ),
            PersonDate( 0, 2, 1, 2000, true ),
            PersonDate( 1, 1, 1, 2030, true ),
            PersonDate( 2, 2, 5, 1998, false ),
            PersonDate( 2, 2, 5, 2060, true )
        };
        
        MergeSort( arr, 6, comparatorPersonDate );
        
        assert( comparatorPersonDate(arr[0], arr[1]));
        assert( comparatorPersonDate(arr[1], arr[2]));
        assert( comparatorPersonDate(arr[2], arr[3]));
        assert( comparatorPersonDate(arr[3], arr[4]));
        assert( comparatorPersonDate(arr[4], arr[5]));
        
        delete[] arr;
    }
    {
        PersonDate* arr = new PersonDate[6]
        {
            PersonDate( 0, 2, 1, 1938, false ),
            PersonDate( 0, 2, 1, 2000, true ),
            
            PersonDate( 1, 1, 1, 2000, false ),
            PersonDate( 1, 1, 1, 2030, true ),
            
            PersonDate( 2, 2, 5, 1998, false ),
            PersonDate( 2, 2, 5, 2060, true )
        };
        
        MergeSort( arr, 6, comparatorPersonDate );
        
        assert( arr[0].year == 1938 && arr[0].month == 1 && arr[0].day == 2 );
        assert( arr[1].year == 1998 && arr[1].month == 5 && arr[1].day == 2 );
        assert( arr[2].year == 2000 && arr[2].month == 1 && arr[2].day == 1 );
        assert( arr[3].year == 2000 && arr[3].month == 1 && arr[3].day == 2 );
        assert( arr[4].year == 2030 && arr[4].month == 1 && arr[4].day == 1 );
        assert( arr[5].year == 2060 && arr[5].month == 5 && arr[5].day == 2 );
        
        int result = solve( arr, 6 );
        assert( result == 3 );
        
        delete[] arr;
    }
}


void run( std::istream& in, std::ostream& out )
{
    int K;

    in >> K;
    
    PersonDate* arr = new PersonDate[ K * 2 ];

    int j = 0;
    for( int i = 0; i < K; i++ )
    {
        int birthDay, birthMonth, birthYear;
        int deathDay, deathMonth, deathYear;

        in >> birthDay >> birthMonth >> birthYear;
        in >> deathDay >> deathMonth >> deathYear;

        int adultYear = birthYear + 18;
        int oldYear = birthYear + 80;

        bool reachedAdultYear = ( deathYear > adultYear ) ||
                                ( deathYear == adultYear && deathMonth > birthMonth ) ||
                                ( deathYear == adultYear && deathMonth == birthMonth && deathDay >= birthDay );

        bool didntReachedOldYear = ( deathYear < oldYear ) ||
                                   ( deathYear == oldYear && deathMonth < birthMonth ) ||
                                   ( deathYear == oldYear && deathMonth == birthMonth && deathDay < birthDay );
        
        if( !reachedAdultYear ) continue;
        arr[j++] = PersonDate( i, birthDay, birthMonth, adultYear, false );

        if ( didntReachedOldYear )
            arr[j++] = PersonDate( i, deathDay, deathMonth, deathYear, true );
        else
            arr[j++] = PersonDate( i, birthDay, birthMonth, oldYear, true );

    }

    MergeSort( arr, j, comparatorPersonDate );

    int result = solve( arr, j );
    
    std::cout << result << "\n";

    delete[] arr;
}


int main( int argc, const char *argv[] )
{
    run( std::cin, std::cout );
    //testLogic();
    return 0;
}
