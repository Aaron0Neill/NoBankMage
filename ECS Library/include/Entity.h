#ifndef ENTITY_H
#define ENTITY_H

#include <limits>
#include <stdint.h>

// Entity ID
using Entity = uint16_t;
const uint16_t MAX_ENTITIES = std::numeric_limits<uint16_t>::max(); // 65,536

#endif