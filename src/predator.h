#ifndef PREDATOR_H
#define PREDATOR_H

#include "vec.h"
#include "animal.h"

class Predator: public Animal {
protected:
  void reproduce(world::Ecosystem ecosystem) override;
  void move(world::Ecosystem ecosystem, long duration) override;
  void metabolism(long duration) override;
public:
  static constexpr double MAX_AGE = 20,
                          SIGHT = 30,
                          METABOLISM = 5,
                          CRITICAL_HUNGER = 0,
                          HUNGRY_SATURATION = 30,
                          SATURATION_CONVERSION = 10,
                          FEEDING_EFFICIENCY = 0.165,
                          REPRODUCTION_CYCLE = 2,
                          MIN_OFFSPRING_NUM = 1,
                          MAX_OFFSPRING_NUM = 9,
                          MAX_OFFSPRING_OFFSET = 30,
                          DEFAULT_SIZE = 3,
                          DEFAULT_MIN_HUNGER = 10,
                          DEFAULT_MAX_HUNGER = 40,
                          DEFAULT_MIN_SATURATION = 10,
                          DEFAULT_MAX_SATURATION = 40,
                          DEFAULT_MIN_WALK = 0.4,
                          DEFAULT_MAX_WALK = 0.8,
                          DEFAULT_MIN_SPRINT = 4,
                          DEFAULT_MAX_SPRINT = 6;
  Predator(double age_val, double size_val, vec pos_val, double hunger_val, double saturation_val, double walk_val, double sprint_val);
  Predator(const Predator &predator);
  Predator();
  bool hungry() const override;
};

#endif
