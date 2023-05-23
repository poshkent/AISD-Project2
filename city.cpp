#include <cstring>

class City
{
    char *name;
    int x, y;
    bool has_roads_ = false;

    void set_name(char *str)
    {
        int len = 0;
        while (str[len] >= 48 && str[len] <= 'Z')
        {
            len++;
        }
        name = new char[len + 1];
        for (int i = 0; i < len; i++)
        {
            name[i] = str[i];
            str[i] = '.';
        }
        name[len] = '\0';
    }
    void find_name(int *x, int *y, char **map, int width, int height)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                if ((dx == 0 && dy == 0) or (*x + dx < 0) or (*y + dy < 0) or (*x + dx >= width) or (*y + dy >= height))
                {
                    continue;
                }
                if (map[*y + dy][*x + dx] >= 48 && map[*y + dy][*x + dx] <= 'Z')
                {
                    *x += dx;
                    *y += dy;
                    find_beginning(map[*y], *x);
                    return;
                }
            }
        }
    }
    void find_beginning(char *str, int &x)
    {
        while (str[x] >= 48 && str[x] <= 'Z')
        {
            x--;
        }
        x++;
    }

public:
    City()
    {
        name = nullptr;
        x = 0;
        y = 0;
    }
    void scan(char **map, int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        if (y > 0 && (map[y - 1][x] == '#' or map[y - 1][x] == '*'))
        {
            has_roads_ = true;
        }
        else if (y < height - 1 && (map[y + 1][x] == '#' or map[y + 1][x] == '*'))
        {
            has_roads_ = true;
        }
        else if (x > 0 && (map[y][x - 1] == '#' or map[y][x - 1] == '*'))
        {
            has_roads_ = true;
        }
        else if (x < width - 1 && (map[y][x + 1] == '#' or map[y][x + 1] == '*'))
        {
            has_roads_ = true;
        }
        find_name(&x, &y, map, width, height);
        set_name(&map[y][x]);
    }
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }
    char *get_name()
    {
        return name;
    }
    bool has_roads()
    {
        return has_roads_;
    }
    ~City()
    {
        delete[] name;
    }
    City &operator=(City &other)
    {
        if (this->name != nullptr)
        {
            delete[] this->name;
        }
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->x = other.x;
        this->y = other.y;
        this->has_roads_ = other.has_roads_;
        return *this;
    }
};