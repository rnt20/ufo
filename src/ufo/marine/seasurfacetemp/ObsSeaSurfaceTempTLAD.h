/*
 * (C) Copyright 2017-2018 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef UFO_MARINE_SEASURFACETEMP_OBSSEASURFACETEMPTLAD_H_
#define UFO_MARINE_SEASURFACETEMP_OBSSEASURFACETEMPTLAD_H_

#include <ostream>
#include <string>

#include <boost/scoped_ptr.hpp>

#include "ioda/ObsSpace.h"

#include "oops/base/Variables.h"
#include "oops/util/Logger.h"
#include "oops/util/ObjectCounter.h"

#include "ufo/LinearObsOperatorBase.h"
#include "ufo/marine/FortranMarine.h"

// Forward declarations
namespace util {
  class DateTime;
}

namespace ioda {
  class ObsVector;
}

namespace ufo {
  class GeoVaLs;
  class ObsBias;
  class ObsBiasIncrement;

// -----------------------------------------------------------------------------

class ObsSeaSurfaceTempTLAD : public LinearObsOperatorBase,
                              private util::ObjectCounter<ObsSeaSurfaceTempTLAD> {
 public:
  static const std::string classname() {return "ufo::ObsSeaSurfaceTempTLAD";}

  ObsSeaSurfaceTempTLAD(const ioda::ObsSpace &, const eckit::Configuration &);
  virtual ~ObsSeaSurfaceTempTLAD();

  // Obs Operators
  void setTrajectory(const GeoVaLs &, const ObsBias &);
  void simulateObsTL(const GeoVaLs &, ioda::ObsVector &, const ObsBiasIncrement &) const;
  void simulateObsAD(GeoVaLs &, const ioda::ObsVector &, ObsBiasIncrement &) const;

  // Other
  const oops::Variables & variables() const {return *varin_;}

  int & toFortran() {return keyOperSeaSurfaceTemp_;}
  const int & toFortran() const {return keyOperSeaSurfaceTemp_;}

 private:
  void print(std::ostream &) const;
  F90hop keyOperSeaSurfaceTemp_;
  const ioda::ObsSpace& odb_;
  boost::scoped_ptr<const oops::Variables> varin_;
};

// -----------------------------------------------------------------------------
/*template <typename MODEL>
  ObsSeaSurfaceTempTLAD<MODEL>::ObsSeaSurfaceTempTLAD(const ioda::ObsSpace & odb, const eckit::Configuration & config)
  : keyOperSeaSurfaceTemp_(0), varin_()
{
  const eckit::Configuration * configc = &config;
  ufo_seasurfacetemp_tlad_setup_f90(keyOperSeaSurfaceTemp_, &configc);
  const std::vector<std::string> vv{"ocean_upper_level_temperature"};
  varin_.reset(new oops::Variables(vv));
  oops::Log::trace() << "ObsSeaSurfaceTempTLAD created" << std::endl;
}

// -----------------------------------------------------------------------------
template <typename MODEL>
ObsSeaSurfaceTempTLAD<MODEL>::~ObsSeaSurfaceTempTLAD() {
  ufo_seasurfacetemp_tlad_delete_f90(keyOperSeaSurfaceTemp_);
  oops::Log::trace() << "ObsSeaSurfaceTempTLAD destrcuted" << std::endl;
}

// -----------------------------------------------------------------------------
template <typename MODEL>
void ObsSeaSurfaceTempTLAD<MODEL>::setTrajectory(const GeoVaLs & geovals, const ObsBias & bias) {
  ufo_seasurfacetemp_tlad_settraj_f90(keyOperSeaSurfaceTemp_, geovals.toFortran());
}

// -----------------------------------------------------------------------------
template <typename MODEL>
  void ObsSeaSurfaceTempTLAD<MODEL>::obsEquivTL(const GeoVaLs & geovals, ioda::ObsVector & ovec,
                               const ObsBiasIncrement & bias) const {
  ufo_seasurfacetemp_tlad_eqv_tl_f90(keyOperSeaSurfaceTemp_, geovals.toFortran(), ovec.toFortran());
}

// -----------------------------------------------------------------------------
template <typename MODEL>
  void ObsSeaSurfaceTempTLAD<MODEL>::obsEquivAD(GeoVaLs & geovals, const ioda::ObsVector & ovec,
                               ObsBiasIncrement & bias) const {
  ufo_seasurfacetemp_tlad_eqv_ad_f90(keyOperSeaSurfaceTemp_, geovals.toFortran(), ovec.toFortran());
}

// -----------------------------------------------------------------------------
template <typename MODEL>
void ObsSeaSurfaceTempTLAD<MODEL>::print(std::ostream & os) const {
  os << "ObsSeaSurfaceTempTLAD::print not implemented" << std::endl;
}
// -----------------------------------------------------------------------------
*/
}  // namespace ufo
#endif  // UFO_MARINE_SEASURFACETEMP_OBSSEASURFACETEMPTLAD_H_