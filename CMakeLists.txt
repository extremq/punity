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
        punity/Components/PSpriteRenderer.h
        punity/Components/PComponent.cpp
        punity/Components/PComponent.h
        punity/Components/PComponent.fwd.h
        punity/Entity/PEntity.fwd.h
        punity/Engine/PEngine.fwd.h
        punity/Components/PTransform.cpp
        punity/Components/PTransform.h
        punity/Entity/PEntity.cpp
        punity/Entity/PEntity.h
        punity/Utils/PTime.h
        punity/Input/PJoystick.h
        punity/Components/PSpriteRenderer.fwd.h
        punity/Utils/PError.h
        punity/Utils/PRandom.h
        punity/Components/PCollider.cpp
        punity/Components/PCollider.h
        punity/Utils/PCollisionComputation.h
        punity/Components/PCircleCollider.cpp
        punity/Components/PCircleCollider.h
        punity/Components/PBoxCollider.cpp
        punity/Components/PBoxCollider.h
        game/Assets/sprites.cpp
        game/Assets/sprites.h
        punity/Components/PUISpriteRenderer.h
        punity/Components/PBasicSprite.cpp
        punity/Components/PBasicSprite.h
        punity/Utils/PInvokable.h
        punity/Utils/PInvokable.fwd.h
        game/Logic/SceneManager.cpp
        game/Logic/SceneManager.h
        game/Logic/SceneCreator.h
        game/Logic/UI/FloatingUI.h
        punity/Input/PButton.h
        game/Logic/Gameplay/GameplaySceneBehaviour.cpp
        game/Logic/Gameplay/GameplaySceneBehaviour.h
        game/Logic/Gameplay/LoadSceneBehaviour.h
        game/Logic/Gameplay/StartSceneBehaviour.h
        punity/Utils/PError.cpp
        punity/Utils/PRandom.cpp
        punity/Utils/PCollisionComputation.cpp
        game/Logic/SceneCreator.cpp
        game/Logic/Gameplay/GameplayPrefabCreator.cpp
        game/Logic/Gameplay/GameplayPrefabCreator.h
        game/Logic/Gameplay/PlayerBehaviour.cpp
        game/Logic/Gameplay/PlayerBehaviour.h
        game/Logic/Gameplay/RoomBehaviour.cpp
        game/Logic/Gameplay/RoomBehaviour.h
        game/Assets/sprite_layers.h
        game/Logic/Gameplay/ActorBehaviour.cpp
        game/Logic/Gameplay/ActorBehaviour.h
        game/Logic/Gameplay/Projectile.cpp
        game/Logic/Gameplay/Projectile.h
        game/Logic/Gameplay/EnemyBehaviour.cpp
        game/Logic/Gameplay/EnemyBehaviour.h
        game/Logic/Gameplay/Weapon.cpp
        game/Logic/Gameplay/Weapon.h
        game/Logic/Gameplay/GameplaySceneManager.cpp
        game/Logic/Gameplay/GameplaySceneManager.h
        game/Assets/weapons.h
        game/Assets/weapons.cpp game/Assets/colliders.h game/Logic/Gameplay/AttractablePickup.cpp game/Logic/Gameplay/AttractablePickup.h game/Logic/Gameplay/ChestBehaviour.cpp game/Logic/Gameplay/ChestBehaviour.h game/Logic/Gameplay/WeaponPickup.cpp game/Logic/Gameplay/WeaponPickup.h game/Assets/groupings.h game/Assets/groupings.cpp punity/Input/PButton.cpp game/Assets/strings.h game/Assets/maps.h game/Assets/maps.cpp game/Logic/Gameplay/CrateBehaviour.cpp game/Logic/Gameplay/CrateBehaviour.h game/Logic/Gameplay/MovingBehaviour.cpp game/Logic/Gameplay/MovingBehaviour.h punity/Utils/PMath.cpp punity/Utils/PMath.h)

pico_enable_stdio_usb(${PROJ_NAME} 1)
pico_enable_stdio_uart(${PROJ_NAME} 0)
pico_add_extra_outputs(${PROJ_NAME})

target_include_directories(${PROJ_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(${PROJ_NAME}
        hardware_spi
        hardware_adc
        pico_stdlib
        )