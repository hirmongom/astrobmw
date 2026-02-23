#pragma once


#include <astro/states/orbits/cartesian.hpp>
#include <astro/states/orbits/keplerian.hpp>


namespace astro::operations::orbits::state_transforms
{


namespace state = astro::states::orbits;


void cartesian_to_keplerian (const state::cartesian &crt, state::keplerian &kpl);


} // namespace astro::operations::orbits::state_transforms
