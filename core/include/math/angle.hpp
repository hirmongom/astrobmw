#pragma once


#include <numbers>
#include <iosfwd>


namespace math::angle
{


constexpr double rad2deg_mod = 180.0 / std::numbers::pi;
constexpr double deg2rad_mod = std::numbers::pi / 180.0;

/**************************************************************************************************/
constexpr double rad2deg(double radians)
{
  return radians * rad2deg_mod;
} // rad2deg()

/**************************************************************************************************/
constexpr double deg2rad(double degrees)
{
  return degrees * deg2rad_mod;
} // deg2rad()

/**************************************************************************************************/
constexpr double quadrantCorrection(double reference, double angleFromACos)
{
  return (reference <= 0.0) ? (2.0 * std::numbers::pi - angleFromACos) : angleFromACos;
} // quadrantCorrection()

/* Stream Manipulators ****************************************************************************/
/**************************************************************************************************/
enum class Unit : long
{
  Radian = 0,
  Degree = 1
};

inline int unitIndex()
{
  static const int idx = std::ios_base::xalloc();
  return idx;
}

inline std::ostream &rad(std::ostream &os)
{
  os.iword(unitIndex()) = static_cast<long>(Unit::Radian);
  return os;
}

inline std::ostream &deg(std::ostream &os)
{
  os.iword(unitIndex()) = static_cast<long>(Unit::Degree);
  return os;
}

inline Unit getUnit(std::ostream &os)
{
  return static_cast<Unit>(os.iword(unitIndex()));
}


} // namespace math::angle
