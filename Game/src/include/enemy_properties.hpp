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

const Property<int> MAX_DETECTION = { 100, 80, 130, 40, 70};
const Property<int> MAX_ROUTE = {9, 0, 4, 4, 0};
const Property<int> MAX_MOVEMENT = { 20, 0, 6, 4, 4};
const Property<float> MAX_SPEED = { 0.3, 0.3, 0.3, 0.3, 0.3};
const Property<int> MAX_DECISIONS = { 2, 2, 2, 2, 2};
const Property<int> MAX_ATTACK = {2, 2, 2 ,2, 2};

#endif