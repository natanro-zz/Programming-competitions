/*
String matching
*/

#include <string>

using namespace std;

/*
For 2D search, we can use backtracking
Maybe build lps array and use it as a prune rule
*/

void computeLPSArray(string& P, vector<int>& lps){
        int len=0;
        lps[0] = 0;
        
        int i=1;
        while(i<lps.size()){
                if(P[i] == P[len]){
                        len++;
                        lps[i] = len;
                        i++;
                }
                else{
                        if(len != 0){
                                len = lps[len-1];
                                
                        }else{
                                lps[i] = 0;
                                i++;
                        }
                }
        }
}

void KMPSearch(string& P, string& T){ // P = pattern T = text
        int m = P.size(), n=T.size();

        vector<int> lps(m); // pre-processing

        computeLPSArray(P, lps);

        int i=j=0;
        while(i<n){
                if(P[j] == T[i]){
                        j++;
                        i++;
                }

                if(j==m){
                        //found pattern at index i-j
                        j = lps[j-1];
                }

                else if(i<n && P[j] != T[i]){

                        if(j != 0){
                                j = lps[j-1];
                        }else i++;
                }
        }
}
