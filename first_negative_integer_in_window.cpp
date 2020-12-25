
#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
using namespace std;

void first_negative_integer_in_window(vector<int>& a, int k){
    
    int first_negative = -1;
    int i =0 ,j=0;
    int len = a.size();
    
    vector<int> negative;
    
    // 12, -1, -7, 8, -15, 30, 16, 28 --> -1 -1 -7 -15 -15 0
    while(j < len){
        if(a[j] < 0) 
            negative.push_back(a[j]);
        
        if(j-i+1 < k){
            j++;
        }
        else if(j-i+1 == k){
            cout << "Window:" << i << " " << j << "-->" ; 
            if(negative.empty())
                cout << 0 << " ";
            else {
                cout << negative.front() << " ";
            }
            
            if(a[i] < 0)
                negative.erase(negative.begin());
            
            i++;
            j++;
        }
    }
    
    return;
}

int main()
{
    vector<int> a{-8, 2, 3, -6, 10}; // -> -8,0,-6,-6
    int window = 2;
    
    first_negative_integer_in_window(a, window);
    
    vector<int> a2{12, -1, -7, 8, -15, 30, 16, 28}; 
    int window2 = 3;
    
    first_negative_integer_in_window(a2, window2);
    
    return 0;
}

