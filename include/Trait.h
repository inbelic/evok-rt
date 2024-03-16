#ifndef _TRAIT_HEADER_
#define _TRAIT_HEADER_

#include "BaseType.h"
#include "ContractState.h"
#include "Field.h"

#include <optional>

#include <memory>
// Temporary pointer of a Trait. TODO: Will implement an arena allocater and
// TraitPtr will be an index in the arena.
class Trait;
using TraitPtr = std::unique_ptr<Trait>;

class Trait {
private:
    TraitPtr next = nullptr;

protected:
    virtual std::optional<BaseType> doEval(const ContractState&, BaseType) = 0;

public:
    virtual ~Trait() {};

    // Evaluation
    std::optional<BaseType> eval(const ContractState& cs) {
        return eval(cs, 0);
    }
    std::optional<BaseType> eval(const ContractState& cs, BaseType val) {
        return doEval(cs, val).and_then([&](BaseType x) {
            return !next ? next->eval(cs, x) : std::optional<BaseType>(x);
        });
    }

    // Modify the trait by appending another trait to the chain
    void modify(TraitPtr _next) { next = std::move(_next); }
};

#endif // _TRAIT_HEADER_
