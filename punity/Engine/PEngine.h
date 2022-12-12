//
// Created by god on 12.11.2022.
//

#ifndef _ENGINE_H
#define _ENGINE_H

#include "punity/Entity/PEntity.fwd.h"
#include "punity/Utils/PInvokable.fwd.h"
#include "punity/Components/PSpriteRenderer.h"
#include "punity/Components/PUISpriteRenderer.h"

#include <cstdint>
#include <list>
#include <set>

namespace Punity {
    // Comparator for sprites
    struct cmp_sprites {
        bool operator() (Components::PSpriteRenderer const* a, Components::PSpriteRenderer const* b) const {
            return a->layer < b->layer;
        }
    };

    struct cmp_ui_sprites {
        bool operator() (Components::PUISpriteRenderer const* a, Components::PUISpriteRenderer const* b) const {
            return a->layer < b->layer;
        }
    };

    class PEngine {
    private:
        PEngine();

        // In microseconds (1e^-6 sec)
        uint64_t m_frame_delay_us = 16666; // Assume 60 fps
        std::list<PEntity*> m_all_entities;
        std::list<Utils::PInvokableBase*> m_invokers;
        std::set<PEntity*> m_to_be_destroyed;

        void update_time(uint64_t);
    public:
        // Prohibit copying.
        PEngine(const PEngine &) = delete;

        PEngine &operator=(const PEngine &) = delete;

        static PEngine &get() {
            // https://stackoverflow.com/questions/13047526/difference-between-singleton-implemention-using-pointer-and-using-static-object
            // Good read about singletons
            static PEngine m_instance;
            return m_instance;
        };

        std::list<PEntity*> const& entity_list = m_all_entities;
        void register_entity(PEntity*);
        void register_invoker(Utils::PInvokableBase*);
        void queue_destruction(PEntity*);

        // Sets... the framerate.
        void set_framerate(float);
        void start_game();

        void print_tree_of_entities();

        PEntity* find_entity(std::string name);

        // Root Entity, head of the Entity Tree
        PEntity* root_entity = nullptr;
    };
}

#endif //_ENGINE_H
