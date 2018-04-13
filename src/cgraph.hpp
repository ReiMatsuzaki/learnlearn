#ifndef OPERATION_H_
#define OPERATION_H_

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <memory>
#include <Eigen>

namespace learnlearn {

  class Node;
  //  class Operation;
  //  class Variable;
  //  class Placeholder;

  typedef std::map<Node*,Eigen::MatrixXd> Replace;

  class Graph {
  public:
    //    std::list<Operation*> operations_;
    //    std::list<Variable*> variables_;
    //    std::list<Placeholder*> placeholders_;
  public:
    static Graph& get_instance() {
      static Graph inst;
      return inst;
    }
    //    std::string str() const;
  };  

  template<int N> class TypeTensor {
  public:
    typedef double Value;
  };
  template<> class TypeTensor<0> {
  public:
    typedef double Value;
  };
  template<> class TypeTensor<1> {
  public:
    typedef Eigen::VectorXd Value;
  };
  template<> class TypeTensor<2> {
  public:
    typedef Eigen::MatrixXd Value;
  };
  
  class Node {
  public:
    std::list<Node*> consumers_;
    virtual std::string to_string() const { return "Node"; }
    virtual void run(const Replace& rep) {}
  public:    
  };
  
  template<int N> class TNode : public Node {
  public:
    typedef typename TypeTensor<N>::Value Value;
    Value output_;
    virtual void run(const Replace& rep) {};    
    const Value& output() const { return output_; }
  };
  
  template<int N> class Placeholder : public TNode<N> {
  private:
    std::string name_;    
  public:    
    Placeholder(std::string name) : name_(name) {}
    virtual void run(const Replace& rep) {
      auto it = rep.find(this);
      this->output_ = it->second;
    }
    virtual std::string to_string() const  { return "Placeholder(" + name_ + ")"; }
  };

  template<int N> class Variable : public TNode<N> {
  public:
    typename TNode<N>::Value& ref() { return this->output_; }
    std::string to_string() const { return "Variable"; }
    void run(const Replace& rep) {}
  };  

  template<int N> class Operation : public TNode<N> {
  protected:
    std::list<Node*> input_nodes_;    
  public:
    Operation() {}
    Operation(Node *a) {
      std::list<Node*> xs;
      xs.push_back(a);
      this->init(xs);
    }
    Operation(Node *a, Node *b) {
      std::list<Node*> xs;
      xs.push_back(a);
      xs.push_back(b);
      this->init(xs);
    }
    Operation(const std::list<Node*>& input_nodes) {
      this->init(input_nodes);
    }
    void init(const std::list<Node*>& input_nodes) {
      for(auto it = input_nodes.begin(); it != input_nodes.end(); ++it) {
	input_nodes_.push_back(*it);
      }
      for(auto it = input_nodes_.begin(); it != input_nodes_.end(); ++it) {
	(*it)->consumers_.push_back(this);
      }
    }    
  };
  template<int N, int NL, int NR> class Add : public Operation<N> {
  private:
    TNode<NL> *a_;
    TNode<NR> *b_;
  public:
    Add(TNode<NL> *a, TNode<NR> *b) : a_(a), b_(b), Operation<N>(a,b) {}
    void run(const Replace& rep) {
      for(auto it = this->input_nodes_.begin();
	  it != this->input_nodes_.end(); ++it) {
	(*it)->run(rep);
      }
      if(N==NL && N==NR) {
	this->output_ = this->a_->output() + this->b_->output();
      } else if(N==2 && NL==2 && NR==1) {
	this->output_ = this->a_->output();
	for(int i = 0; i < this->a_->output().rows(); i++) {
	  for(int j = 0; j < this->a_->output().cols(); j++) {    
	    this->output_(i,j) = this->a_->output()(i,j) + this->b_->output()(j);
	  }
	}
      }
    }
    std::string to_string() const { return "Add"; }
  };
  template<int N> class Matmul   : public Operation<N> {
  private:
    TNode<2> *m_;
    TNode<N> *a_;
  public:
    Matmul(TNode<2> *m, TNode<N> *a) : m_(m),a_(a),Operation<N>(m,a) {}
    void run(const Replace& rep) {
      m_->run(rep);
      a_->run(rep);
      this->output_ = m_->output() * a_->output();
    }
    std::string to_string() const { return "Matmul"; }
  };
  template<int N> class Tanh     : public TNode<N> {
  private:
    TNode<N> *a_;
  public:
    Tanh(TNode<N> *a) : a_(a), Operation<N>(a) {}
    void run(const Replace& rep);    
    std::string to_string() const  { return "Tanh"; }
  };
  template<int N> class Sigmoid  : public Operation<N> {
  private:
    TNode<N> *a_;
  public:
    Sigmoid(TNode<N> *a) : a_(a), Operation<N>(a) {}
    void run(const Replace& rep) {
      a_->run(rep);
      this->output_ = 1 / (1 + (-a_->output().array().exp()));
    }
    std::string to_string() const { return "Sigmoid"; }
  };
  template<int N> class Softmax  : public TNode<N> {
  private:
    TNode<N> *a_;
  public:
    Softmax(TNode<N> *a) : a_(a), Operation<N>(a) {}
    void run(const Replace& rep) {
      a_->run(rep);
      const typename TypeTensor<N>::Value& x(a_->value());
      this->value_ = x.array().exp();
      double sum = this->value_.sum();
      this->value_ /= sum;
    }
    std::string to_string() const  { return "Softmax"; }
  };
  template<int N> class Log      : public TNode<N> {
  private:
    TNode<N> *a_;
  public:
    Log(TNode<N> *a) : a_(a), Operation<N>(a) {}
    void run(const Replace& rep);
    std::string to_string() const  { return "Log"; }
  };
  template<int N> class Multiply : public TNode<N> {
  private:
    TNode<N> *a_, *b_;
  public:
    Multiply(TNode<N> *a, TNode<N> *b) : a_(a), b_(b), Operation<N>(a,b) {}
    void run(const Replace& rep);
    std::string to_string() const  { return "Multiply"; }
  };
  template<int N> class Negative : public TNode<N> {
    private:
    TNode<N> *a_;
  public:
    Negative(TNode<N> *a) : a_(a), Operation<N>(a) {}
    void run(const Replace& rep);
    std::string to_string() const { return "Negative"; }
  };
  
  std::ostream& operator<<(std::ostream& stream, const Node& vallue);
}

#endif


