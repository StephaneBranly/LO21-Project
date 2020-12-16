#include "operatoraritunary.h"
#include "../../computerengine.h"
#include "../../exception/CompException.h"
#include "../litterales/linteger.h"
#include "../litterales/lreal.h"
#include "../litterales/lrational.h"
#include "../litterales/lnumerical.h"
#include <math.h>


void Engine::OperatorAritUnary::registerActionUnary(std::string type, ActionUnary *a)
{
    opes.insert(make_pair(type,a));
}

void Engine::OperatorAritUnary::executeOpe(vector<Expression*> e)
{
    Stack& p = ComputerEngine::getInstance().getStack();
    Expression* L=e[0];
    string t = L->getType();
    if (opes.find(t) != opes.end())
    {
        p.push(dynamic_cast<Lnumerical*>(opes.at(t)->executeActionUnary(L))->simplifyType());
    }
    else
    {
        throw ComputerException("Action "+toString()+" impossible avec "+L->getType());
    }
}

//Constructeurs des opérateurs unaires
//opéteur NEG
Engine::OperatorNEG::OperatorNEG(): OperatorAritUnary("OperatorNEG")
{
    registerActionUnary("Linteger", new NegInt);
    registerActionUnary("Lreal", new NegReal);
    registerActionUnary("Lrational", new NegRat);
}

//Opérateur NUM
Engine::OperatorNUM::OperatorNUM(): OperatorAritUnary("OperatorNUM")
{
    registerActionUnary("Linteger", new NumInt);
    registerActionUnary("Lrational", new NumRat);
}

//Opérateur DEN
Engine::OperatorDEN::OperatorDEN(): OperatorAritUnary("OperatorDEN")
{
    registerActionUnary("Linteger", new DenInt);
    registerActionUnary("Lrational", new DenRat);
}

//Opérateur SIN
Engine::OperatorSIN::OperatorSIN(): OperatorAritUnary("OperatorSIN")
{
    registerActionUnary("Linteger", new SinR1);
    registerActionUnary("Lreal", new SinR1);
    registerActionUnary("Lrational", new SinR1);

}

//Opérateur COS
Engine::OperatorCOS::OperatorCOS(): OperatorAritUnary("OperatorCOS")
{
    registerActionUnary("Linteger", new CosR1);
    registerActionUnary("Lreal", new CosR1);
    registerActionUnary("Lrational", new CosR1);
}

//Opérateur TAN
Engine::OperatorTAN::OperatorTAN(): OperatorAritUnary("OperatorTAN")
{
    registerActionUnary("Linteger", new TanR1);
    registerActionUnary("Lreal", new TanR1);
    registerActionUnary("Lrational", new TanR1);
}

//Opérateur ARCSIN
Engine::OperatorARCSIN::OperatorARCSIN(): OperatorAritUnary("OperatorARCSIN")
{
    registerActionUnary("Linteger", new ArcsinR1);
    registerActionUnary("Lreal", new ArcsinR1);
    registerActionUnary("Lrational", new ArcsinR1);
}

//Opérateur ARCCOS
Engine::OperatorARCCOS::OperatorARCCOS(): OperatorAritUnary("OperatorARCCOS")
{
    registerActionUnary("Linteger", new ArccosR1);
    registerActionUnary("Lreal", new ArccosR1);
    registerActionUnary("Lrational", new ArccosR1);
}

//Opérateur ARCTAN
Engine::OperatorARCTAN::OperatorARCTAN(): OperatorAritUnary("OperatorARCTAN")
{
    registerActionUnary("Linteger", new ArctanR1);
    registerActionUnary("Lreal", new ArctanR1);
    registerActionUnary("Lrational", new ArctanR1);
}

//Redéfinition de la méthode pour chaque ActionUnary
//Opérator NEG
Engine::Expression* Engine::NegInt::executeActionUnary(Expression* L)
{
    return (new Linteger(-1*dynamic_cast<Linteger*>(L)->getValue()));
}

Engine::Expression* Engine::NegReal::executeActionUnary(Expression* L)
{
    return (new Lreal(-1.0*dynamic_cast<Lreal*>(L)->getValue()));
}

Engine::Expression* Engine::NegRat::executeActionUnary(Expression* L)
{
    return (new Lrational(-1*dynamic_cast<Lrational*>(L)->getNumerator(), dynamic_cast<Lrational*>(L)->getDenominator()));
}

//Opérateur NUM
Engine::Expression* Engine::NumInt::executeActionUnary(Expression* L)
{
    return (new Linteger(dynamic_cast<Linteger*>(L)->getValue()));
}

Engine::Expression* Engine::NumRat::executeActionUnary(Expression* L)
{
    return (new Linteger(dynamic_cast<Lrational*>(L)->getNumerator()));
}

//Opérateur DEN
Engine::Expression* Engine::DenInt::executeActionUnary(Expression* L)
{
    return (new Linteger(1));
}

Engine::Expression* Engine::DenRat::executeActionUnary(Expression* L)
{
    return (new Linteger(dynamic_cast<Lrational*>(L)->getDenominator()));
}

//Opérateur SIN
Engine::Expression* Engine::SinR1::executeActionUnary(Expression* L)
{
    return (new Lreal(sin(dynamic_cast<R1value*>(L)->getValue())));
}

//Opérateur COS
Engine::Expression* Engine::CosR1::executeActionUnary(Expression* L)
{
    return (new Lreal(cos(dynamic_cast<R1value*>(L)->getValue())));
}

//Opérateur TAN
Engine::Expression* Engine::TanR1::executeActionUnary(Expression* L)
{
    return (new Lreal(tan(dynamic_cast<R1value*>(L)->getValue())));
}

//Opérateur ARCSIN
Engine::Expression* Engine::ArcsinR1::executeActionUnary(Expression* L)
{
    return (new Lreal(asin(dynamic_cast<R1value*>(L)->getValue())));
}

//Opérateur ARCCOS
Engine::Expression* Engine::ArccosR1::executeActionUnary(Expression* L)
{
    return (new Lreal(acos(dynamic_cast<R1value*>(L)->getValue())));
}

//Opérateur ARCTAN
Engine::Expression* Engine::ArctanR1::executeActionUnary(Expression* L)
{
    return (new Lreal(atan(dynamic_cast<R1value*>(L)->getValue())));
}



