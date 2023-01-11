

# Punity
![](https://i.imgur.com/e5t4SCO.png)
![](https://i.imgur.com/vKiKM2b.png)

Punity (*noun: punishment, punitiveness*) is 
a 2D game engine targeted to the Raspberry Pi Pico microcontroller, designed with Unity as an inspiration.

In this implementation, the Screen is using a ST7735 controller. You will also find logic for interfacing analog joysticks and buttons.

### Extra info
**I had no access to a debugger, the ram of the Pico is limited to
264KB, and it has a 100MHz CPU.**

This project has been made for a university task.

Check out [my previous attempt](https://github.com/extremq/pico_game/) at creating such a game engine. I've learnt from that and moved on to creating Punity just a few days later.

# Documentation
Please note this isn't an exhaustive documentation. A lot has been omitted. Check the implementations,
they are always commented and easy to understand if you want more details. Also check out
the game for example usage.
### 1. The structure
The Punity system is similar in nature to Unity. If you've never heard of Unity before, it's a hierarchical game engine that is widely used today.

A hierarchical game engine employs entities and components that reside in memory the same way files and folders do:
![](https://i.imgur.com/PNicDNp.png)
Left, you have folders and subfolders with files. Right, you have my entity structure that resembles folders and subfolders.

This way of handlind entities makes it so when disabling or destroying an entity, you also destroy all their children entities. Think of how deleting a folder deletes every subfolder.

You can easily disable and enable the player_normal without needing to disable their sword, their arms, hats, etc. since eveything is a child of the player_normal.

Each entity also has a component. Components simply extend an entity's behaviour. You could make a Sprite component which attaches a sprite to the entity, so it can be rendered on the screen, or you could add a BoxCollider component, so you make it have a rectangular hitbox.

Each entity will have a Transform component, which describes the position of the entity in the world.

### 2. The Engine
Now that we have a structure, I need to talk about how the engine works. Basically, logic happens at component level - that means something acts, something has a behaviour because of components. Entities themselves are empty shells with no behaviour.

The way you add functionality to components is by creating overriding their abstract functions. These are:

|               Function               | When it's called                           |
|:------------------------------------:|:-------------------------------------------|
|           void on_enable()           | Each time the component is enabled.        |
|          void on_disable()           | Each time the component is disabled.       |
|          void on_destroy()           | When the component is destroyed.           |
|           void on_start()            | When the engine starts.                    |
|           void on_update()           | Each frame.                                |
| void on_start_collision(PCollider\*) | When you first touch another collidable.   |
|    void on_collision(PCollider\*)    | Each frame you touch another collidable.   |
|  void on_end_collision(PCollider\*)  | When you stop touching another collidable. |

Now, all you have to do to make an entity print something is simple:
1. Make a class `MyComponent` that inherits `PComponent` publicly.
2. Create an entity using `auto my_entity = Punity::Pentity.make_entity(name, is_active)`.
3. Add the component using `my_entity.add_component<MyComponent>()`.
4. That's it!

```cpp
class MyComponent : public Punity::Components::PComponent {
    void on_update() override {
        std::cout << "Hello!\n"; // Prints 'Hello!' every frame.
    }
};

// Somewhere else in your code
auto my_entity = Punity::Pentity.make_entity("My_entity", true);
my_entity.add_component<MyComponent>();
```

The engine is memory managed automatically. Other than that, anything else you allocate
resources for you are responsible for handling. Don't use `delete` on entities
or components.

Going into the details, this is a bit more complicated. 
Since my engine supports disabling, deleting, and whatnot, there are many edge cases
that need to be treated.

My engine has a list of entities that it goes through each frame.

First of all, which entity is called first? Is it the children or the parent?
What happens if I destroy the parent of a child and then call something within the child?

To resolve this, I've implemented a clear **Order of Execution**.
It goes like this:
1. First, check which entities are disabled/destroyed and remove them from the active entities list
2. Then, safely delete the destroyed entities
3. New frame starts here
4. Load the background
5. Loop through all entities and update them while also collecting colliders and sprites
6. Solve Invokers
7. Compute collisions
8. Draw sprites
9. Send the frame
10. Sleep the remaining time and repeat

This means that deletion isn't instant. It takes effect the next frame. It's best to
check the source code if you want to dig even deeper. `punity/Engine/PEngine.cpp`

### 3. Punity Utils
#### 3.1. Invokable
Let's say you want to show enable an entity after a delay.
You could use ifs and whatever, but I made something just for you!

Invokables are a way of calling a function after a specified time in seconds.

The syntax is as follows:
```cpp
new Punity::Utils::PInvokable<Component>(
        &Component::function,
        this,
        delay,
        get_entity()->get_id()
        );
```

Note that the function must be of type `void(void)`.

I also support function with an int parameter using PInvokableWithInt.

### 3.2. Time
You can get the elapsed time in second since boot easily using the `Punity::Time.time` util.

If you'd like to make physics computation independent of frame rate, you can also use
`Punity::Time.delta_time`, which gives you the difference in time between the frames.

Here is a snippet that implements player_normal movement using a joystick.

```cpp
// Construct vector of direction
auto joystick_direction = Punity::Utils::PVector();
joystick_direction.x = Punity::Joystick.get_x_direction();
joystick_direction.y = Punity::Joystick.get_y_direction();

// Normalize the vector
joystick_direction = joystick_direction.norm();

// Save the last direction
last_joystick_direction = joystick_direction;

// Translate the player_normal
get_entity()->get_transform()->translate(joystick_direction * Punity::Time.delta_time * 30);
```

### 3.3. Vector
`Punity::Utils::PVector` is a 2D vector with built-in support for popular operations.
Here is a snippet from the collision computation util which uses `PVector`.
```cpp
// Mathematics
nearest_point.x = std::max(rect_pos.x - rect->width / 2, std::min(circle_pos.x, rect_pos.x + rect->width / 2));
nearest_point.y = std::max(rect_pos.y - rect->height / 2, std::min(circle_pos.y, rect_pos.y + rect->height / 2));

// Ray to the nearest point
Utils::PVector ray_to_nearest_point = nearest_point - circle_pos;

const float mag = ray_to_nearest_point.mag();
const float overlap = circle->radius - mag;

if (overlap < -1e-5) return false;

// If is a trigger return before modifying position of circle
if (rect->is_trigger || circle->is_trigger) return true;

// Resolution
circle_pos.x -= ray_to_nearest_point.x / mag * overlap;
circle_pos.y -= ray_to_nearest_point.y / mag * overlap;
```

### 3.4. Random
**Disclaimer**, this random number generator isn't a top-notch one, but it's good enough.
It uses the ring oscillator provided with the Raspberry Pi Pico.

`Punity::Utils::random(a, b)` or just no parameters generates a number between [a, b] or [0, 1].

Here's an example snippet:
```cpp
// Set a random offset.
pause_time = Punity::Utils::random(1.0f, 1.5f);
shooting_start = Punity::Time.time + Punity::Utils::random() + pause_time;
```

### 3.5. Math
Useful math functions such as distance and lerp. They take Vectors as input, same as 
any other implementation on earth.

### 3.6. Collision Computation
Shouldn't be called but need to be implemented if you want to extend shape interactions.

### 4. Input
Configuring a button or a joystick is as simple as doing:
```cpp
Punity::Joystick.config(JOY_X, JOY_Y); // ADC Pins
Punity::Button.config(JOY_BTN); // GPIO Pins
Punity::Button.config(ACTION_BTN);
```
To read values, simply do:
```cpp
Punity::Joystick.get_x_direction();
Punity::Button.read_button(JOY_BTN);
```

### 5. Screen
The screen is managed in such a way that it only transmits the changes in frame.
I do this because updating the whole frame each time takes a really long time on this screen.

The screen automatically draws sprites from entities that have `PSpriteRenderer` or `PUISpriteRenderer`
and layers them according to the assigned layer.

You can also use a 8x8 sprite to tile the background with.

### 6. Components
There are Sprite Components, Collider components and Transform.
A good snippet showing usage of them all plus other components:
```cpp
Punity::PEntity* make_enemy(Punity::PEntity* parent, uint8_t type) {
    auto enemy_entity = Punity::PEntity::make_entity(Game::Names::ENEMY, parent, true);

    // Choose sprite
    enemy_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
            SPRITE(Game::Sprites::first_enemy_type, Game::Sprites::Layers::PLAYER)
    );

    // Set the collider
    enemy_entity->add_component<Punity::Components::PCircleCollider>()
            ->set_radius(Game::Sprites::first_enemy_type_h / 2)
            ->set_information(Game::Colliders::ENEMY);

    // Set enemy behaviour
    enemy_entity->add_component<EnemyBehaviour>();
    
    // Entity for selector that appears above enemy when player_normal aims at
    auto selector_entity = Punity::PEntity::make_entity(Game::Names::SELECTOR, enemy_entity, false);

    selector_entity->get_transform()->set_local({0, -8}); // place the selector in offset regarding enemy
    selector_entity->add_component<Punity::Components::PSpriteRenderer>()->set_sprite(
            SPRITE(Game::Sprites::enemy_selected_arrow, Game::Sprites::Layers::SELECTOR)
    );

    return enemy_entity;
}
```
