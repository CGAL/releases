// Copyright (c) 2018-2020 GeometryFactory (France)
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL: https://github.com/CGAL/cgal/blob/v5.2.4/Surface_mesh/include/CGAL/draw_surface_mesh.h $
// $Id: draw_surface_mesh.h b134ed8 2021-02-05T16:07:32+01:00 Laurent Rineau
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
// Author(s)     : Guillaume Damiand <guillaume.damiand@liris.cnrs.fr>

#ifndef CGAL_DRAW_SURFACE_MESH_H
#define CGAL_DRAW_SURFACE_MESH_H

#ifdef DOXYGEN_RUNNING

/*!
\ingroup PkgDrawSurfaceMesh

Open a new window and draw `asm`, an instance of the `CGAL::Surface_mesh` class. The function is blocking, that is the program continues as soon as the user closes the window. This function requires CGAL_Qt5, and is only available if the flag CGAL_USE_BASIC_VIEWER is defined at compile time.
\tparam SM an instance of the `CGAL::Surface_mesh` class.
\param asm the surface mesh to draw.

*/
template<class SM>
void draw(const SM& asm);

#else // DOXYGEN_RUNNING

#include <CGAL/license/Surface_mesh.h>
#include <CGAL/Qt/Basic_viewer_qt.h>

#ifdef CGAL_USE_BASIC_VIEWER

#include <CGAL/Qt/init_ogl_context.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/draw_face_graph.h>
namespace CGAL
{

// Specialization of draw function.
template<class K>
void draw(const Surface_mesh<K>& amesh,
          const char* title="Surface_mesh Basic Viewer",
          bool nofill=false)
{
#if defined(CGAL_TEST_SUITE)
  bool cgal_test_suite=true;
#else
  bool cgal_test_suite=qEnvironmentVariableIsSet("CGAL_TEST_SUITE");
#endif

  if (!cgal_test_suite)
  {
    CGAL::Qt::init_ogl_context(4,3);
    int argc=1;
    const char* argv[2]={"surface_mesh_viewer","\0"};
    QApplication app(argc,const_cast<char**>(argv));
    SimpleFaceGraphViewerQt mainwindow(app.activeWindow(), amesh, title,
                                       nofill);
    mainwindow.show();
    app.exec();
  }
}

} // End namespace CGAL

#endif // CGAL_USE_BASIC_VIEWER

#endif // DOXYGEN_RUNNING

#endif // CGAL_DRAW_SURFACE_MESH_H
