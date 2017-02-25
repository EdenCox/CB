#include "BasicCool.h"

#ifndef CGF_H
#define CGF_H

using namespace std;

class Useful : public IO {
private:
typedef IO super;
protected:
public:
Useful();
string _type_() override;
virtual Boolean and(Boolean& b1, Boolean& b2);

};

class Canvas : public Useful {
private:
typedef Useful super;
protected:
Int width;
Int height;
public:
Canvas(Int width, Int height);
string _type_() override;
private:
ArrayAny marks = ArrayAny(width );
public:
virtual Int get_width();
virtual Int get_height();
virtual ArrayAny get_column(Int& x);
virtual Canvas mark(Int& x, Int& y, Color& c);
virtual IO dump_ascii(IO& io);

};

class Color : public Any {
private:
typedef Any super;
protected:
String shade;
public:
Color(String shade);
string _type_() override;
virtual String get_shade();

};

class Delta : public Useful {
private:
typedef Useful super;
protected:
Int dx;
Int dy;
public:
Delta(Int dx, Int dy);
string _type_() override;
virtual Int get_delta_x();
virtual Int get_delta_y();
virtual Delta add(Delta& d);
virtual Delta plus(Delta& d);
virtual Delta divide(Int& i);
Boolean equals(Any& other) override;

};

class Shape : public Useful {
private:
typedef Useful super;
protected:
Color color;
public:
Shape(Color color);
string _type_() override;
virtual Color get_color();
virtual Canvas draw(Canvas& c);
virtual Shape move(Delta& d);

};

class Point : public Shape {
private:
typedef Shape super;
protected:
Color c;
Int x;
Int y;
public:
Point(Color c, Int x, Int y);
string _type_() override;
virtual Int get_x();
virtual Int get_y();
Canvas draw(Canvas& can) override;
Point move(Delta& d) override;
virtual Point plus(Delta& d);
virtual Delta minus(Point& p);
Boolean equals(Any& o) override;

};

class CenteredShape : public Shape {
private:
typedef Shape super;
protected:
Color c;
Point center;
public:
CenteredShape(Color c, Point center);
string _type_() override;
virtual Point get_center();
CenteredShape move(Delta& d) override;

};

class Group : public CenteredShape {
private:
typedef CenteredShape super;
protected:
public:
Group();
string _type_() override;
private:
ArrayList shapes = ArrayList();
public:
virtual CenteredShape get(Int& i);
virtual Group add(CenteredShape& s);
virtual Point compute_center();
Group move(Delta& d) override;
Canvas draw(Canvas& can) override;

};

class Line : public CenteredShape {
private:
typedef CenteredShape super;
protected:
Color cl;
Point p1;
Point p2;
public:
Line(Color cl, Point p1, Point p2);
string _type_() override;
private:
Int length = 0 ;
public:
private:
Boolean horiz = false ;
public:
virtual Int get_length();
virtual Boolean get_horizontal();
virtual Point get_point1();
virtual Point get_point2();
Canvas draw(Canvas& can) override;

};

class Rectangle : public CenteredShape {
private:
typedef CenteredShape super;
protected:
Color cl;
Point cp;
Int width;
Int height;
public:
Rectangle(Color cl, Point cp, Int width, Int height);
string _type_() override;
virtual Int get_width();
virtual Int get_height();
virtual Point get_lower_left();
virtual Point get_lower_right();
virtual Point get_upper_left();
virtual Point get_upper_right();
Canvas draw(Canvas& can) override;

};

class Square : public Rectangle {
private:
typedef Rectangle super;
protected:
Color cs;
Point cps;
Int size;
public:
Square(Color cs, Point cps, Int size);
string _type_() override;
virtual Int get_size();

};

class Block : public Rectangle {
private:
typedef Rectangle super;
protected:
Color cb;
Point p;
Int w;
Int h;
public:
Block(Color cb, Point p, Int w, Int h);
string _type_() override;
Canvas draw(Canvas& can) override;

};

class Main : public IO {
private:
typedef IO super;
protected:
public:
Main();
string _type_() override;
private:
Color white = Color(" ");
public:
private:
Color gray1 = Color("`");
public:
private:
Color gray2 = Color("^");
public:
private:
Color gray3 = Color("C");
public:
private:
Color gray4 = Color("X");
public:
private:
Color gray5 = Color("@");
public:
private:
Color gray6 = Color("M");
public:
private:
Color gray7 = Color("#");
public:
private:
Canvas canvas = Canvas(79 , 40 );
public:

};

class ArrayList : public IO {
private:
typedef IO super;
protected:
public:
ArrayList();
string _type_() override;
private:
ArrayAny array = ArrayAny(1 );
public:
private:
Int size = 0 ;
public:
virtual ArrayList add(Any& item);
virtual Any get(Int& index);
virtual Any set(Int& index, Any& item);
virtual Int size();
virtual ArrayList resize(Int& n);
virtual ArrayList insert(Int& index, Any& item);

};

#endif /* CGF_H */

