#pragma once
#include <iostream>
#include <vector>
#include<dirent.h>
using namespace std;
#define TEST_NUM 10
class Compare{
    private:
        string prefix_path;//前缀文件夹路径
        string compare_folder;
        string eq_output;
        string neq_output;
        vector<string&> all_dir;//待比较的输出数据文件夹
    public:
        Compare(string& prefix_path, string& compare_folder, string& eq_output, string& neq_output);
        void compare_all();
};