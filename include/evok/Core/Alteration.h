#ifndef _EVOK_CORE_ALTERATION_HEADER_
#define _EVOK_CORE_ALTERATION_HEADER_

#include "BaseType.h"
#include "Field.h"

#include <optional>
#include <vector>

namespace evok {

struct Alteration;
using MaybeAlteration = std::optional<Alteration>;
using Alterations = std::vector<Alteration>;

// This should be easy to extend (may be auto-generated)
enum class AlterationType : uint8_t {
  Alter,
  Equip,
  Created,
  Reload, // Core
  PosShift,
  NegShift,
  Set // Extended
};

struct Alteration {
  AlterationType type;
  Field field = Field::Undef;
  BaseType value = 0;
};

} // namespace evok

#endif // _EVOK_CORE_ALTERATION_HEADER_
