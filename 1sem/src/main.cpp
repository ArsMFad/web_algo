#include <iostream>
#include <cassert>
#include <sstream>

struct Node
{
    Node(int data)
    : data(data), next(nullptr)
    {
    }

    int data;
    Node *next;
};


class Queue
{
public:
    Queue()
    : head(nullptr), tail(nullptr)
    {
    }

    Queue(const Queue &other) = delete; //prohibition of copying

    ~Queue()
    {
        while(!IsEmpty())
            Dequeu();
    }

    void Enqueue(int data)
    {
        Node *node = new Node(data);
        if (IsEmpty())
        {
            head = tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }

    int Dequeu()
    {
        if (IsEmpty())
            return -1;

        int tmpData = head->data;
        Node *tmpNode = head;

        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }

        delete tmpNode;
        return tmpData;
    }

    bool IsEmpty()
    {
        return head == nullptr && tail == nullptr;
    };
private:
    Node *head, *tail;
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
