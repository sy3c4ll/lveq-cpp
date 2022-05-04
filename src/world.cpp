#include "world.h"
#include "predator.h"
#include "prey.h"
#include "plant.h"
#include <ctime>
#include <cmath>

long world::ticks() {
  return clock();
}
double world::hours(long t) {
  return t / (CLOCKS_PER_SEC * RSECS_PER_HOUR);
}
double world::days(long t) {
  return t / (CLOCKS_PER_SEC * RSECS_PER_HOUR * HOURS_PER_DAY);
}
double world::years(long t) {
  return t / (CLOCKS_PER_SEC * RSECS_PER_HOUR * HOURS_PER_YEAR);
}
int world::randomi(int min, int max) {
  return rand() % (max - min + 1) + min;
}
double world::randomlf(double min, double max) {
  return (double)rand() / RAND_MAX * (max - min) + min;
}
