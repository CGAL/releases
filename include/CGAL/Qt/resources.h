// Copyright (c) 2011  GeometryFactory Sarl (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/releases/CGAL-3.9-branch/GraphicsView/include/CGAL/Qt/resources.h $
// $Id: resources.h 64055 2011-06-10 17:14:27Z lrineau $
// 
//
// Author(s)     : Laurent Rineau <Laurent.Rineau@geometryfactory.com>

#ifndef CGAL_QT_RESOURCES_H
#define CGAL_QT_RESOURCES_H

// cannot use namespaces because of the Q_INIT_RESOURCE macro
CGAL_QT4_EXPORT void CGAL_Qt4_init_resources();

#define CGAL_QT4_INIT_RESOURCES CGAL_Qt4_init_resources();

#endif // CGAL_QT_RESOURCES_H
