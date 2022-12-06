#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
void selectionSort(vector<int> &q){
    for(int i = 0; i < q.size(); i++){
        for(int j = i + 1; j < q.size(); j++){
            if(q[i] > q[j])
                swap(q[i], q[j]);
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
    selectionSort(q);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}
