#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "defines.h"
#include "Controller.h"
#include "SimulatedDisk.h"
#include "math.h"




Eigen::MatrixXd step()
{
	Eigen::VectorXd observation = Eigen::VectorXd::Zero(80*80);
	return observation;
}


Eigen::MatrixXd stack( std::vector<Eigen::VectorXd> xs)
{
	// TODO: implement correct body
	// stacks elements of std::vector<Eigen::VectorXd> to MatrixXd

	int nEntries = xs.size();
	int entries_per_vector = xs[0].rows();

	Eigen::MatrixXd result = Eigen::MatrixXd::Zero(nEntries,entries_per_vector);
	for(int i = 0; i < nEntries; i++)
	{
		for(int j = 0; j < entries_per_vector; j++)
		{
			result(i,j) = xs[i](j);
		}
	}
	return result;
}

Eigen::VectorXd stack_vector( std::vector<double> x)
{
	double* ptr = &x[0];
	int size = x.size();
	Eigen::Map<Eigen::VectorXd> stacked(ptr, size);

	return stacked;
}


Eigen::MatrixXd prepro(sf::RenderWindow &window)
{
	// TODO: implement actual content

	sf::Image image = window.capture();

	Eigen::MatrixXd dummy = Eigen::VectorXd::Zero(50*50);
	return dummy;
}




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


double stddev()



#endif