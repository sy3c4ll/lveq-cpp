#ifndef PLANT_H
#define PLANT_H

#include "vec.h"
#include "life.h"

class Plant: public Life {
public:
  static constexpr double EDIBLE_AGE = 0.001,
                          SATURATION_PER_AGE = 10000,
                          DEFAULT_MAX_AGE = 0.01,
                          DEFAULT_SIZE = 2.5;
  Plant(double age_val, vec pos_val);
  Plant(const Plant &plant);
  Plant();
  bool isEdible() const;
  double getSaturation() const;
  void die();
};

#endif
