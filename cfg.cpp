#include "cfg.h"

string Main::_type_(){
	return "Main";
}

Boolean Main::pal(String s){
return (s .length() == Int(0) ) ? Boolean(true) : (s .length() == Int(1) ) ? Boolean(true) : (s .charAt(Int(0) ) == s .charAt(s .length()- Int(1) )) ? pal(s .substring(Int(1) , s .length()- Int(1) )): Boolean(false) ;
}

Main::Main() : IO(){
out(String("enter a string\n"));
(pal(in())) ? out(String("that was a palindrome\n")): out(String("that was not a palindrome\n"));
}

#include "cfg.h"

string Sieve::_type_(){
	return "Sieve";
}

Unit Sieve::test(Int n){
return (prime * (n / prime ) == n ) ? Unit() : (is_null(next )) ? out_any(n ), out(String(" ")), next = Sieve(n ), : next .test(n );
}

Sieve::Sieve(Int prime) : IO(), prime(prime){
}

string Main::_type_(){
	return "Main";
}

Main::Main() : IO(){
Sieve s = Sieve(Int(2) );
Int i = Int(2) ;
out(String("2 "));
while(Boolean(true) ){
i = i + Int(1) ;
s .test(i );
}
;
}

