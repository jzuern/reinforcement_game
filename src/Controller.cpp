#include "Controller.h"
#include "defines.h"

#include <stdio.h>



Controller::Controller(float length, float height, float x, float y)
{
	length_ = length;
	height_ = height;

	linear_velocity_y = 0.;
	linear_velocity_x = 0.;

	centerPositionX = x;
	centerPositionY = y;

}

void Controller::updatePosition()
{

	// check for wall collision
	if(centerPositionX+length_/2 > WINSIZEX)
	{
		centerPositionX = WINSIZEX - length_/2;
	}

	if(centerPositionX-length_/2 < 0)
	{
		centerPositionX = length_/2;
	}

}

void Controller::setPosition(float x, float y)
{
	centerPositionX = x;
	centerPositionY = y;
}

float Controller::getPositionX()
{
	return centerPositionX;
}

float Controller::getPositionY()
{
	return centerPositionY;
}

float Controller::getVelX()
{
	return linear_velocity_x;
}

float Controller::getVelY()
{
	return linear_velocity_y;
}

void Controller::setVelocity(float x_vel, float y_vel)
{
	linear_velocity_x = x_vel;
	linear_velocity_y = y_vel;
}


void Controller::move(int direction)
{
	float centerPositionX_old = centerPositionX;

	switch(direction)
	{
	    case 1: 
	    {
	    	centerPositionX -= 0.1;  // Left
	    }
	    break;
	    case 2:
	    {
	    	centerPositionX += 0.1;  // Right
	    }
	    break;
	}

	linear_velocity_x = (centerPositionX_old - centerPositionX) / delta_t;

}

