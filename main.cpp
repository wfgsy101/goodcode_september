#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include"read.h"
#include"file_process.h"

int main(){
    class TableGet file_processor;
    file_processor.table_open("table1.txt");
    
    std::vector<std::string> types = file_processor.get_header();
    std::cout << "types: " << types.size() << std::endl;

    std::string line;
    while (file_processor.get_line(line)) {
        std::vector<std::string> colums = file_processor.split(line, "\t");
        for (int i = 0; i < types.size(); i++) {
            Reader* reader = Reader::get(types[i]);
            reader->parse(colums[i]);
            reader->print();
            delete reader;
        }
    std::cout << std::endl;
    }
    return 0;
}
