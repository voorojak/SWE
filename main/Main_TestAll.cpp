#include <limits.h>
#include "gtest/gtest.h"
#include "Timer.h"
int main(int argc, char **argv) {
  Timer::getInstance()->setTurbo(Timer::TURBO_ON);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
