#include <iostream>
#include "cgraph.hpp"
#include <Eigen>
using namespace std;
using namespace Eigen;
using namespace learnlearn;

int main () {
  int nd = 3;
  int ni = 2;
  int no = 2;  

  auto X = new Placeholder<2>("x"); // batch data
  
  auto W = new Variable<2>();
  auto WW = MatrixXd(ni,no);
  WW<< 0.1, 0.2, 0.3, 0.1;  
  W->ref() = WW;

  auto bb = VectorXd(no);
  bb << 0.1, 0.2;
  auto b = new Variable<1>();
  b->ref() = bb;
  Replace rep;
  MatrixXd x0(nd,ni); x0<<3.0, 1.0, 0.3, 0.1, 0.2, 0.4;
  rep[X] = x0;  
  auto xw = new Matmul<2>(X, W);
  auto xw_b = new Add<2,2,1>(xw, b);

  auto p = new Sigmoid<2>(xw_b);
  p->run(rep);
  cout << "p->output: " << endl;
  cout << p->output() << endl;

}
