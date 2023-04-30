class Pair
{
public:
    Pair(int first, int second) : first(first), second(second) {}
    Pair() : first(0), second(0) {}
    int first;
    int second;
    bool operator<(const Pair &other) const
    {
        return first < other.first;
    }
};