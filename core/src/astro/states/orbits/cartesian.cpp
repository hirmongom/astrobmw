#include <astro/states/orbits/cartesian.hpp>

#include <math/vector.hpp>

#include <array>
#include <string>

#include <ostream>
#include <sstream>
#include <iomanip>


using namespace astro::states::orbits;


/**************************************************************************************************/
Cartesian::Cartesian(const std::array<double, 3> &r, const std::array<double, 3> &v)
  : position_vector(r)
  , velocity_vector(v)
{}

/**************************************************************************************************/
const std::array<double, 3> &Cartesian::r() const
{
  return position_vector;
}

/**************************************************************************************************/
const std::array<double, 3> &Cartesian::v() const
{
  return velocity_vector;
}

/**************************************************************************************************/
std::string Cartesian::toString() const
{
  std::ostringstream ss;
  ss << *this;
  return ss.str();
}

/**************************************************************************************************/
std::ostream &astro::states::orbits::operator<<(std::ostream &os, const Cartesian &crt)
{
  const std::ios_base::fmtflags oldFlags = os.flags();
  const std::streamsize oldPrecision = os.precision();

  os << std::fixed << std::setprecision(10);

  os << "Position Vector: "
     << math::vector::toString(crt.position_vector) << " km\n"
     << "Velocity Vector: "
     << math::vector::toString(crt.velocity_vector) << " km/s";

  os.flags(oldFlags);
  os.precision(oldPrecision);

  return os;
}
