//
// Created by god on 05.12.2022.
//

#ifndef _PINVOKABLE_H
#define _PINVOKABLE_H
#include "punity/Punity.h"

namespace Punity::Utils {
    class PInvokableBase {
    protected:
        float m_execution_time = 0.0f;
        uint64_t m_entity_id = 0;
    public:
        virtual void execute_function() {
            // Commmon method for Engine to call
        }

        float get_execution_time() {
            return m_execution_time;
        }

        uint64_t get_entity_id() {
            return m_entity_id;
        }
    };

    template <class T>
    class PInvokable : protected PInvokableBase {
    private:
        void (T::* m_function)() = nullptr;
        T* m_pointer_to_class = nullptr;
        PInvokable() = default;
    public:
        PInvokable(const PInvokable&) = delete;

        PInvokable(void (T::* function)(), T* pointer_to_entity, float delay_seconds, uint64_t entity_id) {
            m_execution_time = delay_seconds + Punity::Time.time;
            m_pointer_to_class = pointer_to_entity;
            m_function = function;
            m_entity_id = entity_id;
            Punity::Engine.register_invoker(this);
        }

        void execute_function() override {
            // Call the function when event lifetime expires
            (*(m_pointer_to_class).*m_function)();
        }
    };
}

#endif //_PINVOKABLE_H
