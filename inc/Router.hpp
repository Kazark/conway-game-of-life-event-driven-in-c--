#ifndef _EVENTARCHITECTURE_ROUTER_HPP_
#define _EVENTARCHITECTURE_ROUTER_HPP_

// Event Architecture
#include "IHandle.hpp"
#include "Event.hpp"

// C++ Standard libraries
#include <unordered_map>
#include <typeindex>

namespace EventArchitecture {
	class Router {
	public:
        ~Router() {
            for (auto pair : registry) {
                delete pair.second;
            }
        }

        template<typename TEvent>
        void registerHandler(IHandle<TEvent>& handler)
        {
            registry[typeid(TEvent)] = new Unpackager<TEvent>(handler);
        }

        void invokeHandler(Event* event) const
        {
            auto unpackager = registry.at(std::type_index(typeid(*event)));
            unpackager->invokeHandler(event);
        }

	private:
        class IUnpackage {
        public:
            virtual void invokeHandler(Event*) const = 0;
        };

        friend class std::unordered_map<std::type_index, IUnpackage*>;
        std::unordered_map<std::type_index, IUnpackage*> registry;

        template<typename TEvent>
        class Unpackager: public IUnpackage {
        public:
            Unpackager(IHandle<TEvent>& handler) :
                _handler(handler)
            {}

            void invokeHandler(Event* event) const {
                auto unpackagedEvent = static_cast<TEvent*>(event);
                _handler.handle(*unpackagedEvent);
            }
        private:
            IHandle<TEvent>& _handler;
        };
	};
}
#endif