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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/GraphicsView/include/CGAL/Qt/StreamLinesGraphicsItem.h $
// $Id: StreamLinesGraphicsItem.h 58770 2010-09-22 06:16:09Z afabri $
// 
//
// Author(s)     : Andreas Fabri <Andreas.Fabri@geometryfactory.com>
//                 Laurent Rineau <Laurent.Rineau@geometryfactory.com>

#ifndef CGAL_QT_STREAM_LINES_GRAPHICS_ITEM_H
#define CGAL_QT_STREAM_LINES_GRAPHICS_ITEM_H



#include <CGAL/Qt/GraphicsItem.h>
#include <CGAL/Qt/PainterOstream.h>
#include <CGAL/Qt/utility.h>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

class QGraphicsSceneMouseEvent;


namespace CGAL {
namespace Qt {

template <typename SL, typename K>
class StreamLinesGraphicsItem : public GraphicsItem
{

  typedef typename SL::Stream_line_iterator_2 Stream_line_iterator;
  typedef typename SL::Point_iterator_2 Point_iterator;
  typedef typename K::Point_2 Point_2;
  typedef typename K::Segment_2 Segment_2;

public:
  StreamLinesGraphicsItem(SL* sl);


  QRectF 
  boundingRect() const;
  
  void 
  paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  
  void 
  modelChanged();

  const QPen& edgesPen() const
  {
    return edges_pen;
  }

  void setEdgesPen(const QPen& pen)
  {
    edges_pen = pen;
  }

private:
  SL * sl;
  QPen edges_pen;
};



template <typename SL, typename K>
StreamLinesGraphicsItem<SL,K>::StreamLinesGraphicsItem(SL * sl)
  :  sl(sl)
{
  setZValue(3);
}

template <typename SL, typename K>
QRectF 
StreamLinesGraphicsItem<SL,K>::boundingRect() const
{
  QRectF rect = CGAL::Qt::viewportsBbox(scene());
  return rect;
}


template <typename SL, typename K>
void 
StreamLinesGraphicsItem<SL,K>::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
  painter->setPen(this->edgesPen());
  QRectF rect = option->exposedRect;
  PainterOstream<K> pos(painter, rect);
  for (Stream_line_iterator sit = sl->begin(); sit != sl->end(); sit++){
    Point_iterator pit = sit->first;
    Point_2 p = *pit;
    ++pit;
    for (; pit != (*sit).second; pit++){
      Point_2 q = *pit;
      pos << Segment_2(p,q);
      p = q;
    }
  }
}


  template <typename SL, typename K>
void 
  StreamLinesGraphicsItem<SL,K>::modelChanged()
{
  update();
}

} // namespace Qt
} // namespace CGAL

#endif // CGAL_QT_STREAM_LINES_GRAPHICS_ITEM_H
