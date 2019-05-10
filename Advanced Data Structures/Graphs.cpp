#include <bits/stdc++.h>
using namespace std;

#define VISITED 1
#define UNVISITED -1

typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

vi dfs_num;
vector<vii> AdjList;

vi topoSort;                                        //vetor para ordenação topológica

void dfs(int u){
    cout << u << "\n";                              //nó sendo visitado
    dfs_num[u] = VISITED;
    for(int j=0; j<(int)AdjList[u].size(); j++){
        ii v = AdjList[u][j];                       //v é o par (vizinho, peso)
        if(dfs_num[v.first] == UNVISITED){
            dfs(v.first);
        }
    }
    /*
    topoSort.push_back(u);                          //única linha diferente para ordenação topológica
                                                    // fazer loop como para compons. conexas. no main
                                                    //dps fazer o reverse do vetor
    */
}

void bsf(int V, int node){
    /*Neste caso, estamos medindo a distancia dos nos com o node de entrada. 
    Mas tambem podemos calcular a menor distancia entre um caminho de s a t.
    Se fizermos um vetor de inteiros que, para cada nó, ele relembra o pai, 
    podemos traçar o caminho s -> ... -> t
    */

    vi d(V, INT_MAX); d[node] = 0;                  //a distancia para o node do começo é 0
    queue<int> q; q.push(node);

    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int j=0; j < (int)AdjList[u].size(); j++){
            ii v = AdjList[u][j];                       //v é o par (vizinho, peso)
            if(d[v.first] == INT_MAX){
                d[v.first] = d[u] + 1;                  //mede distancia entre o node ou numero da camada
                q.push(v.first);
            }
        }
    }
}
