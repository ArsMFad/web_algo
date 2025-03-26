/*
Дан массив строк. Количество строк не больше 105.
Отсортировать массив методом поразрядной сортировки MSD по символам.
Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
*/



#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>


template< typename T >
class Array
{
public:
    Array();
    Array( int _bufferSize );
    ~Array();

    T& operator[]( int i );
    const T& operator[]( int i ) const;

    void Add( T element );

    bool IsEmpty() const;
    int Size() const;
private:
    T * buffer;
    int bufferSize;
    int actualSize;

    void upsize();
};

template< typename T >
Array<T>::Array() : buffer( nullptr ), bufferSize( 0 ), actualSize( 0 ) {}

template< typename T >
Array<T>::Array( int _bufferSize ) : buffer( nullptr ), bufferSize( _bufferSize ), actualSize( 0 )
{
    bufferSize = _bufferSize;
    T* newBuffer = new T[ bufferSize ];

    delete[] buffer;
    buffer = newBuffer;
}

template< typename T >
Array<T>::~Array()
{
    delete[] buffer;
}

template< typename T >
T& Array<T>::operator[]( int i )
{
    return buffer[i];
}

template< typename T >
const T& Array<T>::operator[]( int i ) const
{
    return buffer[i];
}

template< typename T >
void Array<T>::Add( T element )
{
    if( actualSize == bufferSize )
        upsize();
    
    buffer[ actualSize++ ] = element;
}

template< typename T >
int Array<T>::Size() const
{
    return actualSize;
}

template< typename T >
bool Array<T>::IsEmpty() const
{
    return actualSize == 0;
}

template< typename T >
void Array<T>::upsize()
{
    bufferSize = ( bufferSize == 0 ) ? 2 : bufferSize * 2;
    T* newBuffer = new T[ bufferSize ];

    std::copy( buffer, buffer + actualSize, newBuffer );

    delete [] buffer;
    buffer = newBuffer;
}


void msdSort( Array< std::string >& strings, int start, int n, int pos )
{
    if( n <= 1 ) return;

    const int ALPHABET_SIZE = 257;
    Array< Array< std::string >> buckets( ALPHABET_SIZE );

    for( int i = start; i < start + n; ++i )
    {
        unsigned char c = ( pos < strings[i].size() ) ? strings[i][pos] : '\0';
        buckets[c].Add( strings[i] );
    }

    int index = start;
    for( int c = 0; c < ALPHABET_SIZE; ++c )
    {
        int bucket_size = buckets[c].Size();
        if( bucket_size > 0 )
        {
            for( int i = 0; i < bucket_size; ++i )
                strings[index++] = buckets[c][i];
            
            if( c > 0 && bucket_size > 1 )
                msdSort( strings, index - bucket_size, bucket_size, pos + 1 );
        }
    }
}


void run( std::istream& in, std::ostream& out )
{
    Array< std::string > strings;

    std::string toInput;
    while (std::cin >> toInput) {
        strings.Add(toInput);
    }
    
    msdSort( strings, 0, strings.Size(), 0 );
    
    for( int i = 0; i < strings.Size(); ++i ) {
        std::cout << strings[i] << "\n";
    }
}


void testLogic() {
    {
        Array<std::string> empty;
        msdSort(empty, 0, empty.Size(), 0);
        assert(empty.Size() == 0);
    }
    {
        Array<std::string> identical;
        identical.Add("zzz");
        identical.Add("zzz");
        identical.Add("zzz");
        msdSort(identical, 0, identical.Size(), 0);
        assert(identical[0] == "zzz" && identical[1] == "zzz" && identical[2] == "zzz");
    }
    {
        Array<std::string> normal;
        normal.Add("banana");
        normal.Add("apple");
        normal.Add("cherry");
        normal.Add("apple");
        msdSort(normal, 0, normal.Size(), 0);
        assert(normal[0] == "apple");
        assert(normal[1] == "apple");
        assert(normal[2] == "banana");
        assert(normal[3] == "cherry");
    }
    {
        Array<std::string> diff_length;
        diff_length.Add("a");
        diff_length.Add("");
        diff_length.Add("aaa");
        diff_length.Add("aa");
        msdSort(diff_length, 0, diff_length.Size(), 0);
        assert(diff_length[0] == "");
        assert(diff_length[1] == "a");
        assert(diff_length[2] == "aa");
        assert(diff_length[3] == "aaa");
    }
}


int main() {
    run(std::cin, std::cout);
    //testLogic();

    return 0;
}
