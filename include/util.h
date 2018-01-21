#ifndef UTIL_H
#define UTIL_H

#include "defines.h"
#include "Controller.h"
#include "SimulatedDisk.h"
#include "math.h"
#include <cstdlib>
#include <iostream>

#include <Eigen/Dense> // eigen library for matrix vector stuff


double rand_double(float min, float max)
{
    float r = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(max-min)));

    return double(r);
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
    ulong size = x.size();
    Eigen::Map<Eigen::VectorXd> stacked(ptr, size);

//    Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
//    printf("stacked:\n");
//    std::cout << stacked.format(CleanFmt);

    return stacked;
}


Eigen::VectorXd prepro(sf::RenderWindow &window)
{
    sf::Image image = window.capture();
    auto size = image.getSize();
    int size_x = size.x;
    int size_y = size.y;

    Eigen::VectorXd image_matrix = Eigen::VectorXd::Zero(size_x*size_y);
    int counter = 0;
    for(int i = 0; i < size_x; i++)
    {
        for(int j = 0; j < size_y; j++)
        {
            auto color = image.getPixel(i,j);
            image_matrix(counter) = 1.0/3.0 * (color.r + color.g + color.b);
            counter++;
        }
    }


    return image_matrix;
}





bool collisionDetect(SimulatedDisk &disk_sim, Controller &disk_ctrl, float radius)
{

    bool touched  = false;
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
        touched = true;
		float damp = 1.0;

		// disk_sim.setPosition(x_sim, y_sim);
		disk_sim.setVelocity(disk_vel_x, -damp*disk_vel_y);
	}

    return touched;
}

double std_dev(Eigen::VectorXd discounted_epr, double mean)
{
    double sum = 0.0;
    int N = discounted_epr.size();

    for(int i = 0; i < N; i++)
    {
        sum += (discounted_epr(i) - mean) * (discounted_epr(i) - mean);
    }

    double stddev = sqrt( sum / N);


    return stddev;
}

#endif