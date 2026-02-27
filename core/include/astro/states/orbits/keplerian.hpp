#pragma once


#include <array>
#include <string>
#include <ostream>


namespace astro::states::orbits
{


class Cartesian;

class Keplerian
{
  friend std::ostream &operator<<(std::ostream &os, const Keplerian &kpl);
  friend bool operator==(const Keplerian &a, const Keplerian &b);

  public:
    Keplerian(double p, double e, double i, double Omega, 
              double omega, double nu, double u, double l);
    explicit Keplerian(const Cartesian &crt);
    ~Keplerian() = default;

    double p() const;
    double e() const;
    double i(bool degrees = false) const;
    double Omega(bool degrees = false) const;
    double omega(bool degrees = false) const;
    double nu(bool degrees = false) const;
    double u(bool degrees = false) const;
    double l(bool degrees = false) const;

    std::string toString() const;
    std::string toString(std::ostream &(*manip)(std::ostream &)) const;

  private:
    double semi_latus_rectum;
    double eccentricity;
    double inclination;
    double raan;
    double argument_of_periapsis;
    double true_anomaly;
    double argument_of_latitude;
    double true_longitude;

    struct transitional_data
    {
      std::array<double, 3> h {};
      std::array<double, 3> n {};
      std::array<double, 3> e {};

      double r_mag {};
      double v_mag {};
      double h_mag {};
      double n_mag {};
    };

    void computeEccentricityVector(const Cartesian &crt, transitional_data &data);
}; // class Keplerian

std::ostream &operator<<(std::ostream &os, const Keplerian &kpl);
bool operator==(const Keplerian &a, const Keplerian &b);

} // namespace astro::states::orbits
