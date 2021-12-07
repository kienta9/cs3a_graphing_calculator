#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <SFML/Graphics.hpp>

#include "../../includes/token/token.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/rightparen.h"

#include "../../includes/queue/MyQueue.h"

#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/rpn/rpn.h"

#include "../../graph_info.h"

using namespace std;

bool test_stub(bool debug = false)
{
  if (debug){
    cout << "testB:: test-sub() entering test_sub" << endl;
  }

  vector<sf::Vector2f> a;
  cout << "size: " << a.max_size();
  

  return true;
}

TEST(TEST_STUB, TestStub) {
  
  //EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

