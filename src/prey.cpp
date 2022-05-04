#include "prey.h"
#include "world.h"
#include "life.h"
#include "predator.h"
#include "plant.h"
#include <set>

Prey::Prey(double age_val, double size_val, vec pos_val, double hunger_val, double saturation_val, double walk_val, double sprint_val):
  Animal(age_val, size_val, pos_val, hunger_val, saturation_val, walk_val, sprint_val) {}
Prey::Prey(const Prey &prey):
  Prey(prey.age, prey.size, prey.pos, prey.hunger, prey.saturation, prey.walk, prey.sprint) {}
Prey::Prey():
  Prey(world::randomlf(0, MAX_AGE), DEFAULT_SIZE, {world::randomlf(0, world::WIDTH), world::randomlf(0, world::HEIGHT)}, world::randomlf(DEFAULT_MIN_HUNGER, DEFAULT_MAX_HUNGER), world::randomlf(DEFAULT_MIN_SATURATION, DEFAULT_MAX_SATURATION), world::randomlf(DEFAULT_MIN_WALK, DEFAULT_MAX_WALK), world::randomlf(DEFAULT_MIN_SPRINT, DEFAULT_MAX_SPRINT)) {}
bool Prey::hungry() const {
  return saturation <= HUNGRY_SATURATION;
}
bool Prey::danger() {
  for (auto predator = flee_list.begin(); predator != flee_list.end();)
    if ((*predator)->isAlive() && (*predator)->hungry() && vec::dist(pos, (*predator)->getPos()) <= FLEE_RADIUS)
      ++predator;
    else
      predator = flee_list.erase(predator);
  return !flee_list.empty();
}
void Prey::endanger(Predator *predator) {
  flee_list.insert(predator);
}
void Prey::reproduce(world::Ecosystem ecosystem) {
  static int next_reproduction_age = REPRODUCTION_CYCLE;
  if (age >= next_reproduction_age && !hungry()) {
    int offspring_num = world::randomi(MIN_OFFSPRING_NUM, MAX_OFFSPRING_NUM);
    for (Prey *prey: ecosystem.preys) {
      if (!prey->isAlive()) {
        *prey = Prey(0, DEFAULT_SIZE, pos + vec::resize(vec::random(), world::randomlf(0, MAX_OFFSPRING_OFFSET)), world::randomlf(DEFAULT_MIN_HUNGER, DEFAULT_MAX_HUNGER), world::randomlf(DEFAULT_MIN_SATURATION, DEFAULT_MAX_SATURATION), world::randomlf(DEFAULT_MIN_WALK, DEFAULT_MAX_WALK), world::randomlf(DEFAULT_MIN_SPRINT, DEFAULT_MAX_SPRINT));
        --offspring_num;
      }
      if (!offspring_num)
        break;
    }
    while (offspring_num--)
      ecosystem.preys.emplace_back(new Prey(0, DEFAULT_SIZE, pos + vec::resize(vec::random(), world::randomlf(0, MAX_OFFSPRING_OFFSET)), world::randomlf(DEFAULT_MIN_HUNGER, DEFAULT_MAX_HUNGER), world::randomlf(DEFAULT_MIN_SATURATION, DEFAULT_MAX_SATURATION), world::randomlf(DEFAULT_MIN_WALK, DEFAULT_MAX_WALK), world::randomlf(DEFAULT_MIN_SPRINT, DEFAULT_MAX_SPRINT)));
    next_reproduction_age += REPRODUCTION_CYCLE;
  }
}
void Prey::move(world::Ecosystem ecosystem, long duration) {
  if (hungry() && !danger() && ecosystem.plants.size() > 0) {
    Plant *nearest = ecosystem.plants[0];
    for (Plant *plant: ecosystem.plants)
      if (plant->isEdible() && pos.distsq(plant->getPos()) < pos.distsq(nearest->getPos()))
        nearest = plant;
    if (detectCollision(*nearest, duration)) {
      saturation += nearest->getSaturation() * FEEDING_EFFICIENCY;
      nearest->die();
    } else if (pos.distsq(nearest->getPos()) < SIGHT * SIGHT) {
      vel.direct(nearest->getPos() - pos);
      vel.resize(sprint);
    }
  } else if (danger()) {
    vec direction;
    for (Predator *predator: flee_list)
      direction += pos - predator->getPos();
    vel.direct(direction);
    vel.resize(sprint);
  } else
    vel.resize(walk);
}
void Prey::metabolism(long duration) {
  if (saturation > 0) {
    saturation -= SATURATION_CONVERSION * world::days(duration);
    hunger += SATURATION_CONVERSION * world::days(duration);
  }
  hunger -= METABOLISM * world::days(duration);
  if (hunger < CRITICAL_HUNGER)
    die();
}
