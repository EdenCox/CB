#include "SymbolTable.h"

using namespace std;

TypeEntry::TypeEntry(string key, string value) : key(key), value(value) {}

string TypeEntry::getKey() {return key;}

string TypeEntry::getValue() {return value;}


TypeMap::TypeMap() {
    table = new TypeEntry*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;
}

void TypeMap::put(string key, string value) {
    table[currentLength] = new TypeEntry(key, value);
    currentLength++;
    /*while (table[hash] != NULL && table[hash]->getKey() != key)
        hash = (hash + 1) % TABLE_SIZE;
    if (table[hash] != NULL)
        delete table[hash];
    table[hash] = new HashEntry(key, value);
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL && table[i]->getKey() != key)
        {
            
        }
    }*/
}

//returns 1 if type matches, returns -1 if is mismatches , returns 0 if symbol isn't found.
int TypeMap::checkType(string key, string value) {

    for (int i = 0; i < currentLength; i++){
        if (table[i]->getKey() == key)
            if (table[i]->getValue() == value)
                return 1;
            else
                return -1;
        
    }
    return 0;
}
string TypeMap::getType(string key) {
    for (int i = 0; i < currentLength; i++){
        if (table[i]->getKey() == key)
            return table[i]->getValue();        
    }
    return NULL;
}

TypeMap::~TypeMap() {
    /*
    for (int i = 0; i < currentLength; i++) {
        delete table[i];
    }
    delete [] table;*/
}

FunctionEntry::FunctionEntry(string className, string methodName) : className(className), methodName(methodName) {}
FunctionEntry::FunctionEntry(string className, string methodName, list<string>* formals) : className(className), methodName(methodName), formals(formals)  {}

void FunctionEntry::append(string formal) {formals->push_back(formal);}
void FunctionEntry::append(list<string>* formals) {this->formals->insert(this->formals->end(),formals->begin(), formals->end());}

string FunctionEntry::getClassName() {return className;}
string FunctionEntry::getMethodName() {return methodName;}
list<string>* FunctionEntry::getFormals() {return formals;}

FunctionMap::FunctionMap() {}

void FunctionMap::put(string className, string methodName, list<string>* formals) {table.push_back(FunctionEntry(className,methodName,formals));}
list<string>* FunctionMap::GetFormalsType(string className, string methodName) {
    for (auto &i: table){
        if (i.getClassName() == className &&  i.getMethodName() == methodName)
            return i.getFormals();
    }
    return new list<string> {"empty"};
}

FunctionMap::~FunctionMap(){}

ObjectEntry::ObjectEntry(string className, string extendsName) : className(className), extendsName(extendsName) {}
string ObjectEntry::getClassName(){return className;}
string ObjectEntry::getMethodName() {return extendsName;}

ObjectMap::ObjectMap(){
    table = new ObjectEntry*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                  table[i] = NULL;
}
bool ObjectMap::typeExists(string className){
    for (int i = 0; i < currentLength; i++){
        if (table[i]->getClassName() == className)
            return true;        
    }
    return false;
}
void ObjectMap::put(string className, string extendsName){
    table[currentLength] = new ObjectEntry(className, extendsName);
    currentLength++;
}

string ObjectMap::getExtendsName(string className){
    for (int i = 0; i < currentLength; i++){
        if (table[i]->getClassName() == className)
            return table[i]->getMethodName();        
    }
    return NULL;
}

ObjectMap::~ObjectMap(){}



SymbolTable::SymbolTable(){/*table.push_back(TypeMap());*/ fTable = FunctionMap(); oTable = ObjectMap();}
void SymbolTable::addScope(){rTable.push_back(TypeMap());}
void SymbolTable::removeScope(){rTable.pop_back(); }
void SymbolTable::addVariable(string key, string value){rTable.back().put(key,value);}
int SymbolTable::checkVariable(string key, string value){
    int error = 0;
        for (auto &i: rTable){
            int x = i.checkType(key,value);
            if (x == 1 )
                return 1;
            else if (x < 0)
                error = x;
                
        };
    return error;
}
string SymbolTable::getType(string key) {
    return getType(key);
}
void SymbolTable::addClassMethod(string className, string methodName, list<string>* formals){
    fTable.put(className,methodName,formals);
}

list <string>* SymbolTable::getFormalsType(string className, string methodName){
    return fTable.GetFormalsType(className,methodName);
}

void SymbolTable::addClassName(string className, string extendsName){oTable.put(className, extendsName);}
bool SymbolTable::typeExists(string className){return oTable.typeExists(className);}
string SymbolTable::getExtendsName(string className){return oTable.getExtendsName(className);}

