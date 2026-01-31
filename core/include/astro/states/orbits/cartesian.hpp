#pragma once

#include <array>

namespace astro::states::orbits
{
  struct cartesian
  {
    std::array<double, 3> position_vector;
    std::array<double, 3> velocity_vector;
  };
}
