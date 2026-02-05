// Copyright (c) 2010 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL: https://github.com/CGAL/cgal/blob/v6.1.1/Lab/demo/Lab/implicit_functions/Implicit_function_interface.h $
// $Id: demo/Lab/implicit_functions/Implicit_function_interface.h 08b27d3db14 $
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description :
//******************************************************************************

#ifndef CGAL_MESH_3_IMPLICIT_FUNCTION_INTERFACE_H
#define CGAL_MESH_3_IMPLICIT_FUNCTION_INTERFACE_H

#include <QObject>
#include <QString>
#include <CGAL/Three/Scene_interface.h>

class Implicit_function_interface
{
public:
  typedef CGAL::Three::Scene_interface::Bbox Bbox;

  virtual ~Implicit_function_interface() {}

  virtual QString name() const = 0;
  virtual double operator()(double x, double y, double z) const = 0;
  virtual Bbox bbox() const = 0;

  /// Returns the minimum and maximum of the function.
  ///
  /// The method returns false if it cannot know efficiently its extrema.
  /// In that case, the function will be scanned over the bounding box to
  /// compute approximation of the extrema. If the method is not
  /// overloaded by derived classes, the default is to return false.
  virtual bool get_min_max(double&, double&) {
    return false;
  }
};

Q_DECLARE_INTERFACE(Implicit_function_interface,
                    "com.geometryfactory.Mesh3Demo.Implicit_function_interface/1.0")


#endif // CGAL_MESH_3_IMPLICIT_FUNCTION_INTERFACE_H
