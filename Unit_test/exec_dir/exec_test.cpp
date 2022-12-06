#include <gtest/gtest.h>
#include "../../exec.h"
#include <fstream>

TEST(ExecTest, NoFileFolder)//检测无法打开文件夹时
{
    string files_folder = "./files";
    string output_folder = "./output_dir";
    string input_folder = "./input_dir";
    Exec test_exec = Exec(files_folder, output_folder, input_folder);
    ASSERT_THROW(test_exec.exec_all(), std::runtime_error);
}

TEST(ExecTest, NoInputDir)//检测无输入文件夹文件时
{
    string files_folder = "./files_dir";
    string output_folder = "./output_dir";
    string input_folder = "./input";
    Exec test_exec = Exec(files_folder, output_folder, input_folder);
    ASSERT_THROW(test_exec.exec_all(), std::runtime_error);
}

TEST(ExecTest, Success)//成功执行
{
   string input_files_1 = "./input_dir/test1.txt";
   ofstream eq_stream;
   eq_stream.open(input_files_1, ios::trunc);
   eq_stream<<"hello-world";
   eq_stream.close();
   string input_files_2 = "./input_dir/test2.txt";
   ofstream eq_stream_2;
   eq_stream_2.open(input_files_2, ios::trunc);
   eq_stream_2<<"hello-ymy";
   eq_stream_2.close();
    string files_folder = "./files_dir";
    string output_folder = "./output_dir";
    string input_folder = "./input_dir";
    Exec test_exec = Exec(files_folder, output_folder, input_folder);
    test_exec.exec_all();
    //------------------------cpp-1--------------------------//
    ifstream ifs_1("./output_dir/file.cpp/test1.txt");
    string str;
    
    ASSERT_FALSE(ifs_1 >> str);
    //-----------------------cpp-2-------------------------//
    ifstream ifs_2("./output_dir/file.cpp/test2.txt");
   // string str;
    ASSERT_FALSE(ifs_2 >> str);
    //---------------------c-1--------------------------//
    ifstream ifs_3("./output_dir/file.c/test1.txt");
   // string str;
    ifs_3 >> str;
    ASSERT_STREQ(str.c_str(), "hello-world");
    //--------------------c-2----------------------------//
    ifstream ifs_4("./output_dir/file.c/test2.txt");
   // string str;
    ifs_4 >> str;
    ASSERT_STREQ(str.c_str(), "hello-ymy");
}

int main(int argc,char*argv[])
{
   testing::InitGoogleTest(&argc,argv);
  // srand(time(nullptr));
   return RUN_ALL_TESTS();
}
