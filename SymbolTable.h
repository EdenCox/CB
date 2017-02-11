#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <list>
#include <iostream>

using namespace std;

class TypeEntry {
private:
      string key;
      string value;
public:
      TypeEntry(string key, string value);
 
      string getKey();
      string getValue();
};

const int TABLE_SIZE = 128;
 
class TypeMap {
private:
      TypeEntry **table;
      int currentLength = 0;
public:
      TypeMap();
      int checkType(string key, string value); 
      string getType(string key);
      void put(string key, string value) ;   
      ~TypeMap();
};

class FunctionEntry {
private:
      string className;
      string methodName;
      list<string>* formals;
public:
      FunctionEntry(string className, string methodName);
      FunctionEntry(string className, string methodName, list<string>* formals);
 
      string getClassName();
      string getMethodName();
      list<string>* getFormals();
      void append(string formal);
      void append(list<string>* formals);
};

class FunctionMap {
private:
      list<FunctionEntry> table;
public:
      FunctionMap();
      list<string>* GetFormalsType(string className, string methodName); 
      void put(string className, string methodName, list<string>* formals);   
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
      ObjectEntry **table;
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
    void addScope();
    void removeScope();
    void addVariable(string key, string value);
    int checkVariable(string key, string value);
    string getType(string key);
    void addClassMethod(string className, string methodName, list<string>* formals);
    void addClassName(string className, string extendsName);
    bool typeExists(string className);
    string getExtendsName(string className);
    list<string>* getFormalsType(string className, string methodName);
    
};
#endif	// SYMBOLTABLE_H


