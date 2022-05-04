#ifndef LIFE_H
#define LIFE_H

#include "vec.h"
#include "world.h"

class Life {
protected:
  double age, size;
  vec pos, vel;
  bool alive;
  long clock;
public:
  Life(double age_val, double size_val, vec pos_val, vec vel_val);
  Life(const Life &life);
  double getAge() const;
  double getSize() const;
  vec getPos() const;
  vec getVel() const;
  bool isAlive() const;
  long getClock() const;
  void die();
  bool detectCollisionX() const;
  bool detectCollisionY() const;
  bool detectCollision(const Life &a, long duration) const;
  virtual void update(world::Ecosystem &ecosystem, long duration);
};

#endif
