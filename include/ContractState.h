#ifndef _CONTRACTSTATE_HEADER_
#define _CONTRACTSTATE_HEADER_

#include "BaseType.h"
#include "Field.h"

#include <map>

using TraitState = std::map<Field, BaseType>;

struct ContractState {
    std::map<ID, TraitState> &ts;
};

#endif // _CONTRACTSTATE_HEADER_
