#include "ControllerDisk.h"
#include "defines.h"

#include <stdio.h>



ControllerDisk::ControllerDisk(float radius, float x, float y)
{
	radius_ = radius;
	linear_velocity_y = 0.;
	linear_velocity_x = 0.;
	centerPositionX = x;
	centerPositionY = y;

}

void ControllerDisk::updatePosition()
{

	// check for wall collision
	if(centerPositionX+radius_ > WINSIZEX)
	{
		centerPositionX = WINSIZEX - radius_;
	}

	if(centerPositionX-radius_ < 0)
	{
		centerPositionX = radius_;
	}

}

void ControllerDisk::setPosition(float x, float y)
{
	centerPositionX = x;
	centerPositionY = y;
}

float ControllerDisk::getPositionX()
{
	return centerPositionX;
}

float ControllerDisk::getPositionY()
{
	return centerPositionY;
}

float ControllerDisk::getVelX()
{
	return linear_velocity_x;
}

float ControllerDisk::getVelY()
{
	return linear_velocity_y;
}

void ControllerDisk::setVelocity(float x_vel, float y_vel)
{
	linear_velocity_x = x_vel;
	linear_velocity_y = y_vel;
}


void ControllerDisk::move(int direction)
{
	float centerPositionX_old = centerPositionX;

	switch(direction)
	{
	    case 1: 
	    {
	    	centerPositionX -= 0.5;  // Left
	    }
	    break;
	    case 2:
	    {
	    	centerPositionX += 0.5;  // Right
	    }
	    break;
	}

	linear_velocity_x = (centerPositionX_old - centerPositionX) / delta_t;

}

