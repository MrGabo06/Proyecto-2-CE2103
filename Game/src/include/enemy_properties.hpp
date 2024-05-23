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

const Property<int> MAX_HEALTH = { 5, 1, 3, 2, 10};
const Property<int> MAX_DAMAGE = {10, 0, 1, 1, 3};
const Property<int> MAX_RANGE = {7, 0, 6, 3, 8};
const Property<int> MAX_DISTANCE = { 10, 2, 2, 2, 2};
const Property<int> MAX_ROUTE_SIZE = {9, 0, 3, 5, 5};
const Property<float> MAX_SPEED = { 0.5, 0.0, 0.9, 0.4, 0.6};

#endif