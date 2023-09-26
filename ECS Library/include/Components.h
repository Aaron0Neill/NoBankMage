#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <stdint.h>

using Component = uint32_t; // We'll use one-hot encoding to represent the component ID
constexpr uint8_t MAX_COMPONENTS = sizeof(Component);

struct PhysicsBody
{
	// vec2 velocity
	// vec2 acceleration
};

struct Transform
{
	// vec2 position
	// vec2 rotation
	// vec2 scale
};

#endif