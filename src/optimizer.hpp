#ifndef OPERATION_H_
#define OPERATION_H_

#include <map>
#include <set>
#include "cgraph.hpp"

namespace learnlearn {  

  typedef std::map<Node*, MatrixXd> GradTable;
  void compute_grad(Node *loss, GradTable& grad_table) {
    using std::cout;
    using std::endl;
    using std::set;
    using std::
    using Eigen::MatrixXd;
    
    grad_table[loss] = MatrixXd::Ones(1,1);
    std::set<Node*> visited;
    std::queue<Node*> queue;
    visited.insert(loss);
    queue.push(loss);

    while(!queue.empty()) {
      Node* node = queue.pop(); // = queue.front();

      if(node != loss) {
	for(auto it = node->comsumers.begin(); it != node->comsumers.end(); ++it) {
	  Node *consumer = *it;
	  MatrixXd& output = grad_table[consumer];
	  
	}
      }

      for(auto it = node->input_ndoes.begin(); it != node->input_nodes.end(); ++it) {
	if(visited.find(node) == visited.end()) {
	  visited.insert(node);
	  queue.push(node);
	}
      }
    }
    
  }
    
}
