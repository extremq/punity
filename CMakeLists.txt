cmake_minimum_required(VERSION 3.22.1)
include(pico_sdk_import.cmake)
project(Punity-game-engine C CXX ASM)

set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PROJ_NAME shobi)
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(PICO_CXX_ENABLE_RTTI 1)

pico_sdk_init()
add_executable(${PROJ_NAME}
        main.cpp
        punity/Screen/PScreen.cpp
        punity/Screen/PScreen.h
        punity/Punity.h
        punity/Engine/PEngine.cpp
        punity/Engine/PEngine.h
        punity/Utils/PVector.h
        punity/Screen/ST7735_defines.h
        punity/Components/PSpriteRenderer.cpp
        punity/Components/PSpriteRenderer.h
        punity/Entity/PEntity.cpp
        punity/Entity/PEntity.h
        punity/Components/PComponent.cpp
        punity/Components/PComponent.h
        punity/Components/PComponent.fwd.h
        punity/Entity/PEntity.fwd.h
        punity/Engine/PEngine.fwd.h
        punity/Components/PTransform.cpp
        punity/Components/PTransform.h
        punity/Utils/PTime.h
        punity/Input/PJoystick.h
        punity/Components/PMovement.h
        punity/Components/PSpriteRenderer.fwd.h punity/Utils/PError.h)

pico_enable_stdio_usb(${PROJ_NAME} 1)
pico_enable_stdio_uart(${PROJ_NAME} 0)
pico_add_extra_outputs(${PROJ_NAME})

target_include_directories(${PROJ_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(${PROJ_NAME}
        hardware_spi
        hardware_adc
        pico_stdlib
        )

# Remove this when you compile
add_custom_command(TARGET
        ${PROJ_NAME} POST_BUILD
        COMMAND
        sudo -S /bin/sh ${PROJECT_SOURCE_DIR}/deploy.sh ${PROJECT_SOURCE_DIR}/build/${PROJ_NAME}.uf2)