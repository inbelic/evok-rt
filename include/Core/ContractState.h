#ifndef _CORE_CONTRACTSTATE_HEADER_
#define _CORE_CONTRACTSTATE_HEADER_

#include "BaseType.h"
#include "Field.h"
#include "History.h"

#include <map>

using TraitState = std::map<Field, BaseType>;

struct ContractState {
  std::map<ID, TraitState> ts;
  const History *history;

  void insert(ID id, Field field, BaseType val) {
    // Retreive the current TraitState of the id
    auto search_ts = ts.find(id);
    TraitState traits;
    if (search_ts != ts.end())
      traits = search_ts->second;

    // Insert the evaluated value to the field
    traits[field] = val;
    // Replace the current TraitState with the updated one
    ts.insert_or_assign(id, traits);
  };
};

#endif // _CORE_CONTRACTSTATE_HEADER_
