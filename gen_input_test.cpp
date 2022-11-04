#include "gen_input.cpp"
using namespace std;
int main(){
    srand(time(nullptr));
    Gen_Input test_gen = Gen_Input("./input/4A/stdin_format.txt", "./");
    test_gen.gen_input();
    return 0;
}