#pragma once

#include <array>

namespace astro::states::orbits
{
  struct keplerian
  {
    double semi_major_axis;
    std::array<double, 3> eccentricity_vector;
    double inclination;
    double raan;
    double argument_of_periapsis;
    double true_anomaly;
  };
}
