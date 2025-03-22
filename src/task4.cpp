/*

Напишите программу, которая использует кучу для слияния
K отсортированных массивов суммарной длиной N.

*/


#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>


template <typename T>
struct ArrayIterator
{
    T* buf;
    int size;
    int curPos;
};


template <typename T>
bool comparator(const struct ArrayIterator &v1, const struct ArrayIterator &v2)
{
    return v1.buf[v1.curPos] < v2.buf[v2.curPos];
}


template <typename T>
class Array
{
public:
    Array();
    ~Array();
    Array(const Array& _arr);

    T &operator[] ( int i );
    void Add( T element );

    T Last();
    void DeleteLast();

    bool IsEmpty();
    int Size();
private:
    T * buffer;
    int bufferSize;
    int actualSize;

    void upsize();
};

template <typename T>
Array<T>::Array()
{
    buffer = new T[0];
    bufferSize = 0;
    actualSize = 0;
}

template <typename T>
Array<T>::~Array()
{
    delete[] buffer;
}

template <typename T>
Array<T>::Array(const Array<T>& _arr)
{
    bufferSize = _arr.bufferSize;
    actualSize = _arr.actualSize;

    delete[] buffer;
    buffer = new T[bufferSize];

    for( int i = 0; i < actualSize; ++i )
        arr[i] = _arr[i];
}

template <typename T>
int Array<T>::Size()
{
    return bufferSize;
}

template <typename T>
T & Array<T>::operator[] ( int i )
{
    return buffer[i];
}

template <typename T>
void Array<T>::Add( T element )
{
    if (actualSize == bufferSize)
        upsize();
    
    buffer[actualSize++] = element;
}

template <typename T>
void Array<T>::upsize()
{
    bufferSize = (bufferSize == 0) ? 2 : bufferSize * 2;
    T* newBuffer = new int [ bufferSize ];

    std::copy( buffer, buffer + actualSize, newBuffer );

    delete [] buffer;
    buffer = newBuffer;
}

template <typename T>
bool Array<T>::IsEmpty()
{
    return actualSize == 0;
}

template <typename T>
T Array<T>::Last()
{
    return buffer[actualSize - 1];
}

template <typename T>
void Array<T>::DeleteLast()
{
    actualSize--;
}


template <typename T>
class Heap
{
public:
    Heap();
    ~Heap();
    explicit Heap( const Array<T>& _arr);

    void Insert( T element );

    int ExtractMax();
    int PeekMax() const;
private:
    Array<T> arr;

    void buildHeap();
    void siftDown( int i );
    void siftUp( int i );
};


template <typename T>
Heap<T>::Heap() {}

template <typename T>
Heap<T>::~Heap() {}

template <typename T>
Heap<T>::Heap( const Array<T>& _arr)
{
    arr = _arr;
}

template <typename T>
void Heap<T>::Insert( T element )
{
    arr.Add( element );
    siftUp( arr.Size() - 1 );
}

template <typename T>
int Heap<T>::ExtractMax()
{
    assert( !arr.IsEmpty() );

    int result = arr[0];
    arr[0] = arr.Last();
    arr.DeleteLast();

    if( !arr.IsEmpty() )
        siftDown( 0 );
    
    return result;
}

template <typename T>
int Heap<T>::PeekMax() const
{
    assert( !arr.IsEmpty() );
    return arr[0];
}

template <typename T>
void Heap<T>::buildHeap()
{
    for( int i = arr.Size() / 2 - 1; i >= 0; --i )
        siftDown(i);
}

template <typename T>
void Heap<T>::siftDown( int i )
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int largest = i;

    if (( left < arr.Size() ) && ( arr[left] > arr[i] ))
        largest = left;
    if (( right < arr.Size() ) && ( arr[right] > arr[largest] ))
        largest = right;
    
    if ( largest != i )
    {
        std::swap( arr[i], arr[largest] );
        siftDown( largest );
    }
}

template <typename T>
void Heap<T>::siftUp( int index )
{
    while( index > 0 )
    {
        int parent = ( index - 1 ) / 2;
        if( arr[index] <= arr[parent] )
            return;
        std::swap( arr[index], arr[parent] );
        index = parent;
    }
}


int main( int argc, const char *argv[] )
{
    Array<int> a1, a2, a3;
    a1.Add(6);
    a2.Add(50);
    a2.Add(90);
    a3.Add(1);
    a3.Add(10);
    a3.Add(70);

    Heap<Array<int>> h;

    h.Insert(a1);
    h.Insert(a2);
    h.Insert(a3);
    
    return 0;
}
