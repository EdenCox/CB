%{
#include "parser.h"
#include "TypeChecker.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <map>
#include <list>
#include <string>
#include <stdio.h>
//#include "lex.yy.c"



using namespace std;
#define YYDEBUG 1
// the root of the abstract syntax tree

Program *root;

// stuff from flex that bison needs to know about:

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int line_num;
extern "C" void nextFile(FILE *bffr);
 
void yyerror(const char *s);
%}
// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	bool booleanVal;
	int integerVal;	
	char *stringVal;
	char *tripleStringVal;
	char *object_IdentifierVal;
	char *type_IdentifierVal;
	class Program *program;
	class Classdecl *classdecl;
    	class Classdecls *classdecls;
	class Vfcontent *vfcontent;
    	class Vfcontents *vfcontents;
	class Feature *feature;
    	class Features *features;
	class Formalcontents *formals;
	class Formalcontent *formalcontent;
    	class Formalcontents  *formalcontents;
	class Actuals *actuals;
	class Block *block;
      	class BlockExpression *blockexpression;
	class Exp_node *expression;
   	class Actuals *actualscontent;
	class Casecontent *casecontent;	
    	class Cases *cases;
	char *error_msg;
}

// define the constant-string tokens:
%token ASSIGN CASE CLASS DARROW DEF ELSE EXTENDS EQ_OP IF NATIVE NEW NUL OVERRIDE SUPER THIS VAR WHILE
%token SEMICOLON COLON COMMA
%token OPEN_ACCOLADE CLOSE_ACCOLADE OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_BRACKETS CLOSE_BRACKETS//{}()[]
%token ENDOFILE

/* Declare types for the grammar's non-terminals. */
%type <program> program	
%type <classdecls> classdecls
%type <classdecl> classdecl
%type <vfcontent> vfcontent
%type <vfcontents> vfcontents
%type <features> features
%type <feature> feature	
%type <formalcontents> formals
%type <formalcontent> formalcontent
%type <formalcontents> formalcontents
%type <actuals> actuals
%type <block> block 
%type <block> blockexpressions
%type <blockexpression> blockexpression
%type <expression> expression
%type <actuals> actualscontent
%type <casecontent> casecontent
%type <cases> cases
%type <cases> casecontents

/* Precedence declarations */
%right ASSIGN
%nonassoc IFWHILE
%left MATCH
%left LE LT EQ_OP
%left PLUS MINUS
%left MULTIPLY DIVIDE
%right NOT UMINUS
%left DOT

%token ENDL

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <error_msg>  ERROR
%token <booleanVal> BOOLEAN_CONST
%token <integerVal> INTEGER_CONST
%token <stringVal> STRING_LITERAL
%token <tripleStringVal> TRIPLE_STRING_LITERAL
%token <object_IdentifierVal> OBJECT_IDENTIFIER
%token <type_IdentifierVal> TYPE_IDENTIFIER

%%


program:
	classdecls { $$ = new Program($1); root = $$; }	
	;
classdecls:
	classdecls classdecl {$1->append($2); $$ = $1;} |
	classdecl {$$ = new Classdecls($1);}       
	;
classdecl:
	CLASS TYPE_IDENTIFIER OPEN_PARENTHESES vfcontents CLOSE_PARENTHESES OPEN_ACCOLADE CLOSE_ACCOLADE {$$ = new Classdecl($2,$4,"Any",new Actuals(),new Features());}/*class C(F ) { X } =) class C(F ) extends Any() { X }*/|
	CLASS TYPE_IDENTIFIER OPEN_PARENTHESES vfcontents CLOSE_PARENTHESES OPEN_ACCOLADE features CLOSE_ACCOLADE 
	{$$ = new Classdecl($2,$4,"Any",new Actuals(),$7);}/*class C(F ) { X } =) class C(F ) extends Any() { X }*/|
	CLASS TYPE_IDENTIFIER OPEN_PARENTHESES vfcontents CLOSE_PARENTHESES EXTENDS TYPE_IDENTIFIER actuals
	OPEN_ACCOLADE features CLOSE_ACCOLADE {$10->append(new F_block(new Block(new NormalExpression(new This_exp()))));$$ = new Classdecl($2,$4,$7,$8,$10);}
	/*class C(F ) extends C 0 (A) { X } =) class C(F ) extends C 0 (A) { X { this }}*/|
	CLASS TYPE_IDENTIFIER OPEN_PARENTHESES vfcontents CLOSE_PARENTHESES EXTENDS NATIVE OPEN_ACCOLADE features CLOSE_ACCOLADE
	{$$ = new Classdecl($2,$4,"native",new Actuals(),$9);}|
	/*Error handling for class bodies*/
	CLASS error OPEN_PARENTHESES vfcontents CLOSE_PARENTHESES OPEN_ACCOLADE features CLOSE_ACCOLADE { yyclearin; $$ = NULL; }|
	CLASS TYPE_IDENTIFIER OPEN_PARENTHESES error CLOSE_PARENTHESES OPEN_ACCOLADE features CLOSE_ACCOLADE {yyclearin; $$ = NULL; }
	;

vfcontents:
	vfcontents COMMA vfcontent {$1->append($3); $$ = $1;}|
	vfcontent {$$ = new Vfcontents($1);}|
	{$$ = new Vfcontents();}
	;

vfcontent:
	VAR OBJECT_IDENTIFIER COLON TYPE_IDENTIFIER {$$ = new Vfcontent($2,$4);}
	;

features:
	features feature {$1->append($2); $$ = $1;}|
	feature {$$ = new Features($1);}|
	error {yyclearin; $$ = NULL; }
	;

feature:
	OVERRIDE DEF OBJECT_IDENTIFIER formals COLON TYPE_IDENTIFIER ASSIGN expression SEMICOLON 
	{$$ = new F_overide_expr($3,$4,$6,$8);}|
	OVERRIDE DEF OBJECT_IDENTIFIER formals COLON TYPE_IDENTIFIER ASSIGN NATIVE SEMICOLON
	{$$ = new F_overide_nat($3,$4,$6);} |
	DEF OBJECT_IDENTIFIER formals COLON TYPE_IDENTIFIER ASSIGN expression SEMICOLON 
	{$$ = new F_expr($2,$3,$5,$7);}|
	DEF OBJECT_IDENTIFIER formals COLON TYPE_IDENTIFIER ASSIGN NATIVE SEMICOLON 
	{$$ = new F_nat($2,$3,$5);} |
	VAR OBJECT_IDENTIFIER ASSIGN NATIVE SEMICOLON 
	{$$ = new F_var_nat($2);}|
	VAR OBJECT_IDENTIFIER COLON TYPE_IDENTIFIER ASSIGN expression SEMICOLON 
	{$$ = new F_var_exp($2,$4,$6);}|
	OPEN_ACCOLADE block CLOSE_ACCOLADE SEMICOLON
	{$$ = new F_block($2);}
	;

formals:
	OPEN_PARENTHESES CLOSE_PARENTHESES {$$ = new Formalcontents();}|
	OPEN_PARENTHESES formalcontents CLOSE_PARENTHESES {$$ = $2;}
	;

formalcontents:
	formalcontents COMMA formalcontent {$1->append($3); $$ = $1;} |
	formalcontent {$$ = new Formalcontents($1);}
	;

formalcontent:
	OBJECT_IDENTIFIER COLON TYPE_IDENTIFIER {$$ = new Formalcontent($1,$3);}
	;
actuals:
	OPEN_PARENTHESES CLOSE_PARENTHESES{$$ = new Actuals();}|
	OPEN_PARENTHESES actualscontent CLOSE_PARENTHESES{$$ = $2;}
	;
actualscontent:
	actualscontent COMMA expression {$1->append($3); $$ = $1;}|
	expression {$$ = new Actuals($1);}
	;

block:
	blockexpressions {$$ = $1;}	
	;

blockexpressions:
	blockexpressions SEMICOLON blockexpression {$1->append($3); $$ = $1;}|
	blockexpression	{$$ = new Block($1);}
	;

blockexpression:
	VAR OBJECT_IDENTIFIER COLON TYPE_IDENTIFIER ASSIGN expression {$$ = new InilizationBlockExpression($2,$4,$6);}|
	expression {$$ = new NormalExpression($1);}
	;	

expression: 
	OBJECT_IDENTIFIER ASSIGN expression {$$ = new Assign_exp($1,$3);}|
	NOT expression {$$ = new Not_exp($2); }|
	MINUS expression %prec UMINUS {$$ = new Uminus_exp($2);}| 
	IF OPEN_PARENTHESES expression CLOSE_PARENTHESES expression ELSE expression %prec IFWHILE 
	{$$ = new Cond_exp($3,$5,$7);}|
	WHILE OPEN_PARENTHESES expression CLOSE_PARENTHESES expression %prec IFWHILE 
	{$$ = new Loop_exp($3,$5);}| 
	SUPER DOT OBJECT_IDENTIFIER actuals {$$ = new Super_exp($3,$4);}| 
	OBJECT_IDENTIFIER actuals {$$ = new Object_exp($1,$2);}|
 	NEW TYPE_IDENTIFIER actuals {/*$$ = new Dot_object_exp(new Paren_exp(new Object_id_exp($2)),$2,$3);*/$$ = new Newtype_exp($2,$3);}
	/*new C(A) =) (new C).C(A)*/| 
	OPEN_ACCOLADE block CLOSE_ACCOLADE {$$ = new Block_exp($2);}|  
	OPEN_BRACKETS CLOSE_BRACKETS {$$ = new Empty_exp();}| 
	OPEN_PARENTHESES expression CLOSE_PARENTHESES {$$ = new Paren_exp($2);}| 
	expression DOT OBJECT_IDENTIFIER actuals {$$ = new Dot_object_exp($1,$3,$4);}| 
	expression MATCH cases {$$ = new Case_exp($1,$3);}|
	expression LE expression {$$ = new Leq_exp($1,$3);}| 
	expression LT expression {$$ = new Less_exp($1,$3);}| 
	expression EQ_OP expression {$$ = new Eq_exp($1,$3);}| 
	expression MULTIPLY expression {$$ = new Mul_exp($1,$3);}| 
	expression DIVIDE expression {$$ = new Div_exp($1,$3);}| 
	expression PLUS expression {$$ = new Add_exp($1,$3);}| 
	expression MINUS expression {$$ = new Min_exp($1,$3);} | 
	NUL {$$ = new Null_exp();}| 
	OPEN_PARENTHESES CLOSE_PARENTHESES {$$ = new Empty_exp();}| 
	OBJECT_IDENTIFIER {$$ = new Object_id_exp($1);}| 
	INTEGER_CONST {$$ = new Int_const_exp($1);}| 
	STRING_LITERAL {$$ = new String_lit_exp($1);}| 
	BOOLEAN_CONST {$$ = new Bool_exp($1); }| 
	THIS {$$ = new This_exp();}|
	error {yyclearin; $$ = NULL; }
	;

cases:
	OPEN_ACCOLADE casecontents CLOSE_ACCOLADE {$$ = $2;}
	;

casecontents:
	casecontents casecontent {$1->append($2); $$ = $1;} |
	casecontent {$$ = new Cases($1);}
	;

casecontent:
	CASE OBJECT_IDENTIFIER COLON TYPE_IDENTIFIER DARROW block {$$ = new Casecontent($2,$4,$6);}|/*case i:T => E =) case i:T => { E }*/
	CASE NUL DARROW block {$$ = new Casecontent((char *)"null",(char *)"Null",$4);} /*case null => E =) case null:Null => E*/
	;

%%

int main(int argc, char *argv[]) {

	if(argc  <= 1){
		cout<<"No Filename(s) given to parse"<<endl;
		return -1;
	}
	std::ofstream baseFile("tempPars", std::ios_base::binary | std::ios_base::app);
	std::ifstream first("basic.cool", std::ios_base::binary);

	baseFile<< first.rdbuf();
	for (int i = 1; i < argc; ++i) {
       	   	cout << argv[i] << std::endl;
		std::ifstream rest(argv[i], std::ios_base::binary);
		baseFile<<rest.rdbuf();
    	}
	baseFile<<endl;

	FILE *myfile = fopen("tempPars", "r");
	if (!myfile) {
		cout << "can't open generated file." << endl;
		return -1;
	}
	// set lex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	yyparse();

	remove( "tempPars" );//remove temp reading file.

	TypeChecker* checker = new TypeChecker();
	root->accept(checker);
	
	
	//root->print(0);

}

void yyerror(const char *s) {
	cout << "EEK, parse error on line " << line_num << "!  Message: " << s << endl;
	exit(-1);
}
