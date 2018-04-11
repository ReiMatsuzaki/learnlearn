#include <iostream>
#include "cgraph.hpp"
#include <Eigen>
using namespace std;
using namespace Eigen;
using namespace learnlearn;

int main () {

  int a = 10;
  cout << "output:" << endl;
  cout << a << endl;
  auto x = new Placeholder("x");
  VectorXd yy(1); yy << 2.0;

  auto y = new VarVector(yy);
  cout << "XX" << endl;
  cout << y->to_string() << endl;
  auto z = new Add(x, y);

  //  auto w = new Mul(x, z);

  // w = (x+y) * x

  Replace rep;
  rep[x] = VectorXd::Zero(1);
  rep[x][0] = 2.0;
  //  x->run(rep);
  
  z->run(rep);
  //  cout << "cout<<*z" << endl;
  //  cout << *z << endl;
  cout << "z->output" << endl;
  cout << z->output_ << endl;
  //  cout << w->run(rep) << endl;
  
}
