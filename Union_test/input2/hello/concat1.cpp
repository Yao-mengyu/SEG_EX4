#include <iostream>
using namespace std;
int main(){
  char c;
  string s = "";
  for(int i = 0; i < 4; i++){
    cin>>c;
    s.push_back(c);
  }
  cout<<s;
}
