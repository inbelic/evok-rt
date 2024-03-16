#ifndef _CORE_CONTRACTSTATE_HEADER_
#define _CORE_CONTRACTSTATE_HEADER_

#include "BaseType.h"
#include "Field.h"

#include <map>

using TraitState = std::map<Field, BaseType>;

struct ContractState {
    std::map<ID, TraitState> &ts;
};

#endif // _CORE_CONTRACTSTATE_HEADER_
