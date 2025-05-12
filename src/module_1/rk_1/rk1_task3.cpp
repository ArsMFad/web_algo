/*

На склад привезли много пустых ящиков. Все ящики пронумерованы по порядку
поступления от 0.
Известно, что их все можно сложить один в один (то есть так, что каждый
следующий помещается в предыдущий). Один ящик можно вложить в другой, если
его можно перевернуть так, что размеры одного ящика по всем осям станут
строго меньше размеров другого ящика по соответствующим осям.
Требуется определить, в какой последовательности они будут вложены друг в
друга. Вывести номера ящиков.

Для сортировки точек реализуйте алгоритм сортировки вставками.
Максимальное кол-во 10000. 

*/

#include<iostream>


struct Box
{
    int x;
    int y;
    int z;

    int id;

    Box() : x(0), y(0), z(0), id(0) {}
};


bool cmp(const Box a, const Box b)
{
    if (a.x != b.x) return a.x > b.x;
    if (a.y != b.y) return a.y > b.y;
    return a.z > b.z;
}


void threeIntSort(Box &box)
{
    if (box.x > box.y) std::swap(box.x, box.y);
    if (box.y > box.z) std::swap(box.y, box.z);
    if (box.x > box.y) std::swap(box.x, box.y);
}


void IntensionSort(struct Box *array, int n)
{
    for (int i = 1; i < n; i++)
    {
        struct Box toComp = array[i];
        int j = i - 1;

        while(j >= 0 && cmp(array[j], toComp))
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = toComp;
    }
}


void run(std::istream &in, std::ostream &out)
{
    int n;
    struct Box *A;

    in >> n;

    A = new struct Box[n];
    for (int i = 0; i < n; i++) {
        in >> A[i].x >> A[i].y >> A[i].z;
        A[i].id = i;

        threeIntSort(A[i]);
    }

    IntensionSort(A, n);

    for (int i = 0; i < n; i++)
    {
        out << A[i].id << " ";
    }
    out << "\n";

    delete[] A;
}


int main(int argc, const char *argv[])
{
    run(std::cin, std::cout);

    return 0;
}
