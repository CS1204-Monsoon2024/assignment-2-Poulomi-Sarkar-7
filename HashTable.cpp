#include <iostream>
#include <algorithm>
using namespace std;

class HashTable
{
    int capacity;
    int *dataArray;
    int itemCount;
    float maxLoadFactor;

public:
    HashTable(int initCapacity)
    {
        capacity = initCapacity;
        dataArray = new int[capacity];
        itemCount = 0;
        maxLoadFactor = 0.8;

        // Initialize all elements to -1, as we assume only non-negative keys will be inserted
        for (int i = 0; i < capacity; i++)
        {
            dataArray[i] = -1;
        }
    }

    bool isPrime(int number)
    {
        int divisorCount = 0;
        for (int i = 1; i <= number; i++)
        {
            if (number % i == 0)
            {
                divisorCount++;
            }
        }
        return divisorCount == 2;
    }

    int getNextPrime(int currentCapacity)
    {
        int num = currentCapacity * 2;
        while (!isPrime(num))
        {
            num++;
        }
        return num;
    }

    void expandTable()
    {
        int newCapacity = getNextPrime(capacity);
        int *newDataArray = new int[newCapacity];

        // Initialize new array with -1 to represent empty slots
        for (int i = 0; i < newCapacity; i++)
        {
            newDataArray[i] = -1;
        }

        // Rehash existing keys into new array
        for (int i = 0; i < capacity; i++)
        {
            if (dataArray[i] != -1)
            {
                int key = dataArray[i];
                int newIndex = key % newCapacity;

                // Quadratic probing to resolve collisions in new array
                int j = 0;
                while (newDataArray[(newIndex + j * j) % newCapacity] != -1 && j <= (newCapacity + 1) / 2)
                {
                    j++;
                }
                int newPos = (newIndex + j * j) % newCapacity;
                if (newDataArray[newPos] == -1)
                    newDataArray[newPos] = key;
                else
                    cout << "Collision limit exceeded during rehashing!" << endl;
            }
        }

        delete[] dataArray; // Deallocate old array
        dataArray = newDataArray;
        capacity = newCapacity;
    }

    void insert(int key)
    {
        float load = itemCount / (float)capacity; // Avoid integer division
        if (load >= maxLoadFactor)
        {
            expandTable();
        }

        int index = key % capacity;
        int j = 0;
        while (dataArray[(index + j * j) % capacity] != -1 && j <= (capacity + 1) / 2)
        {
            if (dataArray[(index + j * j) % capacity] == key)
            {
                cout << "Key duplication is not allowed" << endl;
                return;
            }
            j++;
        }
        int pos = (index + j * j) % capacity;
        if (dataArray[pos] == -1)
        {
            dataArray[pos] = key;
            itemCount++;
        }
        else
        {
            cout << "Collision limit reached!" << endl;
        }
    }

    void remove(int key)
    {
        int index = search(key);
        if (index != -1)
        {
            dataArray[index] = -1;
            itemCount--;
        }
        else
            cout << "Key not found" << endl;
    }

    int search(int key)
    {
        int index = key % capacity;
        int j = 0;

        while (dataArray[(index + j * j) % capacity] != key && j <= (capacity + 1) / 2)
        {
            if (dataArray[(index + j * j) % capacity] == -1)
            {
                return -1;
            }
            j++;
        }
        if (dataArray[(index + j * j) % capacity] == key)
            return (index + j * j) % capacity;
        else
            return -1;
    }

    void printTable()
    {
        for (int i = 0; i < capacity; i++)
        {
            if (dataArray[i] == -1)
            {
                cout << "- ";
            }
            else
            {
                cout << dataArray[i] << " ";
            }
        }
        cout << endl;
    }
};
