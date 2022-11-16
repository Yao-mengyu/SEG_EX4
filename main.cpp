#include "gen_input.h"
#include "exec.h"
#include "compare.h"
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include <fstream>
#include <unistd.h>
#define Self_recycle

int main(int argc, char* argv[]){
    srand(time(nullptr));
    if (argc < 2){
        cout<<"You should type a input files folder"<<endl;
        return 0;
    }
    string input_dir(argv[1]);
    DIR* input_d = opendir(argv[1]);
    if (input_d == NULL){
        cout<< "Cannot open the input files folder" <<endl;
        return 0;
    }
    struct dirent* file = new dirent();
    if (access("output", 0) == -1){
        mkdir("output", S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }
    unlink("output/equal.csv");
    unlink("output/inequal.csv");
    string output_eq = "output/equal.csv";
    string output_neq = "output/inequal.csv";
    ofstream eq_stream;
    eq_stream.open(output_eq, ios::app);
    eq_stream<<("file1,file2")<<endl;
    eq_stream.close();
    ofstream neq_stream;
    neq_stream.open(output_neq, ios::app);
    neq_stream<<("file1,file2")<<endl;
    eq_stream.close();
    if (access("gen", 0) == -1){
        mkdir("gen", S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }
    if (access("outcome", 0) == -1){
        mkdir("outcome", S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }

    while((file = readdir(input_d)) != NULL){
        // 跳过隐藏文件, 当前目录(.),或上一级目录
        if(strncmp(file->d_name, ".", 1) == 0)
            continue;
        //如果是普通的文件
        if(file->d_type == 8){
            
        }
        
        //如果是文件夹
        if(file->d_type == 4){
            string folder_name(file->d_name);
            string folder_path = input_dir+"/"+folder_name;
            string data_source = folder_path+"/"+"stdin_format.txt";
            string gen_path = "gen/" + folder_name;
            Gen_Input gen = Gen_Input(data_source, gen_path);
            gen.gen_input();
            string output_path = "outcome/"+folder_name;
            /*if (access(output_path.c_str(), 0) == -1){
             mkdir(output_path.cstr(), S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
            }*/
            Exec exec = Exec(folder_path, output_path, gen_path);
            exec.exec_all();
            Compare compare = Compare(folder_path, output_path, output_eq, output_neq);
           // assert(0);
            compare.compare_all();
            #ifdef Self_recycle
                system(("rm -r " + gen_path).c_str());
                system(("rm -r " + output_path).c_str());
                //system("rm _a.out");
            #endif
        }
    }
    #ifdef Self_recycle
        system("rm -r gen");
        system("rm -r outcome");
    #endif
}