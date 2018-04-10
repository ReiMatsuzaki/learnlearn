#include "operation.hpp"
#include <iostream>

namespace learnlearn {
  using namespace std;
  std::ostream& operator<<(std::ostream& stream, const Graph& value) {
    stream << "Graph" << endl;
    stream << "Operators:" << endl;
    for(auto it = value.operations_.begin(); it != value.operations_.end(); ++it) {
      stream << **it;
    }
    return stream;
  }
  std::ostream& operator<<(std::ostream& stream, const Operation& value) {
    stream << value.to_string();
    return stream;
  }
  std::ostream& operator<<(std::ostream& stream, const Add& value) {
    stream << value.to_string();
    return stream;
  }

  string Node::to_string() const { return "Node"; }
  
  Placeholder::Placeholder(std::string name) {
    name_ = name;
    Graph::get_instance().placeholders_.push_back(this);
  }
  string Placeholder::to_string() const {
    return "Placeholder(" + name_ + ")";
  }

  Operation::Operation() {
    Graph::get_instance().operations_.push_back(this);
  }
  Operation::Operation(const std::list<Node*>& input_nodes) {
    this->init(input_nodes);
  }
  void Operation::init(const std::list<Node*>& input_nodes) {
    for(auto it = input_nodes.begin(); it != input_nodes.end(); ++it) {
      input_nodes_.push_back(*it);
    }
    for(auto it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
      (*it)->consumers_.push_back(this);
    }
  }
  Add::Add(Node* a, Node* b) : Operation() {
    std::list<Node*> input_nodes;
    input_nodes.push_back(a);
    input_nodes.push_back(b);
    this->init(input_nodes);
  }
  string Add::to_string() const {
    auto it = input_nodes_.begin();
    auto buf = "Add(" + (*it)->to_string() + ",";
    it++;
    buf += (*it)->to_string() + ")";
    return buf;
  }

  string Variable::to_string() const {
    return "Variable";
  }
  string Variable0::to_string() const {
    return "Variable0(" + std::to_string(value_) + ")";
  }
  /*
  Node::Node() {}
  Node::Node(const pNodes& input_nodes) {
    this->init(input_nodes);
  }
  void Node::init(const pNodes& input_nodes) {
  for(pNodes::const_iterator it = input_nodes.begin();
	it != input_nodes.end(); ++it) {
      input_nodes_.push_back(*it);
    }
    for(pNodes::iterator it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
      (*it)->consumers_.push_back(shared_from_this());
    }
  }
  Placeholder::Placeholder(std::string name) : name_(name) {}
  
  Add::Add(pNode a, pNode b) {
    pNodes nodes;    
    nodes.push_back(a);
    nodes.push_back(b);
    this->init(nodes);    
  }
  double Add::compute() {
    return 1.0;
  }
  
  double Operation::compute() {
    //    std::cout << "don't call" << std::endl;
    return 0.1;
  }
  */
}
