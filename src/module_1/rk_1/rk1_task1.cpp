/*

Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1].
На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента
k в массиве A, если он там присутствует, либо вернуть позицию, куда его следовало бы
вставить, чтобы массив остался отсортированным.

Требование: сложность O(logN)

*/

#include<iostream>


int binarySearch(int *array, int left, int right, int toFind)
{
    while (left <= right) {
        int mid = (left + right) / 2;

        if (array[mid] == toFind)
            return mid;

        if (array[mid] < toFind)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return left;
}


void run(std::istream &in, std::ostream &out)
{
    int n;
    int *A;

    in >> n;

    A = new int[n];
    for (int i = 0; i < n; i++) {
        in >> A[i];
    }

    int k;
    in >> k;

    int ans = binarySearch(A, 0, n - 1, k);

    out << ans << "\n";

    delete[] A;
}


int main(int argc, const char *argv[])
{
    run(std::cin, std::cout);

    return 0;
}
