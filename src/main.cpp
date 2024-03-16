#include "../include/Core/Contract.h"
#include "../include/Traits/Constant.h"

#include <iostream>
#include <map>
#include <memory>

using IntPtr = std::unique_ptr<int>;
int main() {
  auto trait = TraitPtr(new ConstantTrait(4));
  auto cp_trait = trait->clone();

  int* x = new int(32);
  return 0;
}
