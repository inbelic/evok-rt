#ifndef _CORE_ALTERATION_HEADER_
#define _CORE_ALTERATION_HEADER_

#include "BaseType.h"
#include "Field.h"

#include <vector>
#include <optional>

struct _Alteration;
using Alteration = std::optional<_Alteration>;
using Alterations = std::vector<Alteration>;

enum class AlterationType : uint8_t {
  Shift, Set, Alter, Equip, Created, Reload
};

struct _Alteration {
    AlterationType type;
    Field field = Field::Undef;
    BaseType value = 0;
};

#endif // _CORE_ALTERATION_HEADER_
