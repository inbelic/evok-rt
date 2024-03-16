#ifndef _ALTERATION_HEADER_
#define _ALTERATION_HEADER_

#include "BaseType.h"
#include "Field.h"

#include <vector>

struct Alteration;
using Alterations = std::vector<Alteration>;

enum class AlterationType : uint8_t {
    Alter, Reload
};

struct Alteration {
    AlterationType type;
    Field field = Field::Undef;
    BaseType value = 0;
};

#endif // _ALTERATION_HEADER_
