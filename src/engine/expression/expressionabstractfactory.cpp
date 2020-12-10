#include "expressionabstractfactory.h"
#include "../exception/CompException.h"
#include <QDebug>

Engine::ExpressionAbstractFactory::ExpressionAbstractFactory()
{
    operatorFactory = new OperatorFactory;
    operatorFactory->addOperator("CLEAR",new OperatorCLEAR);
    operatorFactory->addOperator("SWAP",new OperatorSWAP);
    operatorFactory->addOperator("DUP",new OperatorDUP);
    operatorFactory->addOperator("DROP",new OperatorDROP);
}
Engine::Expression* Engine::ExpressionAbstractFactory::createExpressionFromString(const std::string s)
{
    Expression* res=nullptr;
    if(operatorFactory->isSameType(s))
        return operatorFactory->createExpressionFromString(s);
    for(auto it = factories.begin(); it!=factories.end(); ++it){
        if((*it)->isSameType(s))
        {
            if(!res)
            {

                res = (*it)->createExpressionFromString(s);
                qDebug() << "Type reconnu : "+QString::fromStdString(res->getType());
            }
            else
                throw ComputerException("Reconnu par plusieurs types");
        }
    }
    if(!res)
        throw ComputerException("Type non reconnu de "+s);
    return res;
}