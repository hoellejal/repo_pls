#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compression.h"


int main(int argc, char const *argv[]) {
  compression("../test/test.txt");

  return 0;
}
