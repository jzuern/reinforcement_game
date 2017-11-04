#include "SimulatedDisk.h"
#include "defines.h"

#include <stdio.h>



SimulatedDisk::SimulatedDisk(float mass, float radius, float x, float y)
{
	mass_ = mass;
	radius_ = radius;
	linear_velocity_y = 0.;
	linear_velocity_x = 50.;
	centerPositionX = x;
	centerPositionY = y;

}

void SimulatedDisk::updatePosition()
{
	float delta_velocity_y = gravity * delta_t;
	linear_velocity_y += delta_velocity_y;

	float delta_velocity_x = 0.0;
	linear_velocity_x += delta_velocity_x;


	float delta_pos_y = linear_velocity_y * delta_t;
	float delta_pos_x = linear_velocity_x * delta_t;

	centerPositionY += delta_pos_y;
	centerPositionX += delta_pos_x;

	if(centerPositionY+radius_ > WINSIZEY)
	{
		centerPositionY = WINSIZEY - radius_;
		linear_velocity_y = -0.9*linear_velocity_y;
	}

	if(centerPositionY-radius_ < 0)
	{
		centerPositionY = radius_;
		linear_velocity_y = -0.9*linear_velocity_y;
	}

	if(centerPositionX+radius_ > WINSIZEX)
	{
		centerPositionX = WINSIZEX - radius_;
		linear_velocity_x = -0.9*linear_velocity_x;
	}

	if(centerPositionX-radius_ < 0)
	{
		centerPositionX = radius_;
		linear_velocity_x = -0.9*linear_velocity_x;
	}

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