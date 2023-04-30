#include <iostream>

#include "vector.cpp"
#include "city.cpp"
#include "priority_queue.cpp"
#include "pair.cpp"
#include "hashmap.cpp"

const int INF = 1e9 + 7;

class Deigstra
{
    int *answers;
    int *ancestors;
    Vector<Pair> *graph;
    Vector<City> cities;
    char **field;
    int height, width;
    Vector<Pair> moves;
    HashMap hashmap;
    int **distance;

    void parce_cities()
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (field[y][x] == '*')
                {
                    City c;
                    c.scan(field, x, y, width, height);
                    hashmap.insert(c.get_name(), cities.size());
                    cities.push_back(c);
                }
            }
        }
        answers = new int[cities.size()];
        ancestors = new int[cities.size()];
        graph = new Vector<Pair>[cities.size()];
        distance = new int *[height];
        for (int i = 0; i < height; i++)
        {
            distance[i] = new int[width];
        }
    }

    int get_city_index(int x, int y)
    {
        for (int i = 0; i < cities.size(); i++)
        {
            if (cities[i].get_x() == x and cities[i].get_y() == y)
            {
                return i;
            }
        }
        return -1;
    }

    bool can_go(int x, int y)
    {
        return x >= 0 and x < width and y >= 0 and y < height and distance[y][x] == -1 and field[y][x] != '.';
    }

    void bsf_parse_road(int x, int y, int &city_index)
    {
        distance[y][x] = 0;
        Vector<Pair> a;
        a.push_back(Pair(x, y));
        Pair cur;
        while (!a.empty())
        {
            cur = a.pop_front();
            int cx = cur.first, cy = cur.second;

            for (int i = 0; i < moves.size(); i++)
            {
                int dx = moves[i].first, dy = moves[i].second;
                if (can_go(cx + dx, cy + dy))
                {
                    distance[cy + dy][cx + dx] = distance[cy][cx] + 1;
                    if (field[cy + dy][cx + dx] == '#')
                    {
                        a.push_back(Pair(cx + dx, cy + dy));
                    }
                    else if (field[cy + dy][cx + dx] == '*')
                    {
                        int city2_index = get_city_index(cx + dx, cy + dy);
                        graph[city_index].push_back({city2_index, distance[cy + dy][cx + dx]});
                        graph[city2_index].push_back({city_index, distance[cy + dy][cx + dx]});
                    }
                }
            }
        }
    }

    void bfs_parse_roads()
    {
        for (int i = 0; i < cities.size() - 1; i++)
        {
            if (cities[i].has_roads())
            {
                for (int y = 0; y < height; y++)
                    for (int x = 0; x < width; x++)
                    {
                        distance[y][x] = -1;
                    }
                bsf_parse_road(cities[i].get_x(), cities[i].get_y(), i);
            }
        }
    }

public:
    Deigstra()
    {
        moves.push_back(Pair(1, 0));
        moves.push_back(Pair(-1, 0));
        moves.push_back(Pair(0, 1));
        moves.push_back(Pair(0, -1));
    }

    void find_city(char *city1, char *city2, int *arr)
    {
        arr[0] = hashmap.get(city1);
        arr[1] = hashmap.get(city2);
    }

    void add_avialine(char *city1, char *city2, int len)
    {
        int arr[2];
        find_city(city1, city2, arr);
        graph[arr[0]].push_back({arr[1], len});
    }

    void scan_map()
    {
        scanf("%d %d", &width, &height);
        field = new char *[height];
        for (int i = 0; i < height; i++)
        {
            field[i] = new char[width];
            scanf("%s", field[i]);
        }
        parce_cities();
        bfs_parse_roads();
    }

    void deigstra(int start, int end, bool show_path)
    {
        for (int i = 0; i < cities.size(); i++)
        {
            answers[i] = INF;
            ancestors[i] = -1;
        }

        answers[start] = 0;
        PriorityQueue<Pair> pathes_queue;
        pathes_queue.push(Pair(0, start));

        while (!pathes_queue.empty())
        {
            Pair path = pathes_queue.pop();
            int dist = path.first, v = path.second;

            if (answers[v] < dist)
            {
                continue;
            }
            for (int i = 0; i < graph[v].size(); i++)
            {
                int u = graph[v][i].first, len_vu = graph[v][i].second;
                int new_dist = dist + len_vu;
                if (new_dist < answers[u])
                {
                    answers[u] = new_dist;
                    ancestors[u] = v;
                    pathes_queue.push(Pair(new_dist, u));
                }
            }
        }
        printf("%d ", answers[end]);

        if (show_path)
        {
            Vector<int> path;
            int cur = end;
            path.push_back(cur);
            while (ancestors[cur] != -1)
            {
                cur = ancestors[cur];
                path.push_back(cur);
            }
            for (int i = path.size() - 2; i > 0; i--)
            {
                printf("%s ", cities[path[i]].get_name());
            }
        }
        printf("\n");
    }

    ~Deigstra()
    {
        for (int i = 0; i < height; i++)
        {
            delete[] field[i];
            delete[] distance[i];
        }
        delete[] field;
        delete[] distance;
        delete[] answers;
        delete[] ancestors;
        delete[] graph;
    }
};

void input(char *str)
{
    int i = 0;
    char c;
    c = getchar();
    if (c != '\n')
    {
        str[i++] = c;
    }

    while (true)
    {
        c = getchar();
        if (c == '\n' || c == ' ')
        {
            break;
        }
        str[i++] = c;
    }

    str[i] = '\0';
}

int main(int, char **)
{
    Deigstra deigstra;
    deigstra.scan_map();
    int n, len;
    char str[20];
    input(str);
    n = atoi(str);
    char city1[20];
    char city2[20];

    for (int i = 0; i < n; i++)
    {
        input(city1);
        input(city2);
        input(str);
        len = atoi(str);
        deigstra.add_avialine(city1, city2, len);
    }
    input(str);
    n = atoi(str);
    int arr[2];
    for (int i = 0; i < n; i++)
    {
        input(city1);
        input(city2);
        input(str);
        len = atoi(str);
        deigstra.find_city(city1, city2, arr);
        deigstra.deigstra(arr[0], arr[1], len);
    }
    return 0;
}