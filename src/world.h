#ifndef WORLD_H
#define WORLD_H

#include <vector>

class Predator;
class Prey;
class Plant;
namespace world {
  constexpr double WIDTH = 1000,
                   HEIGHT = 1000,
                   RSECS_PER_HOUR = 0.5,
                   HOURS_PER_DAY = 24,
                   HOURS_PER_YEAR = 8760;
  long ticks();
  double hours(long t);
  double days(long t);
  double years(long t);
  int randomi(int min, int max);
  double randomlf(double min, double max);
  typedef struct Ecosystem {
    std::vector<Predator*> predators;
    std::vector<Prey*> preys;
    std::vector<Plant*> plants;
  } Ecosystem;
}

#endif
