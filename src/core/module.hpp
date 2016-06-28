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
        std::shared_ptr<EventBus> pEventBus;

        virtual void onStart() = 0;

    public:
        AbstractModule();

        void start(std::shared_ptr<EventBus> &_pEventBus);

        virtual ~AbstractModule() = default;
    };
}

#endif //SEGE_MODULE_HPP
