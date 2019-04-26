/*Travelling salesman problem*/
#include <bits/stdc++.h>
using namespace std;

int dis[20][20], memo[20][1<<20]; // the complexity is very high, so the maximum number of cities would be less than 16

/*dp top-down algorithm for TSP*/
int tsp(int pos, int bitmask){ // bitmask stores the visited coordinates
	if(bitmask == (1<<n) -1) return dist[pos][0];
	if(memo[pos][bitmask] != -1) return memo[pos][bitmask];

	int ans = 2000000000;
	for(int nxt = 0; nxt < n; nxt++){
		if(nxt != pos && !(bitmsk & (1 << nxt))) // if coordinate nxt is not visited yet
			ans = min( ans, dist[pos][nxt] + tsp(nxt, bitmask | (1<<nxt)));
	return mem [pos][bitmask] = ans;
}
