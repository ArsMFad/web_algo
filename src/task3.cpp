/*

Реализовать дек с динамическим зацикленным буфером (на основе динамического массива).
Требования: Дек должен быть реализован в виде класса.

*/


#include <iostream>
#include <cassert>
#include <sstream>


class Deque
{
public:
    Deque()
    : buffer(nullptr), bufferSize(0), head(-1), tail(-1)
    {
    }

    Deque(const Deque &other) = delete; //prohibition of copying

    ~Deque()
    {
        delete buffer;
    }

    void pushFront(int x)
    {
        
    }

    void pushBack(int x)
    {
        if (tail + 1 == bufferSize) {
            upsize();
        }
        
        ++tail;
        buffer[tail] = x;
    }

    int popFront()
    {

    }

    int popBack()
    {

    }

    void upsize()
    {
        int *new_buffer = new int[(bufferSize + 1)*2];

        for (int i = head, j = 0; i != tail; i = (i + 1) % bufferSize, ++j)
        {
            new_buffer[j] = buffer[i];
        }
        if (tail != -1) {
            new_buffer[tail] = buffer[tail];
        }

        head = 0;

        delete buffer;
        buffer = new_buffer;
        
        bufferSize = (bufferSize+1)*2;
    }

    void printBuffer()
    {
        for (int i = 0; i < bufferSize; i++)
        {
            std::cout << buffer[i] << " ";
        }
        
        std::cout << std::endl << "\n";
    }
private:
    int * buffer;
    int bufferSize;

    int head;
    int tail;
};


int main(int argc, const char *argv[]) {
    Deque q;

    q.printBuffer();
    q.pushBack(1);
    q.printBuffer();
    q.pushBack(1);
    q.printBuffer();
    q.pushBack(1);
    q.printBuffer();
    q.pushBack(1);
    q.printBuffer();
    q.pushBack(1);
    q.printBuffer();
    q.pushBack(1);
    q.printBuffer();
    q.pushBack(1);
    q.printBuffer();
    q.pushBack(1);

    return 0;
}
