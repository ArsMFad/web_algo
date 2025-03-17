/*

Реализовать дек с динамическим зацикленным буфером (на основе динамического массива).
Требования: Дек должен быть реализован в виде класса.

*/


#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>


class Deque
{
public:
    Deque()
    : buffer( nullptr ), bufferSize( 0 ), actualSize( 0 ), head( -1 ), tail( -1 )
    {
    }

    Deque( const Deque &other ) = delete; //prohibition of copying

    ~Deque()
    {
        delete [] buffer;
        buffer = nullptr;
    }

    void pushFront( int x )
    {
        if( isFull() )
        {
            upsize();
            --head;
            if( head < 0 )
                head = bufferSize - 1;
        } else if( isEmpty() )
        {
            upsize();
        } else {
            --head;
            if( head < 0 )
                head = bufferSize - 1;
        }

        ++actualSize;
        buffer[ head ] = x;
    }

    void pushBack( int x )
    {
        if( isFull() ) {
            upsize();
            ++tail;
            if( tail >= bufferSize )
                tail = 0;
        } else if ( isEmpty() ) {
            upsize();
        } else {
            ++tail;
            if( tail >= bufferSize )
                tail = 0;
        }

        ++actualSize;
        buffer[tail] = x;
    }

    int popFront()
    {
        if( isEmpty() )
            return -1;

        int to_ret = buffer[ head ];
        buffer[ head ] = -1;

        --actualSize;
        ++head;

        if( head >= bufferSize )
            head = 0;
        
        return to_ret;
    }

    int popBack()
    {
        if( isEmpty() )
            return -1;

        int to_ret = buffer[ tail ];
        buffer[ tail ] = -1;

        --actualSize;
        --tail;

        if( tail < 0 )
            tail = bufferSize - 1;

        return to_ret;
    }

    void upsize()
    {
        int newBufferSize;

        if( bufferSize == 0 )
        {
            newBufferSize = 10;
        } else
        {
            newBufferSize *= 2;
            newBufferSize = std::max( 1000000, newBufferSize );
        }

        int *new_buffer = new int [ newBufferSize ];

        int j = 0;
        for( int i = head; i != tail; i = ( i + 1 ) % bufferSize, ++j )
        {
            new_buffer[j] = buffer[i];
        }

        if( tail != -1 ) {
            new_buffer[j] = buffer[ tail ];
        }


        delete[] buffer;
        buffer = nullptr;

        head = 0;
        if( actualSize == 0 ) tail = 0;
        else tail = actualSize - 1;
        
        buffer = new_buffer;
        bufferSize = newBufferSize;
    }

    void printBuffer()
    {
        for( int i = 0; i < bufferSize; i++ )
        {
            std::cout << buffer[i] << " ";
        }
        
        std::cout << std::endl << "\n";
    }

    bool isFull()
    {
        return ( actualSize == bufferSize ) && ( actualSize != 0 );
    }

    bool isEmpty()
    {
        return !actualSize;
    }
    
private:
    int * buffer;
    int bufferSize;
    int actualSize;

    int head;
    int tail;
};


void checkIf( bool x ) {
    if ( x )
        std::cout << "YES\n";
    else
        std::cout << "NO\n";
}



void run( std::istream & in, std::ostream & out )
{
    Deque q;

    int sampleCounter;
    int stateOfTask = 1;
    in >> sampleCounter;

    int cmd;
    int num;
    while( sampleCounter-- )
    {
        in >> cmd >> num;

        switch( cmd )
        {
        case 1:
            q.pushFront( num );
            break;
        case 2:
            if ( q.popFront() != num ) stateOfTask = 0;
            break;
        case 3:
            q.pushBack( num );
            break;
        case 4:
            if ( q.popBack() != num ) stateOfTask = 0;
            break;
        
        default:
            break;
        }
    }

    if ( stateOfTask )
        out << "YES" << std::endl;
    else
        out << "NO" << std::endl;
}

/*
void testLogic() {
    {
        Deque q;

        for (int i = 0; i < 1000000; i++)
        {
            if (i % 100000 == 0) {
                std::cout << sizeof(q.buffer) << "\n";
            }
            q.pushBack(1);
        }
        std::cout << "\n\n";
        
    }
    {
        Deque q;
        q.pushFront(1);
        q.printBuffer(); // 1
        q.pushFront(2);
        q.printBuffer(); // 2 1
        q.pushBack(5);
        q.printBuffer(); // 2 1 5
        q.pushBack(4);
        q.printBuffer(); // 2 1 5 4
        q.pushFront(3);
        q.printBuffer(); // 3 2 1 5 4

        assert(q.popFront() == 3);
        assert(q.popBack() == 4);
        assert(q.popFront() == 2);
        assert(q.popBack() == 5);
        assert(q.popBack() == 1);
        assert(q.popBack() == -1); // Дек пуст
        q.pushBack(3);
        assert(q.popBack() == 3);
    }
    {
        Deque q;
        q.pushBack(10);
        assert(q.popFront() == 10);
    }
    {
        Deque q;
        q.pushFront(1);
        q.pushFront(2);
        q.pushBack(3);
        q.pushBack(4);
        assert(q.popFront() == 2);
        assert(q.popBack() == 4);
        assert(q.popFront() == 1);
        assert(q.popBack() == 3);
        assert(q.popFront() == -1); // Дек пуст
    }
    {
        std::cout<<"\n\n\n";
        Deque q;
        q.pushBack(1);
        q.printBuffer();
        q.pushBack(2);
        q.printBuffer();
        q.pushFront(3);
        q.printBuffer();
        q.pushFront(4);
        q.printBuffer();
        assert(q.popBack() == 2);
        assert(q.popFront() == 4);
        assert(q.popBack() == 1);
        assert(q.popFront() == 3);
        assert(q.popBack() == -1); // Дек пуст
    }
    {
        Deque q;
        assert(q.popFront() == -1); // Дек пуст
        assert(q.popBack() == -1);  // Дек пуст
        q.pushFront(1);
        assert(q.popBack() == 1);
        q.pushBack(2);
        assert(q.popFront() == 2);
    }
}
*/

int main( int argc, const char *argv[] )
{
    run( std::cin, std::cout );
    //testLogic();
    return 0;
}
