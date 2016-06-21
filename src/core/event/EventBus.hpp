/*
 * EventBus.hpp
 *
 *  Created on: Feb 15, 2016
 *      Author: Venevitin Nikita (venevitinnikita@gmail.com)
 */

#ifndef SEGE_EVENT_BUS_HPP
#define SEGE_EVENT_BUS_HPP

#include "../../numbers.hpp"

#include <unordered_map>
#include <vector>

#include <typeinfo>
#include <typeindex>

#include <functional>
#include <memory>

namespace Sege
{
    template<typename T>
    using HandlerArgType = std::shared_ptr<T>;

    template<typename T>
    using HandlerType = std::function<void(HandlerArgType<T>)>;

    using HandlersVectorType = std::vector<HandlerType<void>>;

    class EventBus
    {
        std::unordered_map<std::type_index,
                std::shared_ptr<HandlersVectorType>>
                handlers;

    public:
        template<typename EventType>
        void addHandler(
                const HandlerType<EventType> &handler);

        // TODO addHandler for rvalue

        template<typename EventType>
        void fireEvent(std::shared_ptr<EventType> pEvent);

        template<typename EventType>
        void fireEvent();
    };

    template<typename EventType>
    void EventBus::addHandler(
            const HandlerType<EventType> &handler)
    {
        auto type = static_cast<std::type_index>(typeid(EventType));
        // важно, чтобы handler захватывался именно по значению
        auto handlerFunction = [=](std::shared_ptr<void> pEvent)
        {
            handler(std::static_pointer_cast<EventType>(pEvent));
        };
        if (handlers.count(type) == 1)
        {
            handlers[type]->push_back(handlerFunction);
        }
        else
        {
            auto pNewVector = std::make_shared<HandlersVectorType>(
                    std::initializer_list<HandlerType<void>>{handlerFunction});
            handlers.insert({type, pNewVector});
        }
    }

    template<typename EventType>
    void EventBus::fireEvent(std::shared_ptr<EventType> pEvent)
    {
        auto type = static_cast<std::type_index>(typeid(EventType));
        auto handlersList = handlers[type];
        if (handlersList != nullptr)
        {
            for (const auto &handler : *handlersList)
            {
                handler(std::static_pointer_cast<void>(pEvent));
            }
        }
    }

    template<typename EventType>
    void EventBus::fireEvent()
    {
        fireEvent<EventType>(nullptr);
    }
}

#endif /* MODULE_HPP_ */
