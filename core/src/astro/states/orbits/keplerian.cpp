#include <astro/states/orbits/keplerian.hpp>
#include <astro/states/orbits/cartesian.hpp>

#include <astro/constants/bodies/earth.hpp>

#include <math/vector.hpp>
#include <math/angle.hpp>

#include <array>
#include <cmath>
#include <string>

#include <ios>
#include <ostream>
#include <sstream>
#include <iomanip>


using namespace astro::states::orbits;
namespace earth = astro::constants::bodies::earth;


/**************************************************************************************************/
Keplerian::Keplerian(double p, double e, double i, double Omega, 
                     double omega, double nu, double u, double l)
  : semi_latus_rectum(p)
  , eccentricity(e)
  , inclination(i)
  , raan(Omega)
  , argument_of_periapsis(omega)
  , true_anomaly(nu)
  , argument_of_latitude(u)
  , true_longitude(l)
{}

/**************************************************************************************************/
Keplerian::Keplerian(const Cartesian &crt)
{
	transitional_data data {};

	// ---------------------------------------------------------------------
	// 1. Compute magnitudes of r and v
	// ---------------------------------------------------------------------
  data.r_mag = math::vector::magnitude(crt.r());
  data.v_mag = math::vector::magnitude(crt.v());

	// ---------------------------------------------------------------------
	// 2. Compute angular momentum vector h = r × v
	// ---------------------------------------------------------------------
	data.h = math::vector::cross(crt.r(), crt.v());
	data.h_mag = math::vector::magnitude(data.h);

	// ---------------------------------------------------------------------
	// 3. Compute node vector n = k × h
	// ---------------------------------------------------------------------
  data.n = math::vector::cross({0.0, 0.0, 1.0}, data.h);
  data.n_mag = math::vector::magnitude(data.n);

	// ---------------------------------------------------------------------
	// 4. Compute eccentricity vector
	// ---------------------------------------------------------------------
  computeEccentricityVector(crt, data);

	// ---------------------------------------------------------------------
	// 5. Compute orbital elements and populate
	// ---------------------------------------------------------------------
  semi_latus_rectum = data.h_mag * data.h_mag / earth::gravitational_parameter;

  eccentricity = math::vector::magnitude(data.e);

  inclination = std::acos(data.h[2] / data.h_mag);

  raan = std::atan2(data.n[1], data.n[0]);
  if (raan < 0.0) { raan += 2.0 * std::numbers::pi; }

  argument_of_periapsis = std::acos(math::vector::dot(data.n, data.e) / (data.n_mag * eccentricity));
  argument_of_periapsis = math::angle::quadrantCorrection(data.e[2], argument_of_periapsis);

  true_anomaly = std::acos(math::vector::dot(data.e, crt.r()) / (eccentricity * data.r_mag));
  true_anomaly = math::angle::quadrantCorrection(math::vector::dot(crt.r(), crt.v()), true_anomaly);

  // argument_of_latitude = argument_of_periapsis + true_anomaly;
  argument_of_latitude = std::acos(math::vector::dot(data.n, crt.r()) / (data.n_mag * data.r_mag));
  argument_of_latitude = math::angle::quadrantCorrection(crt.r()[2], argument_of_latitude);

  true_longitude = std::fmod(raan + argument_of_latitude, 2.0 * std::numbers::pi);
}

/**************************************************************************************************/
double Keplerian::p() const
{
  return semi_latus_rectum;
}

/**************************************************************************************************/
double Keplerian::e() const
{
  return eccentricity;
}

/**************************************************************************************************/
double Keplerian::i(bool degrees) const
{
  return degrees ? math::angle::rad2deg(inclination) : inclination;
}

/**************************************************************************************************/
double Keplerian::Omega(bool degrees) const
{
  return degrees ? math::angle::rad2deg(raan) : raan;
}

/**************************************************************************************************/
double Keplerian::omega(bool degrees) const
{
  return degrees ? math::angle::rad2deg(argument_of_periapsis) : argument_of_periapsis;
}

/**************************************************************************************************/
double Keplerian::nu(bool degrees) const
{
  return degrees ? math::angle::rad2deg(true_anomaly) : true_anomaly;
}

/**************************************************************************************************/
double Keplerian::u(bool degrees) const
{
  return degrees ? math::angle::rad2deg(argument_of_latitude) : argument_of_latitude;
}

/**************************************************************************************************/
double Keplerian::l(bool degrees) const
{
  return degrees ? math::angle::rad2deg(true_longitude) : true_longitude;
}

/**************************************************************************************************/
std::string Keplerian::toString() const
{
  std::ostringstream ss;
  ss << *this;
  return ss.str();
}

/**************************************************************************************************/
std::string Keplerian::toString(std::ostream &(*manip)(std::ostream &)) const
{
  std::ostringstream ss;
  ss << manip << *this;
  return ss.str();
}
/**************************************************************************************************/
void Keplerian::computeEccentricityVector(const Cartesian &crt, transitional_data &data)
{
  // e = ( v x h ) / mu  -  r / |r|
  std::array<double, 3> tmp = math::vector::cross(crt.v(), data.h);
  tmp = math::vector::scaleInv(tmp, earth::gravitational_parameter);
  
  std::array<double, 3> r_norm = math::vector::normalize(crt.r(), data.r_mag);

  data.e = math::vector::sub(tmp, r_norm);
}

/**************************************************************************************************/
std::ostream &astro::states::orbits::operator<<(std::ostream &os, const Keplerian &kpl)
{
  const std::ios_base::fmtflags oldFlags = os.flags();
  const std::streamsize oldPrecision = os.precision();

  os << std::fixed << std::setprecision(10);

  const math::angle::Unit unit = math::angle::getUnit(os);

  double factor;
  const char *unitStr;

  switch (unit)
  {
    case math::angle::Unit::Degree:
      factor = math::angle::rad2deg_mod;
      unitStr = " deg";
      break;

    case math::angle::Unit::Radian:
    default:
      factor = 1.0;
      unitStr = " rad";
      break;
  }

  os << "Semi-latus Rectum: "
     << kpl.semi_latus_rectum << " km\n"
     << "Eccentricity: "
     << kpl.eccentricity << "\n"
     << "Inclination: "
     << kpl.inclination * factor << unitStr << "\n"
     << "Right Ascension of the Ascending Node: "
     << kpl.raan * factor << unitStr << "\n"
     << "Argument of Periapsis: "
     << kpl.argument_of_periapsis * factor << unitStr << "\n"
     << "True Anomaly: "
     << kpl.true_anomaly * factor << unitStr << "\n"
     << "Argument of Latitude: "
     << kpl.argument_of_latitude * factor << unitStr << "\n"
     << "True Longitude: "
     << kpl.true_longitude * factor << unitStr;

  os.flags(oldFlags);
  os.precision(oldPrecision);

  return os;
}
