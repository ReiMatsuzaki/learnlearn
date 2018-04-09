#include "operation.hpp"
#include <iostream>

namespace learnlearn {

  Node::Node() {}
  Node::Node(const pNodes& input_nodes) {
    
    for(pNodes::const_iterator it = input_nodes.begin();
	it != input_nodes.end(); ++it) {
      input_nodes_.push_back(*it);
    }
    for(pNodes::iterator it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
      (*it)->consumers_.push_back(shared_from_this());
    }
  }
  
  Placeholder::Placeholder(std::string name) : name_(name) {}
  Operation::Operation() {
    std::cout << "non parameter" << std::endl;
  }
  double Operation::compute() {
    //    std::cout << "don't call" << std::endl;
    return 0.1;
  }
}
