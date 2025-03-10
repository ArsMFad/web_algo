/*

Вернуть значение бита в числе N по его номеру K.
Позиции битов нумеруются с 0.

Необходимо использование битовых операций.
Использование арифметических операций запрещено.

*/


#include <iostream>
#include <sstream>
#include <cassert>


//Complexity O(1)
bool findBitByPosition(unsigned long X, unsigned long pos)
{
    return (1 & (X >> pos));
}


//Naive realization of algorithm
bool testFunc(unsigned long X, unsigned long pos)
{
    bool result = X % 2;

    while(pos--) {
        X /= 2;
        result = X % 2;
    }

    return result;
}


void testLogic()
{
    assert(testFunc(1, 0) == findBitByPosition(1, 0));
    assert(testFunc(1, 1) == findBitByPosition(1, 1));
    assert(testFunc(25, 2) == findBitByPosition(25, 2));
    assert(testFunc(25, 3) == findBitByPosition(25, 3));
    assert(testFunc(100, 6) == findBitByPosition(100, 6));
    assert(testFunc(102340, 7) == findBitByPosition(102340, 7));
    assert(testFunc(4294967295, 30) == findBitByPosition(4294967295, 30));

    std::cout << "TESTS ALL DONE\n";
}


void run(std::istream &in, std::ostream &out)
{
    unsigned long N, K;

    in >> N >> K;

    out << findBitByPosition(N, K) << "\n";

    return;
}


int main(int argc, const char *argv[])
{
    run(std::cin, std::cout);
    //testLogic();

    return 0;
}
