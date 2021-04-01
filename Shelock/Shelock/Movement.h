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

    void Set_Forward(char _forward) { forward_key = tolower(_forward); }
    void Set_Backward(char _backward) { backward_key = tolower(_backward); }
    void Set_CCW(char _ccw_rotation) { ccw_rotation_key = tolower(_ccw_rotation); }
    void Set_CW(char _cw_rotation) { cw_rotation_key = tolower(_cw_rotation); }

private:
    
    float forward_speed; 
    float angular_speed; 

    char forward_key; 
    char backward_key; 

    char ccw_rotation_key; 
    char cw_rotation_key;

    std::unordered_map<char, int> input_table; 

};

