#include <iostream>
#include "cgraph.hpp"
#include <Eigen>
using namespace std;
using namespace Eigen;
using namespace learnlearn;

int main () {
  int ni = 2;
  int no = 2;  

  auto x = new Placeholder("x");
  auto W = new VarMatrix(no, ni);
  W->ref() << 0.1, 0.2, 0.3, 0.1;
  auto b = new VarVector(no);
  b->ref() << 0.1, 0.2;
  auto p = new Sigmoid(new Add(new Matmul(W,x), b));

  Replace rep;
  VectorXd x0(ni); x0<<3.0, 1.0;
  rep[x] = x0;
  
  p->run(rep);
  p->run(rep);
  cout << "p->getvec: " << p->getvec() << endl;
  
}
