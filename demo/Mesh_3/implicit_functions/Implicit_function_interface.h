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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/demo/Mesh_3/implicit_functions/Implicit_function_interface.h $
// $Id: Implicit_function_interface.h 56748 2010-06-14 15:45:15Z stayeb $
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
#include <CGAL_demo/Scene_interface.h>

class Implicit_function_interface 
{
public:
  typedef Scene_interface::Bbox Bbox;
  
  virtual ~Implicit_function_interface() {}
  
  virtual QString name() const = 0;
  virtual double operator()(double x, double y, double z) const = 0;
  virtual Bbox bbox() const = 0;
};

Q_DECLARE_INTERFACE(Implicit_function_interface,
                    "com.geometryfactory.Mesh3Demo.Implicit_function_interface/1.0")


#endif // CGAL_MESH_3_IMPLICIT_FUNCTION_INTERFACE_H
