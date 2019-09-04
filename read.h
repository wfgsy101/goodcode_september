#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<vector>
#include"file_process.h"

class Reader {
public:
    virtual void parse(const std::string & table_word) = 0;
    virtual void print() = 0;

    virtual ~Reader(){}

public:
    static Reader* get(const std::string & type);
};

template <typename T>
class TypeReader : public Reader {
protected:
    T value;
};

class IntReader : public TypeReader<int> {
public:
    virtual void parse(const std::string & table_word) {
         this->value = std::stoi(table_word.data());
    }

    virtual void print() {
         std::cout << this->value << " (" << typeid(this->value).name() << ")\t";
    }
};

class FloatReader : public TypeReader<float> {
public:
    virtual void parse(const std::string & table_word) {
         this->value = std::stof(table_word.data());
    }

    virtual void print() { 
         std::cout << this->value << " (" << typeid(this->value).name() << ")\t";
    }
};

class StringReader : public TypeReader<std::string> {
public:
    virtual void parse(const std::string & table_word) {
         this->value = table_word; 
    }

    virtual void print() { 
         std::cout << this->value << " (" << typeid(this->value).name() << ")\t";
    }
};

class User {
public:
    int a;
    int b;
    int c;
};

class UserReader : public TypeReader<User> {
public:
    virtual void parse(const std::string & table_word) {
         std::vector<std::string> fields = TableGet::split(table_word.data(), ":");
         this->value.a = std::stoi(fields[0]);
         this->value.b = std::stoi(fields[1]);
         this->value.c = std::stoi(fields[2]);
    }

    virtual void print() {
         std::cout << "a=" << this->value.a << ","
                   << "b=" << this->value.b << ","
                   << "c=" << this->value.c << ""
                   << " (" << typeid(this->value).name() << ")\t";
    }
};

Reader* Reader::get(const std::string & type) {
    if (type == "int") {
        return new IntReader();
    } else if (type == "float") {
        return new FloatReader();
    } else if (type == "user") {
        return new UserReader();
    } else {
        return new StringReader();
    }
}

