/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CodeGenerator.cpp
 * Author: easy
 * 
 * Created on February 24, 2017, 2:31 PM
 */

#include "SourceGenerator.h"

SourceGenerator::SourceGenerator(ofstream &source) : source(source) {

}

void SourceGenerator::visit(Program* prgm) {
    source << "#include \"cfg.h\"" << endl << endl;

    prgm->classes->accept(this);


}

void SourceGenerator::visit(Classdecls* clssdcls) {

    for (auto &i : clssdcls->classdecls) {
        i->accept(this);
    }

}

void SourceGenerator::visit(Classdecl* clssdcl) {
    if (generateClass(clssdcl->type_id)) {
        currentClass = clssdcl->type_id;
        source << "string " << clssdcl->type_id << "::_type_(){\n\treturn \"" << clssdcl->type_id << "\";\n}\n\n";
        clssdcl->features->accept(this);
    }
}

void SourceGenerator::visit(Vfcontents* vfctnts) {
    for (auto &i : vfctnts->vfcontents) {
        i->accept(this);
    }
}

void SourceGenerator::visit(Vfcontent* vfctnt) {

    source << vfctnt->type_id << " " << vfctnt->object_id << ";" << endl;
}

void SourceGenerator::visit(Features* ftrs) {
    for (auto &i : ftrs->features) {
        i->accept(this);
    }

}

void SourceGenerator::visit(F_block* ftr) {
    cCode = true;

    for (auto &i : ftr->blck->expressions) {
        i->accept(this);
    }
    cCode = false;

}

void SourceGenerator::visit(F_expr* ftr) {
    source << ftr->type_id << " " << currentClass << "::" << ftr->object_id << "(";
    string sep = "";
    for (auto &i : ftr->formalcontents->formalcontents) {
        source << sep << i->type_id << "& " << i->object_id;
        sep = separator;
    }
    source << "){" << endl;



    ftr->exp->accept(this);
    if (!blockCode)
        source << ";\n";
    blockCode = false;

    source << "}\n\n";



}

void SourceGenerator::visit(F_nat* ftr) {

}

void SourceGenerator::visit(F_overide_expr* ftr) {
    source << ftr->type_id << " " << currentClass << "::" << ftr->object_id << "(";
    string sep = "";
    for (auto &i : ftr->formalcontents->formalcontents) {
        source << sep << i->type_id << "& " << i->object_id;
        sep = separator;
    }
    source << "){" << endl;



    ftr->exp->accept(this);

    if (!blockCode)
        source << ";\n";
    blockCode = false;

    source << "}\n";
}

void SourceGenerator::visit(F_overide_nat* ftr) {

}

void SourceGenerator::visit(F_var_exp* ftr) {

}

void SourceGenerator::visit(F_var_nat* ftr) {

}

void SourceGenerator::visit(Formalcontents* frmlcntnts) {

}

void SourceGenerator::visit(Formalcontent* frmlcntnt) {

}

void SourceGenerator::visit(Actuals* actuals) {

}

void SourceGenerator::visit(Block* block) {
    blockCode = true;
    for (int i = 0; i < block->expressions.size(); i++) {
        if (!cCode) {
            if (i + 1 == block->expressions.size())
                if (!ifCode && !loopCode)
                    source << "return ";

            block->expressions.at(i)->accept(this);
            if (ifCode) {
                source << ", ";
            } else {
                source << ";" << endl;
            }
        }
    }
}

void SourceGenerator::visit(NormalExpression* blockexpression) {
    blockexpression->exp->accept(this);
}

void SourceGenerator::visit(InilizationBlockExpression* blockexpression) {
    if (cCode) {
        constructorCode += blockexpression->type_id + " " + blockexpression->object_id + " = ";
        blockexpression->exp->accept(this);
    } else {
        source << blockexpression->type_id << " " << blockexpression->object_id << " = ";
        blockexpression->exp->accept(this);
    }

}

void SourceGenerator::visit(Assign_exp* expression) {
    if (cCode) {
        constructorCode += expression->object_id + " = ";
        expression->exp->accept(this);
    } else {
        source << expression->object_id << " = ";
        expression->exp->accept(this);
    }
}

void SourceGenerator::visit(Not_exp* expression) {
    if (cCode) {
        constructorCode += "!";
        expression->exp->accept(this);
    } else {
        source << "!";
        expression->exp->accept(this);
    }

}

void SourceGenerator::visit(Uminus_exp* expression) {
    if (cCode) {
        constructorCode += "-";
        expression->exp->accept(this);
    } else {
        source << "-";
        expression->exp->accept(this);
    }

}

void SourceGenerator::visit(Cond_exp* expression) {
    ifCode = true;
    if (cCode) {
        constructorCode += "(";
        expression->precedence->accept(this);
        constructorCode += ") ? ";
        expression->then_exp->accept(this);
        constructorCode += ": ";
        expression->else_exp->accept(this);
    } else {
        source << "(";
        expression->precedence->accept(this);
        source << ") ? ";
        expression->then_exp->accept(this);
        source << ": ";
        expression->else_exp->accept(this);
    }
    ifCode = false;

}

void SourceGenerator::visit(Loop_exp* expression) {
    loopCode = true;
    if (cCode) {
        constructorCode += "while(";
        expression->precedence->accept(this);
        constructorCode += "){\n";
        expression->body_exp->accept(this);
        constructorCode += "}\n";
    } else {
        source << "while(";
        expression->precedence->accept(this);
        source << "){\n";
        expression->body_exp->accept(this);
        source << "}\n";
    }
    loopCode = false;

}

void SourceGenerator::visit(Super_exp* expression) {
    if (cCode) {
        constructorCode += "super." + expression->object_id + "(";
        string sep = "";
        for (auto &i : expression->body_exp->expressions) {
            constructorCode + sep;
            i->accept(this);
            sep = separator;
        }
        constructorCode += ")";
    } else {
        source << "super." << expression->object_id << "(";
        string sep = "";
        for (auto &i : expression->body_exp->expressions) {
            source << sep;
            i->accept(this);
            sep = separator;
        }
        source << ")";
    }
}

void SourceGenerator::visit(Object_exp* expression) {
    if (cCode) {
        constructorCode += expression->object_id + "(";
        string sep = "";
        for (auto &i : expression->body_exp->expressions) {
            constructorCode + sep;
            i->accept(this);
            sep = separator;
        }
        constructorCode += ")";
    } else {
        source << expression->object_id << "(";
        string sep = "";
        for (auto &i : expression->body_exp->expressions) {
            source << sep;
            i->accept(this);
            sep = separator;
        }
        source << ")";
    }

}

void SourceGenerator::visit(Newtype_exp* expression) {
    if (cCode) {
        constructorCode += expression->type_id + "(";
        string sep = "";
        for (auto &i : expression->body_exp->expressions) {
            constructorCode += sep;
            i->accept(this);
            sep = separator;
        }
        constructorCode += ")";
    } else {
        source << expression->type_id << "(";
        string sep = "";
        for (auto &i : expression->body_exp->expressions) {
            source << sep;
            i->accept(this);
            sep = separator;
        }
        source << ")";
    }

}

void SourceGenerator::visit(Block_exp* expression) {
    //    if (cCode) {
    //        constructorCode += "{\n";
    //    } else {
    //        source << "{\n";
    //    }
    expression->blck->accept(this);
    //    if (cCode) {
    //        constructorCode += "\n}\n";
    //    } else {
    //        source << "\n}\n";
    //    }
}

void SourceGenerator::visit(Paren_exp* expression) {
    if (cCode) {
        constructorCode += "(";
    } else {
        source << "(";
    }
    expression->exp->accept(this);
    if (cCode) {
        constructorCode += ")";
    } else {
        source << ")";
    }
}

void SourceGenerator::visit(Dot_object_exp* expression) {
    expression->exp->accept(this);
    if (cCode) {
        constructorCode += "." + expression->object_id + "(";
    } else {
        source << "." << expression->object_id << "(";
    }

    string sep = "";
    for (auto &i : expression->body_exp->expressions) {
        if (cCode) {
            constructorCode += sep;
        } else {
            source << sep;
        }
        i->accept(this);
        sep = separator;
    }
    if (cCode) {
        constructorCode += ")";
    } else {
        source << ")";
    }
}

void SourceGenerator::visit(Case_exp* expression) {

}

void SourceGenerator::visit(Less_exp* expression) {
    expression->exp1->accept(this);
    if (cCode) {
        constructorCode += "< ";
    } else {
        source << "< ";
    }
    expression->exp2->accept(this);
}

void SourceGenerator::visit(Leq_exp* expression) {
    expression->exp1->accept(this);
    if (cCode) {
        constructorCode += "<= ";
    } else {
        source << "<= ";
    }
    expression->exp2->accept(this);
}

void SourceGenerator::visit(Eq_exp* expression) {
    expression->exp1->accept(this);
    if (cCode) {
        constructorCode += " == ";
    } else {
        source << " == ";
    }
    expression->exp2->accept(this);
}

void SourceGenerator::visit(Mul_exp* expression) {
    expression->exp1->accept(this);
    if (cCode) {
        constructorCode += "* ";
    } else {
        source << "* ";
    }
    expression->exp2->accept(this);
}

void SourceGenerator::visit(Div_exp* expression) {
    expression->exp1->accept(this);
    if (cCode) {
        constructorCode += "/ ";
    } else {
        source << "/ ";
    }
    expression->exp2->accept(this);
}

void SourceGenerator::visit(Add_exp* expression) {
    expression->exp1->accept(this);
    if (cCode) {
        constructorCode += "+ ";
    } else {
        source << "+ ";
    }
    expression->exp2->accept(this);
}

void SourceGenerator::visit(Min_exp* expression) {
    expression->exp1->accept(this);
    if (cCode) {
        constructorCode += "- ";
    } else {
        source << "- ";
    }
    expression->exp2->accept(this);
}

void SourceGenerator::visit(Null_exp* expression) {
    if (cCode) {
        constructorCode += "Null() ";
    } else {
        source << "Null() ";
    }
}

void SourceGenerator::visit(Empty_exp* expression) {
    if (cCode) {
        constructorCode += "Unit() ";
    } else {
        source << "Unit() ";
    }
}

void SourceGenerator::visit(Object_id_exp* expression) {
    if (cCode) {
        constructorCode += expression->object_id + " ";
    } else {
        source << expression->object_id << " ";
    }

}

void SourceGenerator::visit(Int_const_exp* expression) {
    if (cCode) {
        constructorCode += expression->int_const + " ";
    } else {
        source << expression->int_const << " ";
    }
}

void SourceGenerator::visit(String_lit_exp* expression) {
    if (cCode) {
        constructorCode += "\"" + expression->string_lit + "\"";
    } else {
        source << "\"" << expression->string_lit << "\"";
    }
}

void SourceGenerator::visit(Bool_exp* expression) {
    if (cCode) {
        constructorCode += expression->boolean_const ? "true " : "false ";
    } else {
        source << std::boolalpha << expression->boolean_const << " ";
    }
}

void SourceGenerator::visit(This_exp* expression) {
    source << "*this ";
}

void SourceGenerator::visit(Casecontent* casecontent) {

}

void SourceGenerator::visit(Cases* cases) {

}

bool SourceGenerator::generateClass(string className) {
    return className != "Any" && className != "IO" && className != "Unit" && className != "Int" && className != "Boolean" && className != "String" && className != "Symbol" && className != "ArrayAny" && className != "Null" && className != "Statistics";
}



