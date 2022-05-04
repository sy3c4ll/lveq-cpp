#include "animal.h"

Animal::Animal(double age_val, double size_val, vec pos_val, double hunger_val, double saturation_val, double walk_val, double sprint_val):
  Life(age_val, size_val, pos_val, vec::random()), hunger(hunger_val), saturation(saturation_val), walk(walk_val), sprint(sprint_val) {
    vel.resize(walk);
  }
Animal::Animal(const Animal &animal):
  Animal(animal.age, animal.size, animal.pos, animal.hunger, animal.saturation, animal.walk, animal.sprint) {}
double Animal::getHunger() const {
  return hunger;
}
double Animal::getSaturation() const {
  return saturation;
}
double Animal::getWalkSpeed() const {
  return walk;
}
double Animal::getSprintSpeed() const {
  return sprint;
}
void Animal::update(world::Ecosystem &ecosystem, long duration) {
  Life::update(ecosystem, duration);
  reproduce(ecosystem);
  move(ecosystem, duration);
  metabolism(duration);
}
