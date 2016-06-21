//
// Created by nikita on 21.06.16.
//

#include "module.hpp"

Sege::AbstractModule::AbstractModule() :
        eventBus(nullptr)
{
}

void Sege::AbstractModule::start(EventBus &_eventBus)
{
    eventBus = &_eventBus;
    onStart();
}