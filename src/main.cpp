/*
 * main.cpp
 *
 *  Created on: Feb 16, 2016
 *      Author: Venevitin Nikita (venevitinnikita@gmail.com)
 */

#include "core/event/EventBus.hpp"
#include "core/module.hpp"

#include <iostream>

using namespace Sege;

class SomeEvent
{
    int a;
public:
    int getA() const
    {
        return a;
    }

    void setA(int _a)
    {
        a = _a;
    }
};

class SomeHandler
{
public:
    void operator()(HandlerArgType<SomeEvent> pEvent)
    {
        std::cout << "Handler object invokation (a = " << pEvent->getA() << ")\n";
    }
};

void handlerFunction(HandlerArgType<SomeEvent> pEvent)
{
    std::cout << "Handler function invokation (a = " << pEvent->getA() << ")\n";
}

class SomeModule : public AbstractModule
{
protected:
    void onStart()
    {
        auto handlerLambda = [](HandlerArgType<SomeEvent> pEvent)
        {
            std::cout << "Handler lambda invokation (a = " << pEvent->getA() << ")\n";
        };

        SomeHandler handlerObject;

        eventBus->addHandler<SomeEvent>(handlerLambda);
        eventBus->addHandler<SomeEvent>(handlerFunction);
        eventBus->addHandler<SomeEvent>(handlerObject);
    }
};

int main()
{
    EventBus eventBus;

    SomeModule someModule;
    someModule.start(eventBus);

    auto someEvent = std::make_shared<SomeEvent>();
    someEvent->setA(5);
    eventBus.fireEvent(someEvent);

    return 0;
}
