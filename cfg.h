#ifndef CGF_H
#define CGF_H

#include "BasicCool.h"

using namespace std;

class Main : public IO {
private:
typedef IO super;
protected:
public:
Main();
string _type_() override;
virtual Boolean pal(String s);

};

#endif /* CGF_H */

#ifndef CGF_H
#define CGF_H

#include "BasicCool.h"

using namespace std;

class Sieve : public IO {
private:
typedef IO super;
protected:
Int prime;
public:
Sieve(Int prime);
string _type_() override;
private:
Sieve next = Null() ;
public:
virtual Unit test(Int n);

};

class Main : public IO {
private:
typedef IO super;
protected:
public:
Main();
string _type_() override;

};

#endif /* CGF_H */

