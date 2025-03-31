/*

ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!

Пара слов называется стековой анаграмой, если одно слово можно получить из другого,
проведя последовательность стековых операций с его буквами (взять очередную букву
исходного слова и поместить ее в стек; взять букву из стека и добавить ее в конец
выходного слова). Для заданной пары слов требуется определить, можно ли выполнить
последовательность стековых операций, переводящую первое слово во второе. Все буквы
в слове различные. Длина анаграммы ≤ 10000.

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

    void pushBack( char x ) {
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

    char Front()
    {
        return buffer[ head ];
    }

    char popFront()
    {
        if( isEmpty() )
            return -1;

        char to_ret = buffer[ head ];

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

    char Back()
    {
        return buffer[ tail ];
    }

    char popBack()
    {
        if( isEmpty() )
        {
            return -1;
        }

        char to_ret = buffer[ tail ];

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

        char* newBuffer = new char[ newBufferSize ];

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
    char * buffer;
    int bufferSize;
    int actualSize;

    int head;
    int tail;
};


void run( std::istream & in, std::ostream & out )
{
    std::string s1, s2;

    in >> s1;
    in >> s2;

    Deque stackWord;

    int counter = 0;

    for (char c : s1)
    {
        stackWord.pushBack(c);

        while(!stackWord.isEmpty() && stackWord.Back() == s2[counter])
        {
            stackWord.popBack();
            ++counter;
        }
    }

    if (stackWord.isEmpty())
        out << "YES\n";
    else
        out << "NO\n";
}


int main( int argc, const char *argv[] )
{
    run( std::cin, std::cout );

    return 0;
}
