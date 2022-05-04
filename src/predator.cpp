#include "predator.h"
#include "world.h"
#include "life.h"
#include "prey.h"
#include <cmath>

Predator::Predator(double age_val, double size_val, vec pos_val, double hunger_val, double saturation_val, double walk_val, double sprint_val):
  Animal(age_val, size_val, pos_val, hunger_val, saturation_val, walk_val, sprint_val) {}
Predator::Predator(const Predator &predator):
  Predator(predator.age, predator.size, predator.pos, predator.hunger, predator.saturation, predator.walk, predator.sprint) {}
Predator::Predator():
  Predator(world::randomlf(0, MAX_AGE), DEFAULT_SIZE, {world::randomlf(0, world::WIDTH), world::randomlf(0, world::HEIGHT)}, world::randomlf(DEFAULT_MIN_HUNGER, DEFAULT_MAX_HUNGER), world::randomlf(DEFAULT_MIN_SATURATION, DEFAULT_MAX_SATURATION), world::randomlf(DEFAULT_MIN_WALK, DEFAULT_MAX_WALK), world::randomlf(DEFAULT_MIN_SPRINT, DEFAULT_MAX_SPRINT)) {}
bool Predator::hungry() const {
  return saturation <= HUNGRY_SATURATION;
}
void Predator::reproduce(world::Ecosystem ecosystem) {
  static int next_reproduction_age = REPRODUCTION_CYCLE;
  if (age >= next_reproduction_age && !hungry()) {
    int offspring_num = world::randomi(MIN_OFFSPRING_NUM, MAX_OFFSPRING_NUM);
    for (Predator *predator: ecosystem.predators) {
      if (!predator->isAlive()) {
        *predator = Predator(0, DEFAULT_SIZE, pos + vec::resize(vec::random(), world::randomlf(0, MAX_OFFSPRING_OFFSET)), world::randomlf(DEFAULT_MIN_HUNGER, DEFAULT_MAX_HUNGER), world::randomlf(DEFAULT_MIN_SATURATION, DEFAULT_MAX_SATURATION), world::randomlf(DEFAULT_MIN_WALK, DEFAULT_MAX_WALK), world::randomlf(DEFAULT_MIN_SPRINT, DEFAULT_MAX_SPRINT));
        --offspring_num;
      }
      if (!offspring_num)
        break;
    }
    while (offspring_num--)
      ecosystem.predators.emplace_back(new Predator(0, DEFAULT_SIZE, pos + vec::resize(vec::random(), world::randomlf(0, MAX_OFFSPRING_OFFSET)), world::randomlf(DEFAULT_MIN_HUNGER, DEFAULT_MAX_HUNGER), world::randomlf(DEFAULT_MIN_SATURATION, DEFAULT_MAX_SATURATION), world::randomlf(DEFAULT_MIN_WALK, DEFAULT_MAX_WALK), world::randomlf(DEFAULT_MIN_SPRINT, DEFAULT_MAX_SPRINT)));
    next_reproduction_age += REPRODUCTION_CYCLE;
  }
}
void Predator::move(world::Ecosystem ecosystem, long duration) {
  if (hungry() && ecosystem.preys.size() > 0) {
    Prey *nearest = ecosystem.preys[0];
    for (Prey *prey: ecosystem.preys)
      if (prey->isAlive()) {
        if (pos.distsq(prey->getPos()) < pos.distsq(nearest->getPos()))
          nearest = prey;
        if (pos.distsq(prey->getPos()) < Prey::FLEE_RADIUS * Prey::FLEE_RADIUS)
          prey->endanger(this);
      }
    if (detectCollision(*nearest, duration)) {
      saturation += nearest->getSaturation() * FEEDING_EFFICIENCY;
      nearest->die();
    } else if (pos.distsq(nearest->getPos()) < SIGHT * SIGHT) {
      vel.direct(nearest->getPos() - pos);
      vel.resize(sprint);
    }
  } else
    vel.resize(walk);
}
void Predator::metabolism(long duration) {
  if (saturation > 0) {
    saturation -= SATURATION_CONVERSION * world::days(duration);
    hunger += SATURATION_CONVERSION * world::days(duration);
  }
  hunger -= METABOLISM * world::days(duration);
  if (hunger < CRITICAL_HUNGER)
    die();
}
