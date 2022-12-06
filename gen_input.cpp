#include "gen_input.h"
#include <stdlib.h> 
#include <time.h> 
#include <assert.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>

//srand(time(nullptr));//设置随机数种子【记得放进调用前】
//rand();//产生一个随机数

Gen_Input::Gen_Input(string& source, string& dest) {
            this-> data_source = source;
            this -> input_folder = dest;
}


//----------------------------------------辅助函数（找形式中的num并存储在 vector a 中）----------------------------------------------------//
static inline void find_number(string& str, vector<int>& a, int start_pos){
   int pos = start_pos;//int()
   int i = start_pos;
   while(pos < str.length()){
      if(str[pos]>='0' && str[pos]<='9'){
         i = pos;
         int len = 0;
         while(str[pos]>='0' && str[pos]<='9'){
            pos++;
            len++;
         }
         string s0 = str.substr(i, len);
         int num = 0;
         stringstream s1(s0);
         s1>>num;
         a.push_back(num);
      }else{
         pos++;
      }
   }
}

//---------------------------------------------私有函数-------------------------------------------------//
char Gen_Input::gen_rand_char(){
   int cap_or_not = rand()%2;
   if(cap_or_not == 0){
      char ran_non_cap = (rand()%26) + 'a';
      return ran_non_cap;
   }else{
      char ran_cap = (rand()%26) + 'A';
      return ran_cap;
   }
}

string Gen_Input::gen_rand_string(int a, int b){
   if(a > b) throw std::runtime_error("false length range in gen_rand_string");
   int len = (rand()%(b - a + 1)) + a;
   string s ="";
   for(int i = 0; i< len; i++){
      s.push_back(gen_rand_char());
   }
   //cout<<s<<endl;
   return s;
}

int Gen_Input::gen_rand_int(int a, int b){
   if(a > b) throw std::runtime_error("false range in gen_rand_int");
   return (rand()%(b - a + 1)) + a;
}


void Gen_Input::analyze_form(){
   ifstream ifs(data_source);
   if(!ifs){
     
      throw std::runtime_error("No form file!");
      //return;
   }
   string str;
   while(ifs >> str){
    //  cout<<str<<endl;//for debug
    //string str_j = str.c_str();
    if(str.substr(0, 3)!= "int" && str.substr(0, 4) != "char" && str.substr(0, 6) != "string")
      throw std::runtime_error("wrong form!");
     // cout<<str;
      switch (str[0])
      {
      case 'i':
      {
         vector<int> a;
         find_number(str, a, 4); //int()
        // cout<<a.size()<<" "<<a[0]<<" "<<a[1]<<endl;
         if(a.size() != 2) throw std::runtime_error("false form of int(a, b)");
         struct Input_Form new_form = Input_Form();
         new_form.kind = Int;
         new_form.int_range = make_pair(a[0], a[1]);
         form_vector.emplace_back(new_form);
         break;
      }

      case 'c':
      {
         struct Input_Form new_form = Input_Form();
         new_form.kind = Char;
         form_vector.emplace_back(new_form);
         break;
      }

      case 's':
      {
         vector<int> a;
         find_number(str, a, 7); // string()
         if(a.size() != 2) throw std::runtime_error("false form of string(a, b)");
         struct Input_Form new_form = Input_Form();
         new_form.kind = String;
         new_form.string_length = make_pair(a[0], a[1]);
         form_vector.emplace_back(new_form);
         break;
      }
      default:
         struct Input_Form new_form = Input_Form();
         new_form.kind = Unknown;
         form_vector.emplace_back(new_form);
         break;
      }
   }
}

//------------------------------------------------公有函数，生成过程（生成TEST_NUM个测试用例）-------------------------------------------------//
void Gen_Input::gen_input(){
   analyze_form();
   string dir_name  = input_folder;
   if (access(dir_name.c_str(), 0) == -1){
     // cout<< "Error: cannot create test_folder!\n";
      //assert(0);
      mkdir(dir_name.c_str(), S_IRWXU | S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
   }
   for(int i = 0; i< TEST_NUM; i++){
      ofstream ofs;  
      ofs.open(input_folder + "/test" + to_string(i) + ".txt", ios::out);
      if(!ofs){
         throw std::runtime_error("Error: cannot create ofs!\n");
      }
      for(auto form: form_vector){
         switch (form.kind)
         {
         case Int:
         {
            ofs<< gen_rand_int(form.int_range.first, form.int_range.second) << " ";
            break;
         }

         case Char:
         {
            ofs<< gen_rand_char() << " ";
            break;
         }

         case String:
         {
            ofs<< gen_rand_string(form.string_length.first, form.string_length.second)<< " ";
            break;
         }

         default:
            cout<<"No matched form"<<endl;
            assert(0);
            break;
         }
      }
   }
}

