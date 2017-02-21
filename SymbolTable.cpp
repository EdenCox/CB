#include "SymbolTable.h"

using namespace std;

TypeEntry::TypeEntry() {
}

TypeEntry::TypeEntry(string key, string value) : key(key), value(value) {
}

string TypeEntry::getKey() {
    return key;
}

string TypeEntry::getValue() {
    return value;
}

TypeMap::TypeMap() {

}

void TypeMap::put(string key, string value) {
    table.push_back(TypeEntry(key, value));
}

//returns 1 if type matches, returns -1 if is mismatches , returns 0 if symbol isn't found.

int TypeMap::checkType(string key, string value) {
    for (auto &i : table) {
        if (i.getKey() == key)
            if (i.getValue() == value)
                return 1;
            else
                return -1;
    }
    return 0;
}

bool TypeMap::has(string key){
    for (auto &i : table){
        if (i.getKey() == key)
            return true;
    }
    false;
}

string TypeMap::getType(string key) {
    for (auto &i : table) {
        if (i.getKey() == key)
            return i.getValue();
    }
    return "";
}

TypeMap::~TypeMap() {

}

FunctionEntry::FunctionEntry(string className, string methodName, string typeName) : className(className), methodName(methodName), typeName(typeName) {
}

FunctionEntry::FunctionEntry(string className, string methodName, string typeName, vector<string> formals) : className(className), methodName(methodName), typeName(typeName), formals(formals) {
}

void FunctionEntry::append(string formal) {
    formals.push_back(formal);
}

void FunctionEntry::append(vector<string> formals) {
    this->formals.insert(this->formals.end(), formals.begin(), formals.end());
}

string FunctionEntry::getClassName() {
    return className;
}

string FunctionEntry::getMethodName() {
    return methodName;
}

string FunctionEntry::getTypeName() {
    return typeName;
}

vector<string> FunctionEntry::getFormals() {
    return formals;
}

FunctionMap::FunctionMap() {
}

void FunctionMap::put(string className, string methodName, string typeName, vector<string> formals) {
    table.push_back(FunctionEntry(className, methodName, typeName, formals));
}

vector<string> FunctionMap::GetFormalsType(string className, string methodName) {
    for (auto &i : table) {
        if (i.getClassName() == className && i.getMethodName() == methodName)
            return i.getFormals();
    }
    return {"NOTYPE#"};
}

string FunctionMap::getMethodType(string className, string methodName) {
    for (auto &i : table) {
        if (i.getClassName() == className && i.getMethodName() == methodName)
            return i.getTypeName();
    }
    return "";
}
bool FunctionMap::hasMethod(string className,string methodName){
    for (auto &i : table) {
        if (i.getClassName() == className && i.getMethodName() == methodName)
            return true;
    }
    return false;
}
FunctionMap::~FunctionMap() {
}

ObjectEntry::ObjectEntry(string className, string extendsName) : className(className), extendsName(extendsName) {
}

string ObjectEntry::getClassName() {
    return className;
}

string ObjectEntry::getMethodName() {
    return extendsName;
}

ObjectMap::ObjectMap() {}

bool ObjectMap::typeExists(string className) {
    for (auto &i : table) {
        if (i.getClassName() == className)
            return true;
    }
    return false;
}

void ObjectMap::put(string className, string extendsName) {
    table.push_back(ObjectEntry(className, extendsName));
}

string ObjectMap::getExtendsName(string className) {
     for (auto &i : table) {
        if (i.getClassName() == className)
            return i.getMethodName();
    }
    return "";
}

ObjectMap::~ObjectMap() {
}

SymbolTable::SymbolTable() {
    rTable.push_back(TypeMap());
    fTable = FunctionMap();
    oTable = ObjectMap();
    addClassName("native","");
    addClassMethod("native","native","native",{});
}

void SymbolTable::addScope() {
    rTable.push_back(TypeMap());
}

void SymbolTable::removeScope() {
    rTable.pop_back();
}

void SymbolTable::addVariable(string key, string value) {
    rTable.back().put(key, value);
}
bool SymbolTable::checkVariable(string key){
     for (auto &i : rTable){
         if(i.has(key))
             return true;
     }
     return false;
}


int SymbolTable::checkVariable(string key, string value) {
    for (auto &i : rTable) {
        int x = i.checkType(key, value);
        if (x == 1)
            return 1;
        else if (x == -1)
            return -1;

    };
    return 0;
}

string SymbolTable::getType(string key) {
    string type;
    for (auto &i : rTable) {
        type = i.getType(key);
        if (!type.empty()) {
            return type;
        }
    }
    return "";
}

void SymbolTable::addClassMethod(string className, string methodName, string typeName, vector<string> formals) {
    fTable.put(className, methodName, typeName, formals);
}

vector <string> SymbolTable::getFormalsType(string className, string methodName) {
    vector <string> formaltypes = {"NOTYPE#"}; //= fTable.GetFormalsType(className, methodName);
    while(formaltypes.size() == 1 && formaltypes.at(0) == "NOTYPE#" && className != ""){       
        formaltypes = fTable.GetFormalsType(className,methodName);
        className = getExtendsName(className);
    }
    return formaltypes;
}

bool SymbolTable::hasMethod(string className, string methodName){
    bool has = false;
    while(!has && className != ""){       
        has = fTable.hasMethod(className,methodName);
        className = getExtendsName(className);
    }
        
    return has;
}

void SymbolTable::addClassName(string className, string extendsName) {
    oTable.put(className, extendsName);
}

bool SymbolTable::typeExists(string className) {
    return oTable.typeExists(className);
}

string SymbolTable::getExtendsName(string className) {
    return oTable.getExtendsName(className);
}

string SymbolTable::getMethodType(string className, string methodName) {
    string type = "";
    while(type == "" && className != ""){  
        type = fTable.getMethodType(className, methodName);
        className = getExtendsName(className);    
    }
    return type;
}

string SymbolTable::getLUB(string type1, string type2) {
    string lub1 = type1;
    string lub2 = type2;
    while (lub1 != lub2) {
        lub2 = getExtendsName(lub2);
        if (lub2 == "") {
            lub2 = type2;
            lub1 = getExtendsName(lub1);
            if (lub1 == "")
                return lub1;
        }
    }
    return lub1;
}

bool SymbolTable::isParentype(string parent, string child) {
    while(parent != child){
        child = getExtendsName(child);
        if(child == "")
            return false;
    }
    return true;
}


