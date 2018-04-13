#include "cgraph.hpp"
#include <iostream>

namespace learnlearn {
  using namespace std;
  using namespace Eigen;

  std::ostream& operator<<(std::ostream& stream, const Node& value) {
    stream << value.to_string();
    return stream;
  }

  template<int N> void Tanh<N>::run(const Replace& rep) {
    a_->run(rep);
    const VectorXd& x(a_->getvec());
    for(int i = 0; i < x.size(); i++) {
      this->value_[i] = tanh(x[i]);
    }
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
