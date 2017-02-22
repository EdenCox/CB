#include "TypeChecker.h"

TypeChecker::TypeChecker() : Visitor() {
}

bool TypeChecker::make(){
    return compile;
}

void TypeChecker::visit(Program* prgm) {
    prgm->classes->accept(this);

}

void TypeChecker::visit(Classdecls* clssdcls) {
    for (auto &i : clssdcls->classdecls) {
        if (!table.typeExists(i->type_id)) {
            if (table.typeExists(i->extend_type_id)) {
                table.addClassName(i->type_id, i->extend_type_id);
                vector<TypeEntry> entries;
                for (auto &j : i->vfcontents->vfcontents) {
                    entries.push_back(TypeEntry(j->object_id, j->type_id));
                }
                table.addEntries(i->type_id, entries);
            } else {
                cout << "Type name " << i->extend_type_id << " doesn't exists" << endl;
                compile = false;
            }
        } else {
            cout << "Class name " << i->type_id << " already exists" << endl;
            compile = false;
        }
    }
    MethodAdder *adder = new MethodAdder(table);
    for (auto &i : clssdcls->classdecls) {
        addMethod(i->type_id, i->vfcontents);
        adder->changeClassName(i->type_id);
        i->features->accept(adder);
    }
    delete adder;
    //table.addScope(); 
    for (auto &i : clssdcls->classdecls) {
        i->accept(this);
    }
    //table.removeScope();
}//add all classes and check if add new scope for each class

void TypeChecker::visit(Classdecl* clssdcl) {
    currentClass = clssdcl->type_id;
    table.addScope(); //CONTINUE HERE CHECK ACTUALS OF THE CLASS!

    clssdcl->vfcontents->accept(this);

    table.addParentsAttributes(currentClass);

    string extendedClass = table.getExtendsName(currentClass);
    vector<string> superConstuctor = table.getFormalsType(extendedClass, extendedClass);
    table.addScope();
    if (superConstuctor.size() == clssdcl->exp_body->expressions.size()) {
        for (int i = 0; i < superConstuctor.size(); i++) {
            clssdcl->exp_body->expressions.at(i)->accept(this);
            if (lastType != superConstuctor.at(i)) {
                cout << "In Class " << currentClass << " actuals parameter number " << i << " does not match with the expression" << endl;
                compile = false;
            }
        }
    } else {
        cout << "In Class " << currentClass << " actuals does not have the right amount of parameters" << endl;
        cout << "#" << superConstuctor.size() << " is required" << endl;
        compile = false;
    }
    table.removeScope();

    clssdcl->features->accept(this);
    table.removeScope();
}

void TypeChecker::visit(Vfcontents* vfctnts) {
    for (auto &i : vfctnts->vfcontents) {
        i->accept(this);
    }
}

void TypeChecker::visit(Vfcontent* vfctnt) {
    if (table.typeExists(vfctnt->type_id)) {
        if (!table.checkVariable(vfctnt->object_id)) {
            table.addVariable(vfctnt->object_id, vfctnt->type_id);
        } else {
            cout << "In Class " << currentClass << "varformal: " << vfctnt->object_id << " type has already been declared" << endl;
            compile = false;
        }
    } else {
        cout << "In Class " << currentClass << "varformal: " << vfctnt->object_id << " type " << vfctnt->type_id << " doesn't exist" << endl;
        compile = false;
    }
}//checks if class attribute types exist.

void TypeChecker::visit(Features* ftrs) {
    for (auto &i : ftrs->features) {
        i->accept(this);
    }
}

void TypeChecker::visit(F_block* ftr) {
    ftr->blck->accept(this);
}

void TypeChecker::visit(F_expr* ftr) {
    //addMethod(currentClass, ftr);
    table.addScope();
    ftr->formalcontents->accept(this);
    ftr->exp->accept(this);
    //string type = checkType(ftr->exp);
    if (lastType != ftr->type_id && ftr->type_id != "Unit" && lastType != "Nothing") {
        cout << "In Class " << currentClass << " function " << ftr->object_id << " type: " << ftr->type_id << " Doesn't match the function return type of " << lastType << endl;
        compile = false;
    }
    table.removeScope();
}//add new scope for method declarations.

void TypeChecker::visit(F_nat* ftr) {
    //addMethod(currentClass, ftr);
    table.addScope();
    ftr->formalcontents->accept(this);
    table.removeScope();
}

void TypeChecker::visit(F_overide_expr* ftr) {
    //addMethod(currentClass, ftr);
    table.addScope();
    ftr->formalcontents->accept(this);
    //string type = checkType(ftr->exp);
    ftr->exp->accept(this);
    if (lastType != ftr->type_id && ftr->type_id != "Unit" && lastType != "Nothing") {
        cout << "Class: " << currentClass << " Error - Function type: " << ftr->type_id << "Doesn't match the function return type of " << lastType << endl;
        compile = false;
    }
    table.removeScope();
}//TODO: check if the method that you're overriding exists..

void TypeChecker::visit(F_overide_nat* ftr) {
    //addMethod(currentClass, ftr);
    table.addScope();
    ftr->formalcontents->accept(this);
    table.removeScope();
}//TODO: check if the method that you're overriding exists..

void TypeChecker::visit(F_var_exp* ftr) {
    ftr->exp->accept(this);
    if (lastType != ftr->type_id && lastType != "Null") {//TODO: check if type you're nulling is allowed
        cout << "in Class: " << currentClass << " the expression type of " << lastType << " doesn't match the var type of " << ftr->type_id << endl;
        compile = false;
    }
    if (table.typeExists(ftr->type_id)) {
        if (!table.checkVariable(ftr->object_id))
            table.addVariable(ftr->object_id, ftr->type_id);
        else {
            cout << "in Class: " << currentClass << " Error - variable: " << ftr->type_id << " has already been declared." << endl;
            compile = false;
        }

    } else {
        cout << "Class: " << currentClass << " Error - Type: " << ftr->type_id << " Does not exist." << endl;
        compile = false;
    }


}

void TypeChecker::visit(F_var_nat* ftr) {
    table.addVariable(ftr->object_id, "native");
}//double check rule..

void TypeChecker::visit(Formalcontents* frmlcntnts) {
    for (auto &i : frmlcntnts->formalcontents) {
        i->accept(this);
    }
}

void TypeChecker::visit(Formalcontent* frmlcntnt) {
    table.addVariable(frmlcntnt->object_id, frmlcntnt->type_id);
}

void TypeChecker::visit(Actuals* actuals) {

}// TODO: Check if actuals is corresponds with the extends constructor

void TypeChecker::visit(Block* block) {
    table.addScope();
    for (auto &i : block->expressions) {
        i->accept(this);
    }
    table.removeScope();
}

void TypeChecker::visit(NormalExpression* blockexpression) {
    blockexpression->exp->accept(this);
}

void TypeChecker::visit(InilizationBlockExpression* blockexpression) {
    if (table.typeExists(blockexpression->type_id))
        if (!table.checkVariable(blockexpression->object_id))
            table.addVariable(blockexpression->object_id, blockexpression->type_id);
        else {
            cout << "Class: " << currentClass << "Error - variable: " << blockexpression->object_id << " has already been declared." << endl;
            compile = false;
        } else {
        cout << "Class: " << currentClass << " Error - Type: " << blockexpression->type_id << " Does not exist." << endl;
        compile = false;
    }
}

void TypeChecker::visit(Assign_exp* expression) {
    string type = table.getType(expression->object_id);
    expression->exp->accept(this);
    if (!(table.isParentype(type, lastType))) {
        cout << "Class: " << currentClass << " Error - Type mismatch when assigning to the variable " << expression->object_id << endl;
        cout << "Variable type: " << type << endl;
        cout << "Expression type: " << lastType << endl;
        compile = false;
    }
}

void TypeChecker::visit(Not_exp* expression) {
    expression->exp->accept(this);
    if ("Boolean" != lastType) {
        cout << "Error - can not use \"not\" sign infront of a none Boolean expression" << endl;
        compile = false;
    }
}

void TypeChecker::visit(Uminus_exp* expression) {
    expression->exp->accept(this);
    if ("Int" != lastType) {
        cout << "Error - can not use \"Unary minus\"(-) sign in front of a none Integer expression" << endl;
        compile = false;
    }
}

void TypeChecker::visit(Cond_exp* expression) {

    expression->precedence->accept(this);
    if (lastType != "Boolean") {
        cout << "In Class " << currentClass << " Precedence of the if expression is not of Boolean type" << endl;
        cout << lastType << endl << endl;
        ;
        compile = false;
    }
    table.addScope();
    expression->then_exp->accept(this);
    string thenType = lastType;
    table.removeScope();


    table.addScope();
    expression->else_exp->accept(this);
    lastType = table.getLUB(thenType, lastType);
    table.removeScope();
}

void TypeChecker::visit(Loop_exp* expression) {
    expression->precedence->accept(this);
    if (lastType != "Boolean") {
        cout << "In Class" << currentClass << " Precedence of the loop expression is not of Boolean type" << endl;
        compile = false;
    }

    table.addScope();
    expression->body_exp->accept(this);
    table.removeScope();
}

void TypeChecker::visit(Super_exp* expression) {
    if (table.hasMethod(currentClass, expression->object_id)) {
        string superClass = table.getExtendsName(currentClass);
        vector<string> parameterTypes = table.getFormalsType(superClass, expression->object_id);
        if (parameterTypes.size() == expression->body_exp->expressions.size()) {
            for (int i = 0; i < parameterTypes.size(); i++) {
                expression->body_exp->expressions.at(i)->accept(this);
                if (!table.isParentype(parameterTypes.at(i), lastType)) {
                    cout << "In Class " << currentClass << " method " << expression->object_id << " parameter number #" << i + 1 << " does not match with the expression" << endl;
                    compile = false;
                }
            }
        } else {
            cout << "In Class " << currentClass << " method " << expression->object_id << " does not have the right amount of parameters" << endl;
            cout << "# of parameters in method: " << parameterTypes.size() << endl;
            cout << "# of parameters given: " << expression->body_exp->expressions.size() << endl << endl;

            compile = false;
        }
        lastType = table.getMethodType(superClass, expression->object_id);
    } else {
        cout << "In Class " << currentClass << " does not contain method: " << expression->object_id << endl;
        compile = false;
    }


}//Check the super method call

void TypeChecker::visit(Object_exp* expression) {
    if (table.hasMethod(currentClass, expression->object_id)) {
        vector<string> parameterTypes = table.getFormalsType(currentClass, expression->object_id);
        if (parameterTypes.size() == expression->body_exp->expressions.size()) {
            for (int i = 0; i < parameterTypes.size(); i++) {
                expression->body_exp->expressions.at(i)->accept(this);
                if (!table.isParentype(parameterTypes.at(i), lastType)) {
                    cout << "In Class " << currentClass << " method " << expression->object_id << " parameter number #" << i + 1 << " does not match with the expression" << endl;
                    compile = false;
                }
            }
        } else {
            cout << "In Class " << currentClass << " method " << expression->object_id << " does not have the right amount of parameters" << endl;
            cout << "# of parameters in method: " << parameterTypes.size() << endl;
            cout << "# of parameters given: " << expression->body_exp->expressions.size() << endl << endl;
            compile = false;
        }
        lastType = table.getMethodType(currentClass, expression->object_id);
    } else {
        cout << "In Class " << currentClass << " does not contain method: " << expression->object_id << endl;
        compile = false;
    }
}

void TypeChecker::visit(Newtype_exp* expression) {
    lastType = "ERROR";
    if (table.hasMethod(expression->type_id, expression->type_id)) {
        vector<string> parameterTypes = table.getFormalsType(expression->type_id, expression->type_id);
        if (parameterTypes.size() == expression->body_exp->expressions.size()) {
            for (int i = 0; i < parameterTypes.size(); i++) {
                expression->body_exp->expressions.at(i)->accept(this);
                if (!table.isParentype(parameterTypes.at(i), lastType)) {
                    cout << "In Class " << currentClass << " Constructor " << expression->type_id << " parameter number #" << i + 1 << " does not match with the given expression" << endl;
                    compile = false;
                }
            }
            lastType = table.getMethodType(expression->type_id, expression->type_id);
        } else {
            cout << "In Class " << currentClass << " the constructor call " << expression->type_id << " does not have the right amount of parameters" << endl;
            cout << "# of parameters in method: " << parameterTypes.size() << endl;
            cout << "# of parameters given: " << expression->body_exp->expressions.size() << endl << endl;
            compile = false;
        }
    } else {
        cout << "In Class " << currentClass << " Type " << expression->type_id << " does not exist" << endl;
    }
}

void TypeChecker::visit(Block_exp* expression) {
    table.addScope();
    for (auto &i : expression->blck->expressions)
        i->accept(this);
    table.removeScope();
}

void TypeChecker::visit(Paren_exp* expression) {
    table.addScope();
    expression->exp->accept(this);
    table.removeScope();
}

void TypeChecker::visit(Dot_object_exp* expression) {
    expression->exp->accept(this);
    string methodType = "ERROR";
    if (table.hasMethod(lastType, expression->object_id)) {
        methodType = table.getMethodType(lastType, expression->object_id);
        vector<string> parameterTypes = table.getFormalsType(lastType, expression->object_id);

        for (int i = 0; i < parameterTypes.size(); i++) {
            expression->body_exp->expressions.at(i)->accept(this);
            if (!table.isParentype(parameterTypes.at(i), lastType) && lastType != "Null") {
                cout << "In Class " << currentClass << " method " << expression->object_id << " parameter number #" << i + 1 << " does not match with the expression" << lastType << endl;
                compile = false;
            }
        }
    } else {
        cout << "In class " << currentClass << " type " << lastType << " does not contain a method call named " << expression->object_id << endl;
    }

    lastType = methodType;
}

void TypeChecker::visit(Case_exp* expression) {
    expression->exp->accept(this);
    expression->cases->accept(this);
}

void TypeChecker::visit(Less_exp* expression) {
    expression->exp1->accept(this);
    if (lastType != "Int") {
        cout << "Less then expression in class " << currentClass << " left side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    expression->exp2->accept(this);
    if (lastType != "Int") {
        cout << "Less then expression in class " << currentClass << " right side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    lastType = "Boolean";
}

void TypeChecker::visit(Leq_exp* expression) {
    expression->exp1->accept(this);
    if (lastType != "Int") {
        cout << "Lesser or equals expression in class " << currentClass << " left side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    expression->exp2->accept(this);
    if (lastType != "Int") {
        cout << "Lesser or equals expression in class " << currentClass << " right side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    lastType = "Boolean";
}

void TypeChecker::visit(Eq_exp* expression) {
    expression->exp1->accept(this);
    string leftExp = lastType;
    expression->exp2->accept(this);
    lastType = "Boolean";
}

void TypeChecker::visit(Mul_exp* expression) {
    expression->exp1->accept(this);
    if (lastType != "Int") {
        cout << "Multiply expression in class " << currentClass << " left side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    expression->exp2->accept(this);
    if (lastType != "Int") {
        cout << "Multiply expression in class " << currentClass << " right side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    lastType = "Int";
}

void TypeChecker::visit(Div_exp* expression) {
    expression->exp1->accept(this);
    if (lastType != "Int") {
        cout << "Divide expression in class " << currentClass << " left side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    expression->exp2->accept(this);
    if (lastType != "Int") {
        cout << "Divide expression in class " << currentClass << " right side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    lastType = "Int";
}

void TypeChecker::visit(Add_exp* expression) {
    expression->exp1->accept(this);
    if (lastType != "Int") {
        cout << "Add expression in class " << currentClass << " left side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    expression->exp2->accept(this);
    if (lastType != "Int") {
        cout << "Add expression in class " << currentClass << " right side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    lastType = "Int";
}

void TypeChecker::visit(Min_exp* expression) {
    expression->exp1->accept(this);
    if (lastType != "Int") {
        cout << "Subtract expression in class " << currentClass << " left side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    expression->exp2->accept(this);
    if (lastType != "Int") {
        cout << "Subtract expression in class " << currentClass << " right side of the expression is not of the Type Integer" << endl;
        compile = false;
    }
    lastType = "Int";
}

void TypeChecker::visit(Null_exp* expression) {
    lastType = "Null";
}

void TypeChecker::visit(Empty_exp* expression) {
    lastType = "Unit";
}

void TypeChecker::visit(Object_id_exp* expression) {
    lastType = table.getType(expression->object_id);
}

void TypeChecker::visit(Int_const_exp* expression) {
    lastType = "Int";
}

void TypeChecker::visit(String_lit_exp* expression) {
    lastType = "String";
}

void TypeChecker::visit(Bool_exp* expression) {
    lastType = "Boolean";
}

void TypeChecker::visit(This_exp* expression) {
    lastType = currentClass;
}

void TypeChecker::visit(Casecontent* casecontent) {
    table.addScope();
    table.addVariable(casecontent->object_id, casecontent->type_id);
    casecontent->block->accept(this);
    table.removeScope();
}

void TypeChecker::visit(Cases* cases) {
    string lubType = "";
    for (auto &i : cases->cases) {
        i->accept(this);
        if (lubType != "")
            lubType = table.getLUB(lubType, lastType);
        else
            lubType = lastType;
    }
    lastType = lubType;
}
//Utility methods

void MethodAdder::addMethod(string className, F_expr* ftr) {
    table.addClassMethod(className, ftr->object_id, ftr->type_id, formalContentTypeList(ftr->formalcontents));
}

void MethodAdder::addMethod(string className, F_nat* ftr) {
    table.addClassMethod(className, ftr->object_id, ftr->type_id, formalContentTypeList(ftr->formalcontents));
}

void MethodAdder::addMethod(string className, F_overide_expr* ftr) {
    table.addClassMethod(className, ftr->object_id, ftr->type_id, formalContentTypeList(ftr->formalcontents));
}

void MethodAdder::addMethod(string className, F_overide_nat* ftr) {
    table.addClassMethod(className, ftr->object_id, ftr->type_id, formalContentTypeList(ftr->formalcontents));
}

void TypeChecker::addMethod(string className, Vfcontents* vfcontents) {
    table.addClassMethod(className, className, className, formalContentTypeList(vfcontents));
}

vector<string> MethodAdder::formalContentTypeList(Formalcontents* frmlcnts) {
    vector<string> formalTypes;
    for (auto &i : frmlcnts->formalcontents) {
        formalTypes.push_back(i->type_id);
    }
    return formalTypes;
}

vector<string> TypeChecker::formalContentTypeList(Vfcontents* vfcnts) {
    vector<string> formalTypes;
    for (auto &i : vfcnts->vfcontents) {
        formalTypes.push_back(i->type_id);
    }
    return formalTypes;
}

//MethodAdder methods

MethodAdder::MethodAdder(SymbolTable& table) : Visitor(), table(table) {
}

void MethodAdder::changeClassName(string newClassName) {
    className = newClassName;
}

void MethodAdder::visit(Features* ftrs) {
    for (auto &i : ftrs->features) {
        i->accept(this);
    }
}

void MethodAdder::visit(F_expr* ftr) {
    addMethod(className, ftr);
}

void MethodAdder::visit(F_nat* ftr) {
    addMethod(className, ftr);
}

void MethodAdder::visit(F_overide_expr* ftr) {
    addMethod(className, ftr);
}

void MethodAdder::visit(F_overide_nat* ftr) {
    addMethod(className, ftr);
}

void MethodAdder::visit(F_var_exp* ftr) {
    //ignore not a method
}

void MethodAdder::visit(F_var_nat* ftr) {
    //ignore not a method
}

void MethodAdder::visit(F_block* ftr) {
    //ignore not a method
}

void MethodAdder::visit(Program* prgm) {
}

void MethodAdder::visit(Classdecls* clssdcls) {
}

void MethodAdder::visit(Classdecl* clssdcl) {
}

void MethodAdder::visit(Vfcontents* vfctnts) {
}

void MethodAdder::visit(Vfcontent* vfctnt) {
}

void MethodAdder::visit(Formalcontents* frmlcntnts) {
}

void MethodAdder::visit(Formalcontent* frmlcntnt) {
}

void MethodAdder::visit(Actuals* actuals) {
}

void MethodAdder::visit(Block* block) {
}

void MethodAdder::visit(NormalExpression* blockexpression) {
}

void MethodAdder::visit(InilizationBlockExpression* blockexpression) {
}

void MethodAdder::visit(Assign_exp* expression) {
}

void MethodAdder::visit(Not_exp* expression) {
}

void MethodAdder::visit(Uminus_exp* expression) {
}

void MethodAdder::visit(Cond_exp* expression) {
}

void MethodAdder::visit(Loop_exp* expression) {
}

void MethodAdder::visit(Super_exp* expression) {
}

void MethodAdder::visit(Object_exp* expression) {
}

void MethodAdder::visit(Newtype_exp* expression) {
}

void MethodAdder::visit(Block_exp* expression) {
}

void MethodAdder::visit(Paren_exp* expression) {
}

void MethodAdder::visit(Dot_object_exp* expression) {
}

void MethodAdder::visit(Case_exp* expression) {
}

void MethodAdder::visit(Less_exp* expression) {
}

void MethodAdder::visit(Leq_exp* expression) {
}

void MethodAdder::visit(Eq_exp* expression) {
}

void MethodAdder::visit(Mul_exp* expression) {
}

void MethodAdder::visit(Div_exp* expression) {
}

void MethodAdder::visit(Add_exp* expression) {
}

void MethodAdder::visit(Min_exp* expression) {
}

void MethodAdder::visit(Null_exp* expression) {
}

void MethodAdder::visit(Empty_exp* expression) {
}

void MethodAdder::visit(Object_id_exp* expression) {
}

void MethodAdder::visit(Int_const_exp* expression) {
}

void MethodAdder::visit(String_lit_exp* expression) {
}

void MethodAdder::visit(Bool_exp* expression) {
}

void MethodAdder::visit(This_exp* expression) {
}

void MethodAdder::visit(Casecontent* casecontent) {
}

void MethodAdder::visit(Cases* cases) {
}




