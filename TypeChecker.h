#ifndef TYPECHECKER_H
#define TYPECHECKER_H

#include <string>
#include <list>
#include <vector>
#include "parser.h"
#include "SymbolTable.h"

using namespace std;

class TypeChecker : public Visitor {
private:
    SymbolTable table = SymbolTable();
    bool compile = true;
    string lastType, currentClass = "";

public:
    TypeChecker();
    bool make();
    using Visitor::visit;
    void visit(Program* prgm) override;
    void visit(Classdecls* clssdcls) override;
    void visit(Classdecl* clssdcl) override;
    void visit(Vfcontents* vfctnts) override;
    void visit(Vfcontent* vfctnt) override;
    void visit(Features* ftrs) override;
    void visit(F_block* ftr) override;
    void visit(F_expr* ftr) override;
    void visit(F_nat* ftr) override;
    void visit(F_overide_expr* ftr) override;
    void visit(F_overide_nat* ftr) override;
    void visit(F_var_exp* ftr) override;
    void visit(F_var_nat* ftr) override;
    void visit(Formalcontents* frmlcntnts) override;
    void visit(Formalcontent* frmlcntnt) override;
    void visit(Actuals* actuals) override;
    void visit(Block* block) override;
    void visit(NormalExpression* blockexpression) override;
    void visit(InilizationBlockExpression* blockexpression) override;
    void visit(Assign_exp* expression) override;
    void visit(Not_exp* expression) override;
    void visit(Uminus_exp* expression) override;
    void visit(Cond_exp* expression) override;
    void visit(Loop_exp* expression) override;
    void visit(Super_exp* expression) override;
    void visit(Object_exp* expression) override;
    void visit(Newtype_exp* expression) override;
    void visit(Block_exp* expression) override;
    void visit(Paren_exp* expression) override;
    void visit(Dot_object_exp* expression) override;
    void visit(Case_exp* expression) override;
    void visit(Less_exp* expression) override;
    void visit(Leq_exp* expression) override;
    void visit(Eq_exp* expression) override;
    void visit(Mul_exp* expression) override;
    void visit(Div_exp* expression) override;
    void visit(Add_exp* expression) override;
    void visit(Min_exp* expression) override;
    void visit(Null_exp* expression) override;
    void visit(Empty_exp* expression) override;
    void visit(Object_id_exp* expression) override;
    void visit(Int_const_exp* expression) override;
    void visit(String_lit_exp* expression) override;
    void visit(Bool_exp* expression) override;
    void visit(This_exp* expression) override;
    void visit(Casecontent* casecontent) override;
    void visit(Cases* cases) override;

private:
    void addMethod(string className, Vfcontents* vfcontents);
    vector<string> formalContentTypeList(Vfcontents* vfcnts);
};

class MethodAdder : public Visitor {
private:
    SymbolTable &table;
    string className;
    
public:    
    MethodAdder(SymbolTable& table);
    void changeClassName(string newClassName);
    using::Visitor::visit;
    void visit(Program* prgm) override;
    void visit(Classdecls* clssdcls) override;
    void visit(Classdecl* clssdcl) override;
    void visit(Vfcontents* vfctnts) override;
    void visit(Vfcontent* vfctnt) override;
    void visit(Features* ftrs) override;
    void visit(F_block* ftr) override;
    void visit(F_expr* ftr) override;
    void visit(F_nat* ftr) override;
    void visit(F_overide_expr* ftr) override;
    void visit(F_overide_nat* ftr) override;
    void visit(F_var_exp* ftr) override;
    void visit(F_var_nat* ftr) override;
    void visit(Formalcontents* frmlcntnts) override;
    void visit(Formalcontent* frmlcntnt) override;
    void visit(Actuals* actuals) override;
    void visit(Block* block) override;
    void visit(NormalExpression* blockexpression) override;
    void visit(InilizationBlockExpression* blockexpression) override;
    void visit(Assign_exp* expression) override;
    void visit(Not_exp* expression) override;
    void visit(Uminus_exp* expression) override;
    void visit(Cond_exp* expression) override;
    void visit(Loop_exp* expression) override;
    void visit(Super_exp* expression) override;
    void visit(Object_exp* expression) override;
    void visit(Newtype_exp* expression) override;
    void visit(Block_exp* expression) override;
    void visit(Paren_exp* expression) override;
    void visit(Dot_object_exp* expression) override;
    void visit(Case_exp* expression) override;
    void visit(Less_exp* expression) override;
    void visit(Leq_exp* expression) override;
    void visit(Eq_exp* expression) override;
    void visit(Mul_exp* expression) override;
    void visit(Div_exp* expression) override;
    void visit(Add_exp* expression) override;
    void visit(Min_exp* expression) override;
    void visit(Null_exp* expression) override;
    void visit(Empty_exp* expression) override;
    void visit(Object_id_exp* expression) override;
    void visit(Int_const_exp* expression) override;
    void visit(String_lit_exp* expression) override;
    void visit(Bool_exp* expression) override;
    void visit(This_exp* expression) override;
    void visit(Casecontent* casecontent) override;
    void visit(Cases* cases) override;
    
private:
    void addMethod(string className, F_expr* ftr); // <--Continue here for add all methods.
    void addMethod(string className, F_nat* ftr);
    void addMethod(string className, F_overide_expr* ftr);
    void addMethod(string className, F_overide_nat* ftr);
    vector<string> formalContentTypeList(Formalcontents* frmlcnts);
};

#endif /* TYPECHECKER_H */


