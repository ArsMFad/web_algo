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
        if (buffer) delete[] buffer;
    }

    void pushFront(int x)
    {
        if (isFull())
        {
            upsize();
            head--;
            if (head < 0) head = bufferSize - 1;
        } else if (isEmpty())
        {
            upsize();
        } else {
            --head;
            if (head < 0) head = bufferSize - 1;
        }
        ++fullof;
        buffer[head] = x;
    }

    void pushBack(int x)
    {
        if (isFull()) {
            upsize();
            ++tail;
            if (tail >= bufferSize) tail = 0;
        } else if (isEmpty()) {
            upsize();
        } else {
            ++tail;
            if (tail >= bufferSize) tail = 0;
        }
        fullof++;
        buffer[tail] = x;
    }

    int popFront()
    {
        if (isEmpty()) return -1;

        int to_ret = buffer[head];
        buffer[head] = -1;

        fullof--;
        ++head;
        if (head >= bufferSize) head = 0;
        
        return to_ret;
    }

    int popBack()
    {
        if (isEmpty()) return -1;

        int to_ret = buffer[tail];
        buffer[tail] = -1;
        fullof--;
        --tail;
        if (tail < 0) tail = bufferSize - 1;

        return to_ret;
    }

    void upsize()
    {
        int *new_buffer = new int[(bufferSize + 1)*2];
        int j = 0;
        for (int i = head; i != tail; i = (i + 1) % bufferSize, ++j)
        {
            new_buffer[j] = buffer[i];
        }

        if (tail != -1) {
            new_buffer[j] = buffer[tail];
        }

        head = 0;
        if (fullof == 0) tail = 0;
        else tail = fullof - 1;

        delete[] buffer;
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
        return (fullof == bufferSize) && (fullof != 0);
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



void run(std::istream & in, std::ostream & out)
{
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
        //q.printBuffer();
    }

    if (stateOfTask) std::cout << "YES" << std::endl;
    else std::cout << "NO" << std::endl;
}


void testLogic() {
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

int main(int argc, const char *argv[]) {
    run(std::cin, std::cout);
    //testLogic();
    return 0;
}
