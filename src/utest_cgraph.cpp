#include <iostream>

#include <Eigen>
#include <gtest/gtest.h>

#include "cgraph.hpp"

using namespace std;
using namespace Eigen;
using namespace learnlearn;

namespace {
  
  class UTestCGraph : public ::testing::Test{};
  
  TEST_F(UTestCGraph, test_placeholder) {
    auto X = new Placeholder<2>("x"); // batch data
  }
}

int sub () {
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
  auto logp = new Log<2>(p);

  auto C = new Variable<2>();
  auto CC = MatrixXd(nd, no);
  CC << 0.1, 0.2, 0.3, 0.1, 0.2, 0.3;
  C->ref() = CC;

  auto C_logp = new Multiply<2>(C, logp);  

    
  auto j = new Sum<2>(C_logp);
  
  logp->run(rep);
  cout << "p" << endl;
  cout << p->output() << endl;
  cout << "logp->output: " << endl;
  cout << logp->output() << endl;
  cout << "logp->output: " << endl;
  C_logp->run(rep);
  cout << C_logp->output() << endl;
  cout << "j->output: " << endl;
  j->run(rep);
  cout << j->output() << endl;

  return 0;
}
