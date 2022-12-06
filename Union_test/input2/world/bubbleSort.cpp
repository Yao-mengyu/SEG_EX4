#include <iostream>
#include <algorithm>
#include <vector>
 
using namespace std;
 
void bubbleSort(vector<int> &q){
    for(int i = q.size() - 1; i > 0; i--){
        bool flag = false;
        for(int j = 0; j + 1 <= i; j++){
            if(q[j] > q[j+1]){
                swap(q[j], q[j+1]);
                flag = true;
            }
        }
        if(!flag)
            break;
    }
}
 
int main(){
  //  int n;
    vector<int> q;
//    cin >> n;
    for(int i = 0, t; i < 10; i++){
        cin >> t;
        q.push_back(t);
    }
    bubbleSort(q);
    for(auto x : q)
        cout << x << ' ';
    cout << endl;
    return 0;
}
