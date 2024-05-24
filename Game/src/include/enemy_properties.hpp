#ifndef PROPERTIES_H
#define PROPERTIES_H

/// @brief Struct that allows storing a property quality for multiple types
template <typename T>
struct Property {
    T specter;
    T eye;
    T chocobo;
    T rat;
    T super;
};

// [ DECLARATION OF MAX ATTRIBUTE CONFIGURATION FOR ENTITIES ]

const Property<int> MAX_HEALTH = { 20, 1, 3, 2, 15};
const Property<int> MAX_DAMAGE = {10, 0, 1, 1, 3};
const Property<int> MAX_RANGE = {7, 15, 10, 5, 8};
const Property<int> MAX_DISTANCE = { 15, 0, 6, 5, 5};
const Property<int> MAX_ROUTE_SIZE = {9, 0, 4, 5, 5};
const Property<float> MAX_SPEED = { 2.4, 0.0, 2.8, 0.9, 1.0};

#endif