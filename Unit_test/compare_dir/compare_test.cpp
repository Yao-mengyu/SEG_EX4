#include <gtest/gtest.h>
#include "../../compare.h"
#include <fstream>

TEST(CompareTest, NoCompareFolder)//检测无法打开文件夹时
{
    string compare_folder = "./compare";
    string prefix_path = "mytest";
    string eq_output = "./output/eq.csv";
    string neq_output = "./output/neq.csv";
    Compare test_compare = Compare(prefix_path, compare_folder, eq_output, neq_output);
    ASSERT_THROW(test_compare.compare_all(), std::runtime_error);
}


TEST(ExecTest, Success)//成功执行
{
   string compare_folder = "./compare_dir";
    string prefix_path = "mytest";
    string eq_output = "./output/eq.csv";
    string neq_output = "./output/neq.csv";
    Compare test_compare = Compare(prefix_path, compare_folder, eq_output, neq_output);
    test_compare.compare_all();
    //------------------------eq--------------------------//
    ifstream ifs_1("./output/eq.csv");
    string str;
    ifs_1 >> str;
    ASSERT_STREQ(str.c_str(), "mytest/demo1,mytest/demo2");
    //-----------------------neq-------------------------//
    ifstream ifs_2("./output/neq.csv");
   // string str;
    ASSERT_TRUE(ifs_2 >> str);
    //ASSERT_STREQ(str.c_str(), "mytest/demo3,mytest/demo1");
   ASSERT_TRUE(ifs_2 >> str);
   // ASSERT_STREQ(str.c_str(), "mytest/demo2,mytest/demo3");
}

int main(int argc,char*argv[])
{
   testing::InitGoogleTest(&argc,argv);
   string eq_output = "./output/eq.csv";
    string neq_output = "./output/neq.csv";
    unlink(eq_output.c_str());
    unlink(neq_output.c_str());
 //i  srand(time(nullptr));
   return RUN_ALL_TESTS();
}
