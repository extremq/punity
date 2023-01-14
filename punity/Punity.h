//
// Created by god on 12.11.2022.
//

#ifndef _PUNITY_H
#define _PUNITY_H

#include <cstdlib>
#include "pico/stdlib.h"

#include "punity/Utils/PTime.h"
#include "punity/Utils/PError.h"
#include "punity/Utils/PVector.h"
#include "punity/Utils/PRandom.h"
#include "punity/Input/PJoystick.h"
#include "punity/Input/PButton.h"
#include "punity/Engine/PEngine.h"
#include "punity/Screen/PScreen.h"
#include "punity/Sound/PSound.h"

// Start of Punity!
namespace Punity {
    // The statics
    static PScreen& Screen = PScreen::get();
    static PEngine& Engine = PEngine::get();
    static Utils::PTime& Time = Utils::PTime::get();
    static Sound::PSound& Buzzer = Sound::PSound::get();
    static Input::PJoystick& Joystick = Input::PJoystick::get();
    static Input::PButton& Button = Input::PButton::get();
}

#endif //_PUNITY_H
