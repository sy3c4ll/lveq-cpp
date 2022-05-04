#include "vec.h"
#include <cmath>

const vec vec::zero(0, 0), vec::e1(1, 0), vec::e2(0, 1);

vec::vec(double x_val, double y_val): x(x_val), y(y_val) {}
vec::vec(const vec &a): x(a.x), y(a.y) {}
vec::vec(): x(0), y(0) {}
vec *vec::clone() const {
  return new vec(*this);
}
void vec::set(double x_val, double y_val) {
  x = x_val, y = y_val;
}
void vec::set(const vec &a) {
  x = a.x, y = a.y;
}

void vec::add(const vec &a) {
  x += a.x, y += a.y;
}
void vec::add(double x_val, double y_val) {
  x += x_val, y += y_val;
}
void vec::sub(const vec &a) {
  x -= a.x, y -= a.y;
}
void vec::sub(double x_val, double y_val) {
  x -= x_val, y -= y_val;
}
void vec::mul(double k) {
  x *= k, y *= k;
}
void vec::div(double k) {
  x /= k, y /= k;
}
double vec::dot(const vec &a) const {
  return x * a.x + y * a.y;
}
double vec::mag() const {
  return sqrt(x * x + y * y);
}
double vec::magsq() const {
  return x * x + y * y;
}
double vec::dist(const vec &a) const {
  return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
}
double vec::dist(double x_val, double y_val) const {
  return sqrt((x - x_val) * (x - x_val) + (y - y_val) * (y - y_val));
}
double vec::distsq(const vec &a) const {
  return (x - a.x) * (x - a.x) + (y - a.y) * (y - a.y);
}
double vec::distsq(double x_val, double y_val) const {
  return (x - x_val) * (x - x_val) + (y - y_val) * (y - y_val);
}
void vec::norm() {
  double r = 1 / mag();
  x *= r, y *= r;
}
void vec::resize(double m) {
  double r = m / mag();
  x *= r, y *= r;
}
void vec::limit(double m) {
  if (mag() > m)
    resize(m);
}
void vec::direct(const vec &a) {
  double r = mag() / mag(a);
  x = a.x * r, y = a.y * r;
}
void vec::direct(double x_val, double y_val) {
  double r = mag() / sqrt(x_val * x_val + y_val * y_val);
  x = x_val * r, y = y_val * r;
}

vec vec::random() {
  return vec((double)rand() / RAND_MAX * 2 - 1, (double)rand() / RAND_MAX * 2 - 1);
}
vec vec::add(const vec &a, const vec &b) {
  return vec(a.x + b.x, a.y + b.y);
}
vec vec::sub(const vec &a, const vec &b) {
  return vec(a.x - b.x, a.y - b.y);
}
vec vec::mul(const vec &a, double k) {
  return vec(a.x * k, a.y * k);
}
vec vec::div(const vec &a, double k) {
  return vec(a.x / k, a.y / k);
}
double vec::dot(const vec &a, const vec &b) {
  return a.x * b.x + a.y * b.y;
}
double vec::mag(const vec &a) {
  return sqrt(a.x * a.x + a.y * a.y);
}
double vec::magsq(const vec &a) {
  return a.x * a.x + a.y * a.y;
}
double vec::dist(const vec &a, const vec &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double vec::distsq(const vec &a, const vec &b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
vec vec::norm(const vec &a) {
  double r = 1 / mag(a);
  return vec(a.x * r, a.y * r);
}
vec vec::resize(const vec &a, double m) {
  double r = m / mag(a);
  return vec(a.x * r, a.y * r);
}
vec vec::limit(const vec &a, double m) {
  if (mag(a) > m)
    return resize(a, m);
  else
    return a;
}
vec vec::direct(const vec &a, const vec &b) {
  double r = mag(a) / mag(b);
  return vec(b.x * r, b.y * r);
}

vec vec::operator+(const vec &a) const {
  return vec(x + a.x, y + a.y);
}
vec vec::operator-(const vec &a) const {
  return vec(x - a.x, y - a.y);
}
vec vec::operator*(double k) const {
  return vec(x * k, y * k);
}
double vec::operator*(const vec &a) const {
  return x * a.x + y * a.y;
}
vec vec::operator/(double k) const {
  return vec(x / k, y / k);
}
bool vec::operator==(const vec &a) const {
  return (x == a.x) && (y == a.y);
}
vec &vec::operator+=(const vec &a) {
  x += a.x, y += a.y;
  return *this;
}
vec &vec::operator-=(const vec &a) {
  x -= a.x, y -= a.y;
  return *this;
}
vec &vec::operator*=(double k) {
  x *= k, y *= k;
  return *this;
}
vec &vec::operator/=(double k) {
  x /= k, y /= k;
  return *this;
}
