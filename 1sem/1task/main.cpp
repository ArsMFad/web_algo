#include <iostream>

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
}



int main(int argc, const char *argv[]) {

    return 0;
}
