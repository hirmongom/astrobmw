#pragma once

#include <iostream>
#include <array>
#include <cmath>

namespace vect
{

inline void print_vec (const char *name, const std::array<double, 3> &v)
{
	std::cout << name << " = [ "
	          << v[0] << ", "
	          << v[1] << ", "
	          << v[2] << " ]\n";
} // print_vec()

inline void print_scalar (const char *name, double value)
{
	std::cout << name << " = "
	          << value << "\n";
} // print_scalar()

inline double magnitude (const std::array<double, 3> &vec)
{
  return std::sqrt(
    vec[0] * vec[0] +
    vec[1] * vec[1] +
    vec[2] * vec[2]
  );
} // magnitude()

inline std::array<double, 3> scalar_product (const std::array<double, 3> &vec, double scalar)
{
  return {
    vec[0] * scalar,
    vec[1] * scalar,
    vec[2] * scalar
  };
} // scalar_product()

inline std::array<double, 3> scalar_division (const std::array<double, 3> &vec, double scalar)
{
  return {
    vec[0] / scalar,
    vec[1] / scalar,
    vec[2] / scalar
  };
} // scalar_division()

inline std::array<double, 3> subtraction (
  const std::array<double, 3> &a, 
  const std::array<double, 3> &b)
{
  return {
    a[0] - b[0],
    a[1] - b[1],
    a[2] - b[2]
  };
} // subtraction()

inline double dot_product (const std::array<double, 3> &a, const std::array<double, 3> &b)
{
  return 
    a[0] * b[0] +
    a[1] * b[1] +
    a[2] * b[2];
} // dot_product()

inline std::array<double, 3> cross_product 
  (const std::array<double, 3> &a, const std::array<double, 3> &b)
{
  return {
    a[1] * b[2] - a[2] * b[1],
    a[2] * b[0] - a[0] * b[2],
    a[0] * b[1] - a[1] * b[0]
  };
} // cross_product()

} // vect namespace
