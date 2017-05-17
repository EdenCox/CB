/* 
 * File:   CodeGenerator.cpp
 * Author: Eden Cox
 * 
 * Created on February 24, 2017, 2:31 PM
 */

#include "CodeGenerator.h"

CodeGenerator::CodeGenerator(ofstream &header) : header(header) {

}

CodeGenerator::~CodeGenerator() {

}

void CodeGenerator::visit(Program* prgm) {
    header << "#ifndef CGF_H\n#define CGF_H\n\n";
    header << "#include \"BasicCool.h\"\n\n";
    header << "using namespace std;\n\n";
    //source << "#include \"cgf.h\"" << endl << endl;

    prgm->classes->accept(this);

    header << "#endif /* CGF_H */" << endl << endl;

}

void CodeGenerator::visit(Classdecls* clssdcls) {

    for (auto &i : clssdcls->classdecls) {
        i->accept(this);
    }

}

void CodeGenerator::visit(Classdecl* clssdcl) {
    if (generateClass(clssdcl->type_id)) {
        header << "class " << clssdcl->type_id << " : public " << clssdcl->extend_type_id << " {\nprivate:\n";
        header << "typedef " << clssdcl->extend_type_id << " super;\nprotected:\n";
        clssdcl->vfcontents->accept(this);
        header << "public:\n";
        header << clssdcl->type_id << "(";
        std::string sep = "";
        for (auto &i : clssdcl->vfcontents->vfcontents) {
            header << sep << i->type_id << " " << i->object_id;
            sep = separator;
        }
        header << ");\n" ;
        header << "string _type_() override;\n";

        clssdcl->features->accept(this);

        header << "\n};\n\n";
    }
}

void CodeGenerator::visit(Vfcontents* vfctnts) {
    for (auto &i : vfctnts->vfcontents) {
        i->accept(this);
    }
}

void CodeGenerator::visit(Vfcontent* vfctnt) {

    header << vfctnt->type_id << " " << vfctnt->object_id << ";\n";
}

void CodeGenerator::visit(Features* ftrs) {
    for (auto &i : ftrs->features) {
        i->accept(this);
    }

}

void CodeGenerator::visit(F_block* ftr) {


}

void CodeGenerator::visit(F_expr* ftr) {
    header << "virtual " << ftr->type_id << " " << ftr->object_id << "(";
    std::string sep = "";
    for (auto &i : ftr->formalcontents->formalcontents) {
        header << sep << i->type_id << " " << i->object_id;
        sep = separator;
    }
    header << ");\n";


}

void CodeGenerator::visit(F_nat* ftr) {

}

void CodeGenerator::visit(F_overide_expr* ftr) {
    header << ftr->type_id << " " << ftr->object_id << "(";
    std::string sep = "";
    for (auto &i : ftr->formalcontents->formalcontents) {
        header << sep << i->type_id << " " << i->object_id;
        sep = separator;
    }
    header << ") override;\n";
}

void CodeGenerator::visit(F_overide_nat* ftr) {

}

void CodeGenerator::visit(F_var_exp* ftr) {

    header << "private:\n" << ftr->type_id << " " << ftr->object_id <<" = ";
    ftr->exp->accept(this);
    header <<";\n"<<"public:\n";

}

void CodeGenerator::visit(F_var_nat* ftr) {

}

void CodeGenerator::visit(Formalcontents* frmlcntnts) {

}

void CodeGenerator::visit(Formalcontent* frmlcntnt) {

}

void CodeGenerator::visit(Actuals* actuals) {

}

void CodeGenerator::visit(Block* block) {

}

void CodeGenerator::visit(NormalExpression* blockexpression) {

}

void CodeGenerator::visit(InilizationBlockExpression* blockexpression) {

}

void CodeGenerator::visit(Assign_exp* expression) {
   
}

void CodeGenerator::visit(Not_exp* expression) {
    header<<"!";
    expression->exp->accept(this);
}

void CodeGenerator::visit(Uminus_exp* expression) {
    header<<"-";
    expression->exp->accept(this);
}

void CodeGenerator::visit(Cond_exp* expression) {

}

void CodeGenerator::visit(Loop_exp* expression) {
    

}

void CodeGenerator::visit(Super_exp* expression) {
    header << "super." << expression->object_id << "(";
    string sep = "";
    for (auto &i : expression->body_exp->expressions) {
        header << sep;
        i->accept(this);
        sep = separator;
    }
    header << ")";
}

void CodeGenerator::visit(Object_exp* expression) {
    header << expression->object_id << "(";
    string sep = "";
    for (auto &i : expression->body_exp->expressions) {
        header << sep;
        i->accept(this);
        sep = separator;
    }
    header << ")";

}

void CodeGenerator::visit(Newtype_exp* expression) {
    header << expression->type_id << "(";
    string sep = "";
    for (auto &i : expression->body_exp->expressions) {
        header << sep;
        i->accept(this);
        sep = separator;
    }
    header << ")";

}

void CodeGenerator::visit(Block_exp* expression) {
    header << "{";
    expression->blck->accept(this);
    header << "}";
}

void CodeGenerator::visit(Paren_exp* expression) {
    header << "(";
    expression->exp->accept(this);
    header << ")";
}

void CodeGenerator::visit(Dot_object_exp* expression) {
    expression->accept(this);
    header << "." << expression->object_id << "(";
    string sep = "";
    for (auto &i : expression->body_exp->expressions) {
        header << sep;
        i->accept(this);
        sep = separator;
    }
    header << ")";
}

void CodeGenerator::visit(Case_exp* expression) {

}

void CodeGenerator::visit(Less_exp* expression) {
    expression->exp1->accept(this);
    header << "< ";
    expression->exp2->accept(this);
}

void CodeGenerator::visit(Leq_exp* expression) {
    expression->exp1->accept(this);
    header << "<= ";
    expression->exp2->accept(this);
}

void CodeGenerator::visit(Eq_exp* expression) {
    expression->exp1->accept(this);
    header << ".equals(";
    expression->exp2->accept(this);
    header << ")";
}

void CodeGenerator::visit(Mul_exp* expression) {
    expression->exp1->accept(this);
    header << "* ";
    expression->exp2->accept(this);
}

void CodeGenerator::visit(Div_exp* expression) {
    expression->exp1->accept(this);
    header << "/ ";
    expression->exp2->accept(this);
}

void CodeGenerator::visit(Add_exp* expression) {
    expression->exp1->accept(this);
    header << "+ ";
    expression->exp2->accept(this);
}

void CodeGenerator::visit(Min_exp* expression) {
    expression->exp1->accept(this);
    header << "- ";
    expression->exp2->accept(this);
}

void CodeGenerator::visit(Null_exp* expression) {
    header << "Null() ";
}

void CodeGenerator::visit(Empty_exp* expression) {

}

void CodeGenerator::visit(Object_id_exp* expression) {
    header << expression->object_id << " ";
}

void CodeGenerator::visit(Int_const_exp* expression) {
    header << expression->int_const << " ";
}

void CodeGenerator::visit(String_lit_exp* expression) {
    header<<"\"" << expression->string_lit <<"\"";
}

void CodeGenerator::visit(Bool_exp* expression) {
    header << std::boolalpha<<expression->boolean_const << " ";
}

void CodeGenerator::visit(This_exp* expression) {
    header << "this ";
}

void CodeGenerator::visit(Casecontent* casecontent) {

}

void CodeGenerator::visit(Cases* cases) {

}

bool CodeGenerator::generateClass(string className) {
    return className != "Any" && className != "IO" && className != "Unit" && className != "Int" && className != "Boolean" && className != "String" && className != "Symbol" && className != "ArrayAny" && className != "Null" && className != "Statistics";
}



