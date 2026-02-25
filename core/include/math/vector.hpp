#pragma once


#include <cassert>

#include <array>
#include <cmath>
#include <string>

#include <sstream>
#include <iomanip>


namespace math::vector
{


/**************************************************************************************************/
inline std::string toString(const std::array<double, 3> &vec)
{
  std::ostringstream ss;
  ss << std::fixed << std::setprecision(10);

  ss << "[ "
     << vec[0] << ", "
     << vec[1] << ", "
     << vec[2] << " ]";

  return ss.str();
} // toString()

/**************************************************************************************************/
constexpr double magnitude(const std::array<double, 3> &vec)
{
  return std::sqrt(
    vec[0] * vec[0] +
    vec[1] * vec[1] +
    vec[2] * vec[2]
  );
} // magnitude()

/**************************************************************************************************/
constexpr std::array<double, 3> scale(const std::array<double, 3> &vec, double scalar)
{
  return {
    vec[0] * scalar,
    vec[1] * scalar,
    vec[2] * scalar
  };
} // scale()

/**************************************************************************************************/
constexpr std::array<double, 3> scaleInv(const std::array<double, 3> &vec, double scalar)
{
  return {
    vec[0] / scalar,
    vec[1] / scalar,
    vec[2] / scalar
  };
} // scaleInv()

/**************************************************************************************************/
constexpr std::array<double, 3> sub(const std::array<double, 3> &a, const std::array<double, 3> &b)
{
  return {
    a[0] - b[0],
    a[1] - b[1],
    a[2] - b[2]
  };
} // sub()

/**************************************************************************************************/
constexpr double dot(const std::array<double, 3> &a, const std::array<double, 3> &b)
{
  return 
    a[0] * b[0] +
    a[1] * b[1] +
    a[2] * b[2];
} // dot()

/**************************************************************************************************/
constexpr std::array<double, 3> cross
  (const std::array<double, 3> &a, const std::array<double, 3> &b)
{
  return {
    a[1] * b[2] - a[2] * b[1],
    a[2] * b[0] - a[0] * b[2],
    a[0] * b[1] - a[1] * b[0]
  };
} // cross()

/**************************************************************************************************/
constexpr std::array<double, 3> normalize (const std::array<double, 3> &vec, double mag)
{
  assert(std::abs(mag) > 1e-15);

  return scaleInv(vec, mag);
} // normalize()

/**************************************************************************************************/
constexpr std::array<double, 3> normalize(const std::array<double, 3> &vec)
{
  const double mag = magnitude(vec);
  assert(std::abs(mag) > 1e-15);
  
  return normalize(vec, mag);
} // normalize()


} // namespace math::vector
