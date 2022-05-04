#include "plant.h"

Plant::Plant(double age_val, vec pos_val):
  Life(age_val, DEFAULT_SIZE, pos_val, vec::zero) {}
Plant::Plant(const Plant &plant):
  Plant(plant.age, plant.pos) {}
Plant::Plant():
  Plant(world::randomlf(EDIBLE_AGE, DEFAULT_MAX_AGE), {world::randomlf(0, world::WIDTH), world::randomlf(0, world::HEIGHT)}) {}
bool Plant::isEdible() const {
  return age >= EDIBLE_AGE;
}
double Plant::getSaturation() const {
  return age * SATURATION_PER_AGE;
}
void Plant::die() {
  age = 0;
}
