#include "Controller.h"
#include "defines.h"

#include <stdio.h>



Controller::Controller(double length, double height, double x, double y)
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

void Controller::setPosition(double x, double y)
{
	centerPositionX = x;
	centerPositionY = y;
}

double Controller::getPositionX()
{
	return centerPositionX;
}

double Controller::getPositionY()
{
	return centerPositionY;
}

double Controller::getVelX()
{
	return linear_velocity_x;
}

double Controller::getVelY()
{
	return linear_velocity_y;
}

void Controller::setVelocity(double x_vel, double y_vel)
{
	linear_velocity_x = x_vel;
	linear_velocity_y = y_vel;
}


void Controller::move(int direction)
{
	double centerPositionX_old = centerPositionX;

	switch(direction)
	{
	    case 1: 
	    {
	    	centerPositionX -= 1.0;  // Left
	    }
	    break;
	    case 2:
	    {
	    	centerPositionX += 1.0;  // Right
	    }
	    break;
	}

	linear_velocity_x = (centerPositionX_old - centerPositionX) / delta_t;

}

