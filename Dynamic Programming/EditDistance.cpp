/*Problema EditDistance
calcula a distancia entre strings, pode calcular o numero minimo de
modificacoes para a string A se transformar na string B
insert: ABC -> ABCD
remove: ABC -> AB
modify: ABC -> ADC*/
#include <bits/stdc++.h>
using namespace std;

int editDistance(string a, string b){
	int asize = a.size(), bsize=b.size();
	vector<vector<int>> table(asize+1, vector<int>(bsize+1));
	for(int i=0; i<=asize; i++){
		for(int j=0; j<=bsize; j++){
			if(i==0) table[i][j] = j;
			else if(j==0) table[i][j] = i;
			else{
				int minimum = min(table[i-1][j] +1, table[i][j-1]+1);
				table[i][j] = (a[i-1] == b[j-1]) ? min(minimum, table[i-1][j-1]) : min(minimum, table[i-1][j-1]+1);
			}
		}
	}
	return table[asize][bsize];
}

int main(){
	string a, b;
	cin >> a >> b;
	cout << editDistance(a, b) << endl;
	return 0;
}
