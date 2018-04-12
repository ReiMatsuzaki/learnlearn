#ifndef OPERATION_H_
#define OPERATION_H_

#include <string>
#include <list>
#include <map>
#include <memory>
#include <Eigen>

namespace learnlearn {

  class Node;
  class Operation;
  class Variable;
  class Placeholder;

  typedef std::map<Node*,Eigen::VectorXd> Replace;

  class Graph {
  public:
    std::list<Operation*> operations_;
    std::list<Variable*> variables_;
    std::list<Placeholder*> placeholders_;
  public:
    static Graph& get_instance() {
      static Graph inst;
      return inst;
    }
    //    std::string str() const;
  };  

  class Node {
  public:
    std::list<Node*> consumers_;
    virtual std::string to_string() const = 0;
    virtual void run(const Replace& rep);
  public:    
  };
  
  template<int N> class TNode : public Node {
    TNode() {}
  };
  template<> class TNode<0> {
  private:
    double value_;
  public:
    double value() const { return value_; }
  };    
  template<> class TNode<1> {
  private:
    Eigen::VectorXd value_;
  public:
    const Eigen::VectorXd& value() const { return value_; }
  };
  template<> class TNode<2> {
  private:
    Eigen::MatrixXd value_;
  public:
    const Eigen::MatrixXd& value() const { return value_; }
  };

  class VectorNode : public Node {
  protected:    
    Eigen::VectorXd value_; // value_[]
    VectorNode() {}
    VectorNode(int n) : value_(n) {}
  public:
    const Eigen::VectorXd& getvec() const;
  };
  
  class Placeholder : public VectorNode {
  private:
    std::string name_;    
  public:    
    Placeholder(std::string name);
    virtual void run(const Replace& rep);
    virtual std::string to_string() const;
  };

  class VarScalar : public Node {
  private:
    double val_scalar_;
  public:
    VarScalar(double value);
    //    virtual const Eigen::VectorXd& run(const Replace& rep);
    virtual std::string to_string() const;
  };
  class VarVector : public VectorNode {
  public:
    VarVector(int n) : VectorNode(n) {}
    VarVector(const Eigen::VectorXd& value);
    virtual std::string to_string() const;
    Eigen::VectorXd& ref() { return value_; }
  };
  class VarMatrix : public Node {
  public:
    Eigen::MatrixXd mat_value_;
    VarMatrix(int n, int m) : mat_value_(n,m) {}
    VarMatrix(const Eigen::MatrixXd& value);
    virtual std::string to_string() const;
    Eigen::MatrixXd& ref() { return mat_value_; }
  };

  class Operation : public VectorNode {
  protected:
    std::list<Node*> input_nodes_;    
  public:
    Operation();
    Operation(Node *a);
    Operation(Node *a, Node *b);
    Operation(const std::list<Node*>& input_nodes);
    void init(const std::list<Node*>& input_nodes);
  };
  class Add : public Operation {
  private:
    VectorNode *a_, *b_;
  public:
    Add(VectorNode *a, VectorNode *b) : a_(a), b_(b), Operation(a,b) {}
    void run(const Replace& rep);    
    std::string to_string() const;
  };
  class Matmul : public Operation {
  private:
    VarMatrix *m_;
    VectorNode *a_;
  public:
    Matmul(VarMatrix *m, VectorNode *a) : m_(m),a_(a),Operation(m,a) {}
    void run(const Replace& rep);    
    std::string to_string() const;
  };

  class Tanh : public Operation {
  private:
    VectorNode *a_;
  public:
    Tanh(VectorNode *a) : a_(a), Operation(a) {}
    void run(const Replace& rep);    
    std::string to_string() const  { return "Tanh"; }
  };
  class Sigmoid : public Operation {
  private:
    VectorNode *a_;
  public:
    Sigmoid(VectorNode *a) : a_(a), Operation(a) {}
    void run(const Replace& rep);
    std::string to_string() const { return "Sigmoid"; }
  };
  class Softmax : public Operation {
  private:
    VectorNode *a_;
  public:
    Softmax(VectorNode *a) : a_(a), Operation(a) {}
    void run(const Replace& rep);
    std::string to_string() const  { return "Softmax"; }
  };
  class Log : public Operation {
  private:
    VectorNode *a_;
  public:
    Log(VectorNode *a) : a_(a), Operation(a) {}
    void run(const Replace& rep);
    std::string to_string() const  { return "Log"; }
  };
  class Multiply : public Operation {
  private:
    VectorNode *a_, *b_;
  public:
    Multiply(VectorNode *a, VectorNode *b) : a_(a), b_(b), Operation(a,b) {}
    void run(const Replace& rep);
    std::string to_string() const  { return "Multiply"; }
  };
  class Negative : public Operation {
    private:
    VectorNode *a_;
  public:
    Negative(VectorNode *a) : a_(a), Operation(a) {}
    void run(const Replace& rep);
    std::string to_string() const { return "Negative"; }
  };
  
  std::ostream& operator<<(std::ostream& stream, const Node& vallue);
}

#endif
