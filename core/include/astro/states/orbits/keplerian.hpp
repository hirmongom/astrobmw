#pragma once

#include <array>

namespace astro::states::orbits
{
  struct keplerian
  {
    double semi_latus_rectum;
    double eccentricity;
    // std::array<double, 3> eccentricity_vector;
    double inclination;
    double raan;
    double argument_of_periapsis;
    double true_anomaly;
    double argument_of_latitude;
    double true_longitude;
  };
}
