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
        Utils::PVector m_local_position;
        // The global position will be relative to the root. The root is standing at 0, 0.
        Utils::PVector m_global_position;
    public:
        Utils::PVector const& local_position = m_local_position;
        Utils::PVector const& global_position = m_global_position;

        // That's all for members
    };
}


#endif //_PTRANSFORM_H
