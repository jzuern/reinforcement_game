#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "defines.h"
#include "ControllerDisk.h"
#include "SimulatedDisk.h"
#include "math.h"

void collisionDetect(SimulatedDisk &disk_sim, ControllerDisk &disk_ctrl, float r_contr, float r_sim)
{
	float x_sim = disk_sim.getPositionX();
	float y_sim = disk_sim.getPositionY();

	float x_ctrl = disk_ctrl.getPositionX();
	float y_ctrl = disk_ctrl.getPositionY();

	float v1_x = disk_sim.getVelX();
	float v1_y = disk_sim.getVelY();

	float v2_x = disk_ctrl.getVelX();
	// float v2_y = disk_ctrl.getVelY();

	float m1 = 0.0001;
	float m2 = 1000.;

	float distance = sqrt( (x_sim - x_ctrl)*(x_sim - x_ctrl) + (y_sim - y_ctrl)*(y_sim - y_ctrl));

	float v1_new_x,v1_new_y;

	if (distance < (r_contr + r_sim))
	{

		float pi = atan(1)*4;

		float dx = x_sim - x_ctrl;
		float dy = y_sim - y_ctrl;
		float angle = atan2(dy, dx);

		float magnitude_1 = sqrt(v1_x*v1_x+v1_y*v1_y);
		float direction_1 = atan2(v1_x, v1_y);

		float new_xspeed_1 = magnitude_1*cos(direction_1 - angle);
		float new_yspeed_1 = magnitude_1*sin(direction_1 - angle);
		float new_xspeed_2 = v2_x;

		float final_xspeed_1 = ((m1-m2)*new_xspeed_1+(m1+m2)*new_xspeed_2)/(m1+m2);
		float final_yspeed_1 = new_yspeed_1;

		v1_new_x = cos(angle)*final_xspeed_1+cos(angle+pi/2)*final_yspeed_1;
		v1_new_y = sin(angle)*final_xspeed_1+sin(angle+pi/2)*final_yspeed_1;

		printf("detected collision! Changed sim disk velocities from (%f,%f) to (%f,%f)\n",
			v1_x,v1_y,v1_new_x,v1_new_y);

		disk_sim.setVelocity(v1_new_x, v1_new_y);
	}
}


#endif