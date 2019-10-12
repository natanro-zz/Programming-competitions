/*
A saber: qual palindromo formado? Não apenas o comprimento deste.

Palindrome in a string.
O(n²) time. Up to N<=5k
*/

#include<bits/stdc++.h>

using namespace std;

int LongestPalindrome(string& a, int l, int r){
        if(l==r) return 1;
        if(l+1==r) return ( (a[l] == a[r]) ? 2:1);

        if(a[l] == a[r]) return 2+LongestPalindrome(a, l+1, r-1);
        else return max(LongestPalindrome(a, l, r-1), LongestPalindrome(a, l+1, r)); 
}

int main(){
        string a;
        cin >> a;
        cout << LongestPalindrome(a, 0, a.size()) << endl;
        return 0;
}
