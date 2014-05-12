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

#ifndef POINTSAMPLERBASE_H
#define POINTSAMPLERBASE_H

#include "GeneralVectorPostprocessor.h"
#include "SamplerBase.h"
#include "CoupleableMooseVariableDependencyIntermediateInterface.h"

//Forward Declarations
class PointSamplerBase;

template<>
InputParameters validParams<PointSamplerBase>();

class PointSamplerBase :
  public GeneralVectorPostprocessor,
  public CoupleableMooseVariableDependencyIntermediateInterface,
  protected SamplerBase
{
public:
  PointSamplerBase(const std::string & name, InputParameters parameters);

  virtual ~PointSamplerBase() {}

  virtual void initialize();
  virtual void execute();
  virtual void finalize();

  virtual void threadJoin(const UserObject & y);

protected:

  /**
   * Find the local element that contains the point.  This will attempt to use a cached element to speed things up.
   *
   * @param p The point in physical space
   * @param id A unique ID for this point.
   * @return The Elem containing the point or NULL if this processor doesn't contain an element that contains this point.
   */
  const Elem * getLocalElemContainingPoint(const Point & p, unsigned int id);

  /// The Mesh we're using
  MooseMesh & _mesh;

  /// The points to evaluate at
  std::vector<Point> _points;

  /// The ID to use for each point (yes, this is Real on purpose)
  std::vector<Real> _ids;

  /// So we don't have to create and destroy this vector over and over again
  std::vector<Real> _values;

  unsigned int _qp;

  /// So we don't have to create and destroy this
  std::vector<Point> _point_vec;

  AutoPtr<PointLocatorBase> _pl;
};

#endif
