// Copyright (c) 2008  GeometryFactory Sarl (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/GraphicsView/include/CGAL/Qt/utility.h $
// $Id: utility.h 47047 2008-11-26 13:08:15Z lrineau $
// 
//
// Author(s)     : Andreas Fabri <Andreas.Fabri@geometryfactory.com>
//                 Laurent Rineau <Laurent.Rineau@geometryfactory.com>

#ifndef CGAL_QT_UTILITY_H
#define CGAL_QT_UTILITY_H

#include <QRectF>
#include <QRect>
#include <CGAL/auto_link/Qt4.h>

class QGraphicsScene;
class QGraphicsView;

namespace CGAL {
namespace Qt {

QRectF mapToScene(const QGraphicsView* v, const QRect rect);
QRectF viewportsBbox(const QGraphicsScene*);

} // namespace Qt
} // namespace CGAL

#endif // CGAL_QT_UTILITY_H
