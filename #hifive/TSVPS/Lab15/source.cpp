#include <iostream>
#define inf 100000
using namespace std;

struct Edges {
    int u, v, w;
};

const int Vmax = 1000;
const int Emax = Vmax * (Vmax - 1) / 2;

int i, j, n = 5, e;
Edges edge[Emax];
int d[Vmax];

int setDistance(Edges edge[Emax], int& e, int i, int j, int w) {
    edge[e].v = i;
    edge[e].u = j;
    edge[e].w = w;

    e += 1;

    return 0;
}

//алгоритм Беллмана-Форда
void bellman_ford(int n, int s)
{
    int i, j;

    for (i = 0; i < n; i++) d[i] = inf;
    d[s] = 0;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < e; j++)
            if (d[edge[j].v] + edge[j].w < d[edge[j].u])
                d[edge[j].u] = d[edge[j].v] + edge[j].w;

    for (i = 0; i < n; i++) {
        if (d[i] == inf) {
            cout << endl << s << "->" << i << "=" << "Not";
        }
        else
        {
            cout << endl << s << "->" << i << "=" << d[i];
        }
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int w;
    int start = 4;
    e = 0;

    setDistance(edge, e, 0, 0, 0);
    setDistance(edge, e, 0, 1, 25);
    setDistance(edge, e, 0, 2, 15);
    setDistance(edge, e, 0, 3, 7);
    setDistance(edge, e, 0, 4, 2);

    setDistance(edge, e, 1, 0, 25);
    setDistance(edge, e, 1, 1, 0);
    setDistance(edge, e, 1, 2, 6);
    setDistance(edge, e, 1, 3, inf);
    setDistance(edge, e, 1, 4, inf);

    setDistance(edge, e, 2, 0, 15);
    setDistance(edge, e, 2, 1, 6);
    setDistance(edge, e, 2, 2, 0);
    setDistance(edge, e, 2, 3, 4);
    setDistance(edge, e, 2, 4, inf);

    setDistance(edge, e, 3, 0, 7);
    setDistance(edge, e, 3, 1, inf);
    setDistance(edge, e, 3, 2, 4);
    setDistance(edge, e, 3, 3, 0);
    setDistance(edge, e, 3, 4, 3);

    setDistance(edge, e, 4, 0, 2);
    setDistance(edge, e, 4, 1, inf);
    setDistance(edge, e, 4, 2, inf);
    setDistance(edge, e, 4, 3, 3);
    setDistance(edge, e, 4, 4, 0);

    cout << "Стартовая вершина > "; cin >> start ;
    cout << "Список кратчайших путей:";
    bellman_ford(n, start);
 
    return 0;
}