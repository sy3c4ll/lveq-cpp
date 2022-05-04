#ifndef PREY_H
#define PREY_H

#include "vec.h"
#include "animal.h"
#include <set>

class Prey: public Animal {
protected:
  std::set<Predator*> flee_list;
  void reproduce(world::Ecosystem ecosystem) override;
  void move(world::Ecosystem ecosystem, long duration) override;
  void metabolism(long duration) override;
public:
  static constexpr double ADULT_AGE = 10,
                          MAX_AGE = 30,
                          SIGHT = 30,
                          FLEE_RADIUS = 20,
                          METABOLISM = 7.5,
                          CRITICAL_HUNGER = 0,
                          HUNGRY_SATURATION = 30,
                          SATURATION_CONVERSION = 10,
                          FEEDING_EFFICIENCY = 0.145,
                          REPRODUCTION_CYCLE = 2,
                          MIN_OFFSPRING_NUM = 3,
                          MAX_OFFSPRING_NUM = 9,
                          MAX_OFFSPRING_OFFSET = 30,
                          DEFAULT_SIZE = 3,
                          DEFAULT_MIN_HUNGER = 10,
                          DEFAULT_MAX_HUNGER = 60,
                          DEFAULT_MIN_SATURATION = 10,
                          DEFAULT_MAX_SATURATION = 60,
                          DEFAULT_MIN_WALK = 0.8,
                          DEFAULT_MAX_WALK = 1.6,
                          DEFAULT_MIN_SPRINT = 8,
                          DEFAULT_MAX_SPRINT = 12;
  Prey(double age_val, double size_val, vec pos_val, double hunger_val, double saturation_val, double walk_val, double sprint_val);
  Prey(const Prey &prey);
  Prey();
  bool hungry() const override;
  bool danger();
  void endanger(Predator *predator);
};

#endif
