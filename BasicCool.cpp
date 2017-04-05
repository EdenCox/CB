/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BasicCool.cpp
 * Author: easy
 * 
 * Created on February 23, 2017, 2:53 PM
 */

#include "BasicCool.h"

Any::Any() {
}

String Any::toString() {
    return String("this is an \"Any\" object.");
}

Boolean Any::equals(Any &other) {
    return this == &other;
}

string Any::_type_() {
    return "Any";
}

IO::IO() : Any() {
}

string IO::_type_() {
    return "IO";
}

Nothing IO::abort(String message) {
    cout << message.str_field << endl;
    exit(EXIT_FAILURE);
    return Nothing();
}

IO IO::out(String arg) {
    cout << arg.str_field << endl;
    return IO();
}

Boolean IO::is_null(Any &arg) {
    return Boolean(arg._type_() == "Null");
}

IO IO::out_any(Any arg) {
    out(arg.toString().str_field);
}

String IO::in() {
    string in;
    cin>>in;
    return String(in);
}

Symbol IO::symbol(String name) {
    return Symbol(name.str_field);
}

String IO::symbol_name(Symbol sym) {
    return String(sym.name);
}

Int::Int(int value) : value(value) {

}

Int::Int(const Int& obj) {
    value = obj.value;
}

String Int::toString() {
    return String(std::to_string(value));
}

string Int::_type_() {
    return "Int";
}

Boolean Int::equals(Any &other) {
    if (other._type_() == "Int") {
        return dynamic_cast<Int&> (other).value == value;
    }
    return false;
}

Boolean Int::equals(Int &other) {
    return Boolean(value == other.value);
}

Boolean::Boolean(bool value) : value(value) {

}

//Boolean::Boolean(Boolean &other) {
//    this->value = other.value;
//}

string Boolean::_type_() {
    return "Boolean";
}

String Boolean::toString() {
    return String(value ? "true" : "false");
}

Boolean Boolean::equals(Any &other) {
    if (other._type_() == "Boolean") {
        return dynamic_cast<Boolean&> (other).value == value;
    }
    return false;
}

Boolean Boolean::equals(Boolean &other) {
    return (Boolean(value == other.value));
}

String::String(string str) {
    str_field = str;
}

string String::_type_() {
    return "String";
}

Boolean String::equals(Any &other) {
    if (other._type_() == "String") {
        return dynamic_cast<String&> (other).str_field == str_field;
    }
    return false;
}

Boolean String::equals(String &other) {
    return Boolean(str_field == other.str_field);
}

String String::toString() {
    return String(str_field);
}

Int String::length() {
    return Int(str_field.size());
}

String String::concat(String arg) {
    return String(str_field + arg.str_field);
}

String String::substring(Int start, Int end) {
    if (start.value >= str_field.size()) {
        cout << "Index: out of bounce\nString size: " << str_field.size() << "\n start Index given: " << start.value << endl;
        exit(EXIT_FAILURE);
    }
    return String(str_field.substr(start.value, end.value - start.value));
}

Int String::charAt(Int index) {
    return Int(str_field.at(index.value));
}

Int String::indexOf(String sub) {

    return Int(str_field.find(sub.str_field, 0));
}

Symbol::Symbol(string name) : name(name) {

}

string Symbol::_type_() {
    return "Symbol";
}

String Symbol::toString() {
    return String("." + name);
}

Int Symbol::hashCode() {

    return std::hash<std::string>{}
    (name);
}

ArrayAny::ArrayAny(Int len) : len(len) {
    array.resize(len.value);
}

ArrayAny::ArrayAny(Int len, vector<Any*> array) : len(len), array(array) {
}

string ArrayAny::_type_() {
    return "ArrayAny";
}

Int ArrayAny::length() {
    return Int(len);
}

ArrayAny ArrayAny::resize(Int s) {
    return ArrayAny(s, array);
}

Any& ArrayAny::get(Int index) {
    return *array.at(index.value);
}

Any& ArrayAny::set(Int index, Any& obj) {
    Any *buf = array.at(index.value);
    array[index.value] = &obj;
    return *buf;
}

//String Null::toString() {
//    return String("Null");
//}

string Null::_type_() {
    return "Null";
}

void Boolean::operator=(const bool& other) {
    this->value = other;
}

Boolean Boolean::operator!() {
    return Boolean(!value);
}

Int Int::operator+(const Int& other) {
    return Int(value + other.value);
}

Int Int::operator+(const int& other) {
    return Int(value + other);
}

Int Int::operator-(const Int& other) {
    return Int(value - other.value);
}

Int Int::operator-(const int& other) {
    return Int(value - other);
}

Int Int::operator-() {
    return Int(-value);
}

Int Int::operator*(const Int& other) {
    return Int(value * other.value);
}

Int Int::operator*(const int& other) {
    return Int(value * other);
}

Int Int::operator/(const Int& other) {
    return Int(value / other.value);
}

Int Int::operator/(const int& other) {
    return Int(value / other);
}

void Int::operator=(const Int& other) {
    value = other.value;
}

void Int::operator=(const int& other) {
    value = other;
}

Boolean Int::operator<(const Int& other) {
    return value < other.value;
}

Boolean Int::operator<(const int& other) {
    return value < other;
}

Boolean Int::operator<=(const Int& other) {
    return value <= other.value;
}

Boolean Int::operator<=(const int& other) {
    return value <= value;
}

Boolean Int::operator==(const Int& other) {
    return Boolean(value == other.value);
}

Boolean Int::operator==(const int& other) {
    return Boolean(value == other);
}

void String::operator=(const string& other) {
    str_field = other;
}



