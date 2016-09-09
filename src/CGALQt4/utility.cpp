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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/GraphicsView/src/CGALQt4/utility.cpp $
// $Id: utility.cpp 46606 2008-10-31 13:48:01Z lrineau $
// 
//
// Author(s)     : Andreas Fabri <Andreas.Fabri@geometryfactory.com>
//                 Laurent Rineau <Laurent.Rineau@geometryfactory.com>

#include <CGAL/Qt/utility.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <QPoint>
#include <QPointF>

namespace CGAL {
namespace Qt {

QRectF mapToScene(const QGraphicsView* v, const QRect rect)
{
  QPointF top_left = v->mapToScene(rect.topLeft());
  QPointF size = v->mapToScene(rect.bottomRight());
  size -= top_left;
  return QRectF(top_left.x(),
		top_left.y(),
		size.x(),
		size.y());
}

QRectF viewportsBbox(const QGraphicsScene* scene) {
   QRectF rect;
   Q_FOREACH(QGraphicsView* view, scene->views())
   {
     rect |= mapToScene(view, view->viewport()->rect());
   }
   rect = rect.normalized();
   return rect;
}

} // namespace Qt
} // namespace CGAL
