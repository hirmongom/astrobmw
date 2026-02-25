#pragma once


#include <array>
#include <string>
#include <ostream>


namespace astro::states::orbits
{


class Cartesian
{
  friend std::ostream &operator<<(std::ostream &os, const Cartesian &crt);

  public:
    Cartesian(const std::array<double, 3> &r, const std::array<double, 3> &v);
    ~Cartesian() noexcept = default;

    const std::array<double, 3> &r() const;
    const std::array<double, 3> &v() const;

    std::string toString() const;

  private:
    std::array<double, 3> position_vector;
    std::array<double, 3> velocity_vector;
}; // class Cartesian

std::ostream &operator<<(std::ostream &os, const Cartesian &crt);


} // namespace astro::states::orbits
