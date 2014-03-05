#include "Channel.hpp"
using namespace ::EventArchitecture;

Channel::Channel(IHandle<Event*>& handler) :
    _handler(handler)
{}

Channel::~Channel() {
    while (hasMore()) {
        delete _eventQueue.front();
        _eventQueue.pop();
    };
}

void Channel::handle(Event* event) {
    _eventQueue.push(event);
}

void Channel::deliverOne() {
    delete _eventQueue.front();
    _eventQueue.pop();
}

bool Channel::hasMore() const {
    return !_eventQueue.empty();
}
