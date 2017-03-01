#include "cfg.h"

string Useful::_type_(){
	return "Useful";
}

Boolean Useful::and(Boolean& b1, Boolean& b2){
(b1 ) ? b2 : false ;
}

string Canvas::_type_(){
	return "Canvas";
}

Int Canvas::get_width(){
width }

Int Canvas::get_height(){
height ;
}

ArrayAny Canvas::get_column(Int& x){
;
}

Canvas Canvas::mark(Int& x, Int& y, Color& c){
return (and(and(0 <= x , x < width ), and(0 <= y , y < height ))) ? get_column(x ).set(y , c .get_shade()), *this , : *this ;
}

IO Canvas::dump_ascii(IO& io){
Int j = height - 1 ;
while(0 <= j ){
Int i = 0 ;
while(i < width ){
;
i = i + 1 ;
}
;
io .out("\n");
return j = j - 1 ;
}
;
return io ;
}

string Color::_type_(){
	return "Color";
}

String Color::get_shade(){
shade ;
}

string Delta::_type_(){
	return "Delta";
}

Int Delta::get_delta_x(){
dx ;
}

Int Delta::get_delta_y(){
dy ;
}

Delta Delta::add(Delta& d){
dx = dx + d .get_delta_x();
dy = dy + d .get_delta_y();
return *this ;
}

Delta Delta::plus(Delta& d){
return Delta(dx + d .get_delta_x(), dy + d .get_delta_y());
}

Delta Delta::divide(Int& i){
return Delta(dx / i , dy / i );
}

Boolean Delta::equals(Any& other){
return ;
}
string Shape::_type_(){
	return "Shape";
}

Color Shape::get_color(){
color ;
}

Canvas Shape::draw(Canvas& c){
abort("draw is abstract");
}

Shape Shape::move(Delta& d){
abort("move is abstract");
}

string Point::_type_(){
	return "Point";
}

Int Point::get_x(){
x ;
}

Int Point::get_y(){
y ;
}

Canvas Point::draw(Canvas& can){
return can .mark(x , y , color );
}
Point Point::move(Delta& d){
x = x + d .get_delta_x();
y = y + d .get_delta_y();
return *this ;
}
Point Point::plus(Delta& d){
return Point(color , x , y ).move(d );
}

Delta Point::minus(Point& p){
return Delta(x - p .get_x(), y - p .get_y());
}

Boolean Point::equals(Any& o){
return ;
}
string CenteredShape::_type_(){
	return "CenteredShape";
}

Point CenteredShape::get_center(){
center ;
}

CenteredShape CenteredShape::move(Delta& d){
center = center .plus(d );
return *this ;
}
string Group::_type_(){
	return "Group";
}

CenteredShape Group::get(Int& i){
return ;
}

Group Group::add(CenteredShape& s){
shapes .add(s );
compute_center();
return *this ;
}

Point Group::compute_center(){
Int n = shapes .size();
Point origin = Point(color , 0 , 0 );
Delta sum = Delta(0 , 0 );
Int i = 0 ;
while(i < n ){
Point p1 = get(i ).get_center();
sum .add(p1 .minus(origin ));
i = i + 1 ;
}
;
return (0 < n ) ? center = origin .move(sum .divide(n )), center , : center , ;
}

Group Group::move(Delta& d){
super.move(d );
Int n = shapes .size();
Int i = 0 ;
while(i < n ){
get(i ).move(d );
i = i + 1 ;
}
;
return *this ;
}
Canvas Group::draw(Canvas& can){
Int n = shapes .size();
Int i = 0 ;
while(i < n ){
get(i ).draw(can );
i = i + 1 ;
}
;
return can ;
}
string Line::_type_(){
	return "Line";
}

Int Line::get_length(){
length }

Boolean Line::get_horizontal(){
horiz ;
}

Point Line::get_point1(){
center .plus(Delta((horiz ) ? -length / 2 : 0 , (horiz ) ? 0 : -length / 2 ));
}

Point Line::get_point2(){
center .plus(Delta((horiz ) ? length + -length / 2 : 0 , (horiz ) ? 0 : length + -length / 2 ));
}

Canvas Line::draw(Canvas& can){
Point p = get_point1();
Point pend = get_point2();
Delta d = Delta((horiz ) ? 1 : 0 , (horiz ) ? 0 : 1 );
p .draw(can );
while(!(p  == pend )){
p .move(d );
p .draw(can );
}
;
return can ;
}
string Rectangle::_type_(){
	return "Rectangle";
}

Int Rectangle::get_width(){
width ;
}

Int Rectangle::get_height(){
height ;
}

Point Rectangle::get_lower_left(){
return get_center().plus(Delta(-width / 2 , -height / 2 ));
}

Point Rectangle::get_lower_right(){
return get_center().plus(Delta(width - width / 2 , -height / 2 ));
}

Point Rectangle::get_upper_left(){
return get_center().plus(Delta(-width / 2 , height - height / 2 ));
}

Point Rectangle::get_upper_right(){
return get_center().plus(Delta(width - width / 2 , height - height / 2 ));
}

Canvas Rectangle::draw(Canvas& can){
Point ll = get_lower_left();
Point lr = get_lower_right();
Point ul = get_upper_left();
Point ur = get_upper_right();
Line(color , ul , ur ).draw(can );
Line(color , ll , lr ).draw(can );
Line(color , ll , ul ).draw(can );
return Line(color , lr , ur ).draw(can );
}
string Square::_type_(){
	return "Square";
}

Int Square::get_size(){
size ;
}

string Block::_type_(){
	return "Block";
}

Canvas Block::draw(Canvas& can){
Point ul = get_upper_left();
Point l = get_lower_left();
Point r = get_lower_right();
Delta up1 = Delta(0 , 1 );
while(l .get_y()<= ul .get_y()){
Line(color , l , r ).draw(can );
l .move(up1 );
r .move(up1 );
*this ;
}
;
return can ;
}
string Main::_type_(){
	return "Main";
}

*this string ArrayList::_type_(){
	return "ArrayList";
}

ArrayList ArrayList::add(Any& item){
return insert(size , item );
}

Any ArrayList::get(Int& index){
return (index < 0 ) ? abort("ArrayList.get: negative index"), : (size <= index ) ? abort("ArrayList.get: index too large"), : array .get(index ), ;
;
}

Any ArrayList::set(Int& index, Any& item){
return (index < 0 ) ? abort("ArrayList.set: negative index"), : (size <= index ) ? abort("ArrayList.set: index too large"), : array .set(index , item ), ;
;
}

Int ArrayList::size(){
size ;
}

ArrayList ArrayList::resize(Int& n){
(n < 0 ) ? abort("ArrayList.resize: negative size"), : Unit() ;
while(array .length()< n ){
array = array .resize(array .length()* 2 );
}
;
while(size < n ){
array .set(size , Null() );
size = size + 1 ;
}
;
size = n ;
return *this ;
}

ArrayList ArrayList::insert(Int& index, Any& item){
(index < 0 ) ? abort("ArrayList.insert: negative index"), : (size < index ) ? abort("ArrayList.insert: index too large"), : size = size + 1 , resize(size ), Int j = size - 1 , while(index < j ){
array .set(j , array .get(j - 1 )), j = j - 1 , }
, array .set(index , item ), ;
;
return *this ;
}

