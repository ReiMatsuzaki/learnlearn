#ifndef OPERATION_H_
#define OPERATION_H_

#include <string>
#include <list>
#include <memory>

namespace learnlearn {
  //  class Node;
  
  /*
  class Operation;
  typedef std::list< std::shared_ptr<Operation> > pOperationList;
  */

  class Node : public std::enable_shared_from_this<Node> {
    typedef std::list< std::shared_ptr<Node> > pNodes;
  public:
    pNodes input_nodes_;
    pNodes consumers_;
  public:
    Node();
    Node(const pNodes& input_nodes);
  };

  class Placeholder : public Node {
    std::string name_;
  public:
    Placeholder(std::string name);
  };
  
  class Operation : public Node {
  public:
    Operation();
    double compute();
  };
  
  class Add : public Operation {
  public:
    Add(const Operation& a, const Operation& b);
    double compute();
  };
}

#endif
