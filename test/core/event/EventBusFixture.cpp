//
// Created by nikita on 22.06.16.
//

#include <gtest/gtest.h>
#include "../../../src/core/event/EventBus.hpp"

using namespace Sege;

class SomeEvent
{
};

class EventWithValue
{
    int a;
public:
    int getA() const;

    void setA(int _a);
};

class SomeHandler
{
public:
    void operator()(HandlerArgType<SomeEvent> pEvent);
};

void handlerFunction(HandlerArgType<SomeEvent> pEvent);

class EventBusFixture : public ::testing::Test
{
protected:
    std::shared_ptr<EventBus> eventBus;

    virtual void SetUp()
    {
        eventBus = std::make_shared<EventBus>();

        SomeHandler handlerObject;

        eventBus->addHandler<SomeEvent>(handlerFunction);
        eventBus->addHandler<SomeEvent>(handlerObject);
    }
};


TEST_F(EventBusFixture, EventBusFixture_UsageExample_Test)
{
    eventBus->fireEvent<SomeEvent>();
}


TEST_F(EventBusFixture, EventBusFixture_Lambda_Test)
{
    int a;
    auto handlerLambda = [&a](HandlerArgType<EventWithValue> pEvent)
    {
        a = pEvent->getA();
    };
    eventBus->addHandler<EventWithValue>(handlerLambda);

    auto someEvent = std::make_shared<EventWithValue>();
    someEvent->setA(5);
    eventBus->fireEvent(someEvent);

    ASSERT_EQ(5, a);
}

int EventWithValue::getA() const
{
    return a;
}

void EventWithValue::setA(int _a)
{
    a = _a;
}

void SomeHandler::operator()(HandlerArgType<SomeEvent> pEvent)
{
    std::cout << "Handler object invokation\n";
}

void handlerFunction(HandlerArgType<SomeEvent> pEvent)
{
    std::cout << "\nHandler function invokation\n";
}