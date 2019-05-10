/*Kadane's algorithm*/

#include <bits/stdc++.h>
using namespace std;

/*maximum range sum algorithm*/

#define MAX_N 100000

int A[MAX_N], DP[MAX_N+1];

int dp_mrs(int n){
	DP[0] = 0;
	int maxMRS = DP[0];

	for(int i=0; i<n; i++){
		D[i+1] = max(0, DP[i] + A[i]);
		maxMRS = max(maxMRS, DP[i+1]);
	}

	return maxMRS;
}
