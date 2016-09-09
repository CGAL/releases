// Copyright (c) 2010 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/demo/Mesh_3/implicit_functions/Tanglecube_implicit_function.cpp $
// $Id: Tanglecube_implicit_function.cpp 57336 2010-07-06 07:26:40Z stayeb $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#include <QObject>
#include "Implicit_function_interface.h"


const double radius = 4.;

class Tanglecube_implicit_function :
  public QObject,
  public Implicit_function_interface
{
  Q_OBJECT
  Q_INTERFACES(Implicit_function_interface)
  
public:
  virtual QString name() const { return "Tanglecube function"; }
  
  virtual double operator()(double x, double y, double z) const
  {
    double x2=x*x, y2=y*y, z2=z*z;
    double x4=x2*x2, y4=y2*y2, z4=z2*z2;
    return x4 - 5*x2 + y4 - 5*y2 + z4 - 5*z2 + 11.8;
  }
  
  virtual Bbox bbox() const
  {
    double r = radius * 1.2;
    return Bbox(-r,-r,-r,r,r,r);
  }
};



#include <QtPlugin>
Q_EXPORT_PLUGIN2(Tanglecube_implicit_function, Tanglecube_implicit_function)
#include "Tanglecube_implicit_function.moc"
