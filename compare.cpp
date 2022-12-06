#include "compare.h"
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include <fstream>
#include <iterator>
#include <vector>

Compare::Compare(const string& prefix_path, const string& compare_folder, const string& eq_output, const string& neq_output){
    this ->prefix_path = prefix_path;
    this ->compare_folder = compare_folder;
    this ->eq_output = eq_output;
    this ->neq_output = neq_output;
    this ->all_dir.clear();
}

//https://www.codenong.com/6163611/
static inline bool compareFiles(const string& p1, const string& p2) {
  ifstream f1(p1, ifstream::binary|ifstream::ate);
  ifstream f2(p2, ifstream::binary|ifstream::ate);

  if (f1.fail() || f2.fail()) {
    if(f1.fail() && f2.fail()) return true;
    //cout<<"?"<<p1<<p2<<endl;
    return false; //file problem
  }

  if (f1.tellg() != f2.tellg()) {
   // cout<<"!"<<p1<<p2<<endl;
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, ifstream::beg);
  f2.seekg(0, ifstream::beg);
  return equal(istreambuf_iterator<char>(f1.rdbuf()),
               istreambuf_iterator<char>(),
               istreambuf_iterator<char>(f2.rdbuf()));
}

//https://blog.csdn.net/weixin_41558411/article/details/116136595

static bool Compare_code(const string& d1, const string& d2){
    for(int i = 0; i < TEST_NUM; i++){
        string fix = "/test" + to_string(i) + ".txt";
        if(!compareFiles(d1+ fix, d2 + fix)) return false;
    }
    return true;
}

void Compare::compare_all(){
    DIR *d;
    
    if(!(d = opendir(compare_folder.c_str()))){
        throw std::runtime_error("cannot open compare_folder");
        //return;
    }
    struct dirent* file;

    while((file = readdir(d)) != NULL){
        // 跳过隐藏文件, 当前目录(.),或上一级目录
        //cout<<file->d_name<<endl;
        if(strncmp(file->d_name, ".", 1) == 0)
            continue;
        //如果是文件夹
        if(file->d_type == 4){
            string folder_name(file->d_name);
            string folder_path = folder_name;
           // DIR *d = opendir(folder_path.c_str());
            all_dir.emplace_back(folder_path);
        }
    }
    ofstream eq_stream;
    eq_stream.open(eq_output, ios::app);
    ofstream neq_stream;
    neq_stream.open(neq_output, ios::app);
    for(int i = 0; i< all_dir.size(); i++){
        for(int j = i+1; j< all_dir.size(); j++){
            if(Compare_code(compare_folder+"/"+all_dir[i], compare_folder+"/"+all_dir[j])){
                eq_stream<<(prefix_path+"/"+all_dir[i]+","+prefix_path+"/"+all_dir[j])<<endl;
            }else{
                neq_stream<<(prefix_path+"/"+all_dir[i]+","+prefix_path+"/"+all_dir[j])<<endl;
            }
        }
    }
    eq_stream.close();
    neq_stream.close();
    closedir(d);
    return;
}
