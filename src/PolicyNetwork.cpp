#include "PolicyNetwork.h"
#include <math.h> 

float sigmoid(float x)
{
  return 1.0 / (1.0 + exp(-x));
}

PolicyNetwork::policy_backward(VectorXd eph, VectorXd epdlogp)
{

  //   """ backward pass. (eph is array of intermediate hidden states) """
  //   dW2 = np.dot(eph.T, epdlogp).ravel()
  Eigen::VectorXd dW2 = eph * epdlogp;

  //   dh = np.outer(epdlogp, model['W2'])
  Eigen::MatrixXd dh = epdlogp*this.W2.transpose();

  //   dh[eph <= 0] = 0 # backpro prelu
  for(int i = 0; i < dh.rows(); i++)
  {
    for(int j = 0; j < dh.cols(); i++)
    {
      dh[i][j] = dh[i][j] < 0.0 ? 0.0:dh[i][j]; // ReLu
    }
  }

  //   dW1 = np.dot(dh.T, epx)
  Eigen::VectorXd dW2 = dh * epx;  // where do we get epx??

  //   return {'W1':dW1, 'W2':dW2}
  return std::make_tuple (dW1, dW2); 
}


PolicyNetwork::policy_forward(VectorXd x)
{
  //  h = np.dot(model['W1'], x)
  VectorXd h = x.array() * this.W1.array()

  // h[h<0] = 0 # ReLU nonlinearity
  for(int i = 0; i < h.size(); i++)
  {
    h[i] = h[i] < 0.0 ? 0.0:h[i]; // ReLu
  }
  //   logp = np.dot(model['W2'], h)
  VectorXd logp = this.W2.array() * h.array();

  //  p = sigmoid(logp)
  VectorXd p;
  for(int i = 0; i < logp.size(); i++)
  {
    p[i] = sigmoid(logp[i]);
  }


  // return p, h # return probability of taking action 2, and hidden state
  return std::make_tuple (p, h); 
}



PolicyNetwork::PolicyNetwork()
{
  // hyperparameters:
  int nHidden = 200;
  int batch_size = 10;
  float learning_rate = 1e-4;
  float gamma = 0.99;
  float decay_rate = 0.99;
  bool render = false;

}


void PolicyNetwork::initialize()
{
  // input dimensionality:
  int D = 80*80;
  int H = 200;

  // TODO: add xavier initialization instead of zeros
  W1 = Eigen::VectorXd::Zero(H,D);
  W2 = Eigen::VectorXd::Zero(H);

  grad_buffer_W1 = Eigen::VectorXd::Zero(H,D);
  grad_buffer_W2 = Eigen::VectorXd::Zero(H);

  rmsprop_cache_W1 = Eigen::VectorXd::Zero(H,D);
  rmsprop_cache_W2 = Eigen::VectorXd::Zero(H);
}

Eigen::MatrixXd PolicyNetwork::prepro()
{
  // TODO: implement actual content

  MatrixXd dummy = Eigen::MatrixXd::Zero(80,80);
  return dummy
}


Eigen::MatrixXd PolicyNetwork::discount_rewards(MatrixXd r)
{

  Eigen::MatrixXd discounted_r = Eigen::MatrixXd::Zero(r.rows(),r.cols());
  
  int running_add = 0;

  for(i = r.rows(); i >= 0; i--)
  {
    if (r[i] != 0)
    {
      running_add = 0;
    }
    running_add = running_add * gamma + r[i]
    discounted_r[i] = running_add;
  }

  return discounted_r
}
