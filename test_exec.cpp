#include "exec.cpp"

int main(){
    Exec exec = Exec("t_exec", "t_exec_out", "t_exec_in");
    exec.exec_all();
    return 0;
}