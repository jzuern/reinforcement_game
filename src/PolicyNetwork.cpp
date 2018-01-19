#include "PolicyNetwork.h"
#include <math.h> 

double sigmoid(double x)
{
  return 1.0 / (1.0 + exp(-x));
}

std::pair<Eigen::MatrixXd,Eigen::VectorXd> PolicyNetwork::policy_backward(Eigen::MatrixXd eph, Eigen::VectorXd epdlogp, Eigen::MatrixXd epx)
{

  //   """ backward pass. (eph is array of intermediate hidden states) """
  //   dW2 = np.dot(eph.T, epdlogp).ravel()
  Eigen::VectorXd dW2 = eph.transpose() * epdlogp;

  //   dh = np.outer(epdlogp, model['W2'])
  Eigen::MatrixXd dh = epdlogp * W2.transpose();

  //   dh[eph <= 0] = 0 # backpro prelu
  for(int i = 0; i < dh.rows(); i++)
  {
    for(int j = 0; j < dh.cols(); j++)
    {
      dh(i,j) = dh(i,j) < 0.0 ? 0.0:dh(i,j); // ReLu
    }
  }

  //   dW1 = np.dot(dh.T, epx)
  Eigen::MatrixXd dW1 = dh.transpose() * epx;

  //   return {'W1':dW1, 'W2':dW2}
  return std::make_pair (dW1, dW2); 
}


std::pair<double,Eigen::VectorXd> PolicyNetwork::policy_forward(Eigen::VectorXd x)
{
  //  h = np.dot(model['W1'], x)
  Eigen::VectorXd h = W1 * x;

  // h[h<0] = 0 # ReLU nonlinearity
  for(int i = 0; i < h.size(); i++)
  {
    h(i) = h(i) < 0.0 ? 0.0:h(i); // ReLu
  }
  //   logp = np.dot(model['W2'], h)
  double logp = W2.transpose() * h;

  //  p = sigmoid(logp)
  double p = sigmoid(logp);

  // return p, h # return probability of taking action 2, and hidden state
  return std::make_pair(p, h); 
}



PolicyNetwork::PolicyNetwork()
{
    nHidden = 10;
    batch_size = 10;
    learning_rate = 1e-4;
    gamma = 0.99;
    decay_rate = 0.99;
}


void PolicyNetwork::initialize()
{
  // input dimensionality:
  int D = 50*50;
  int H = nHidden;

  // TODO: add xavier initialization instead of zeros
  W1 = Eigen::MatrixXd::Zero(H,D);
  W2 = Eigen::VectorXd::Zero(H);

  grad_buffer_W1 = Eigen::MatrixXd::Zero(H,D);
  grad_buffer_W2 = Eigen::VectorXd::Zero(H);

  rmsprop_cache_W1 = Eigen::MatrixXd::Zero(H,D);
  rmsprop_cache_W2 = Eigen::VectorXd::Zero(H);
}



Eigen::VectorXd PolicyNetwork::discount_rewards(Eigen::VectorXd r)
{

  Eigen::VectorXd discounted_r = Eigen::VectorXd::Zero(r.size());
  
  double running_add = 0.0;

  for(int i = r.size()-1; i >= 0; i--)
  {
    if (r(i) != 0.0)
    {
      running_add = 0.0;
    }
    running_add = running_add * gamma + r(i);
    discounted_r(i) = running_add;
  }

  return discounted_r;
}
