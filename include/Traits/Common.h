#ifndef _TRAITS_CONSTANT_HEADER_
#define _TRAITS_CONSTANT_HEADER_

#include "../Core/BaseType.h"
#include "../Core/Trait.h"

class ConstantTrait : public Trait {
private:
  BaseType value;

public:
  ConstantTrait(BaseType value) : Trait(), value { value } {};

  Trait* clone() const override { return new ConstantTrait(value); };

  ~ConstantTrait() {};

  std::optional<BaseType> doEval(const ContractState& /*cs*/, BaseType /*val*/) override {
    return value;
  };
};

#endif // _TRAITS_CONSTANT_HEADER_
