#ifndef VEC_H
#define VEC_H

class vec {
public:
  static const vec zero, e1, e2;

  double x, y;

  vec(double x_val, double y_val);
  vec(const vec &a);
  vec();
  vec *clone() const;
  void set(double x_val, double y_val);
  void set(const vec &a);

  void add(const vec &a);
  void add(double x_val, double y_val);
  void sub(const vec &a);
  void sub(double x_val, double y_val);
  void mul(double k);
  void div(double k);
  double dot(const vec &a) const;
  double mag() const;
  double magsq() const;
  double dist(const vec &a) const;
  double dist(double x_val, double y_val) const;
  double distsq(const vec &a) const;
  double distsq(double x_val, double y_val) const;
  void norm();
  void resize(double m);
  void limit(double m);
  void direct(const vec &a);
  void direct(double x_val, double y_val);

  static vec random();
  static vec add(const vec &a, const vec &b);
  static vec sub(const vec &a, const vec &b);
  static vec mul(const vec &a, double k);
  static vec div(const vec &a, double k);
  static double dot(const vec &a, const vec &b);
  static double mag(const vec &a);
  static double magsq(const vec &a);
  static double dist(const vec &a, const vec &b);
  static double distsq(const vec &a, const vec &b);
  static vec norm(const vec &a);
  static vec resize(const vec &a, double m);
  static vec limit(const vec &a, double m);
  static vec direct(const vec &a, const vec &b);
  
  vec operator+(const vec &a) const;
  vec operator-(const vec &a) const;
  vec operator*(double k) const;
  double operator*(const vec &a) const;
  vec operator/(double k) const;
  bool operator==(const vec &a) const;
  vec &operator+=(const vec &a);
  vec &operator-=(const vec &a);
  vec &operator*=(double k);
  vec &operator/=(double k);
};

#endif
