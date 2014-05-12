/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef SIDEVALUESAMPLER_H
#define SIDEVALUESAMPLER_H

#include "SideVectorPostprocessor.h"
#include "SamplerBase.h"

//Forward Declarations
class SideValueSampler;

template<>
InputParameters validParams<SideValueSampler>();

class SideValueSampler :
  public SideVectorPostprocessor,
  protected SamplerBase
{
public:
  SideValueSampler(const std::string & name, InputParameters parameters);

  virtual ~SideValueSampler() {}

  virtual void initialize();
  virtual void execute();
  virtual void finalize();

  virtual void threadJoin(const UserObject & y);

protected:
  /// So we don't have to create and destroy this vector over and over again
  std::vector<Real> _values;

  unsigned int _qp;
};

#endif
