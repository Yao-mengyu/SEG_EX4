#include "compare.cpp"

int main(){
    Compare ctest = Compare("input/1", "compare", "equal.csv", "nequal.csv");
    ctest.compare_all();
    return 0;
}