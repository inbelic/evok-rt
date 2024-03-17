#ifndef _EVOK_TRAITS_COMMON_HEADER_
#define _EVOK_TRAITS_COMMON_HEADER_

#include "../Core/BaseType.h"
#include "../Core/Trait.h"

#include <utility>

namespace evok {
namespace trait {

class ConstantTrait : public Trait {
private:
  BaseType value;

public:
  ConstantTrait(BaseType value) : Trait(), value{value} {};

  Trait *clone() const override { return new ConstantTrait(value); };

  ~ConstantTrait(){};

  std::optional<BaseType> doEval(const ContractState & /*cs*/,
                                 BaseType /*val*/) override {
    return value;
  };
};

class ClampedShiftTrait : public Trait {
private:
  bool pos; // Is it a positive shift
  BaseType value;

public:
  ClampedShiftTrait(bool pos, BaseType value)
      : Trait(), pos{pos}, value{value} {};

  Trait *clone() const override { return new ClampedShiftTrait(pos, value); };

  ~ClampedShiftTrait(){};

  std::optional<BaseType> doEval(const ContractState & /*cs*/,
                                 BaseType val) override {
    BaseType posRet = std::cmp_less<BaseType, BaseType>(val + value, val)
                          ? BASETYPE_MAX
                          : val + value;
    BaseType negRet = std::cmp_less<BaseType, BaseType>(val, val - value)
                          ? BASETYPE_MIN
                          : val - value;
    return pos ? posRet : negRet;
  };
};

} // namespace trait
} // namespace evok

#endif // _EVOK_TRAITS_COMMON_HEADER_
