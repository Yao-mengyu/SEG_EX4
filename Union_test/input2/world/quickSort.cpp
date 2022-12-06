#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
 
using namespace std;
 
void quickSort(vector<int> &q, int l, int r){
    if(l >= r)
        return;
    int i = l - 1, j = r + 1, x = q[l + rand() % (r - l + 1)];
    while(i < j){
        do j--; while(q[j] > x);
        do i++; while(q[i] < x);
        if(i < j)
            swap(q[i], q[j]);
        else{
            quickSort(q, l, j);
            quickSort(q, j + 1, r);
        }
    }
}
 
int main(){
//    int n;
    vector<int> q;
  //  cin >> n;
    for(int i = 0, t; i < 10; i++){
        cin >> t;
        q.push_back(t);
    }
    quickSort(q, 0, 9);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}
