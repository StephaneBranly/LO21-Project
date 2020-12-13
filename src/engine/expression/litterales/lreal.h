#ifndef LREELLE_H
#define LREELLE_H
#include "lnumerical.h"
#include <string>
#include "linteger.h"

namespace Engine {
class Lreal : public Lnumerical
{
    float real;
protected:
    std::string type="Lreal";
public:
    Lreal(const std::string s);
    Lreal(float r): real(r){};
    Lreal* setReal(float r);
    double getValue() override {return real;}
    float getfloatvalue() {return real;}
//    LReal* createCopy()const override{return new LReal(*this);}
    std::string const toString()const override{return std::to_string(real);}
    const std::string getType() const override { return this->type; }
    Expression* getCopy() const override { return new Lreal(real); }
    Linteger* simplifyType() override;
};
}
#endif // LREELLE_H
