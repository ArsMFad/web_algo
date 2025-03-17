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
    : buffer(nullptr), bufferSize(0), fullof(0), head(-1), tail(-1)
    {
    }

    Deque(const Deque &other) = delete; //prohibition of copying

    ~Deque()
    {
        delete buffer;
    }

    void pushFront(int x)
    {
        ++fullof;
        if (isFull()) upsize();
        head--;
        if (head < 0) head = bufferSize - 1;
        buffer[head] = x;
    }

    void pushBack(int x)
    {
        fullof++;
        if (isFull()) upsize();
        ++tail;
        if (tail >= bufferSize) tail = 0;
        buffer[tail] = x;
    }

    int popFront()
    {
        int to_ret = buffer[head];

        fullof--;
        ++head;
        if (head >= bufferSize) head = 0;
        
        return to_ret;
    }

    int popBack()
    {
        int to_ret = buffer[tail];
        fullof--;
        --tail;
        if (tail < 0) tail = bufferSize - 1;

        return to_ret;
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

    bool isFull() {
        return fullof > bufferSize;
    }
private:
    int * buffer;
    int bufferSize;
    int fullof;

    int head;
    int tail;
};


int main(int argc, const char *argv[]) {
    Deque q;

    q.printBuffer();
    q.pushBack(1);
    q.printBuffer();
    q.pushBack(2);
    q.pushBack(3);
    q.pushBack(4);
    q.pushBack(5);
    q.printBuffer();
    q.popFront();
    q.pushFront(6);
    q.printBuffer();
    q.pushFront(7);
    q.printBuffer();
    q.popBack();
    q.printBuffer();
    q.pushBack(10);
    q.printBuffer();

    return 0;
}
