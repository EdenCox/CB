#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class TypeEntry {
private:
      string key;
      string value;
public:
      TypeEntry();
      TypeEntry(string key, string value);
 
      string getKey();
      string getValue();
};

const int TABLE_SIZE = 512;
 
class TypeMap {
private:
      vector<TypeEntry> table;
public:
      TypeMap();
      int checkType(string key, string value); 
      bool has(string key);
      string getType(string key);
      void put(string key, string value) ;   
      ~TypeMap();
};

class FunctionEntry {
private:
      string className;
      string typeName;
      string methodName;
      vector<string> formals;
public:
      FunctionEntry(string className, string methodName, string typeName);
      FunctionEntry(string className, string methodName, string typeName, vector<string> formals);
 
      string getClassName();
      string getMethodName();
      string getTypeName();
      vector<string> getFormals();
      void append(string formal);
      void append(vector<string> formals);
};

class FunctionMap {
private:
      list<FunctionEntry> table;
public:
      FunctionMap();
      vector<string> GetFormalsType(string className, string methodName); 
      string getMethodType(string className,string methodName);
      bool hasMethod(string className,string methodName);
      void put(string className, string methodName, string typeName, vector<string> formals);   
      ~FunctionMap();
};

class ObjectEntry {
private:
      string className;
      string extendsName;

public:
      ObjectEntry(string className, string extendsName);
 
      string getClassName();
      string getMethodName();
};

class ObjectMap {
private:
      vector<ObjectEntry> table;
      int currentLength = 0;
public:
      ObjectMap();
      bool typeExists(string className); 
      string getExtendsName(string className);
      void put(string className, string extendsName);   
      ~ObjectMap();
};



class SymbolTable {
private:
    list<TypeMap> rTable;
    FunctionMap fTable;
    ObjectMap oTable;
    
public:
    SymbolTable();
    void addScope();//adds a scope
    void removeScope();//removes most recent scope
    void addVariable(string key, string value);//adds a variable declaration to the scope.
    bool checkVariable(string key);//checks if a variable exist
    int checkVariable(string key, string value);//checks if a variable exist
    string getType(string key);//returns the type of a variable.
    void addClassMethod(string className, string methodName, string typeName, vector<string> formals);//adds a method name of a available class.
    void addClassName(string className, string extendsName);//add a class name.
    bool typeExists(string className);//check if a type/class exists
    string getExtendsName(string className);//get the extension of a class.
    vector<string> getFormalsType(string className, string methodName);//get all the parameter types of a class.
    bool hasMethod(string className, string methodName);
    string getMethodType(string className,string methodName);//get the method return type of a class
    string getLUB(string type1, string type2);//get the LUB of 2 types.
    bool isParentype(string parent,string child);
};
#endif	// SYMBOLTABLE_H


