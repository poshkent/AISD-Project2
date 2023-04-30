#pragma once
#include <iostream>

template <typename T>
class Vector
{
    T *array;
    int size_;
    int capacity;

public:
    Vector()
    {
        array = new T[1];
        size_ = 0;
        capacity = 1;
    }
    void push_back(T &data)
    {
        if (size_ == capacity)
        {
            T *temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = array[i];
            }
            delete[] array;
            capacity *= 2;
            array = temp;
        }
        array[size_] = data;
        size_++;
    }
    void push_back(const T &data)
    {
        if (size_ == capacity)
        {
            T *temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++)
            {
                temp[i] = array[i];
            }
            delete[] array;
            capacity *= 2;
            array = temp;
        }
        array[size_] = data;
        size_++;
    }
    T pop_back()
    {
        size_--;
        return array[size_];
    }
    T pop_front()
    {
        T temp = array[0];
        for (int i = 0; i < size_ - 1; i++)
        {
            std::swap(array[i], array[i + 1]);
        }
        size_--;
        return temp;
    }
    int size() const
    {
        return size_;
    }
    bool empty()
    {
        return size_ == 0;
    }
    T &operator[](int index)
    {
        return array[index];
    }
    T front()
    {
        return array[0];
    }
    T back()
    {
        return array[size_ - 1];
    }
    ~Vector()
    {
        delete[] array;
    }
    friend std::ostream &operator<<(std::ostream &out, const Vector<T> &v)
    {
        for (int i = 0; i < v.size_; i++)
        {
            out << v.array[i] << std::endl;
        }
        return out;
    }
};