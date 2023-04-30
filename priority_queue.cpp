#include "vector.cpp"

template <typename T>
class PriorityQueue
{
    Vector<T> data;

public:
    void push(const T &value)
    {
        data.push_back(value);
        int position = data.size() - 1;
        while (position > 0 and data[position -1] < value)
        {
            std::swap(data[position], data[position - 1]);
            position--;
        }
    }

    T pop()
    {
        return data.pop_back();
    }

    bool empty()
    {
        return data.empty();
    }
};
