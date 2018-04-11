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
    Eigen::VectorXd output_;
    virtual std::string to_string() const;
    virtual void run(const Replace& rep);
  public:    
  };

  class IVector {
    Eigen::VectorXd x;
  public:
    virtual const Eigen::VectorXd& getvec() const;
    virtual void run(const Replace& rep);
  };
  
  class Placeholder : public Node, public IVector {
  private:
    std::string name_;    
  public:    
    Placeholder(std::string name);
    virtual const Eigen::VectorXd& getvec() const;
    virtual void run(const Replace& rep);
    virtual std::string to_string() const;
  };

  class Variable : public Node {
  public:
    virtual std::string to_string() const;
  };
  class VarScalar : public Variable {
  private:
    double val_scalar_;
  public:
    VarScalar(double value);
    //    virtual const Eigen::VectorXd& run(const Replace& rep);
    virtual std::string to_string() const;
  };
  class VarVector : public Variable, public IVector {
  public:
    Eigen::VectorXd vec_value_;
    VarVector(const Eigen::VectorXd& value);
    const Eigen::VectorXd& getvec() const;
    virtual std::string to_string() const;
  };
  class VarMatrix : public Variable {
  public:
    Eigen::MatrixXd mat_value_;
    VarMatrix(const Eigen::MatrixXd& value);
    virtual std::string to_string() const;
  };
  
  class Operation : public Node {
  protected:
    std::list<Node*> input_nodes_;    
  public:
    Operation();
    Operation(const std::list<Node*>& input_nodes);
    void init(const std::list<Node*>& input_nodes);
    virtual void run(const Replace& rep);
    virtual std::string to_string() const = 0;
  };
  class Add : public Operation, IVector {
  private:
    IVector *a_, *b_;
  public:
    Add(IVector *a, IVector *b);
    virtual void run(const Replace& rep);
    const Eigen::VectorXd& getvec() const;
    virtual std::string to_string() const;
  };
  /*
  class Mul : public Operation {
  public:
    Mul(Node* a, Node* b);
    virtual void run(const Replace& rep);
    virtual std::string to_string() const;
  };
  */
  std::ostream& operator<<(std::ostream& stream, const Graph& vallue);
  std::ostream& operator<<(std::ostream& stream, const Operation& value);
  std::ostream& operator<<(std::ostream& stream, const Add& vallue);
  /*
  class Node;
  typedef std::list< std::shared_ptr<Node> > pNodes;
  typedef std::shared_ptr<Node> pNode;
  
  class Node : public std::enable_shared_from_this<Node> {    
  public:
    pNodes input_nodes_;
    pNodes consumers_;
  public:
    Node();
    Node(const pNodes& input_nodes);
  protected:
    void init(const pNodes& input_nodes);
  };  

  class Placeholder : public Node {
    std::string name_;
  public:
    Placeholder(std::string name);
  };
  
  class Operation : public Node {
  public:
    double compute();
  };
  
  class Add : public Operation {
  public:
    Add(pNode a, pNode b);
    double compute();
  };
  */
}

#endif
