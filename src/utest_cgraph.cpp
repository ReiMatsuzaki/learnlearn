#include <iostream>
#include "cgraph.hpp"
#include <Eigen>
using namespace std;
using namespace Eigen;
using namespace learnlearn;

int main () {
  int ni = 2;
  int no = 2;  

  auto x = new Placeholder<1>("x");
  auto W = new Variable<2>();

  auto WW = MatrixXd(no,ni);
  WW<< 0.1, 0.2, 0.3, 0.1;
  W->ref() = WW;

  auto bb = VectorXd(no);
  bb << 0.1, 0.2;
  auto b = new Variable<1>();
  b->ref() = bb;

  Replace rep;
  VectorXd x0(ni); x0<<3.0, 1.0;
  rep[x] = x0;

  auto wx = new Matmul(W, x);
  wx->run(rep);

  auto p = new Sigmoid<1>(new Add<1,1,1>(wx, b));
  p->run(rep);
  cout << "p->output: " << endl;
  cout << p->output() << endl;

}
