#ifndef __GOODCODER_IDG_TABLE_FILE__
#define __GOODCODER_IDG_TABLE_FILE__

#include <fstream>
#include <cstring>

//#include <com_log.h>

class TableGet {
public:
    bool table_open(const std::string & filename);
    bool get_line(std::string& line);
    void close();

    std::vector<std::string> get_header();

public:
    static std::vector<std::string> split(const std::string & str,const std::string & brk);

private:
    std::ifstream ifs_table;
};

bool TableGet::table_open(const std::string & filename){
   if (ifs_table.is_open()){
       ifs_table.close();
   }

   ifs_table.open(filename.c_str(),std::ios::in);
   if (!ifs_table.is_open()){
       ifs_table.close();
       return false;
   }
   
   return true;
}

bool TableGet::get_line(std::string & line){
    if(!ifs_table.is_open()){
        return false;
    }

    if (!std::getline(ifs_table, line)){
        return false;
    }
    return true;

}

void TableGet::close(){
    ifs_table.close();
}

std::vector<std::string> TableGet::get_header(){
    std::string word_types;
    this->get_line(word_types);
    return split(word_types, "\t");
}

std::vector<std::string> TableGet::split(const std::string & str, const std::string & brk){
    std::vector<std::string> des;
    if(str == "") return des;

    char * strs = new char[str.length() + 1];
    strcpy(strs,str.c_str());

    char * d = new char[brk.length() + 1];
    strcpy(d, brk.c_str());

    char * p = strtok(strs,d);
    while(p){
        std::string s = p;
        des.push_back(s);
        p = strtok(NULL,d);
    }
    delete[] strs;
    delete[] d;
    return des;

}

#endif
