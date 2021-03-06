#include "connector.h"
#include "../interface/mainwindow.h"
#include "../observer/observer.h"
#include "../engine/exception/CompException.h"

#include <QDebug>

#include <string>

Connector::Connector(Mainwindow& w, Engine::ComputerEngine& e) : window(w), engine(e)
{
    // Connexion du connector a l'Engine et a l'Interface
    window.show();
    window.attach(this);
    engine.getInstance().attach(this);
}

void Connector::notify(const std::string &message)
{
    // Filtrage des differents messages pouvant etre recus.
    // Et communication entre les deux parties pour transmettre correctement les informations
    if(message=="clickEval")
    {
        const std::string content = window.getContentCommandLine().toStdString();
        try{engine.getInstance().getExpressionManager().evalCommandLine(content); window.setMessage("OK"); window.clearCommandLine(); }
        catch(Engine::ComputerException e){ window.setMessage(QString::fromStdString(e.what()));}
    }else if(message=="stackChanged")
    {
        const std::list<std::string> items = engine.getInstance().getStack().toStringList();
        std::list<QString> forStack;
        for(auto it = items.begin(); it!=items.end(); ++it)
            forStack.push_back(QString::fromStdString(*it));
        window.updateStack(forStack);
    }else if(message=="atomsChanged")
    {
        std::list<std::tuple<std::string,std::string,std::string>> list = engine.getInstance().getAtomManager().toTupleStringList();
        std::tuple<QString,QString,QString> tu;
        std::list<std::tuple<QString,QString,QString>> listQstring;
        for(auto it = list.begin(); it!=list.end();++it)
        {
            tu = make_tuple(QString::fromStdString(std::get<0>(*it)),QString::fromStdString(std::get<1>(*it)),QString::fromStdString(std::get<2>(*it)));
            listQstring.push_back(tu);
        }
        window.updateAtoms(listQstring);
    }else if(message=="executeBuffer")
    {
        const std::string buffer = window.getBuffer().toStdString();
        try{engine.getExpressionManager().evalCommandLine(buffer); window.setMessage("OK");  }
        catch(Engine::ComputerException e){ window.setMessage(QString::fromStdString(e.what()));}
    }else if(message=="needAtomValue"){
        const std::string atomName = window.getBuffer().toStdString();
        try{
            Engine::Expression* exp = engine.getInstance().getAtomManager().getExpressionFromString(atomName);
            string s = "";
            if(dynamic_cast<Engine::editString*>(exp)==nullptr)
                s = exp->toString();
            else
                s = dynamic_cast<Engine::editString*>(exp)->toEditString();
            window.setBuffer(QString::fromStdString(s));
            window.setMessage("OK");
        }
        catch(Engine::ComputerException e){ window.setMessage(QString::fromStdString(e.what()));}
    }else if(message=="updateCommandLine")
    {
        string s = engine.getInstance().getExpressionManager().getContentEval();
        window.clearCommandLine();
        window.addToCommandline(QString::fromStdString(s));
    }

};
