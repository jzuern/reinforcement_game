#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "defines.h"

class Controller
{
	public:
		Controller(float length, float height, float x, float y); 
		void updatePosition();
		void setPosition(float x, float y);
		void setVelocity(float x_vel, float y_vel);
		float getPositionX();
		float getPositionY();
		void move(int direction);
		float getVelX();
		float getVelY();

	private:
		float length_;
		float height_;

		float centerPositionX;
		float centerPositionY;
		float linear_velocity_y;
		float linear_velocity_x;

};


#endif