#pragma once
class Actor
{
public:
	
	Actor(); 

	virtual void Update(float delta_time) = 0; 
	virtual void Process_Input() = 0; 

	virtual ~Actor() {};
};

