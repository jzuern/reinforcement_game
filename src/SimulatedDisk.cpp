#include "SimulatedDisk.h"
#include "defines.h"

#include <stdio.h>



SimulatedDisk::SimulatedDisk(float radius, float x, float y, float x_vel)
{
	radius_ = radius;
	linear_velocity_y = x_vel;
	linear_velocity_x = x_vel;
	centerPositionX = x;
	centerPositionY = y;

}

bool SimulatedDisk::updatePosition()
{
	bool out_of_bounds = false;

	float delta_velocity_y = gravity * delta_t;
	linear_velocity_y += delta_velocity_y;

	float delta_velocity_x = 0.0;
	linear_velocity_x += delta_velocity_x;

	float delta_pos_y = linear_velocity_y * delta_t;
	float delta_pos_x = linear_velocity_x * delta_t;

	float bounce = 1.0;

	centerPositionY += delta_pos_y;
	centerPositionX += delta_pos_x;

	if(centerPositionY+radius_ > WINSIZEY) // disk is out of bounds
	{
		// centerPositionY = WINSIZEY - radius_;
		// linear_velocity_y = -bounce*linear_velocity_y;

		// if this happens, remove disk from game
		out_of_bounds = true;

//		centerPositionX = -100.;
//		centerPositionY = -100.;
//		linear_velocity_y = 0.;
//		linear_velocity_y = 0.;
	}

	if(centerPositionY-radius_ < 0)
	{
		centerPositionY = radius_;
		linear_velocity_y = -bounce*linear_velocity_y;
	}

	if(centerPositionX+radius_ > WINSIZEX)
	{
		centerPositionX = WINSIZEX - radius_;
		linear_velocity_x = -bounce*linear_velocity_x;
	}

	if(centerPositionX-radius_ < 0)
	{
		centerPositionX = radius_;
		linear_velocity_x = -bounce*linear_velocity_x;
	}


	return out_of_bounds;
}

void SimulatedDisk::setPosition(float x, float y)
{
	centerPositionX = x;
	centerPositionY = y;
}

void SimulatedDisk::setVelocity(float x_vel, float y_vel)
{
	linear_velocity_x = x_vel;
	linear_velocity_y = y_vel;
}

float SimulatedDisk::getPositionX()
{
	return centerPositionX;
}

float SimulatedDisk::getPositionY()
{
	return centerPositionY;
}

float SimulatedDisk::getVelX()
{
	return linear_velocity_x;
}

float SimulatedDisk::getVelY()
{
	return linear_velocity_y;
}