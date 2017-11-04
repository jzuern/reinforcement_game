#ifndef CONTROLLERDISK_H
#define CONTROLLERDISK_H

#include "defines.h"

class ControllerDisk
{
	public:
		ControllerDisk(float radius, float x, float y); 
		void updatePosition();
		void setPosition(float x, float y);
		void setVelocity(float x_vel, float y_vel);
		float getPositionX();
		float getPositionY();
		void move(int direction);
		float getVelX();
		float getVelY();

	private:
		float mass_;
		float radius_;

		float centerPositionX;
		float centerPositionY;
		float linear_velocity_y;
		float linear_velocity_x;

};


#endif