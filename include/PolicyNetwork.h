#ifndef POLICYNETWORK_H
#define POLICYNETWORK_H

#include <Eigen/Dense> // eigen library for matrix vector stuff
#include <random>



class PolicyNetwork
{
	public:
		PolicyNetwork(); 
		void initialize();
		
	private:

		Eigen::MatrixXd W1;
		Eigen::VectorXd W2;

		Eigen::MatrixXd grad_buffer_W1;
		Eigen::VectorXd grad_buffer_W2;

		Eigen::MatrixXd rmsprop_cache_W1;
		Eigen::VectorXd rmsprop_cache_W2;
};


#endif

