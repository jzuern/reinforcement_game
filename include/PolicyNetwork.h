#ifndef POLICYNETWORK_H
#define POLICYNETWORK_H

#include <random>
#include <Eigen/Dense> // eigen library for matrix vector stuff
#include "defines.h"

class PolicyNetwork
{
	public:
		PolicyNetwork(); 
		void initialize(char* filename);
		void initialize_zeros();

		std::pair<Eigen::MatrixXd,Eigen::VectorXd> policy_backward(Eigen::MatrixXd &eph,
				Eigen::VectorXd &epdlogp, Eigen::MatrixXd &epx);
		
		std::pair<double, Eigen::VectorXd> policy_forward(Eigen::VectorXd &x);
		
		Eigen::VectorXd discount_rewards(Eigen::VectorXd &r);

		Eigen::MatrixXd W1;
		Eigen::VectorXd W2;

		Eigen::MatrixXd grad_buffer_W1;
		Eigen::VectorXd grad_buffer_W2;

		Eigen::MatrixXd rmsprop_cache_W1;
		Eigen::VectorXd rmsprop_cache_W2;

		// network parameters
		int nHidden;
		int batch_size;
		double learning_rate;
		double gamma;
		double decay_rate;
		bool render;
};


#endif

