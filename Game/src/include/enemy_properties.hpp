#ifndef PROPERTIES_H
#define PROPERTIES_H

/// @brief Struct that allows storing a property quality for multiple types
template <typename T>
struct Property{
    T specter;
    T eye;
    T chocobo;
    T rat;
    T super;
};

// [ DECLARATION OF MAX ATTRIBUTE CONFIGURATION FOR ENTITIES ]

const Property<int> MAX_DETECTION = { 5, 5, 5, 5, 5};
const Property<int> MAX_ROUTE = {1, 2, 3, 4, 5};
const Property<int> MAX_MOVEMENT = { 3, 3, 3, 3, 3};
const Property<float> MAX_SPEED = { 0.3f, 0.3f, 0.3f, 0.3f, 0.3f};
const Property<int> MAX_DECISIONS = { 2, 2, 2, 2, 2};
const Property<int> MAX_ATTACK = {2, 2, 2 ,2, 2};

#endif