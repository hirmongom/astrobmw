/*
 * From book (Chapter 2, page 117
 * Exercise 2.7
 * For this data:
 *  r = -6378.14i -6378.14j -6378.14k (km)
 *  v = +2.63234i -2.63234j +2.63234k (km/s)
 * The expected results are as follows:
 *  Intermediate results
 *    Angular momentum vector: -33578.8661i +33578.8661k (km^2/s)
 *    Node vector: -33578.8661j
 *    Excentricity vector: +0.3555961289i +0.133942756j +0.3555961289k
 *  Results
 *    Semi-latus rectum: 5657.496231 km
 *    Eccentricity: 0.520420864
 *    Inclination: 45 deg
 *    Longitude of the ascending node: 270 deg
 *    Argument of periapsis: 104.9142965 deg
 *    True anomaly at epoch: 200.35017 deg
 *    Argument of latitude at epoch: 305.2643897 deg
 *    True longitude at epoch: 215.2644665 deg
 */


#include <iostream>

#include <astro.hpp>


int main (int argc, char **argv)
{
  std::array<double, 3> r = { -6378.14, -6378.14, -6378.14 };
  std::array<double, 3> v = { 2.63234, -2.63234, 2.63234 };

  using namespace astro::states::orbits;
  struct cartesian crt { r, v };
  struct keplerian kpl {};

  astro::operations::orbits::state_transforms::cartesian_to_keplerian (crt, kpl);

  return 0;
}
