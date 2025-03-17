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
        if (isEmpty()) return -1;

        int to_ret = buffer[head];

        fullof--;
        ++head;
        if (head >= bufferSize) head = 0;
        
        return to_ret;
    }

    int popBack()
    {
        if (isEmpty()) return -1;

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

    bool isFull()
    {
        return fullof > bufferSize;
    }

    bool isEmpty()
    {
        return !fullof;
    }
private:
    int * buffer;
    int bufferSize;
    int fullof;

    int head;
    int tail;
};


void checkIf(bool x) {
    if (x) std::cout << "YES\n";
    else std::cout << "NO\n";
}


int main(int argc, const char *argv[]) {
    Deque q;

    int sampleCounter;
    int stateOfTask = 1;
    std::cin >> sampleCounter;

    while(sampleCounter--)
    {
        int cmd;
        int num;
        std::cin >> cmd >> num;

        switch (cmd)
        {
        case 1:
            q.pushFront(num);
            break;
        case 2:
            if (q.popFront() != num) stateOfTask = 0;
            break;
        case 3:
            q.pushBack(num);
            break;
        case 4:
            if (q.popBack() != num) stateOfTask = 0;
            break;
        
        default:
            break;
        }
    }

    if (stateOfTask) std::cout << "YES" << std::endl;
    else std::cout << "NO" << std::endl;

    return 0;
}
