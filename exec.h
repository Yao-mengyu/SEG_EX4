#include <iostream>
using namespace std;
class Exec{
    private:
        string files_folder;//源代码文件夹
        //string exec_folder;//可执行文件文件夹
        string output_folder;//输出文件夹
        string input_folder;//输入文件夹
    public:
        Exec(string& files_folder, string& output_folder, string& input_folder);
        void exec_all();
};