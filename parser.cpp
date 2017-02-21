
#include "parser.h"

using namespace std;

  Casecontent::Casecontent(Block *block) :block(block) {}
  Casecontent::Casecontent(char* object_id, char* type_id, Block *block) :
  object_id(object_id), type_id(type_id),block(block){}
  void Casecontent::accept(Visitor* v) {v->visit(this);}
  void Casecontent::print(int indent) {cout<<"case "<<object_id<<" : "<<type_id<<" => "; block->print(indent);}

  Cases::Cases(Casecontent* casecontent) {cases.push_back(casecontent);}
  void Cases::append(Casecontent* casecontent) {cases.push_back(casecontent);}
  void Cases::accept(Visitor* v){v->visit(this);}
  void Cases::print(int indent) {for (Casecontent* cse : cases){cout<<std::string(indent,'\t');cse->print(indent+1);cout<<endl;}}


  Assign_exp::Assign_exp(char* object_id,Exp_node* exp) : object_id(object_id),exp(exp) {}
  void Assign_exp::accept(Visitor* v){v->visit(this);}
  void Assign_exp::print(int indent) {cout<<object_id<<" = ";exp->print(indent);}

  

  Not_exp::Not_exp(Exp_node* exp) : exp(exp){}
  void Not_exp::accept(Visitor* v){v->visit(this);}
  void Not_exp::print(int indent) {cout<<"!";exp->print(indent);}

  


  Uminus_exp::Uminus_exp(Exp_node* exp) : exp(exp){}
  void Uminus_exp::accept(Visitor* v){v->visit(this);}
  void Uminus_exp::print(int indent) {cout<<"-"; exp->print(indent);}



  Cond_exp::Cond_exp (Exp_node* precedence, Exp_node* then_exp, Exp_node* else_exp) :
  precedence(precedence) , then_exp(then_exp), else_exp(else_exp) {}
  void Cond_exp::accept(Visitor* v){v->visit(this);}
  void Cond_exp::print(int indent) {cout<<"if (";precedence->print(indent);cout<<") "; then_exp->print(indent); cout<<"\n"<<std::string(indent,'\t')<<"else "; else_exp->print(indent);}


  Loop_exp::Loop_exp(Exp_node* precedence, Exp_node* body_exp) :
  precedence(precedence) , body_exp(body_exp) {}
  void Loop_exp::accept(Visitor* v){v->visit(this);}
  void Loop_exp::print(int indent) {cout<<"while ("; precedence->print(indent); cout<<")"; body_exp->print(indent);}



  Super_exp::Super_exp(char* object_id, Actuals *body_exp) :
  object_id(object_id), body_exp(body_exp) {}
  void Super_exp::accept(Visitor* v){v->visit(this);}
  void Super_exp::print(int indent) {cout<<"super."<<object_id<<"("; body_exp->print(indent); cout<<")";}


  Object_exp::Object_exp(char* object_id, Actuals *body_exp) :
  object_id(object_id), body_exp(body_exp) {}
  void Object_exp::accept(Visitor* v){v->visit(this);}
  void Object_exp::print(int indent) {cout<<object_id<<"("; body_exp->print(indent); cout<<")";}



  Newtype_exp::Newtype_exp(char* type_id, Actuals *exp_body) :
  type_id(type_id), body_exp(exp_body) {}
  void Newtype_exp::accept(Visitor* v){v->visit(this);}
  void Newtype_exp::print(int indent) {cout<<"new "<<type_id<<"("; body_exp->print(indent); cout<<")";}


  Block_exp::Block_exp(Block* blck):blck(blck) {}
  void Block_exp::accept(Visitor* v){v->visit(this);}
  void Block_exp::print(int indent) {cout<<"{"<<endl; blck->print(indent+1); cout<<"\n"<<std::string(indent,'\t')<<"}";}



  Paren_exp::Paren_exp(Exp_node* exp): exp(exp) {}
  void Paren_exp::accept(Visitor* v){v->visit(this);}
  void Paren_exp::print(int indent) {cout<<"("; exp->print(indent); cout<<")";}
//continue here..

  Dot_object_exp::Dot_object_exp(Exp_node* exp, char* object_id, Actuals* exp_body) :
  exp(exp), object_id(object_id), body_exp(exp_body) {}
  void Dot_object_exp::accept(Visitor* v){v->visit(this);}
  void Dot_object_exp::print(int indent) {exp->print(indent); cout<<"."<<object_id<<"("; body_exp->print(indent); cout<<")";}


  Case_exp::Case_exp(Exp_node* exp, Cases* cases) :
  exp(exp), cases(cases) {}
  void Case_exp::accept(Visitor* v){v->visit(this);}
  void Case_exp::print(int indent) {exp->print(indent+1); cout<<" match {\n"; cases->print(indent+1); cout<<std::string(indent,'\t')<<"}";}


  Less_exp::Less_exp(Exp_node* exp1, Exp_node* exp2) :
  exp1(exp1), exp2(exp2) {}
  void Less_exp::accept(Visitor* v){v->visit(this);}
  void Less_exp::print(int indent) {exp1->print(indent); cout<<" < "; exp2->print(indent);}

  Leq_exp::Leq_exp(Exp_node* exp1, Exp_node* exp2) :
  exp1(exp1), exp2(exp2) {}
  void Leq_exp::accept(Visitor* v){v->visit(this);}
  void Leq_exp::print(int indent) {exp1->print(indent); cout<<" <= "; exp2->print(indent);}

  Eq_exp::Eq_exp(Exp_node* exp1, Exp_node* exp2) :
  exp1(exp1), exp2(exp2) {}
  void Eq_exp::accept(Visitor* v){v->visit(this);}
  void Eq_exp::print(int indent) {exp1->print(indent); cout<<" == "; exp2->print(indent);}

  
  Mul_exp::Mul_exp(Exp_node* exp1, Exp_node* exp2) :
  exp1(exp1), exp2(exp2) {}
  void Mul_exp::accept(Visitor* v){v->visit(this);}
  void Mul_exp::print(int indent) {exp1->print(indent); cout<<" * "; exp2->print(indent);}

  
  Div_exp::Div_exp(Exp_node* exp1, Exp_node* exp2) :
  exp1(exp1), exp2(exp2) {}
  void Div_exp::accept(Visitor* v){v->visit(this);}
  void Div_exp::print(int indent) {exp1->print(indent); cout<<" / "; exp2->print(indent);}


  Add_exp::Add_exp(Exp_node* exp1, Exp_node* exp2) :
  exp1(exp1), exp2(exp2) {}
  void Add_exp::accept(Visitor* v){v->visit(this);}
  void Add_exp::print(int indent) {exp1->print(indent); cout<<" + "; exp2->print(indent);}


  Min_exp::Min_exp(Exp_node* exp1, Exp_node* exp2) :
  exp1(exp1), exp2(exp2) {}
  void Min_exp::accept(Visitor* v){v->visit(this);}
  void Min_exp::print(int indent) {exp1->print(indent); cout<<" - "; exp2->print(indent);}

  void Null_exp::accept(Visitor* v){v->visit(this);}
  void Null_exp::print(int indent) {cout<<"null ";}

  void Empty_exp::accept(Visitor* v){v->visit(this);}
  void Empty_exp::print(int indent) {cout<<"( )";}

  Object_id_exp::Object_id_exp(char* object_id) : object_id(object_id) {}
  void Object_id_exp::accept(Visitor* v){v->visit(this);}
  void Object_id_exp::print(int indent) {cout<<object_id;}

 
  Int_const_exp::Int_const_exp(int int_const) : int_const(int_const) {}
  void Int_const_exp::accept(Visitor* v){v->visit(this);}
  void Int_const_exp::print(int indent) {cout<<" "<<int_const;}


  String_lit_exp::String_lit_exp(char* string_lit) : string_lit(string_lit) {}
  void String_lit_exp::accept(Visitor* v){v->visit(this);}
  void String_lit_exp::print(int indent) {cout<<"\""<<replaceAll(string_lit,string("\n"),string("\\n"))<<"\"";}
  string String_lit_exp::replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}


  Bool_exp::Bool_exp(bool boolean_const) : boolean_const(boolean_const) {}
  void Bool_exp::accept(Visitor* v){v->visit(this);}
  void Bool_exp::print(int indent) {cout<<std::boolalpha<<boolean_const<<" ";}

  void This_exp::accept(Visitor* v){v->visit(this);}
  void This_exp::print(int indent) {cout<<"this";}

  BlockExpression::BlockExpression(Exp_node* exp) : exp(exp) {}
  
  NormalExpression::NormalExpression(Exp_node* exp) : BlockExpression(exp) {}
  void NormalExpression::accept(Visitor* v){v->visit(this);}
  void NormalExpression::print(int indent) {exp->print(indent);}

  InilizationBlockExpression::InilizationBlockExpression(char* object_id, char* type_id, Exp_node* exp) :
  BlockExpression(exp), object_id(object_id), type_id(type_id) {}
  void InilizationBlockExpression::accept(Visitor* v){v->visit(this);}
  void InilizationBlockExpression::print(int indent) {cout<<"var "<<object_id<<" : "<<type_id<<" = "; exp->print(indent);}

  Block::Block(){}
  Block::Block(BlockExpression* exp){expressions.push_back(exp);}
  void Block::append(BlockExpression* exp){expressions.push_back(exp);}
  void Block::accept(Visitor* v){v->visit(this);}
  void Block::print(int indent) {const string separator = ";\n"; string sep = "";  for(auto &exp : expressions){cout<<sep<<std::string(indent,'\t'); sep = separator; exp->print(indent); }}

  Actuals::Actuals(){}
  Actuals::Actuals(Exp_node* expression) {expressions.push_back(expression);}
  void Actuals::append(Exp_node* expression) {expressions.push_back(expression);}
  void Actuals::accept(Visitor* v){v->visit(this);}
  void Actuals::print(int indent) {const string separator = ", "; string sep = "";  for(auto &exp : expressions){cout<<sep; exp->print(indent); sep = separator;}}


  Formalcontent::Formalcontent(char* object_id, char* type_id) :
  object_id(object_id), type_id(type_id) {}
  void Formalcontent::accept(Visitor* v){v->visit(this);}
  void Formalcontent::print(int indent) {cout<<object_id<<":"<<type_id;}

  Formalcontents::Formalcontents(){}
  Formalcontents::Formalcontents(Formalcontent* formalcontent) {formalcontents.push_back(formalcontent);}
  void Formalcontents::append(Formalcontent* formalcontent) {formalcontents.push_back(formalcontent);}
  void Formalcontents::accept(Visitor* v){v->visit(this);}
  void Formalcontents::print(int indent) {const string separator = ", "; string sep = "";for(auto &formalcontent : formalcontents){cout<<sep; sep=separator; formalcontent->print(indent);}}

  Features::Features() {}
  Features::Features(Feature* feature) {features.push_back(feature); }
  void Features::append(Feature* feature) {features.push_back(feature);}

  void Features::accept(Visitor* v){v->visit(this);}
  void Features::print(int indent) {for(auto &feature : features){feature->print(indent); cout<<";"<<endl;}}

  F_overide_expr::F_overide_expr(char* object_id, Formalcontents* formalcontents, char* type_id, Exp_node* exp) :
  object_id(object_id), formalcontents(formalcontents), type_id(type_id), exp(exp) {}
  void F_overide_expr::accept(Visitor* v){v->visit(this);}
  void F_overide_expr::print(int indent) {cout<<std::string(indent,'\t')<<"override def "<<object_id<<"("; formalcontents->print(indent); cout<<") : "<<type_id<<" = "; exp->print(indent); cout<<endl;}


  F_overide_nat::F_overide_nat(char* object_id, Formalcontents* formalcontents,char* type_id) : 
  object_id(object_id), formalcontents(formalcontents), type_id(type_id) {}  
  void F_overide_nat::accept(Visitor* v){v->visit(this);}
  void F_overide_nat::print(int indent) {cout<<std::string(indent,'\t')<<"override def "<<object_id<<"("; formalcontents->print(indent); cout<<") : "<<type_id<<" = native";}
  

  F_expr::F_expr(char* object_id, Formalcontents* formalcontents,char* type_id,Exp_node* exp) :
  object_id(object_id), formalcontents(formalcontents), type_id(type_id), exp(exp) {}
  void F_expr::accept(Visitor* v){v->visit(this);}
  void F_expr::print(int indent) {cout<<std::string(indent,'\t')<<"def "<<object_id<<"("; formalcontents->print(indent); cout<<") : "<<type_id<<" = "; exp->print(indent);}

  F_nat::F_nat(char* object_id, Formalcontents* formalcontents,char* type_id) :
  object_id(object_id), formalcontents(formalcontents), type_id(type_id) {}
  void F_nat::accept(Visitor* v){v->visit(this);}
  void F_nat::print(int indent) {cout<<std::string(indent,'\t')<<"def "<<object_id<<"("; formalcontents->print(indent); cout<<") : "<<type_id<<" = native";}

  F_var_nat::F_var_nat(char* object_id) :
  object_id(object_id) {}
  void F_var_nat::accept(Visitor* v){v->visit(this);}
  void F_var_nat::print(int indent) {cout<<std::string(indent,'\t')<<"var "<<object_id<<" = native;";}

  
  F_var_exp::F_var_exp (char* object_id, char* type_id, Exp_node* exp) :
  object_id(object_id), type_id(type_id), exp(exp) {}
  void F_var_exp::accept(Visitor* v){v->visit(this);}
  void F_var_exp::print(int indent) {cout<<std::string(indent,'\t')<<"var "<<object_id<<": "<<type_id<<" = ";exp->print(indent);}


  F_block::F_block(Block* blck) : blck(blck) {}
  void F_block::accept(Visitor* v){v->visit(this);}
  void F_block::print(int indent) {cout<<std::string(indent,'\t')<<"{"<<endl;blck->print(indent+1);cout<<"}";}


  Vfcontent::Vfcontent(char* object_id,char* type_id) :
  object_id(object_id), type_id(type_id) {}
  void Vfcontent::accept(Visitor* v) {v->visit(this);}
  void Vfcontent::print(int indent) {cout<<object_id<<":"<<type_id;}
	
  Vfcontents::Vfcontents() {}
  Vfcontents::Vfcontents(Vfcontent* vfcontent) {vfcontents.push_back(vfcontent);}
  void Vfcontents::append(Vfcontent* vfcontent) { vfcontents.push_back(vfcontent); }
  void Vfcontents::accept(Visitor* v) {v->visit(this);}
  void Vfcontents::print(int indent) {const std::string separator = ", "; std::string sep = ""; for (auto &vfcontent: vfcontents){cout<<sep; sep = separator; vfcontent->print(indent);}}

  Classdecl::Classdecl(char* type_id, Vfcontents *vfcontents, string extend_type_id, Actuals* exp_body, Features *features) :
  type_id(type_id), vfcontents(vfcontents), features(features), extend_type_id(extend_type_id), exp_body(exp_body) {}
  void Classdecl::accept(Visitor* v) {v->visit(this);}
  void Classdecl::print(int indent) {cout<<"class "<<type_id << " ("; vfcontents->print(indent); cout<<") extends "<<extend_type_id<<"(";exp_body->print(indent); cout<<") {"<<endl; features->print(indent+1); cout<<"}"<<endl<<endl;}

  Classdecls::Classdecls(Classdecl * classdecl) {classdecls.push_back(classdecl);}
  void Classdecls::append(Classdecl * classdecl) { classdecls.push_back(classdecl); }
  void Classdecls::accept(Visitor* v) {v->visit(this);}
  void Classdecls::print(int indent) {for (auto clss: classdecls){clss->print(indent);}}
  

  Program::Program(Classdecls* classes) : classes(classes) {}
  void Program::accept(Visitor* v) { v->visit(this);}
  void Program::print(int indent) {classes->print(indent);}
  
  Visitor::Visitor() {}
  
  
