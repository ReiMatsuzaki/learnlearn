#include <iostream>
#include "cgraph.hpp"
#include <Eigen>
using namespace std;
using namespace Eigen;
using namespace learnlearn;

int main () {

  auto x = new Placeholder("x");
  VectorXd yy(1); yy << 2.0;
  auto y = new VarVector(yy);
  auto z = new Add(x, y);
  MatrixXd mm(1,1); mm << 4.0;
  auto m = new VarMatrix(mm);
  auto w = new Mul(m, z);
  // w = (x+y) * x

  Replace rep;
  VectorXd x0(1); x0<<3.0;
  rep[x] = x0;
  
  w->run(rep);
  cout << "w->output: " << w->getvec() << endl;
  //  cout << w->run(rep) << endl;
  
}
