#include <astro.hpp>

#include <iostream>
#include <iomanip>
#include <limits>


int main (int argc, char **argv)
{
  std::cout
    << std::setprecision(std::numeric_limits<double>::max_digits10)
    << astro::constants::bodies::earth::gravitational_parameter
    << "\n";

  return 0;
}
