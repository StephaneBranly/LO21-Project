#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "../interface/mainwindow.h"
#include "../engine/computerengine.h"

#include "../observer/observer.h"
#include <string>

// Permet de faire la connection entre l'Engine et l'Interfarce
class Connector : public Observer
{
public:
    Connector(Mainwindow& w, Engine::ComputerEngine& engine);
    void notify(const std::string &message);
private:
    Mainwindow& window;
    Engine::ComputerEngine& engine;
};

#endif // CONNECTOR_H
