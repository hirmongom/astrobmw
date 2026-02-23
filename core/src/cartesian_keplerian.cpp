/*
 * @TODO input checking?
 * @TODO performance?
 * @TODO memory mgmt
 */


#include <array>
#include <cmath>
#include <numbers>

#include <astro/constants/bodies/earth.hpp>
#include <astro/states/orbits.hpp>
#include <astro/operations/orbits/state_transforms/cartesian_keplerian.hpp>

#include <math/vector.hpp>


namespace earth = astro::constants::bodies::earth;
namespace state = astro::states::orbits;

namespace astro::operations::orbits::state_transforms

{

/**************************************************************************************************/
namespace
{

struct transitional_data
{
	std::array<double, 3> h;
	std::array<double, 3> n;
	std::array<double, 3> e;

	double r_mag;
	double v_mag;
	double h_mag;
	double n_mag;
};

} // unnamed namespace

/**************************************************************************************************/
inline void compute_eccentricity_vector (const state::cartesian &crt, transitional_data &data)
{
// e = ( v x h ) / mu  -  r / |r|
  std::array<double, 3> tmp = vect::cross_product(crt.velocity_vector, data.h);
  tmp = vect::scalar_division(tmp, earth::gravitational_parameter);
  
  std::array<double, 3> r_norm = vect::scalar_division(crt.position_vector, data.r_mag);

  data.e = vect::subtraction(tmp, r_norm);
} // compute_eccentricity_vec()

/**************************************************************************************************/
void cartesian_to_keplerian (const state::cartesian &crt, state::keplerian &kpl) 
{
	transitional_data data {};

	// ---------------------------------------------------------------------
	// 1. Compute magnitudes of r and v
	// ---------------------------------------------------------------------
  data.r_mag = vect::magnitude(crt.position_vector);
  data.v_mag = vect::magnitude(crt.velocity_vector);

	// ---------------------------------------------------------------------
	// 2. Compute angular momentum vector h = r × v
	// ---------------------------------------------------------------------
	data.h = vect::cross_product(crt.position_vector, crt.velocity_vector);
	data.h_mag = vect::magnitude(data.h);
	// ---------------------------------------------------------------------
	// 3. Compute node vector n = k × h
	// ---------------------------------------------------------------------
  data.n = vect::cross_product({0.0, 0.0, 1.0}, data.h);
  data.n_mag = vect::magnitude(data.n);

	// ---------------------------------------------------------------------
	// 4. Compute eccentricity vector
	// ---------------------------------------------------------------------
  compute_eccentricity_vector(crt, data);

	// ---------------------------------------------------------------------
	// 5. Compute orbital elements and populate kpl
	// ---------------------------------------------------------------------
  kpl.semi_latus_rectum = data.h_mag * data.h_mag / earth::gravitational_parameter;

  kpl.eccentricity = vect::magnitude(data.e);

  kpl.inclination = std::acos(data.h[2] / data.h_mag);

  kpl.raan = std::atan2(data.n[1], data.n[0]);
  if (kpl.raan < 0.0) { kpl.raan += 2.0 * std::numbers::pi; }

  kpl.argument_of_periapsis = std::acos(vect::dot_product(data.n, data.e) / (data.n_mag * kpl.eccentricity));
  if (data.e[2] <= 0) { kpl.argument_of_periapsis = 2.0 * std::numbers::pi - kpl.argument_of_periapsis; }

  kpl.true_anomaly = std::acos(vect::dot_product(data.e, crt.position_vector) / (kpl.eccentricity * data.r_mag));
  if (vect::dot_product(crt.position_vector, crt.velocity_vector) <= 0) {
    kpl.true_anomaly = 2.0 * std::numbers::pi - kpl.true_anomaly;
  }

  // kpl.argument_of_latitude = kpl.argument_of_periapsis + kpl.true_anomaly;
  kpl.argument_of_latitude = std::acos(vect::dot_product(data.n, crt.position_vector) / (data.n_mag * data.r_mag));
  if (crt.position_vector[2] <= 0) {
    kpl.argument_of_latitude = 2.0 * std::numbers::pi - kpl.argument_of_latitude;
  }

  kpl.true_longitude = std::fmod(kpl.raan + kpl.argument_of_latitude, 2.0 * std::numbers::pi);

  // Debug print
  vect::print_vec("r", crt.position_vector);
  vect::print_scalar("r_mag", data.r_mag);

  vect::print_vec("v", crt.velocity_vector);
  vect::print_scalar("v_mag", data.v_mag);

  vect::print_vec("h", data.h);
  vect::print_scalar("h_mag", data.h_mag);

  vect::print_vec("n", data.n);
  vect::print_scalar("n_mag", data.n_mag);

  vect::print_vec("e", data.e);

  vect::print_scalar("semi_latus_rectum", kpl.semi_latus_rectum);
  vect::print_scalar("eccentricity", kpl.eccentricity);
  vect::print_scalar("inclination", kpl.inclination);
  vect::print_scalar("raan", kpl.raan);
  vect::print_scalar("argument_of_periapsis", kpl.argument_of_periapsis);
  vect::print_scalar("true_anomaly", kpl.true_anomaly);
  vect::print_scalar("argument_of_latitude", kpl.argument_of_latitude);
  vect::print_scalar("true_longitude", kpl.true_longitude);
}

} // namespace astro::operations::orbits::state_transforms
