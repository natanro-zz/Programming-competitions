#include <bits/stdc++.h>
using namespace std;

int calculaValues(vector<int> values, vector<int> objSizes, int tamMochila, int N){
	vector<vector<int>> tabulation(N+1,vector<int>(tamMochila+1));
	for(int i=0; i<=N; i++){
		for(int j=0; j<=tamMochila; j++){
			if(i==0 || j==0) tabulation[i][j] = 0;
			else if(objSizes[i-1] > j) tabulation[i][j] = tabulation[i-1][j];
			else{
				tabulation[i][j] = max(tabulation[i-1][j] , tabulation[i-1][j-objSizes[i-1]] +values[i-1]);
			}
		}
	}
	return tabulation[N][tamMochila];
}

int main(){
	int N;
	while(cin>>N && N){
		int tamMochila;
		cin >> tamMochila;
		vector<int> values(N, 0), objSizes(N, 0);
		for(int i=0; i<N; i++){
			int c, w;
			cin >> c >> w;
			values[i] = c;
			objSizes[i] = w;
		}
		cout << calculaValues(values, objSizes, tamMochila, N) << " min."<<endl;
	}
	return 0;
}
