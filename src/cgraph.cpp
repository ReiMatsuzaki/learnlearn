#include "cgraph.hpp"
#include <iostream>

namespace learnlearn {
  using namespace std;
  using namespace Eigen;

  std::ostream& operator<<(std::ostream& stream, const Node& value) {
    stream << value.to_string();
    return stream;
  }

  void Node::run(const Replace& rep) {}
  
  const VectorXd& VectorNode::getvec() const { return value_; }
  
  Placeholder::Placeholder(std::string name) {
    name_ = name;
    Graph::get_instance().placeholders_.push_back(this);
  }
  void Placeholder::run(const Replace& rep) {
    auto it = rep.find(this);
    this->value_ = it->second;
  }
  string Placeholder::to_string() const {
    return "Placeholder(" + name_ + ")";
  }

  VarScalar::VarScalar(double value) { val_scalar_ = value; }
  string VarScalar::to_string() const { return "Scalar"; }
  VarVector::VarVector(const VectorXd& value) { value_=value; }
  string VarVector::to_string() const {
    auto buf = "VarVector";
    return buf;
  }
  VarMatrix::VarMatrix(const Eigen::MatrixXd& value) { mat_value_=value; }
  string VarMatrix::to_string() const {
    return "Matrix";
    //return "Variable0(" + std::to_string(output_) + ")";
  }

  Operation::Operation() {
    //    Graph::get_instance().operations_.push_back(this);
  }
  Operation::Operation(Node *a) {
    input_nodes_.push_back(a);
  }
  Operation::Operation(Node *a, Node *b) {
    input_nodes_.push_back(a);
    input_nodes_.push_back(b);
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

  Add::Add(VectorNode *a, VectorNode *b) : a_(a), b_(b), Operation(a,b) {}
  void Add::run(const Replace& rep) {
    //    for(auto it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
    //      (*it)->run(rep);
    //    }
    a_->run(rep);
    b_->run(rep);
    this->value_ = this->a_->getvec() + this->b_->getvec();
  }
  string Add::to_string() const {
    //    auto it = input_nodes_.begin();
    auto buf = "Add(" + a_->to_string() + ",";
    //    it++;
    buf += b_->to_string() + ")";
    return buf;
  }
  Mul::Mul(VarMatrix *m, VectorNode *a) : m_(m), a_(a), Operation(m,a) {}
  void Mul::run(const Replace& rep) {
    a_->run(rep);
    value_ = m_->mat_value_ * a_->getvec();
  }
  string Mul::to_string() const { return "matmul"; }

  Tanh::Tanh(VectorNode *a): a_(a), Operation(a) {}
  void Tanh::run(const Replace& rep) {
    a_->run(rep);
    const VectorXd& x(a_->getvec());
    for(int i = 0; i < x.size(); i++) {
      this->value_[i] = tanh(x[i]);
    }
  }
  string Tanh::to_string() const { return "Tanh"; }
}
