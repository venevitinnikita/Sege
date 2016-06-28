//
// Created by nikita on 21.06.16.
//

#include "module.hpp"

Sege::AbstractModule::AbstractModule() :
        pEventBus(nullptr)
{
}

void Sege::AbstractModule::start(std::shared_ptr<EventBus> &_pEventBus)
{
    pEventBus = std::shared_ptr<EventBus>(_pEventBus);
    onStart();
}