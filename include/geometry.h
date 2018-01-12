#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "defines.h"
#include "Controller.h"
#include "SimulatedDisk.h"
#include "math.h"


void collisionDetect(SimulatedDisk &disk_sim, Controller &disk_ctrl, float radius)
{
	float disk_pos_x = disk_sim.getPositionX();
	float disk_pos_y = disk_sim.getPositionY();

	float disk_vel_x = disk_sim.getVelX();
	float disk_vel_y = disk_sim.getVelY();

	float controller_pos_center_x = disk_ctrl.getPositionX();
	float controller_pos_max_x = controller_pos_center_x + controller_length/2.;
	float controller_pos_min_x = controller_pos_center_x - controller_length/2.;

	float distance_y = WINSIZEY - disk_pos_y - diskRadius;


	if (disk_pos_x < controller_pos_max_x &&
		disk_pos_x > controller_pos_min_x && 
		abs(distance_y) < controller_height)
	{
		printf("disk touched controller\n");
		float damp = 1.0;

		// disk_sim.setPosition(x_sim, y_sim);
		disk_sim.setVelocity(disk_vel_x, -damp*disk_vel_y);
	}
}



#endif