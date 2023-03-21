#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include<sstream>

using namespace std;

int xiv[1000][1000];
int n, store[1000] = {0}, aux[1000] = {0};
int graph[1000][1000];
int d[1000];
int ok = 0;

int main(int argc, char* argv[])
{
    
    ifstream fin(argv[1]);
    int edges[1000][1000];
    int k;
    int m;

    // Citirea din fisier a parametrilor
    fin>>k>>n>>m;
    
    // Construirea grafului
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 2; j++) {
            fin >> edges[i][j]; 
        }
        graph[edges[i][0]][edges[i][1]] = 1;
        graph[edges[i][1]][edges[i][0]] = 1;
        d[edges[i][0]]++;
        d[edges[i][1]]++;
    }

    // O lista de variabile xiv -> "v este al i-lea nod din clica C"
    int count = 1;
    for(int i = 1; i <= k; i++){
        for(int j = 1; j <= n; j++){
            xiv[i][j] = count++;
        }
    }

    // Conditia 1 - Intre oricare 2 noduri trebuie sa existe o muchie
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
                for(int l = 1; l <= k-1; l++){
                    for(int q = l + 1; l <= k; l++){
                        if(graph[i][j] == 0 && i != j){
                        cout << "(~" << xiv[l][i] << " V " << "~" << xiv[q][j] << ")"; 
                        cout << " ^ ";
                        }
                    }
                }
            
        }
    }
    
    // Conditia 2 - Niciun nod nu trebuie sa se repete
    for(int q = 1; q <= n; q++){
    for(int i = 1; i <= k; i++){
        for(int j = 1; j <= k; j++){
            if(i != j){
                    cout << "(~" << xiv[i][q] << " V " << " ~" << xiv[j][q] << ")"; 
                    cout << " ^ ";
                
                }
            }
        }
    }
    
    // Conditia 3 - Exista cate un nod pentru fiecare pozitie din subgraf
    int c = 0;
    for(int i = 1; i <= k; i++){
        for(int j = 1; j <= n; j++){
            if(c%2 == 0){
                cout<<"(";
                cout << xiv[i][j];
                cout << " V ";
                c++; 
            } else {
                cout << xiv[i][j];
                cout<<")";
                if(xiv[i][j] < k*n)
                    cout << " ^ ";
                c++;
            }
        }
    }

    return 0;
}
