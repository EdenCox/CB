/* 
 * File:   CompileSources.h
 * Author: Eden Cox
 *
 */

#ifndef COMPILESOURCES_H
#define COMPILESOURCES_H

auto basicCoolHeader = "#include <string>\n"
"#include <iostream>\n"
"#include <cstdlib>\n"
"#include <vector>\n"
"\n"
"#ifndef BASICCOOL_H\n"
"#define BASICCOOL_H\n"
"\n"
"using namespace std;\n"
"\n"
"class BasicCool {\n"
"};\n"
"\n"
"class Nothing {\n"
"};\n"
"\n"
"class String;\n"
"class Boolean;\n"
"class Symbol;\n"
"\n"
"class Null {\n"
"public:\n"
"   virtual string _type_();\n"
"};\n"
"\n"
"class Any : public Null{\n"
"public:\n"
"    Any();\n"
"    virtual String toString();\n"
"    virtual Boolean equals(Any &other);\n"
"    string _type_() override;//This method will be used for pattern matching, since c++ doesn't have any.\n"
"\n"
"\n"
"};\n"
"\n"
"class IO : public Any {\n"
"public:\n"
"    IO();\n"
"    Nothing abort(String message);\n"
"    IO out(String arg);\n"
"    Boolean is_null(Any &arg);\n"
"    IO out_any(Any arg);\n"
"    String in();\n"
"    Symbol symbol(String name);\n"
"    String symbol_name(Symbol sym);\n"
"    string _type_() override;\n"
"\n"
"};\n"
"\n"
"class Unit : public Any {\n"
"};\n"
"\n"
"class Int : public Any {\n"
"public:\n"
"    int value = 0;\n"
"    Int();\n"
"    Int(int value);\n"
"    Int (const Int &obj);\n"
"    String toString() override;\n"
"    Boolean equals(Any &other) override;\n"
"    Boolean equals(Int &other);\n"
"    string _type_() override;\n"
"    /*overloading functions*/\n"
"    Int operator+(const Int& other);\n"
"    Int operator-(const Int& other);\n"
"    Int operator*(const Int& other);\n"
"    Int operator/(const Int& other);\n"
"    Int operator+(const int& other);\n"
"    Int operator-(const int& other);\n"
"    Int operator- ();\n"
"    Int operator*(const int& other);\n"
"    Int operator/(const int& other);\n"
"    void operator=(const int& other);\n"
"    void operator=(const Int& other);\n"
"    Boolean operator<(const int& other);\n"
"    Boolean operator<(const Int& other);\n"
"    Boolean operator<=(const int& other);\n"
"    Boolean operator<=(const Int& other);\n"
"    Boolean operator==(const Int& other);\n"
"    Boolean operator==(const int& other);\n"
"    friend ostream& operator<<(ostream& out, const Int& i);\n"
"    \n"
"\n"
"};\n"
"\n"
"class Boolean : public Any {\n"
"public:\n"
"    bool value = false;\n"
"    Boolean();\n"
"    Boolean(bool value);\n"
"    //Boolean(Boolean &other);\n"
"    String toString() override;\n"
"    Boolean equals(Any &other) override;\n"
"    Boolean equals(Boolean &other);\n"
"    string _type_() override;\n"
"    /*overloading functions*/\n"
"    Boolean operator! ();\n"
"    void operator=(const bool& other);\n"
"    operator bool() const{\n"
"        return value;\n"
"    }\n"
"\n"
"};\n"
"\n"
"class String : public Any {\n"
"public:\n"
"    string str_field = \"\";\n"
"    String();\n"
"    String(string str);\n"
"    String toString() override;\n"
"    Boolean equals(Any &other) override;\n"
"    Boolean equals(String &other);\n"
"    Int length();\n"
"    String concat(String arg);\n"
"    String substring(Int start, Int end);\n"
"    Int charAt(Int Index);\n"
"    Int indexOf(String sub);   \n"
"    string _type_() override;\n"
"    \n"
"    void operator=(const string& other);\n"
"};\n"
"\n"
"class Symbol : public Any {\n"
"public:\n"
"    string name;\n"
"    Symbol(string name);\n"
"    String toString() override;\n"
"    string _type_() override;\n"
"    Int hashCode();\n"
"\n"
"};\n"
"\n"
"class ArrayAny : public Any {\n"
"private:\n"
"    vector<Any*> array;\n"
"    Int len;\n"
"public:\n"
"    string _type_() override;\n"
"    ArrayAny(Int len);\n"
"    ArrayAny(Int len,vector<Any*> array);\n"
"    Int length();\n"
"    ArrayAny resize(Int s);\n"
"    Any& get(Int index);\n"
"    Any& set(Int index, Any& obj);\n"
"\n"
"};\n"
"\n"
"\n"
"\n"
"#endif /* BASICCOOL_H */\n"
"";

auto basicCoolSource = "#include \"BasicCool.h\"\n"
"\n"
"Any::Any() {\n"
"}\n"
"\n"
"String Any::toString() {\n"
"    return String(\"this is an \\\"Any\\\" object.\");\n"
"}\n"
"\n"
"Boolean Any::equals(Any &other) {\n"
"    return this == &other;\n"
"}\n"
"\n"
"string Any::_type_() {\n"
"    return \"Any\";\n"
"}\n"
"\n"
"IO::IO() : Any() {\n"
"}\n"
"\n"
"string IO::_type_() {\n"
"    return \"IO\";\n"
"}\n"
"\n"
"Nothing IO::abort(String message) {\n"
"    cout << message.str_field << endl;\n"
"    exit(EXIT_FAILURE);\n"
"    return Nothing();\n"
"}\n"
"\n"
"IO IO::out(String arg) {\n"
"    cout << arg.str_field << endl;\n"
"    return IO();\n"
"}\n"
"\n"
"Boolean IO::is_null(Any &arg) {\n"
"    return Boolean(arg._type_() == \"Null\");\n"
"}\n"
"\n"
"IO IO::out_any(Any arg) {\n"
"    out(arg.toString().str_field);\n"
"}\n"
"\n"
"String IO::in() {\n"
"    string in;\n"
"    cin>>in;\n"
"    return String(in);\n"
"}\n"
"\n"
"Symbol IO::symbol(String name) {\n"
"    return Symbol(name.str_field);\n"
"}\n"
"\n"
"String IO::symbol_name(Symbol sym) {\n"
"    return String(sym.name);\n"
"}\n"
"\n"
"Int::Int(int value) : value(value) {\n"
"\n"
"}\n"
"\n"
"Int::Int(const Int& obj) {\n"
"    value = obj.value;\n"
"}\n"
"\n"
"String Int::toString() {\n"
"    return String(std::to_string(value));\n"
"}\n"
"\n"
"string Int::_type_() {\n"
"    return \"Int\";\n"
"}\n"
"\n"
"Boolean Int::equals(Any &other) {\n"
"    if (other._type_() == \"Int\") {\n"
"        return dynamic_cast<Int&> (other).value == value;\n"
"    }\n"
"    return false;\n"
"}\n"
"\n"
"Boolean Int::equals(Int &other) {\n"
"    return Boolean(value == other.value);\n"
"}\n"
"\n"
"Boolean::Boolean(bool value) : value(value) {\n"
"\n"
"}\n"
"\n"
"//Boolean::Boolean(Boolean &other) {\n"
"//    this->value = other.value;\n"
"//}\n"
"\n"
"string Boolean::_type_() {\n"
"    return \"Boolean\";\n"
"}\n"
"\n"
"String Boolean::toString() {\n"
"    return String(value ? \"true\" : \"false\");\n"
"}\n"
"\n"
"Boolean Boolean::equals(Any &other) {\n"
"    if (other._type_() == \"Boolean\") {\n"
"        return dynamic_cast<Boolean&> (other).value == value;\n"
"    }\n"
"    return false;\n"
"}\n"
"\n"
"Boolean Boolean::equals(Boolean &other) {\n"
"    return (Boolean(value == other.value));\n"
"}\n"
"\n"
"String::String(string str) {\n"
"    str_field = str;\n"
"}\n"
"\n"
"string String::_type_() {\n"
"    return \"String\";\n"
"}\n"
"\n"
"Boolean String::equals(Any &other) {\n"
"    if (other._type_() == \"String\") {\n"
"        return dynamic_cast<String&> (other).str_field == str_field;\n"
"    }\n"
"    return false;\n"
"}\n"
"\n"
"Boolean String::equals(String &other) {\n"
"    return Boolean(str_field == other.str_field);\n"
"}\n"
"\n"
"String String::toString() {\n"
"    return String(str_field);\n"
"}\n"
"\n"
"Int String::length() {\n"
"    return Int(str_field.size());\n"
"}\n"
"\n"
"String String::concat(String arg) {\n"
"    return String(str_field + arg.str_field);\n"
"}\n"
"\n"
"String String::substring(Int start, Int end) {\n"
"    if (start.value >= str_field.size()) {\n"
"        cout << \"Index: out of bounce\\nString size: \" << str_field.size() << \"\\n start Index given: \" << start.value << endl;\n"
"        exit(EXIT_FAILURE);\n"
"    }\n"
"    return String(str_field.substr(start.value, end.value - start.value));\n"
"}\n"
"\n"
"Int String::charAt(Int index) {\n"
"    return Int(str_field.at(index.value));\n"
"}\n"
"\n"
"Int String::indexOf(String sub) {\n"
"\n"
"    return Int(str_field.find(sub.str_field, 0));\n"
"}\n"
"\n"
"Symbol::Symbol(string name) : name(name) {\n"
"\n"
"}\n"
"\n"
"string Symbol::_type_() {\n"
"    return \"Symbol\";\n"
"}\n"
"\n"
"String Symbol::toString() {\n"
"    return String(\".\" + name);\n"
"}\n"
"\n"
"Int Symbol::hashCode() {\n"
"\n"
"    return std::hash<std::string>{}\n"
"    (name);\n"
"}\n"
"\n"
"ArrayAny::ArrayAny(Int len) : len(len) {\n"
"    array.resize(len.value);\n"
"}\n"
"\n"
"ArrayAny::ArrayAny(Int len, vector<Any*> array) : len(len), array(array) {\n"
"}\n"
"\n"
"string ArrayAny::_type_() {\n"
"    return \"ArrayAny\";\n"
"}\n"
"\n"
"Int ArrayAny::length() {\n"
"    return Int(len);\n"
"}\n"
"\n"
"ArrayAny ArrayAny::resize(Int s) {\n"
"    return ArrayAny(s, array);\n"
"}\n"
"\n"
"Any& ArrayAny::get(Int index) {\n"
"    return *array.at(index.value);\n"
"}\n"
"\n"
"Any& ArrayAny::set(Int index, Any& obj) {\n"
"    Any *buf = array.at(index.value);\n"
"    array[index.value] = &obj;\n"
"    return *buf;\n"
"}\n"
"\n"
"//String Null::toString() {\n"
"//    return String(\"Null\");\n"
"//}\n"
"\n"
"string Null::_type_() {\n"
"    return \"Null\";\n"
"}\n"
"\n"
"void Boolean::operator=(const bool& other) {\n"
"    this->value = other;\n"
"}\n"
"\n"
"Boolean Boolean::operator!() {\n"
"    return Boolean(!value);\n"
"}\n"
"\n"
"Int Int::operator+(const Int& other) {\n"
"    return Int(value + other.value);\n"
"}\n"
"\n"
"Int Int::operator+(const int& other) {\n"
"    return Int(value + other);\n"
"}\n"
"\n"
"Int Int::operator-(const Int& other) {\n"
"    return Int(value - other.value);\n"
"}\n"
"\n"
"Int Int::operator-(const int& other) {\n"
"    return Int(value - other);\n"
"}\n"
"\n"
"Int Int::operator-() {\n"
"    return Int(-value);\n"
"}\n"
"\n"
"Int Int::operator*(const Int& other) {\n"
"    return Int(value * other.value);\n"
"}\n"
"\n"
"Int Int::operator*(const int& other) {\n"
"    return Int(value * other);\n"
"}\n"
"\n"
"Int Int::operator/(const Int& other) {\n"
"    return Int(value / other.value);\n"
"}\n"
"\n"
"Int Int::operator/(const int& other) {\n"
"    return Int(value / other);\n"
"}\n"
"\n"
"void Int::operator=(const Int& other) {\n"
"    value = other.value;\n"
"}\n"
"\n"
"void Int::operator=(const int& other) {\n"
"    value = other;\n"
"}\n"
"\n"
"Boolean Int::operator<(const Int& other) {\n"
"    return value < other.value;\n"
"}\n"
"\n"
"Boolean Int::operator<(const int& other) {\n"
"    return value < other;\n"
"}\n"
"\n"
"Boolean Int::operator<=(const Int& other) {\n"
"    return value <= other.value;\n"
"}\n"
"\n"
"Boolean Int::operator<=(const int& other) {\n"
"    return value <= value;\n"
"}\n"
"\n"
"Boolean Int::operator==(const Int& other) {\n"
"    return Boolean(value == other.value);\n"
"}\n"
"\n"
"Boolean Int::operator==(const int& other) {\n"
"    return Boolean(value == other);\n"
"}\n"
"\n"
"void String::operator=(const string& other) {\n"
"    str_field = other;\n"
"}\n"
"";


auto mainProgram = "#include \"cfg.h\"\n"
"int main(int argc, char** argv)\n"
"{\n"
"   Main();\t\n"
"   return 0;\n"
"}";

#endif /* COMPILESOURCES_H */


