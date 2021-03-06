#include "expressionabstractfactory.h"
#include "../exception/CompException.h"
#include "operator/operatoraritbinary.h"
#include "operator/operatoraritunary.h"
#include "operator/operatorlogic.h"
#include "operator/operatorcond.h"
#include <QDebug>

Engine::ExpressionAbstractFactory::ExpressionAbstractFactory()
{
    operatorFactory = new OperatorFactory;
    operatorFactory->addOperator("CLEAR",new OperatorCLEAR);
    operatorFactory->addOperator("SWAP",new OperatorSWAP);
    operatorFactory->addOperator("DUP",new OperatorDUP);
    operatorFactory->addOperator("DROP",new OperatorDROP);
    operatorFactory->addOperator("AND",new OperatorAnd);
    operatorFactory->addOperator("OR",new OperatorOr);
    operatorFactory->addOperator("NOT",new OperatorNot);
    operatorFactory->addOperator("=",new OperatorEq);
    operatorFactory->addOperator("!=",new OperatorDiff);
    operatorFactory->addOperator(">",new OperatorGt);
    operatorFactory->addOperator("<",new OperatorLt);
    operatorFactory->addOperator(">=",new OperatorGeq);
    operatorFactory->addOperator("=<",new OperatorLeq);
    operatorFactory->addOperator("EVAL",new OperatorEVAL);
    operatorFactory->addOperator("STO",new OperatorSTO);
    operatorFactory->addOperator("FORGET",new OperatorFORGET);
    operatorFactory->addOperator("+",new OperatorPLUS);
    operatorFactory->addOperator("-",new OperatorMINUS);
    operatorFactory->addOperator("*",new OperatorMUL);
    operatorFactory->addOperator("/",new OperatorDIV);
    operatorFactory->addOperator("DIV",new OperatorDIVINT);
    operatorFactory->addOperator("MOD",new OperatorMOD);
    operatorFactory->addOperator("NEG",new OperatorNEG);
    operatorFactory->addOperator("NUM",new OperatorNUM);
    operatorFactory->addOperator("DEN",new OperatorDEN);
    operatorFactory->addOperator("POW",new OperatorPOW);
    operatorFactory->addOperator("SIN",new OperatorSIN);
    operatorFactory->addOperator("COS",new OperatorCOS);
    operatorFactory->addOperator("TAN",new OperatorTAN);
    operatorFactory->addOperator("ARCSIN",new OperatorARCSIN);
    operatorFactory->addOperator("ARCCOS",new OperatorARCCOS);
    operatorFactory->addOperator("ARCTAN",new OperatorARCTAN);
    operatorFactory->addOperator("SQRT",new OperatorSQRT);
    operatorFactory->addOperator("EXP",new OperatorEXP);
    operatorFactory->addOperator("LN",new OperatorLN);
    operatorFactory->addOperator("IFT",new OperatorIFT);
    operatorFactory->addOperator("IFTE",new OperatorIFTE);
    operatorFactory->addOperator("WHILE",new OperatorWHILE);
    operatorFactory->addOperator("TYPE",new OperatorTYPE);
}

Engine::Expression* Engine::ExpressionAbstractFactory::createExpressionFromString(const std::string s) const
{
    Expression* res=nullptr;
    if(operatorFactory->isSameType(s)) // On regarde si ce n'est pas un operateur
        return operatorFactory->createExpressionFromString(s);
    for(auto it = factories.begin(); it!=factories.end(); ++it){ // Sinon, on parcours toutes les autres factories pour savoir si le type est reconnu
        if((*it)->isSameType(s))
        {
            if(!res)
                res = (*it)->createExpressionFromString(s);

            else
                throw ComputerException("Reconnu par plusieurs types"); // Si des Regex sont valides pour plusieurs types, un message est throw
        }
    }
    if(!res)
        throw ComputerException("Type non reconnu de "+s); // Si jamais le type est non reconnu, un message est throw
    return res;
}
