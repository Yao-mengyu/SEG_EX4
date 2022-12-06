#include "exec.h"
#include <sys/types.h>  
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

Exec::Exec(string& files_folder, string& output_folder, string& input_folder){
    this ->files_folder = files_folder;
    this ->output_folder = output_folder;
    this ->input_folder = input_folder;
}

static inline void traverse_exec(string& folder, string& out_folder, string& file_name){
    DIR *d_input;
    if(!(d_input = opendir(folder.c_str()))){
        throw std::runtime_error("Cannot open the input files folder");
       // return;
    }
    
    if(access((out_folder + "/" + file_name).c_str(), 0) == -1){
        mkdir((out_folder + "/" + file_name).c_str(), S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }
    struct dirent* input_file;
    while((input_file = readdir(d_input)) != NULL){
        // 跳过隐藏文件, 当前目录(.),或上一级目录
        string input_file_name(input_file->d_name);
        if(strncmp(input_file->d_name, ".", 1) == 0)
            continue;
        //如果是普通的文件
        if(input_file->d_type == 8){
            string file_path = folder + "/" + input_file_name;
            system(("timeout 5s ./_a.out <" + file_path +" >" + out_folder + "/" + file_name + "/" + input_file ->d_name
                +" 2>&1").c_str());
           // unlink("_a.out");
        }
    }
    unlink("_a.out");
}

void Exec::exec_all(){
    
    DIR *d;
    if(!(d = opendir(files_folder.c_str()))){
        throw std::runtime_error("Cannot open the files folder");
       // return;
    }
    
    if(access((output_folder).c_str(), 0) == -1){
        mkdir((output_folder).c_str(), S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }
    /*
    if(access(exec_folder.c_str(), 0) == -1){
        mkdir(exec_folder.c_str(), S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
        if(access(exec_folder.c_str(), 0) == -1){
            cout<<"Cannot make the exec folder"<<endl;
            return;
        }
    }*/
    struct dirent* file;
    while((file = readdir(d)) != NULL){
        // 跳过隐藏文件, 当前目录(.),或上一级目录
        if(strncmp(file->d_name, ".", 1) == 0)
            continue;
        //如果是普通的文件
        if(file->d_type == 8){
           // printf("%s\n", file->d_name);
            string file_name(file->d_name);
            string file_path = files_folder + "/" + file_name;
          //  int ret =0;
            if (file->d_name[strlen(file->d_name) - 1] == 'p'){//cpp
                system(("g++ -w " + file_path + " -o " + "_a.out").c_str());
                traverse_exec(input_folder, output_folder, file_name);
            }else if (file->d_name[strlen(file->d_name) - 1] == 'c'){
                system(("gcc -w " + file_path + " -o " + "_a.out").c_str());
                traverse_exec(input_folder, output_folder, file_name);
            }
            
        }
    }
    closedir(d);
    return;
}
