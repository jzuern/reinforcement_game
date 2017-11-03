#include "SimulatedDisk.h"
#include "defines.h"

#include <stdio.h>



SimulatedDisk::SimulatedDisk(float mass, float radius)
{
	mass_ = mass;
	radius_ = radius;
	linear_velocity_y = 0.;
	linear_velocity_x = 50.;
	centerPositionX = 100.;
	centerPositionY = 100.;

}

void SimulatedDisk::updatePosition()
{
	float delta_t = 0.01;
	float delta_velocity_y = gravity * delta_t;
	linear_velocity_y += delta_velocity_y;

	float delta_velocity_x = 0.0;
	linear_velocity_x += delta_velocity_x;


	float delta_pos_y = linear_velocity_y * delta_t;
	float delta_pos_x = linear_velocity_x * delta_t;

	centerPositionY += delta_pos_y;
	centerPositionX += delta_pos_x;



	printf("Center position: x = %f, y = %f. v_y = %f\n", 
		centerPositionX, centerPositionY, linear_velocity_y);

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

float SimulatedDisk::getPositionX()
{
	return centerPositionX;
}

float SimulatedDisk::getPositionY()
{
	return centerPositionY;
}

	// private:
	// 	const float mass_;
	// 	const float radius_;

	// 	float centerPositionX;
	// 	float centerPositionY;
	// 	// float angular_velocity;

