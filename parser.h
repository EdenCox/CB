#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "SymbolTable.h"

using namespace std;

/*Forward declaration*/
class Block;
class Actuals;
class Program;
class Visitor;

class TreeNode {
 public:
  virtual void accept(Visitor* v) = 0;
};

class Casecontent : public TreeNode{
 public:
  string object_id;
  string type_id;
  Block *block;
 public:
  Casecontent(Block *block);
  Casecontent(char* object_id, char* type_id, Block *block);
  void accept(Visitor* v) override;
  void print(int indents);
};

class Cases : public TreeNode{
 public:
  list<Casecontent*> cases;
 public: 
  Cases(Casecontent* casecontent);
  void append(Casecontent* casecontent);
  void accept(Visitor* v) override;
  void print(int indents);
  
};

class Exp_node : public TreeNode {
 public:
  virtual void print(int indents) = 0;
};

class Assign_exp : public Exp_node {
 public:
  string object_id;
  Exp_node* exp;
 public:
  Assign_exp(char* object_id, Exp_node* exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Not_exp : public Exp_node {
 public:
  Exp_node* exp;
 public:
  Not_exp(Exp_node* exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Uminus_exp : public Exp_node {
 public:
  Exp_node* exp;
 public:
  Uminus_exp(Exp_node* exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Cond_exp : public Exp_node {
 public:
  Exp_node* precedence;
  Exp_node* then_exp;
  Exp_node* else_exp;
 public:
  Cond_exp (Exp_node* precedence, Exp_node* then_exp, Exp_node* else_exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Loop_exp : public Exp_node {
 public:
  Exp_node* precedence;
  Exp_node* body_exp;
 public:
  Loop_exp(Exp_node* precedence, Exp_node* body_exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Super_exp : public Exp_node {
 protected:
  string object_id;
  Actuals *body_exp;
 public:
  Super_exp(char* object_id, Actuals *body_exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Object_exp : public Exp_node {
 public:
  string object_id;
  Actuals* body_exp;
 public:
  Object_exp(char* object_id, Actuals *body_exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Newtype_exp : public Exp_node {
 public:
  string type_id;
  Actuals* body_exp;
 public:
  Newtype_exp(char* type_id, Actuals *body_exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Block_exp : public Exp_node {
 public:
  Block *blck;
 public:
  Block_exp(Block *blck);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Paren_exp : public Exp_node {
 public:
  Exp_node* exp;
 public:
  Paren_exp(Exp_node* exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Dot_object_exp : public Exp_node {
 public:
  Exp_node* exp;
  string object_id;
  Actuals *body_exp;
 public:
  Dot_object_exp(Exp_node* exp, char* object_id, Actuals *body_exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Case_exp : public Exp_node {
 public:
  Exp_node* exp;
  Cases *cases;
 public:
  Case_exp(Exp_node* exp, Cases* cases);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Less_exp : public Exp_node {
 public:
  Exp_node* exp1;
  Exp_node* exp2;
 public:
  Less_exp(Exp_node* exp1, Exp_node* exp2);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Leq_exp : public Exp_node {
 public:
  Exp_node* exp1;
  Exp_node* exp2;
 public:
  Leq_exp(Exp_node* exp1, Exp_node* exp2);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Eq_exp : public Exp_node {
 public:
  Exp_node* exp1;
  Exp_node* exp2;
 public:
  Eq_exp(Exp_node* exp1, Exp_node* exp2);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Mul_exp : public Exp_node {
 public:
  Exp_node* exp1;
  Exp_node* exp2;
 public:
  Mul_exp(Exp_node* exp1, Exp_node* exp2);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Div_exp : public Exp_node {
 public:
  Exp_node* exp1;
  Exp_node* exp2;
 public:
  Div_exp(Exp_node* exp1, Exp_node* exp2);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Add_exp : public Exp_node {
 public:
  Exp_node* exp1;
  Exp_node* exp2;
 public:
  Add_exp(Exp_node* exp1, Exp_node* exp2);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Min_exp : public Exp_node {
 public:
  Exp_node* exp1;
  Exp_node* exp2;
 public:
  Min_exp(Exp_node* exp1, Exp_node* exp2);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Null_exp : public Exp_node {
 public:
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Empty_exp : public Exp_node {
 public:
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Object_id_exp : public Exp_node { 
 public:
  string object_id;
 public:
  Object_id_exp(char* object_id);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Int_const_exp : public Exp_node { 
 public:
  int int_const;
 public:
  Int_const_exp(int int_const);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class String_lit_exp : public Exp_node { 
 public:
  string string_lit;
 public:
  String_lit_exp (char* String_lit);
  void accept(Visitor* v) override;
  void print(int indents) override;
  string replaceAll(std::string str, const std::string& from, const std::string& to);
};

class Bool_exp : public Exp_node { 
 public:
  bool boolean_const;
 public:
  Bool_exp(bool boolean_const);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class This_exp : public Exp_node {
 public:
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class BlockExpression : public TreeNode{
 public:
  Exp_node* exp;
 public:
  BlockExpression(Exp_node* exp);
  virtual void accept(Visitor* v) = 0;
  virtual void print(int indents) = 0;
};

class NormalExpression : public BlockExpression{
 public:
  NormalExpression(Exp_node* exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class InilizationBlockExpression : public BlockExpression {
 public:
  string object_id;
  string type_id;
 public:
  InilizationBlockExpression(char* object_id, char* type_id,Exp_node* exp);
  void accept(Visitor* v) override;
  void print(int indents) override;
};

class Block : public TreeNode {
 public:
  list<BlockExpression* > expressions;
 public:
  Block();
  Block(BlockExpression* exp);
  void append(BlockExpression* exp);
  void accept(Visitor* v) override;
  void print(int indents);
};
 
class Actuals : public TreeNode{
 public:
  list<Exp_node* > expressions;
 public:
  Actuals();
  Actuals(Exp_node* expression);
  void append(Exp_node* expression);
  void accept(Visitor* v) override;
  void print(int indents);
};

class Formalcontent : public TreeNode {
 public:
  string object_id;
  string type_id;
 public:
  Formalcontent(char* object_id, char* type_id);
  void accept(Visitor* v) override;
  void print(int indents);
};

class Formalcontents : public TreeNode {
 public:
  list<Formalcontent* > formalcontents;
 public:
  Formalcontents();
  Formalcontents(Formalcontent* formalcontent);
  void append(Formalcontent* formalcontent);
  void accept(Visitor* v) override;
  void print(int indents);
};

class Feature : public TreeNode{
 public:
  virtual void print(int indents) = 0;
};

class Features : public TreeNode{
public:
 list<Feature*> features;
public:
 Features();
 Features(Feature* feature);
 void append(Feature* feature);
 void accept(Visitor* v) override;
 void print(int indents);
};

class F_overide_expr : public Feature {
 public:
  string object_id;
  Formalcontents* formalcontents;
  string type_id;
  Exp_node* exp;
 public: 
  F_overide_expr(char* object_id, Formalcontents* formalcontents, char* type_id, Exp_node* exp); 
  void accept(Visitor* v) override;
  void print(int indent) override;
};

class F_overide_nat : public Feature {
 public:
  string object_id;
  Formalcontents* formalcontents;
  string type_id;
 public: 
  F_overide_nat(char* object_id,Formalcontents* formalcontents,char* type_id);
  void accept(Visitor* v) override;
  void print(int indent) override;
};

class F_expr : public Feature {
 public:
  string object_id;
  Formalcontents* formalcontents;
  string type_id;
  Exp_node* exp;
 public: 
  F_expr(char* object_id, Formalcontents* formalcontents, char* type_id, Exp_node* exp);
  void accept(Visitor* v) override;
  void print(int indent) override;
};

class F_nat : public Feature {
 public:
  string object_id;
  Formalcontents* formalcontents;
  string type_id;
 public:
  F_nat(char* object_id, Formalcontents* formalcontents, char* type_id);
  void accept(Visitor* v) override;
  void print(int indent) override;
};

class F_var_nat : public Feature {
 public:
  string object_id;
 public: 
  F_var_nat (char* object_id);
  void accept(Visitor* v) override;
  void print(int indent) override;
};

class F_var_exp : public Feature {
 public:
  string object_id;
  string type_id;
  Exp_node* exp;
 public: 
  F_var_exp (char* object_id, char* type_id, Exp_node* exp); 
  void accept(Visitor* v) override;
  void print(int indent) override;
};

class F_block : public Feature { 
 public:
  Block* blck;
 public:
  F_block(Block *blck);
  void accept(Visitor* v) override;
  void print(int indent) override;
};

class Vfcontent : public TreeNode {
 public:
  string object_id;
  string type_id;
 public:
  Vfcontent(char* object_id,char* type_id); 
  void accept(Visitor* v) override;
  void print(int indent);
};

class Vfcontents : public TreeNode {
 public:
  list<Vfcontent*> vfcontents;
 public: 
  Vfcontents();
  Vfcontents(Vfcontent* vfcontent);
  void append(Vfcontent* vfcontent);
  void accept(Visitor* v) override;  
  void print(int indent);
};

class Classdecl : public TreeNode {
 public:
  string type_id;
  Vfcontents* vfcontents;
  Features* features;
  string extend_type_id;
  Actuals* exp_body;
 public:
  Classdecl(char* type_id, Vfcontents *vfcontents, string extend_type_id, Actuals* exp_body, Features *features);
  void accept(Visitor* v) override;
  void print(int indent); 
};

class Classdecls : public TreeNode{
 public:
  list<Classdecl *> classdecls;
 public:
  Classdecls(Classdecl * classdecl);
  void append(Classdecl * classdecl);
  void accept(Visitor* v) override;
  void print(int indent);
};

/*class Normal_class: public Classdecl {
 public:
  Normal_class(char* type_id, Vfcontents *vfcontents,Features *features);
  void accept(Visitor* v);
  void print(int indent); 
};


class Native_class : public Classdecl {
 public:
  string extend_type_id;
  Actuals* exp_body;
 public: 
  Native_class(char* type_id, Vfcontents* vfcontents, char* extend_type_id, Actuals* exp_body, Features* features);
  void accept(Visitor* v) override;
  void print(int indent);
};

class Extends_typeid : public Classdecl {
 public:
  string extend_type_id;
  Actuals* exp_body;
 public:
  Extends_typeid(char* type_id, Vfcontents* vfcontents, char* extend_type_id, Actuals* exp_body, Features* features);
  void accept(Visitor* v) override;
  void print(int indent);
};

class Extends_native : public Classdecl {
 public:
  Extends_native(char* type_id, Vfcontents* vfcontents,Features* features);
  void accept(Visitor* v) override;
  void print(int indent);
};*/
 
class Program : public TreeNode {
 public:
  Classdecls* classes;
 public:
  Program(Classdecls * classes);
  void accept(Visitor* v) override;
  void print(int indent);
  
};

class Visitor {
  public:
      Visitor();
      virtual void visit (Program* prgm) = 0;
      virtual void visit (Classdecls* clssdcls) = 0;
      virtual void visit (Classdecl* clssdcl) = 0;
      virtual void visit (Vfcontents* vfctnts) = 0;
      virtual void visit (Vfcontent* vfctnt) = 0;
      virtual void visit (Features* ftrs) = 0;
      virtual void visit (F_block* ftr) = 0;
      virtual void visit (F_expr* ftr) = 0;
      virtual void visit (F_nat* ftr) = 0;
      virtual void visit (F_overide_expr* ftr) = 0;
      virtual void visit (F_overide_nat* ftr) = 0;
      virtual void visit (F_var_exp* ftr) = 0;
      virtual void visit (F_var_nat* ftr) = 0;
      virtual void visit (Formalcontents* frmlcntnts) = 0;
      virtual void visit (Formalcontent* frmlcntnt) = 0;
      virtual void visit (Actuals* actuals) = 0;
      virtual void visit (Block* block) = 0;
      virtual void visit (NormalExpression* blockexpression) = 0;
      virtual void visit (InilizationBlockExpression* blockexpression) = 0;
      virtual void visit (Assign_exp* expression) = 0;
      virtual void visit (Not_exp* expression) = 0;
      virtual void visit (Uminus_exp* expression) = 0;
      virtual void visit (Cond_exp* expression) = 0;
      virtual void visit (Loop_exp* expression) = 0;
      virtual void visit (Super_exp* expression) = 0;
      virtual void visit (Object_exp* expression) = 0;
      virtual void visit (Newtype_exp* expression) = 0;
      virtual void visit (Block_exp* expression) = 0;
      virtual void visit (Paren_exp* expression) = 0;
      virtual void visit (Dot_object_exp* expression) = 0;    
      virtual void visit (Case_exp* expression) = 0;
      virtual void visit (Less_exp* expression) = 0;
      virtual void visit (Leq_exp* expression) = 0;
      virtual void visit (Eq_exp* expression) = 0;
      virtual void visit (Mul_exp* expression) = 0;
      virtual void visit (Div_exp* expression) = 0;
      virtual void visit (Add_exp* expression) = 0;
      virtual void visit (Min_exp* expression) = 0;
      virtual void visit (Null_exp* expression) = 0;
      virtual void visit (Empty_exp* expression) = 0;
      virtual void visit (Object_id_exp* expression) = 0;
      virtual void visit (Int_const_exp* expression) = 0;
      virtual void visit (String_lit_exp* expression) = 0;
      virtual void visit (Bool_exp* expression) = 0;
      virtual void visit (This_exp* expression) = 0;
      virtual void visit (Casecontent* casecontent) = 0;
      virtual void visit (Cases* cases) = 0;           
};

/*class TreePrinter : public Visitor {
 private:
  int depth = 0;
 public:
  TreePrinter();
  using Visitor::visit;
  void visit (Program* prgm) override;
  void visit (Classdecls* clssdcls) override;
  void visit (Classdecl* clssdcl) override;
  void visit (Vfcontents* vfctnts) override;
  void visit (Vfcontent* vfctnt) override;
  void visit (Features* ftrs) override;
  void visit (Feature* ftr) override;
  void visit (Formalcontents* frmlcntnts) override;
  void visit (Formalcontent* frmlcntnt) override;
  void visit (Actuals* actuals) override;
  void visit (Block* block) override;
  void visit (BlockExpression* blockexpression) override;
  void visit (Exp_node* expression) override;
  void visit (Casecontent* casecontent) override;
  void visit (Cases* cases) override;
};*/

class TypeChecker : public Visitor {
 private:
     SymbolTable table = SymbolTable();
 public:
  TypeChecker();
  using Visitor::visit;
      void visit (Program* prgm) override;
      void visit (Classdecls* clssdcls) override;
      void visit (Classdecl* clssdcl) override;
      void visit (Vfcontents* vfctnts) override;
      void visit (Vfcontent* vfctnt) override;
      void visit (Features* ftrs) override;
      void visit (F_block* ftr) override;
      void visit (F_expr* ftr) override;
      void visit (F_nat* ftr) override;
      void visit (F_overide_expr* ftr) override;
      void visit (F_overide_nat* ftr) override;
      void visit (F_var_exp* ftr) override;
      void visit (F_var_nat* ftr) override;
      void visit (Formalcontents* frmlcntnts) override;
      void visit (Formalcontent* frmlcntnt) override;
      void visit (Actuals* actuals) override;
      void visit (Block* block) override;
      void visit (NormalExpression* blockexpression) override;
      void visit (InilizationBlockExpression* blockexpression) override;
      void visit (Assign_exp* expression) override;
      void visit (Not_exp* expression) override;
      void visit (Uminus_exp* expression) override;
      void visit (Cond_exp* expression) override;
      void visit (Loop_exp* expression) override;
      void visit (Super_exp* expression) override;
      void visit (Object_exp* expression) override;
      void visit (Newtype_exp* expression) override;
      void visit (Block_exp* expression) override;
      void visit (Paren_exp* expression) override;
      void visit (Dot_object_exp* expression) override;    
      void visit (Case_exp* expression) override;
      void visit (Less_exp* expression) override;
      void visit (Leq_exp* expression) override;
      void visit (Eq_exp* expression) override;
      void visit (Mul_exp* expression) override;
      void visit (Div_exp* expression) override;
      void visit (Add_exp* expression) override;
      void visit (Min_exp* expression) override;
      void visit (Null_exp* expression) override;
      void visit (Empty_exp* expression) override;
      void visit (Object_id_exp* expression) override;
      void visit (Int_const_exp* expression) override;
      void visit (String_lit_exp* expression) override;
      void visit (Bool_exp* expression) override;
      void visit (This_exp* expression) override;
      void visit (Casecontent* casecontent) override;
      void visit (Cases* cases) override;           
};

#endif	// PARSER_H


