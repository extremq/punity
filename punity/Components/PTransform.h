//
// Created by god on 14.11.2022.
//

#ifndef _PTRANSFORM_H
#define _PTRANSFORM_H

#include "PComponent.h"
#include "../Utils/PVector.h"

namespace Punity::Components {
    // Transform component that pretty much describes location in space
    class PTransform : public PComponent {
    private:
        // The local position will be relative to the parent object
        // Basically an offset
        Utils::PVector m_local_position;
        // The global position will be relative to the root. The root is standing at 0, 0.
        Utils::PVector m_global_position;

        void update_position_of_children();
    public:
        Utils::PVector const& local_position = m_local_position;
        Utils::PVector const& global_position = m_global_position;

        void set_local(Utils::PVector const&);
        void set_global(Utils::PVector const&);

        // That's all for members
    };
}


#endif //_PTRANSFORM_H
