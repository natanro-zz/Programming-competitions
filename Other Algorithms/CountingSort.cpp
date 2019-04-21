/*couting sort: sorting in O(n)*

funciona quando temos um range mais ou menos pequeno de número que vamos receber em um array
no caso do problema 1566 do URI, temos um range de 20 a 230 inclusos

a ideia é fazer um vetor de indices, do menor valor do range até o maior valor do range (incluso)[1]
nesse vetor de indices, contamos a frequencia que os elementos aparecem no array dado
dps fazemos um array com o mesmo tamanho do array dado que será o novoarray ordenado [2]

após a contagem de frequencia, vamos distribuindo essa frequencia[3] pelo array para de fato impor onde vão os numeros
no array de output e por ultimo, de acordo com a frequencia, vamos inserindo no novo array [4]*/

#include <bits/stdc++.h>
using namespace std;



int main(){
        int n;scanf(" %d", &n);
        for(int i=0; i<n; i++){
                int a;scanf(" %d", &a);;
                vector<int> v(a);
                for(int i=0; i<a; i++){
                        scanf(" %d", &v[i]);
                }
                vector<int> position(231, 0);// [1] vetor de indices
                vector<int> result(a+1);// [2] novo array ordenado
                for(int j=0; j<a; j++){
                        position[v[j]] += 1;
                }

                for(int k=21; k<231; k++){
                        position[k] += position[k-1];// [3] distruibicao de frequencia
                }

                for(int j=0; j<a; j++){
                        result[position[v[j]]] = v[j];// [4] insercao no novo array
                        position[v[j]] --;
                }
                for(int j=1; j<result.size(); j++){
                        if(j < result.size()-1)printf("%d ", result[j]);
                        else printf("%d\n", result[j]);
                }
        }
        return 0;
}

