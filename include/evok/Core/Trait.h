#ifndef _EVOK_CORE_TRAIT_HEADER_
#define _EVOK_CORE_TRAIT_HEADER_

#include "BaseType.h"
#include "ContractState.h"
#include "Field.h"

#include <optional>

#include <memory>
#include <unordered_set>

namespace evok {

class Trait;
using TraitPtr = Trait *;
using TraitSet = std::unordered_set<TraitPtr>;

class Trait {
private:
  TraitPtr next = nullptr;

protected:
  Trait(){};

  virtual std::optional<BaseType> doEval(const ContractState &, BaseType) = 0;

public:
  virtual ~Trait(){};

  virtual TraitPtr clone() const = 0;

  // Evaluation
  std::optional<BaseType> eval(const ContractState &cs) { return eval(cs, 0); }
  std::optional<BaseType> eval(const ContractState &cs, BaseType val) {
    return next
      ? next->eval(cs, val).and_then([&](BaseType x) { return doEval(cs, x); })
      : doEval(cs, val);
  }

  // Modify the trait by appending another trait to the chain
  void modify(TraitPtr _next) {
    next = _next;
  }

  // Mark this trait as currently being used
  void mark(TraitSet &marked) {
    marked.insert(this);
    if (next) next->mark(marked);
  }
};

} // namespace evok

#endif // _EVOK_CORE_TRAIT_HEADER_
