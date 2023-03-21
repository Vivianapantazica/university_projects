#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int n, store[1000] = {0}, aux[1000] = {0};
int graph[1000][1000];
int d[1000];
int ok = 0;

/* functia verifica daca un subgraf este o clica */
int is_clique (int b)
{
    for (int i = 1; i < b; i++) {
        for (int j = i + 1; j < b; j++)
            if (graph[store[i]][store[j]] == 0)
                return 0;
    }
    return 1;
}

/* functia verifica daca in graful dat se gaseste o clica de dimensiune k */
int findCliques(int i, int l, int k)
{
    for (int j = i + 1; j <= n - (k - l); j++) {
        if (d[j] >= k - 1) {
            store[l] = j;
            if (is_clique(l + 1)) {
                if (l < k) {
                   findCliques(j, l + 1, k);
                } 
                else{
                    ok = 1;
                    return ok;
                }
            }
        }
    }
    return ok;
}

int main(int argc, char* argv[])
{
    
    ifstream fin(argv[1]);
    int edges[1000][1000];
    int k,m;

    // citirea din fisier a parametrilor
    fin>>k>>n>>m;
    
    //construirea grafului
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 2; j++) {
            fin >> edges[i][j]; 
        }
        graph[edges[i][0]][edges[i][1]] = 1;
        graph[edges[i][1]][edges[i][0]] = 1;
        d[edges[i][0]]++;
        d[edges[i][1]]++;
    }

    //apelarea functiei care gaseste clicile de dimensiune k existente in graf
    int value = findCliques(0, 1, k);

    //scrierea la consola a valorii de adevar returnate de functie
    if(value == 1)
        cout<<"True\n";
    else
        cout<<"False\n";
        
    return 0;
}