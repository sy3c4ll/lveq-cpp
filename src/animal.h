#ifndef ANIMAL_H
#define ANIMAL_H

#include "vec.h"
#include "life.h"

class Animal: public Life {
protected:
  double hunger, saturation, walk, sprint;
  virtual void reproduce(world::Ecosystem ecosystem) = 0;
  virtual void move(world::Ecosystem ecosystem, long duration) = 0;
  virtual void metabolism(long duration) = 0;
public:
  Animal(double age_val, double size_val, vec pos_val, double hunger_val, double saturation_val, double walk_val, double sprint_val);
  Animal(const Animal &animal);
  double getHunger() const;
  double getSaturation() const;
  double getWalkSpeed() const ;
  double getSprintSpeed() const;
  virtual bool hungry() const = 0;
  void update(world::Ecosystem &ecosystem, long duration) override;
};

#endif
