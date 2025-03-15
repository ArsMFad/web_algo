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

    }

    int popFront()
    {

    }

    int popBack()
    {

    }

    void upsize()
    {
        int *new_buffer = new int[bufferSize*2];

        for (int i = head, j = 0; i !=tail; i++)
        {
            new_buffer[j] = buffer[i];
        }
        
    }
private:
    int * buffer;
    int bufferSize;

    int head;
    int tail;
};


void testLogic()
{
    Queue queue;
    int sampleCount = 100;

    assert(queue.IsEmpty());

    for (int i = 0; i < sampleCount; i++)
        queue.Enqueue(i);

    assert(!queue.IsEmpty());

    for (int i = 0; i < sampleCount; i++)
        assert(i == queue.Dequeu());
    
    assert(queue.IsEmpty());
}


void run(std::istream &input, std::ostream &output)
{
    Queue queue;

    int n = 0;
    input >> n;

    for (int i = 0; i < n; i++)
    {
        int op = 0, val = 0;
        input >> op >> val;

        switch (op)
        {
            case 2:
            {
                int tmpVal = queue.Dequeu();
                if (tmpVal != val)
                {
                    output << "NO" << std::endl;
                    return;
                }
                break;
            }
            case 3:
            {
                queue.Enqueue(val);
                break;
            }
            default:
                break;
        }
    }

    std::cout << "YES" << std::endl;
    
    return;
}


void testQueue()
{
    {
    std::stringstream input, output;
    input << "3" << std::endl;
    input << "3 111" << std::endl;
    input << "2 111" << std::endl;
    input << "3 222" << std::endl;
    run(input, output);
    assert(output.str() == "YES\n");
    }
    {
    std::stringstream input, output;
    input << "3" << std::endl;
    input << "3 111" << std::endl;
    input << "2 222" << std::endl;
    input << "3 222" << std::endl;
    run(input, output);
    assert(output.str() == "NO\n");
    }
}


int main(int argc, const char *argv[]) {
    run(std::cin, std::cout);

    //testLogic();
    return 0;
}
