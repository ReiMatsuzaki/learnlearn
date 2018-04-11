#include "cgraph.hpp"
#include <iostream>

namespace learnlearn {
  using namespace std;
  using namespace Eigen;
  
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
  void Node::run(const Replace& rep0) { }
    
  const VectorXd& IVector::getvec() const { return x; }
  void IVector::run(const Replace& rep) {}
  
  Placeholder::Placeholder(std::string name) {
    name_ = name;
    Graph::get_instance().placeholders_.push_back(this);
  }
  const VectorXd& Placeholder::getvec() const { return this->output_; }
  void Placeholder::run(const Replace& rep) {
    auto it = rep.find(this);
    this->output_ = it->second;
    cout << "Placeholder::run  " << this->output_ << endl;
  }
  
  string Placeholder::to_string() const {
    return "Placeholder(" + name_ + ")";
  }

  string Variable::to_string() const { return "Variable"; }
  VarScalar::VarScalar(double value) { val_scalar_ = value; }
  string VarScalar::to_string() const { return "Scalar"; }
  VarVector::VarVector(const Eigen::VectorXd& value) { vec_value_=value; }
  const VectorXd& VarVector::getvec() const { return vec_value_; }
  string VarVector::to_string() const {
    auto buf = "VarVector";
    cout << vec_value_ << endl;
    return buf;
  }
  VarMatrix::VarMatrix(const Eigen::MatrixXd& value) { mat_value_=value; }
  string VarMatrix::to_string() const {
    return "Matrix";
    //return "Variable0(" + std::to_string(output_) + ")";
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
  void Operation::run(const Replace& rep) {}
  Add::Add(IVector *a, IVector *b) : Operation(), a_(a), b_(b) {
    /*
    std::list<Node*> input_nodes;
    input_nodes.push_back(a);
    input_nodes.push_back(b);
    this->init(input_nodes);
    */
  }
  const VectorXd& Add::getvec() const { return output_; }
  void Add::run(const Replace& rep) {
    //    for(auto it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
    //      (*it)->run(rep);
    //    }
    a_->run(rep);
    b_->run(rep);
    cout << "Add:run >>" << endl;
    cout << this->a_->getvec() << endl;
    cout << this->b_->getvec() << endl;
    this->output_ = this->a_->getvec() + this->b_->getvec();
  }
  string Add::to_string() const {
    auto it = input_nodes_.begin();
    auto buf = "Add(" + (*it)->to_string() + ",";
    it++;
    buf += (*it)->to_string() + ")";
    return buf;
  }
  /*
  Mul::Mul(Node* a, Node* b) : Operation() {
    std::list<Node*> input_nodes;
    input_nodes.push_back(a);
    input_nodes.push_back(b);
    this->init(input_nodes);
  }
  void Mul::run(const Replace& rep) {
    Eigen::VectorXd acc = 1;
    for(auto it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
      acc *= (*it)->run(rep);      
    }
    this->output_ = acc;
  }
  string Mul::to_string() const {
    auto it = input_nodes_.begin();
    auto buf = "Mul(" + (*it)->to_string() + ",";
    it++;
    buf += (*it)->to_string() + ")";
    return buf;
  }
  */

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
