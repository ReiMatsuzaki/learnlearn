#include <iostream>
#include "operation.hpp"
using namespace std;
using namespace learnlearn;

int main () {

  int a = 10;
  cout << "output:" << endl;
  cout << a << endl;
  auto x = new Placeholder("x");
  auto y = new Variable0(1.2);
  auto xpy = new Add(x, y);

  cout << *xpy << endl;

  /*
  std::shared_ptr<Placeholder> x(new Placeholder("x"));
  std::shared_ptr<Placeholder> y(new Placeholder("y"));
  std::shared_ptr<Add> x_plus_y(new Add(x, y));
  */
}
