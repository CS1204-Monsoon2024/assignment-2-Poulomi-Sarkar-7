#include <iostream>
#include <algorithm>
using namespace std;

class HashTable
{
    int size;
    int *arr1;
    int input;
    float lf;       //lf=Loadfactor

public:
    HashTable(int x)
    {
        size = x;
        arr1 = new int[size];
        lf = 0.8;
        input = 0;
        

        // initially set every input to -1
        for (int i = 0; i < size; i++)
        {
            arr1[i] = -1;
        }
    }


    int resize(int size_current)    //Next prime number atleats twice the current size
    {
        int no = size_current * 2;
        while (isPrime(no) != true)
        {
            no += 1;
        }
        return no;
    }
    
    bool isPrime(int no)        //To check if number is prime
    {
        int c = 0;      //counter
        for (int i = 1; i <= no; i++)
        {
            if (no % i == 0)
            {
                c += 1;
            }
        }
        return c == 2;
    }

    void Resizing()
    {
        int size_new = resize(size);        //size of resized table
        int *arr2 = new int[size_new];

        // initially set values to -1
        for (int i = 0; i < size_new; i++)
        {
            arr2[i] = -1;
        }

        for (int i = 0; i < size; i++)
        {
            if (arr1[i] != -1)
            {
                int key = arr1[i];
                int index = key % size_new;

                // using quadratic probing
                int j = 0;
                while (arr2[(index + j * j) % size_new] != -1 && j <= ((size_new + 1) / 2))
                {
                    j += 1;
                }
                int pos = (index + j * j) % size_new;
                if (arr2[pos] == -1)
                    arr2[pos] = key;
                else
                    cout << "Max probing limit reached!" << endl;
            }
        }

        delete[] arr1; // delete the older array
        arr1 = arr2;
        size = size_new;
    }

    void insert(int key)
    {
        float new_lf = input / (float)size; // typecast to float type
        if (new_lf >= lf)
        {
            Resizing();         //resize
        }

        int index = key % size;
        int i = 0;
        while (arr1[(index + i * i) % size] != -1 && i <= ((size + 1) / 2))
        {
            if (arr1[(index + i * i) % size] == key)
            {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }
            i += 1;
        }
        int pos = (index + i * i) % size;
        if (arr1[pos] == -1)
            {arr1[pos] = key;
            input += 1;}
        else
        {
            cout << "Max probing limit reached!" << endl;
            return;
        }
    }


    int search(int key)             //function to search
    {
        int index = key % size;
        int i = 0;

        while (arr1[(index + i * i) % size] != key && i <= ((size + 1) / 2))
        {
            if (arr1[(index + i * i) % size] == -1)
            {
                return -1;
            }
            i++;
        }
        if (arr1[(index + i * i) % size] == key)
            return (index + i * i) % size;
        else
            return -1;
    }
    
    void remove(int key)
    {
        int x = search(key);        //Element to remove
        if (x != -1)
        {
            arr1[x] = -1;
            input--;
        }
        else
            cout << "Element not found" << endl;
    }

    void printTable()
    {
        for (int i = 0; i < size; i++) 
        {
            if (arr1[i] == -1)
            {
                cout << "- ";
            }
            else
            {
                cout << arr1[i] << " ";
            }
        }
        cout << endl;
    }
};
