/*

Напишите программу, которая использует кучу для слияния
K отсортированных массивов суммарной длиной N.

*/


#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>


template <typename T>
class Array
{
public:
    Array();
    ~Array();

    T& operator[]( int i );
    const T& operator[]( int i ) const;

    void Add( T element );

    T Last() const;
    void DeleteLast();

    bool IsEmpty() const;
    int Size() const;
private:
    T * buffer;
    int bufferSize;
    int actualSize;

    void upsize();
};

template <typename T>
Array<T>::Array() : buffer(nullptr), bufferSize(0), actualSize(0) {}

template <typename T>
Array<T>::~Array()
{
    delete[] buffer;
}

template <typename T>
T& Array<T>::operator[]( int i )
{
    return buffer[i];
}

template <typename T>
const T& Array<T>::operator[]( int i ) const
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
T Array<T>::Last() const
{
    return buffer[actualSize - 1];
}

template <typename T>
void Array<T>::DeleteLast()
{
    assert( actualSize > 0 );
    actualSize--;
}

template <typename T>
int Array<T>::Size() const
{
    return actualSize;
}

template <typename T>
bool Array<T>::IsEmpty() const
{
    return actualSize == 0;
}

template <typename T>
void Array<T>::upsize()
{
    bufferSize = (bufferSize == 0) ? 2 : bufferSize * 2;
    T* newBuffer = new T[ bufferSize ];

    std::copy( buffer, buffer + actualSize, newBuffer );

    delete [] buffer;
    buffer = newBuffer;
}


template <typename T>
struct ArrayIterator
{
    Array<T> *buffer;
    int curPos;

    T Value() const
    {
        return (*buffer)[curPos];
    }

    bool HasNext() const
    {
        return curPos + 1 < buffer->Size();
    }

    ArrayIterator Next() const
    {
        return {buffer, curPos + 1};
    }
};


template <typename T, typename Comparator = std::less<T>>
class Heap
{
public:
    Heap();
    Heap(Comparator _comp);
    ~Heap();

    void Insert( const ArrayIterator<T>& element );

    ArrayIterator<T> ExtractMin();
    ArrayIterator<T> PeekMin() const;

    bool IsEmpty() const;
private:
    Array<ArrayIterator<T>> arr;
    Comparator comp;

    void siftDown( int i );
    void siftUp( int i );
};


template <typename T, typename Comparator>
Heap<T, Comparator>::Heap() : comp(Comparator()) {}

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(Comparator _comp) : comp(_comp) {}

template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap() {}


template <typename T, typename Comparator>
void Heap<T, Comparator>::Insert( const ArrayIterator<T>& element )
{
    arr.Add( element );
    siftUp( arr.Size() - 1 );
}

template <typename T, typename Comparator>
ArrayIterator<T> Heap<T, Comparator>::ExtractMin()
{
    assert( !arr.IsEmpty() );

    ArrayIterator<T> result = arr[0];
    arr[0] = arr.Last();
    arr.DeleteLast();

    if( !arr.IsEmpty() )
        siftDown( 0 );
    
    return result;
}

template <typename T, typename Comparator>
ArrayIterator<T> Heap<T, Comparator>::PeekMin() const
{
    assert( !arr.IsEmpty() );
    return arr[0];
}

template <typename T, typename Comparator>
bool Heap<T, Comparator>::IsEmpty() const {
    return arr.IsEmpty();
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftDown( int i )
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int smallest = i;

    if (( left < arr.Size() ) && comp( arr[ left ].Value(), arr[ smallest ].Value() ))
        smallest = left;
    if (( right < arr.Size() ) && comp( arr[ right ].Value(), arr[ smallest ].Value() ))
        smallest = right;
    
    if ( smallest != i )
    {
        std::swap( arr[i], arr[smallest] );
        siftDown( smallest );
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftUp( int index )
{
    while( index > 0 )
    {
        int parent = ( index - 1 ) / 2;
        if( comp( arr[ index ].Value(), arr[ parent ].Value() ))
        {
            std::swap( arr[ index ], arr[ parent ] );
            index = parent;
        } else
            break;
    }
}


template <typename T, typename Comparator>
Array<T> mergeKSortedArrays(const Array<Array<T>*>& arrays, Comparator comp) {
    Heap<T, Comparator> heap(comp);
    Array<T> result;

    for (int i = 0; i < arrays.Size(); ++i) {
        if (!arrays[i]->IsEmpty()) {
            ArrayIterator<T> iterator;
            iterator.buffer = arrays[i];
            iterator.curPos = 0;
            heap.Insert(iterator);
        }
    }

    while (!heap.IsEmpty()) {
        ArrayIterator<T> minElement = heap.ExtractMin();
        result.Add(minElement.Value());

        if (minElement.HasNext()) {
            heap.Insert(minElement.Next());
        }
    }

    return result;
}


void run(std::istream& in, std::ostream& out)
{
    int K;
    in >> K;

    Array<Array<int>*> arrays;
    while( K-- )
    {
        int size;
        in >> size;

        Array<int> *arr = new Array<int>();
        for ( int j = 0; j < size; j++ )
        {
            int element;
            in >> element;
            arr->Add(element);
        }
        arrays.Add(arr);
    }

    Heap<int> heap;
    for (int i = 0; i < arrays.Size(); i++)
    {
        if( !arrays[i]->IsEmpty() )
        {
            ArrayIterator<int> it;
            it.buffer = arrays[i];
            it.curPos = 0;
            heap.Insert(it);
        }
    }

    Array<int> result;

    while( !heap.IsEmpty() )
    {
        ArrayIterator<int> min = heap.ExtractMin();
        result.Add(min.Value());

        if ( min.HasNext() )
        {
            heap.Insert( min.Next() );
        }
    }

    for ( int i = 0; i < result.Size(); i++ )
    {
        out << result[i] << " ";
    }
    out << "\n";
    

    for( int i = 0; i < arrays.Size(); ++i )
        delete arrays[i];
}


int main( int argc, const char *argv[] )
{
    run(std::cin, std::cout);
    //testLogic();
    
    return 0;
}
