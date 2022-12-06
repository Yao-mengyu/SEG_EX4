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
    string output_dir = "output";
    if(argc >=3 ) output_dir = argv[2];
    if (access(output_dir.c_str(), 0) == -1){
        mkdir(output_dir.c_str(), S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }
    unlink((output_dir + "/equal.csv").c_str());
    unlink((output_dir + "/inequal.csv").c_str());
    string output_eq = output_dir + "/equal.csv";
    string output_neq = output_dir + "/inequal.csv";
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
    struct dirent* file;
    while((file = readdir(input_d)) != NULL){
        // 跳过隐藏文件, 当前目录(.),或上一级目录
        if(strncmp(file->d_name, ".", 1) == 0)
            continue;

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