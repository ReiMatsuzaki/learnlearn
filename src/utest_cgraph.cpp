#include <iostream>
#include "operation.hpp"
#include <Eigen>
using namespace std;
using namespace learnlearn;

int main () {

  int a = 10;
  cout << "output:" << endl;
  cout << a << endl;
  auto x = new Placeholder("x");
  auto y = new Variable0(2.0);
  auto z = new Add(x, y);
  auto w = new Mul(x, z);

  // w = (x+y) * x

  Replace rep;
  rep[x] = 3.0;
  
  cout << *w << endl;
  cout << z->run(rep) << endl;
  cout << w->run(rep) << endl;

  /*
  std::shared_ptr<Placeholder> x(new Placeholder("x"));
  std::shared_ptr<Placeholder> y(new Placeholder("y"));
  std::shared_ptr<Add> x_plus_y(new Add(x, y));
  */
}
