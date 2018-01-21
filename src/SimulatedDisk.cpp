#include "SimulatedDisk.h"
#include "defines.h"


SimulatedDisk::SimulatedDisk(double radius, double x, double y)
{
	radius_ = radius;
	linear_velocity_y = 0.0;
	linear_velocity_x = 0.0;
	centerPositionX = x;
	centerPositionY = y;
}

bool SimulatedDisk::updatePosition()
{
	bool out_of_bounds = false;

    double delta_velocity_y = gravity * delta_t;
	linear_velocity_y += delta_velocity_y;

    double delta_velocity_x = 0.0;
	linear_velocity_x += delta_velocity_x;

    double delta_pos_y = linear_velocity_y * delta_t;
    double delta_pos_x = linear_velocity_x * delta_t;

    double bounce = 1.0;

	centerPositionY += delta_pos_y;
	centerPositionX += delta_pos_x;

	if(centerPositionY+radius_ > WINSIZEY) // disk is out of bounds
	{
		// centerPositionY = WINSIZEY - radius_;
		// linear_velocity_y = -bounce*linear_velocity_y;

		// if this happens, remove disk from game
		out_of_bounds = true;

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

void SimulatedDisk::setPosition(double x, double y)
{
	centerPositionX = x;
	centerPositionY = y;
}

void SimulatedDisk::setVelocity(double x_vel, double y_vel)
{
	linear_velocity_x = x_vel;
	linear_velocity_y = y_vel;
}

double SimulatedDisk::getPositionX()
{
	return centerPositionX;
}

double SimulatedDisk::getPositionY()
{
	return centerPositionY;
}

double SimulatedDisk::getVelX()
{
	return linear_velocity_x;
}

double SimulatedDisk::getVelY()
{
	return linear_velocity_y;
}