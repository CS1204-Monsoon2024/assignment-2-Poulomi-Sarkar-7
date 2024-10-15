#include "HashTable.cpp"


#include <iostream>
#include <algorithm>
using namespace std;

class HashTable
{
    int size;
    int *Array0;
    int entered;
    float loadfactor;

public:
    HashTable(int initialSize)
    {
        size = initialSize;
        Array0 = new int[size];
        entered = 0;
        loadfactor = 0.8;

        // initial values set to -1, as only non-negative keys entered
        for (int i = 0; i < size; i++)
        {
            Array0[i] = -1;
        }
    }

    bool primeCheck(int num)
    {
        int count = 0;
        for (int i = 1; i <= num; i++)
        {
            if (num % i == 0)
            {
                count += 1;
            }
        }
        return count == 2;
    }

    int primeResize(int currentSize)
    {
        int num = currentSize * 2;
        while (primeCheck(num) != true)
        {
            num += 1;
        }
        return num;
    }

    void Resizing()
    {
        int newSize = primeResize(size);
        int *Array1 = new int[newSize];

        // initial values set to -1, as only non-negative keys entered
        for (int i = 0; i < newSize; i++)
        {
            Array1[i] = -1;
        }

        for (int i = 0; i < size; i++)
        {
            if (Array0[i] != -1)
            {
                int key = Array0[i];
                int index = key % newSize;

                // Quadratic probing to find empty slots in new array
                int j = 0;
                while (Array1[(index + j * j) % newSize] != -1 && j <= ((newSize + 1) / 2))
                {
                    j += 1;
                }
                int position = (index + j * j) % newSize;
                if (Array1[position] == -1)
                    Array1[position] = key;
                else
                    cout << "Max probing limit reached!" << endl;
            }
        }

        delete[] Array0; // Deleting old array outside the loop
        Array0 = Array1;
        size = newSize;
    }

    void insert(int key)
    {
        float load = entered / (float)size; // Cast to float to avoid integer truncation
        if (load >= loadfactor)
        {
            Resizing();
        }

        int index = key % size;
        int j = 0;
        while (Array0[(index + j * j) % size] != -1 && j <= ((size + 1) / 2))
        {
            if (Array0[(index + j * j) % size] == key)
            {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            j += 1;
        }
        int position = (index + j * j) % size;
        if (Array0[position] == -1)
            {Array0[position] = key;
            entered += 1;}
        else
        {
            cout << "Max probing limit reached!" << endl;
            return;
        }
    }

    void remove(int key)
    {
        int indexRM = search(key);
        if (indexRM != -1)
        {
            Array0[indexRM] = -1;
            entered--;
        }
        else
            cout << "Element not found" << endl;
    }

    int search(int key)
    {
        int index = key % size;
        int j = 0;

        while (Array0[(index + j * j) % size] != key && j <= ((size + 1) / 2))
        {
            if (Array0[(index + j * j) % size] == -1)
            {
                return -1;
            }
            j++;
        }
        if (Array0[(index + j * j) % size] == key)
            return (index + j * j) % size;
        else
            return -1;
    }

    void printTable()
    {
        for (int i = 0; i < size; i++) // Corrected loop condition
        {
            if (Array0[i] == -1)
            {
                cout << "- ";
            }
            else
            {
                cout << Array0[i] << " ";
            }
        }
        cout << endl;
    }
};

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
