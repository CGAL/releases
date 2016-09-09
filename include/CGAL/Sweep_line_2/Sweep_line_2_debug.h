// Copyright (c) 1997  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Arrangement_2/include/CGAL/Sweep_line_2/Sweep_line_2_debug.h $
// $Id: Sweep_line_2_debug.h 35514 2006-12-11 15:34:13Z wein $
// 
//
// Author(s)     : Baruch Zukerman <baruchzu@post.tau.ac.il>

#ifndef CGAL_SWEEP_LINE_2_DEBUG_H
#define CGAL_SWEEP_LINE_2_DEBUG_H


#include <CGAL/Basic_sweep_line_2.h>


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//                         DEBUG UTILITIES                                //
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


template <class Traits_,
          class SweepVisitor,
          class CurveWrap,
          class SweepEvent,
          typename Allocator>
inline void 
Basic_sweep_line_2<Traits_,
                   SweepVisitor,
                   CurveWrap,
                   SweepEvent,
                   Allocator>::
PrintEventQueue()
{
  CGAL_SL_DEBUG(std::cout << std::endl << "Event queue: " << std::endl;)
  EventQueueIter iter = m_queue->begin();
  while ( iter != m_queue->end() )
  {
    CGAL_SL_DEBUG(std::cout << "Point (" << iter->first << ")" << std::endl;)
    Event *e = iter->second;
    e->Print();
    ++iter;
  }
  CGAL_SL_DEBUG(std::cout << "--------------------------------" << std::endl;)
}

template <class Traits_,
          class SweepVisitor,
          class CurveWrap,
          class SweepEvent,
          typename Allocator>
inline void 
Basic_sweep_line_2<Traits_,
                   SweepVisitor,
                   CurveWrap,
                   SweepEvent,
                   Allocator>::
PrintSubCurves()
{
  CGAL_SL_DEBUG(std::cout << std::endl << "Sub curves: " << std::endl;)
  for(unsigned int i=0 ; i < m_num_of_subCurves ; ++i)
  {
    m_subCurves[i].Print();
  }
}

template < class SweepLineTraits_2,
           class SweepEvent, class CurveWrap, class SweepNotif,
           typename Allocator >
inline void 
Basic_sweep_line_2<SweepLineTraits_2,SweepEvent,CurveWrap,SweepNotif,
                  Allocator>::
PrintStatusLine()
{
  if ( m_statusLine.size() == 0) {
    std::cout << std::endl << "Status line: empty" << std::endl;
    return;
  }
  std::cout << std::endl << "Status line: (" ;
  if(m_currentEvent->is_finite())
    std::cout << m_currentEvent->get_point() << ")" << std::endl;
  else
  {
    Boundary_type x = m_currentEvent->infinity_at_x(),
                  y = m_currentEvent->infinity_at_y();

    PrintInfinityType(x, y);
  }
  StatusLineIter iter = m_statusLine.begin();
  while ( iter != m_statusLine.end() )
  {
    (*iter)->Print();
    ++iter;
  }
  std::cout << "Status line - end" << std::endl;
}

template <class Traits_,
          class SweepVisitor,
          class CurveWrap,
          class SweepEvent,
          typename Allocator>
inline void 
Basic_sweep_line_2<Traits_,
                   SweepVisitor,
                   CurveWrap,
                   SweepEvent,
                   Allocator>::
PrintInfinityType(Boundary_type x, Boundary_type y)
{
  switch(x)
  {
  case MINUS_INFINITY:
    std::cout<<" X = -00 ";
    return;
  case PLUS_INFINITY:
    std::cout<<" X = +00 ";
    return;
  case NO_BOUNDARY:
    break;
  }

  switch(y)
  {
  case MINUS_INFINITY:
    std::cout<<" Y = -00 ";
    return;
  case PLUS_INFINITY:
    std::cout<<" Y = +00 ";
    return;
  case NO_BOUNDARY:
    CGAL_assertion(false);
  }
}

template <class Traits_,
          class SweepVisitor,
          class CurveWrap,
          class SweepEvent,
          typename Allocator>
inline void 
Basic_sweep_line_2<Traits_,
                   SweepVisitor,
                   CurveWrap,
                   SweepEvent,
                   Allocator>::
PrintEvent(const Event* e)
{
  if(e->is_finite())
    std::cout<< e->get_point();
  else
  {
    Boundary_type x = e->infinity_at_x(),
                  y = e->infinity_at_y();
    PrintInfinityType(x, y);
    std::cout<<" with unbounded curve: " <<e->get_unbounded_curve();
  }

 
}
          



#endif
