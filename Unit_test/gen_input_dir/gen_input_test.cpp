#include <gtest/gtest.h>
#include "../../gen_input.h"
#include <fstream>

TEST(GenInputTest, NoDataSource)//检测无输入文件时
{
    string data_source = "";
    string input_folder = "./nodatasource";
    Gen_Input test_gen = Gen_Input(data_source, input_folder);
    ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, NoInputDir)//检测无输出文件夹文件时
{
    string data_source = "./input_test/test_no_dir.txt";
    ofstream eq_stream;
    eq_stream.open(data_source, ios::trunc);
    eq_stream<<"";
    eq_stream.close();
    string input_folder = "";
    Gen_Input test_gen = Gen_Input(data_source, input_folder);
    ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, FormFail)//检测错误生成格式
{
   string data_source = "./input_test/form_fail.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"hello world";
   eq_stream.close();
   string input_folder = "./gen_fail";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, GenNumberFormFail1)//检测生成随机数字格式错误
{
   string data_source = "./input_test/gen_number_form_fail1.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"int(2,3) int(2)";
   eq_stream.close();
   string input_folder = "./gen_number";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, GenNumberFormFail2)//检测生成随机数字格式错误
{
   string data_source = "./input_test/gen_number_form_fail2.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"int(2,3) int(hello)";
   eq_stream.close();
   string input_folder = "./gen_number";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, GenNumberRangeFail)//检测生成随机数字范围错误
{
   string data_source = "./input_test/gen_number_range_fail.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"int(25,4)";
   eq_stream.close();
   string input_folder = "./gen_number";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, GenNumberSuccess)//检测生成随机数字
{

   string data_source = "./input_test/test_gen_number.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"int(4,25) int(1234,5678)";
   eq_stream.close();
   string input_folder = "./gen_number";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   test_gen.gen_input();
   for(int i = 0; i< TEST_NUM; i++){
      ifstream ifs(input_folder + "/test" + to_string(i) + ".txt");
      int num;
      ifs >> num;
      ASSERT_GE(num, 4);
      ASSERT_LE(num, 25);
      ifs >> num;
      ASSERT_GE(num, 1234);
      ASSERT_LE(num, 5678);
      ASSERT_FALSE(ifs >> num);
   }
   
}

TEST(GenInputTest, GenCharSuccess)//检测生成随机字符
{
   string data_source = "./input_test/test_gen_char.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"char char";
   eq_stream.close();
   string input_folder = "./gen_char";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   test_gen.gen_input();
   for(int i = 0; i< TEST_NUM; i++){
      ifstream ifs(input_folder + "/test" + to_string(i) + ".txt");
      char c;
      ASSERT_TRUE(ifs >> c);
      ASSERT_TRUE(ifs >> c);
      ASSERT_FALSE(ifs >> c);
   }
}

TEST(GenInputTest, GenStringFormFail1)//检测生成随机字符串格式错误
{
   string data_source = "./input_test/gen_string_form_fail1.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"string(2,3) string(2)";
   eq_stream.close();
   string input_folder = "./gen_string";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, GenStringFormFail2)//检测生成随机字符串格式错误
{
   string data_source = "./input_test/gen_string_form_fail2.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"string(2,3) string(hello)";
   eq_stream.close();
   string input_folder = "./gen_string";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, GenStringRangeFail)//检测生成随机字符串范围错误
{
   string data_source = "./input_test/gen_string_range_fail.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"string(25,4)";
   eq_stream.close();
   string input_folder = "./gen_string";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   ASSERT_THROW(test_gen.gen_input(), std::runtime_error);
}

TEST(GenInputTest, GenStringSuccess)//检测生成随机字符串
{
   string data_source = "./input_test/test_gen_string.txt";
   ofstream eq_stream;
   eq_stream.open(data_source, ios::trunc);
   eq_stream<<"string(1234,5678) string(4,25)";
   eq_stream.close();
   string input_folder = "./gen_string";
   Gen_Input test_gen = Gen_Input(data_source, input_folder);
   test_gen.gen_input();
   for(int i = 0; i< TEST_NUM; i++){
      ifstream ifs(input_folder + "/test" + to_string(i) + ".txt");
      string str;
      ifs >> str;
      ASSERT_GE(str.length(), 1234);
      ASSERT_LE(str.length(), 5678);
      ifs >> str;
      ASSERT_GE(str.length(), 4);
      ASSERT_LE(str.length(), 25);
      ASSERT_FALSE(ifs >> str);
   }
}

int main(int argc,char*argv[])
{
   testing::InitGoogleTest(&argc,argv);
   srand(time(nullptr));
   if (access("input_test", 0) == -1){
        mkdir("input_test", S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
   }
   return RUN_ALL_TESTS();
}
