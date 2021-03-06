#ifndef LATOM_H
#define LATOM_H
#include "../../expression/expression.h"
#include <string>

namespace Engine {

// Un atom est un identifiant potentiel associe a un Lprogram pour Lnumerical
class Latom : public Expression
{
    std::string atom;
public:
    Latom(const std::string s): Expression("Latom"), atom(s){};
    Latom(const Latom&): Expression("Latom"){}
    Latom* setLatom(const std::string s);
    std::string getValue() const {return atom;}
    void eval() override;
    const std::string toString() const override{return atom;}
    Expression* getCopy() const override { return new Latom(atom); }
    ~Latom() = default;
};
}
#endif // LATOM_H

