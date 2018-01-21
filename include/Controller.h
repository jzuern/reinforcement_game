#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "defines.h"

class Controller
{
	public:
		Controller(double length, double height, double x, double y);
		void updatePosition();
		void setPosition(double x, double y);
		void setVelocity(double x_vel, double y_vel);
		double getPositionX();
		double getPositionY();
		void move(int direction);
		double getVelX();
		double getVelY();

	private:
		double length_;
		double height_;

		double centerPositionX;
		double centerPositionY;
		double linear_velocity_y;
		double linear_velocity_x;

};


#endif