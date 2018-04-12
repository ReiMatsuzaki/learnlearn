#include "cgraph.hpp"
#include <iostream>

namespace learnlearn {
  using namespace std;
  using namespace Eigen;

  std::ostream& operator<<(std::ostream& stream, const Node& value) {
    stream << value.to_string();
    return stream;
  }
  
  //  const VectorXd& VectorNode::getvec() const { return value_; }
  
  template<int N> Placeholder<N>::Placeholder(std::string name) {
    name_ = name;
    //    Graph::get_instance().placeholders_.push_back(this);
  }
  template<int N> void Placeholder<N>::run(const Replace& rep) {
    auto it = rep.find(this);
    this->value_ = it->second;
  }
  
  template<int N> Operation<N>::Operation(Node *a) {
    list<Node*> xs;
    xs.push_back(a);
    this->init(xs);
  }
  template<int N> Operation<N>::Operation(Node *a, Node *b) {
    list<Node*> xs;
    xs.push_back(a);
    xs.push_back(b);
    this->init(xs);
  }
  template<int N> Operation<N>::Operation(const std::list<Node*>& input_nodes) {
    this->init(input_nodes);
  }
  template<int N> void Operation<N>::init(const std::list<Node*>& input_nodes) {
    for(auto it = input_nodes.begin(); it != input_nodes.end(); ++it) {
      input_nodes_.push_back(*it);
    }
    for(auto it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
      (*it)->consumers_.push_back(this);
    }
  }

  template<> void Add<1,1,1>::run(const Replace& rep) {
    //    for(auto it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
    //      (*it)->run(rep);
    //    }
    a_->run(rep);
    b_->run(rep);
    this->value_ = this->a_->value() + this->b_->value();
  }
  void Matmul::run(const Replace& rep) {
    a_->run(rep);
    value_ = m_->value() * a_->value();
  }
  template<int N> void Tanh<N>::run(const Replace& rep) {
    a_->run(rep);
    const VectorXd& x(a_->getvec());
    for(int i = 0; i < x.size(); i++) {
      this->value_[i] = tanh(x[i]);
    }
  }
  template<int N> void Sigmoid<N>::run(const Replace& rep) {
    a_->run(rep);
    //    const VectorXd& x(a_->getvec());
    //    value_ = 1 / (1 + (-x).array().exp());
    this->value_ = 1 / (1 + (-a_->value().array().exp()));
  }
  template<int N> void Softmax<N>::run(const Replace& rep) {
    a_->run(rep);
    const typename TypeTensor<N>::Value& x(a_->value());
    this->value_ = x.array().exp();
    double sum = this->value_.sum();
    this->value_ /= sum;
  }
  template<int N> void Log<N>::run(const Replace& rep) {
    a_->run(rep);
    this->value_ = a_->value().array().log();
  }
  template<int N> void Multiply<N>::run(const Replace& rep) {
    a_->run(rep);
    b_->run(rep);
    this->value_ = a_->value().array() * b_->value().array();
  }
  template<int N> void Negative<N>::run(const Replace& rep) {
    a_->run(rep);
    this->value_ = -a_->getvec();
  }
}
