/*

Реализовать дек с динамическим зацикленным буфером (на основе динамического массива).
Требования: Дек должен быть реализован в виде класса.

*/


#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>


class Deque {
public:
    Deque()
        : buffer( nullptr ), bufferSize( 0 ), actualSize( 0 ), head( -1 ), tail( -1 )
    {
    }

    ~Deque()
    {
        delete[] buffer;
    }

    void pushFront( int x )
    {
        if( isFull() )
            upsize();

        if( isEmpty() )
        {
            head = 0;
            tail = 0;
        } else
        {
            head = ( head - 1 + bufferSize ) % bufferSize;
        }

        buffer[ head ] = x;
        ++actualSize;
    }

    void pushBack( int x ) {
        if(isFull())
            upsize();

        if( isEmpty() )
        {
            head = 0;
            tail = 0;
        } else
        {
            tail = ( tail + 1 ) % bufferSize;
        }

        buffer[ tail ] = x;
        ++actualSize;
    }

    int popFront()
    {
        if( isEmpty() )
            return -1;

        int to_ret = buffer[ head ];

        --actualSize;
        if( isEmpty() )
        {
            head = -1;
            tail = -1;
        } else {
            head = ( head + 1 ) % bufferSize;
        }

        return to_ret;
    }

    int popBack()
    {
        if( isEmpty() )
        {
            return -1;
        }

        int to_ret = buffer[ tail ];

        --actualSize;
        if( isEmpty() )
        {
            head = -1;
            tail = -1;
        } else
        {
            tail = (tail - 1 + bufferSize) % bufferSize;
        }

        return to_ret;
    }

    void upsize()
    {
        int newBufferSize = ( bufferSize == 0 ) ? 2 : bufferSize * 2;
        newBufferSize = std::min( newBufferSize, 1000000 );

        int* newBuffer = new int[ newBufferSize ];

        if( !isEmpty() )
        {
            if( head <= tail )
            {
                std::copy( buffer + head, buffer + tail + 1, newBuffer );
            } else
            {
                std::copy( buffer + head, buffer + bufferSize, newBuffer );
                std::copy( buffer, buffer + tail + 1, newBuffer + ( bufferSize - head ));
            }
        }

        delete [] buffer;
        buffer = newBuffer;

        if( !isEmpty() )
        {
            head = 0;
            tail = actualSize - 1;
        } else
        {
            head = -1;
            tail = -1;
        }

        bufferSize = newBufferSize;
    }

    void printBuffer() const
    {
        for( int i = 0; i < bufferSize; ++i )
        {
            std::cout << buffer[i] << " ";
        }
        std::cout << std::endl;
    }

    bool isFull() const
    {
        return actualSize == bufferSize;
    }

    bool isEmpty() const
    {
        return actualSize == 0;
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
        out << "YES\n";
    else
        out << "NO\n";
}


void testLogic() {
    {
        Deque q;

        for (int i = 0; i < 1000000; i++)
        {
            q.pushBack(1);
        }
    }
    {
        Deque q;
        q.pushFront(1);
        q.pushFront(2);
        q.pushBack(5);
        q.pushBack(4);
        q.pushFront(3);

        assert(q.popFront() == 3);
        assert(q.popBack() == 4);
        assert(q.popFront() == 2);
        assert(q.popBack() == 5);
        assert(q.popBack() == 1);
        assert(q.popBack() == -1);
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
        assert(q.popFront() == -1);
    }
    {
        Deque q;
        q.pushBack(1);
        q.pushBack(2);
        q.pushFront(3);
        q.pushFront(4);
        assert(q.popBack() == 2);
        assert(q.popFront() == 4);
        assert(q.popBack() == 1);
        assert(q.popFront() == 3);
        assert(q.popBack() == -1);
    }
    {
        Deque q;
        assert(q.popFront() == -1);
        assert(q.popBack() == -1);
        q.pushFront(1);
        assert(q.popBack() == 1);
        q.pushBack(2);
        assert(q.popFront() == 2);
    }
    {
        Deque q;
        q.pushFront(1);
        q.pushFront(2);
        q.pushBack(5);
        q.pushBack(4);
        q.pushFront(3);

        assert(q.popFront() == 3);
        assert(q.popBack() == 4);
        assert(q.popFront() == 2);
        assert(q.popBack() == 5);
        assert(q.popBack() == 1);
        assert(q.popBack() == -1);
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
        assert(q.popFront() == -1);
    }
    {
        Deque q;
        q.pushBack(1);
        q.pushBack(2);
        q.pushFront(3);
        q.pushFront(4);
        assert(q.popBack() == 2);
        assert(q.popFront() == 4);
        assert(q.popBack() == 1);
        assert(q.popFront() == 3);
        assert(q.popBack() == -1);
    }
    {
        Deque q;
        assert(q.popFront() == -1);
        assert(q.popBack() == -1);
        q.pushFront(1);
        assert(q.popBack() == 1);
        q.pushBack(2);
        assert(q.popFront() == 2);
    }
    {
        Deque q;
        for (int i = 0; i < 101; ++i) {
            q.pushFront(i);
        }
        for (int i = 100; i >= 0; --i) {
            assert(q.popFront() == i);
        }
        assert(q.popFront() == -1);
    }
    {
        Deque q;
        q.pushBack(1);
        q.pushFront(2);
        q.pushBack(3);
        q.pushFront(4);
        assert(q.popFront() == 4);
        assert(q.popBack() == 3);
        assert(q.popFront() == 2);
        assert(q.popBack() == 1);
        assert(q.popFront() == -1);
    }
    {
        Deque q;
        q.pushFront(1);
        q.pushBack(2);
        q.pushFront(3);
        q.pushBack(4);
        assert(q.popFront() == 3);
        assert(q.popBack() == 4);
        q.pushFront(5);
        q.pushBack(6);
        assert(q.popFront() == 5);
        assert(q.popBack() == 6);
        assert(q.popFront() == 1);
        assert(q.popBack() == 2);
        assert(q.popFront() == -1);
    }
    {
        Deque q;
        q.pushFront(1);
        q.pushBack(2);
        assert(q.popFront() == 1);
        assert(q.popBack() == 2);
        assert(q.popFront() == -1);
        assert(q.popBack() == -1);
        q.pushBack(3);
        assert(q.popFront() == 3);
    }
    {
        Deque q;
        q.pushFront(42);
        assert(q.popBack() == 42);
        assert(q.popFront() == -1);
        q.pushBack(100);
        assert(q.popFront() == 100);
        assert(q.popBack() == -1);
    }
    {
        Deque q;
        for (int i = 0; i < 10000; ++i) {
            q.pushFront(i);
            q.pushBack(i);
        }
        for (int i = 9999; i >= 0; --i) {
            assert(q.popFront() == i);
            assert(q.popBack() == i);
        }
        assert(q.popFront() == -1);
        assert(q.popBack() == -1);
    }
}


int main( int argc, const char *argv[] )
{
    run( std::cin, std::cout );
//    testLogic();
    return 0;
}
