//
// Created by god on 17.12.2022.
//
#include "PButton.h"

#include "punity/Punity.h"

bool Punity::Input::PButton::read_button(uint8_t pin) {
    if (!m_configured[pin]) Utils::Error("Cannot read button that wasn't configurated.");

    return !gpio_get(pin);
}