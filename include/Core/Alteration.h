#ifndef _CORE_ALTERATION_HEADER_
#define _CORE_ALTERATION_HEADER_

#include "BaseType.h"
#include "Field.h"

#include <vector>
#include <optional>

struct Alteration;
using MaybeAlteration = std::optional<Alteration>;
using Alterations = std::vector<Alteration>;

enum class AlterationType : uint8_t {
  PosShift, NegShift, Set, Alter, Equip, Created, Reload
};

struct Alteration {
    AlterationType type;
    Field field = Field::Undef;
    BaseType value = 0;
};

#endif // _CORE_ALTERATION_HEADER_
