%{
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "parser.tab.h"


using namespace std;

#define YY_DECL extern "C" int yylex()
#define MAX_STR_CONST 1025

int line_num = 1;
int string_length = 0;
int nesting = 0;
char string_buf[MAX_STR_CONST]; /* to assemble string constants  va*/
char *string_buf_ptr;

void addToStr(char* str);
bool strTooLong();
void resetStr();
int strLenErr();
int reservedKeywordError();
extern "C" void nextFile(FILE *bffr);



%}

DIGIT		[0-9]
ALPANUMERIC	[0-9A-Za-z_]
LETTER		[A-Za-z]
LOWERCASE 	[a-z]
UPPERCASE 	[A-Z]
NOTZERO		[1-9]
ZERO 		[0]
INTEGER		{ZERO}|{NOTZERO}{DIGIT}*

%x MULTILINE_COMMENT
%x SINGLELINE_COMMENT
%x STRING
%x BROKENSTRING
%x DQ_STRING_LITERALS
%x TQ_STRING_LITERALS

%%



\/\/				{ BEGIN(SINGLELINE_COMMENT); }
<SINGLELINE_COMMENT>\n		{ ++line_num; BEGIN(INITIAL); }
<SINGLELINE_COMMENT>.		{}

\/\*                 		{ BEGIN(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>\/\*   	{ ++nesting; }
<MULTILINE_COMMENT>\*\/ 	{ if(--nesting <= 0){ BEGIN(INITIAL); } }
<MULTILINE_COMMENT>\n     	{ ++line_num; } 
<MULTILINE_COMMENT>.	  	{}

\"            { 
                    // "starting tag
		    
                    BEGIN(STRING);
                }
<STRING>\"    { 
                    // Closing tag"
                    yylval.stringVal = strdup(string_buf);
                    resetStr();
                    BEGIN(INITIAL);
                    return(STRING_LITERAL);
                }
<STRING>(\0|\\\0) {
                      yylval.error_msg = (char *)"String contains null character";
                      BEGIN(BROKENSTRING);
                      return(ERROR);
                }
<BROKENSTRING>.*[\"\n] {
                    //"//Get to the end of broken string
                    BEGIN(INITIAL);
                }

<STRING>\n      {   
                    // unescaped new line
                    line_num++; 
                    BEGIN(INITIAL);
                    resetStr();
                    yylval.error_msg = (char *)"Unterminated string constant";
                    return(ERROR);
                }

<STRING><<EOF>> {   
                    BEGIN(INITIAL);
                    yylval.error_msg = (char *)"EOF in string constant";
                    return(ERROR);
                }

<STRING>\\n      {  // escaped slash, then an n
                    if (strTooLong()) { return strLenErr(); }
                    line_num++; 
                    addToStr((char *)"\n");
                }

<STRING>\\t     {
                    if (strTooLong()) { return strLenErr(); }
                    string_length++;
                    addToStr((char *)"\t");
}
<STRING>\\b     {
                    if (strTooLong()) { return strLenErr(); }
                    string_length++;
                    addToStr((char *)"\b");
}
<STRING>\\f     {
                    if (strTooLong()) { return strLenErr(); }
                    string_length++;
                    addToStr((char *)"\f");
}
<STRING>\\.     {
                    //escaped character, just add the character
                    if (strTooLong()) { return strLenErr(); }
                    string_length++;
                    addToStr(&strdup(yytext)[1]);
                }
<STRING>.       {   
                    if (strTooLong()) { return strLenErr(); }
                    addToStr(yytext);
                    string_length++;
                }


\"\"\"					{ BEGIN(TQ_STRING_LITERALS); }
<TQ_STRING_LITERALS>(.|\n)*\"\"\"	{ yylval.tripleStringVal = strdup(yytext); BEGIN(INITIAL); return TRIPLE_STRING_LITERAL; }

case		{ return CASE; }
class	        { return CLASS; }
def		{ return DEF; }
else            { return ELSE; }
extends		{ return EXTENDS; }
false		{ yylval.booleanVal = false; return BOOLEAN_CONST; }
if         	{ return IF; }
match 		{ return MATCH; }
native		{ return NATIVE; }
new 		{ return NEW; }
null 		{ return NUL; }
override	{ return OVERRIDE; }
super		{ return SUPER; }
this		{ return THIS; }
true		{ yylval.booleanVal = true; return BOOLEAN_CONST; }
var		{ return VAR; }
while		{ return WHILE; }

abstract	{return reservedKeywordError();}
catch 		{return reservedKeywordError();}
do 		{return reservedKeywordError();}
final 		{return reservedKeywordError();}
finally 	{return reservedKeywordError();}
for 		{return reservedKeywordError();}
forSome 	{return reservedKeywordError();}
implicit 	{return reservedKeywordError();}
import		{return reservedKeywordError();}
lazy 		{return reservedKeywordError();}
object 		{return reservedKeywordError();}
package 	{return reservedKeywordError();}
private 	{return reservedKeywordError();}
protected 	{return reservedKeywordError();}
requires 	{return reservedKeywordError();}
return 		{return reservedKeywordError();}
sealed 		{return reservedKeywordError();}
throw 		{return reservedKeywordError();}
trait 		{return reservedKeywordError();}
try 		{return reservedKeywordError();}
type 		{return reservedKeywordError();}
val 		{return reservedKeywordError();}
with		{return reservedKeywordError();}
yield		{return reservedKeywordError();}

"<="		{ return LE; }
"=>"		{ return DARROW; }
"=="		{ return EQ_OP; }
"="		{ return ASSIGN; }
"<"		{ return LT; }
";"		{ return SEMICOLON; }
":"		{ return COLON; }
","		{ return COMMA; }
"."		{ return DOT; }
"!"		{ return NOT; }
"{"		{ return OPEN_ACCOLADE; }
"}"		{ return CLOSE_ACCOLADE; }
"("		{ return OPEN_PARENTHESES; }
")"		{ return CLOSE_PARENTHESES; }
"["		{ return OPEN_BRACKETS; }
"]"		{ return CLOSE_BRACKETS; }
"-"		{ return MINUS; }
"+"		{ return PLUS; }
"*"		{ return MULTIPLY; }
"/"		{ return DIVIDE; }
"\n"            { ++line_num;}

{INTEGER}				{ yylval.integerVal = atoi(yytext); return INTEGER_CONST;}
{LOWERCASE}{ALPANUMERIC}*		{ yylval.object_IdentifierVal = strdup(yytext); return OBJECT_IDENTIFIER; }
{UPPERCASE}({ALPANUMERIC})*		{ yylval.type_IdentifierVal = strdup(yytext); return TYPE_IDENTIFIER; }
.              ;

%%

void addToStr(char* str) {
    strcat(string_buf, str);
}

bool strTooLong() {
  if (string_length + 1 >= MAX_STR_CONST) {
      BEGIN(BROKENSTRING);
      return true;
    }
    return false;
}

void resetStr() {
    string_length = 0;
    string_buf[0] = '\0';
}

int strLenErr() {
  resetStr();
    yylval.error_msg = (char*)"String constant too long";
    return ERROR;
}

int reservedKeywordError() {
	yylval.error_msg = (char*)"Keyword is reserved.";
	return ERROR;	
}

void nextFile(FILE *bffr){
	yyrestart(bffr);
	//yylex();
}
