#pragma once

#include "Component.h"

#include "../Dependencies/GLM/vec3.hpp"

#include <unordered_map>
#include <string>



class Movement :
    public Component
{
public:
    Movement(class Actor* _owner);

    void Update(float delta_time) override; 
    
    float forward_speed; 
    float angular_speed; 

    char forward_key; 
    char backward_key; 

    char ccw_rotation_key; 
    char cw_rotation_key;

    std::unordered_map<char, int> input_table; 

};

