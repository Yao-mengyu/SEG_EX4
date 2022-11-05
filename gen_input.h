#pragma once
#include <iostream>
#include <vector>
using namespace std;
#define TEST_NUM 10

enum Input_Kind{
    Int, Char, String
};

class Input_Form{
   public:
   enum Input_Kind kind;
   union 
   {
     pair<int,int> int_range;
     pair<int,int> string_length;
   };
   Input_Form(){};
};

class Gen_Input{

    private:
        string data_source;
        string input_folder;
        int gen_rand_int(int a, int b);
        char gen_rand_char();
        string gen_rand_string(int a, int b);
        void analyze_form();
        vector<Input_Form> form_vector;
    public:
        void gen_input();
        Gen_Input(string& source, string& dest);
};