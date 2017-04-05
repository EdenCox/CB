/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BasicCool.h
 * Author: easy
 *
 * Created on February 23, 2017, 2:53 PM
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

#ifndef BASICCOOL_H
#define BASICCOOL_H

using namespace std;

class BasicCool {
};

class Nothing {
};

class String;
class Boolean;
class Symbol;

class Null {
public:
   virtual string _type_();
};

class Any : public Null{
public:
    Any();
    virtual String toString();
    virtual Boolean equals(Any &other);
    string _type_() override;//This method will be used for pattern matching, since c++ doesn't have any.


};

class IO : public Any {
public:
    IO();
    Nothing abort(String message);
    IO out(String arg);
    Boolean is_null(Any &arg);
    IO out_any(Any arg);
    String in();
    Symbol symbol(String name);
    String symbol_name(Symbol sym);
    string _type_() override;

};

class Unit : public Any {
};

class Int : public Any {
public:
    int value = 0;
    Int();
    Int(int value);
    Int (const Int &obj);
    String toString() override;
    Boolean equals(Any &other) override;
    Boolean equals(Int &other);
    string _type_() override;
    /*overloading functions*/
    Int operator+(const Int& other);
    Int operator-(const Int& other);
    Int operator*(const Int& other);
    Int operator/(const Int& other);
    Int operator+(const int& other);
    Int operator-(const int& other);
    Int operator- ();
    Int operator*(const int& other);
    Int operator/(const int& other);
    void operator=(const int& other);
    void operator=(const Int& other);
    Boolean operator<(const int& other);
    Boolean operator<(const Int& other);
    Boolean operator<=(const int& other);
    Boolean operator<=(const Int& other);
    Boolean operator==(const Int& other);
    Boolean operator==(const int& other);
    friend ostream& operator<<(ostream& out, const Int& i);
    

};

class Boolean : public Any {
public:
    bool value = false;
    Boolean();
    Boolean(bool value);
    //Boolean(Boolean &other);
    String toString() override;
    Boolean equals(Any &other) override;
    Boolean equals(Boolean &other);
    string _type_() override;
    /*overloading functions*/
    Boolean operator! ();
    void operator=(const bool& other);
    operator bool() const{
        return value;
    }

};

class String : public Any {
public:
    string str_field = "";
    String();
    String(string str);
    String toString() override;
    Boolean equals(Any &other) override;
    Boolean equals(String &other);
    Int length();
    String concat(String arg);
    String substring(Int start, Int end);
    Int charAt(Int Index);
    Int indexOf(String sub);   
    string _type_() override;
    
    void operator=(const string& other);
};

class Symbol : public Any {
public:
    string name;
    Symbol(string name);
    String toString() override;
    string _type_() override;
    Int hashCode();

};

class ArrayAny : public Any {
private:
    vector<Any*> array;
    Int len;
public:
    string _type_() override;
    ArrayAny(Int len);
    ArrayAny(Int len,vector<Any*> array);
    Int length();
    ArrayAny resize(Int s);
    Any& get(Int index);
    Any& set(Int index, Any& obj);

};



#endif /* BASICCOOL_H */

