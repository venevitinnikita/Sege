//
// Created by nikita on 21.06.16.
//

#ifndef SEGE_MODULE_HPP
#define SEGE_MODULE_HPP

#include "event/EventBus.hpp"

namespace Sege
{
    class AbstractModule
    {
    protected:
        EventBus *eventBus;

        virtual void onStart() = 0;

    public:
        AbstractModule();

        void start(EventBus &_eventBus);

        virtual ~AbstractModule() = default;
    };
}

#endif //SEGE_MODULE_HPP
