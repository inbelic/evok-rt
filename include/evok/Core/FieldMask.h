#ifndef _EVOK_CORE_FIELDMASK_HEADER_
#define _EVOK_CORE_FIELDMASK_HEADER_

namespace evok {

// This file *will* be auto-generated

#include "BaseType.h"
#include "Field.h"

using FieldMask = uint8_t;
const uint8_t NUM_FIELDS = 2;
const FieldMask baseMask = 3;

Field FIELDS[NUM_FIELDS] = {Field::SetID, Field::ContractID};

uint8_t fieldID(Field field) {
  switch (field) {
  case Field::Undef:
    return ~0;
  case Field::SetID:
    return 0;
  case Field::ContractID:
    return 1;
  }
}

FieldMask setField(FieldMask mask, Field field) {
  if (field == Field::Undef)
    return mask;
  return mask | (1 << fieldID(field));
}

FieldMask clearField(FieldMask mask, Field field) {
  if (field == Field::Undef)
    return mask;
  return mask & ~(1 << fieldID(field));
}

bool isFieldSet(FieldMask mask, Field field) {
  return mask & (1 << fieldID(field));
}

} // namespace evok

#endif // _EVOK_CORE_FIELDMASK_HEADER_
