#include "life.h"
#include <algorithm>

double _det(vec a, vec b) {
  return a.x * b.y - a.y * b.x;
}
double _point_segment_distance(vec p, vec a1, vec a2) {
  if (a1 == a2)
    return vec::mag(p - a1);
  double t = (p - a1) * (a2 - a1) / vec::magsq(a2 - a1);
  if (t < 0)
    return vec::mag(p - a1);
  else if (t > 1)
    return vec::mag(p - a2);
  else
    return vec::mag(p - (a1 + (a2 - a1) * t));
}
bool _segments_intersect(vec a1, vec a2, vec b1, vec b2) {
  double d = _det(a2 - a1, b2 - b1);
  if (d == 0)
    return false;
  double s = _det(a2 - a1, a1 - b1) / d,
         t = _det(b2 - b1, a1 - b1) / -d;
  return 0 <= s && s <= 1 && 0 <= t && t <= 1;
}
double _segments_distance(vec a1, vec a2, vec b1, vec b2) {
  if (_segments_intersect(a1, a2, b1, b2))
    return 0;
  else
    return std::min({_point_segment_distance(a1, b1, b2),
                     _point_segment_distance(a2, b1, b2),
                     _point_segment_distance(b1, a1, a2),
                     _point_segment_distance(b2, a1, a2)});
}

Life::Life(double age_val, double size_val, vec pos_val, vec vel_val):
  age(age_val), size(size_val), pos(pos_val), vel(vel_val), alive(true), clock(world::ticks()) {}
Life::Life(const Life &life):
  age(life.age), size(life.size), pos(life.pos), vel(life.vel), alive(true), clock(world::ticks()) {}
double Life::getAge() const {
  return age;
}
double Life::getSize() const {
  return size;
}
vec Life::getPos() const {
  return pos;
}
vec Life::getVel() const {
  return vel;
}
bool Life::isAlive() const {
  return alive;
}
long Life::getClock() const {
  return clock;
}
void Life::die() {
  alive = false;
}
bool Life::detectCollisionX() const {
  return pos.x < size || pos.x > world::WIDTH - size;
}
bool Life::detectCollisionY() const {
  return pos.y < size || pos.y > world::HEIGHT - size;
}
bool Life::detectCollision(const Life &a, long duration) const {
  return _segments_distance(pos, pos - vel * world::hours(duration), a.getPos(), a.getPos() - a.getVel() * world::hours(duration)) < size + a.getSize();
}
void Life::update(world::Ecosystem &ecosystem, long duration) {
  if (!alive)
    return;
  pos += (vel * world::hours(duration));
  age += world::years(duration);
  if (detectCollisionX()) {
    pos.x = std::min(std::max(pos.x, size), world::WIDTH - size);
    vel.x = -vel.x;
  }
  if (detectCollisionY()) {
    pos.y = std::min(std::max(pos.y, size), world::HEIGHT - size);
    vel.y = -vel.y;
  }
  clock += duration;
}
