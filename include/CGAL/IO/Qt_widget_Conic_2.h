// Copyright (c) 1997-2000  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Qt_widget/include/CGAL/IO/Qt_widget_Conic_2.h,v $
// $Revision: 1.7 $ $Date: 2003/10/21 12:23:02 $
// $Name: current_submission $
//
// Author(s)     : Radu Ursu


#ifndef CGAL_QT_WIDGET_CONIC_2_H
#define CGAL_QT_WIDGET_CONIC_2_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/Conic_2.h>

namespace CGAL{

template< class R >
Qt_widget&
operator << ( Qt_widget& ws, const CGAL::Conic_2<R>& c)
{
  typedef typename R::Point_2 Point;    
  // pixel dimensions of window
  int dim = std::max( ws.width(), ws.height());    
  // length of a pixel in window-coordinates
  double pixel_x = (ws.x_max() - ws.x_min())/dim;
  double pixel_y = (ws.y_max() - ws.y_min())/dim;
  // pixel coordinates, stored for faster output
  typedef typename std::pair<double, double> pcoordinates;
  std::vector<pcoordinates> vcoordinates;
  typedef typename std::vector<pcoordinates>::const_iterator CIT;
  // conic coordinates
  double r = CGAL::to_double (c.r()),
         s = CGAL::to_double (c.s()),
         t = CGAL::to_double (c.t()),
         u = CGAL::to_double (c.u()),
         v = CGAL::to_double (c.v()),
         w = CGAL::to_double (c.w());

  // Phase I (drawing in x-direction)    
  // solve conic equation for y
  if (s != 0.0)
      for (double x = ws.x_min(); x <= ws.x_max(); x+=pixel_x) {
          double discr = (t*t-4.0*r*s)*(x*x) + (2.0*t*v-4.0*s*u)*x +
                            v*v - 4.0*s*w;
          if (discr >= 0.0) {
              double y1 = (-t*x - v - CGAL::sqrt(discr))/(2.0*s);
              double y2 = (-t*x - v + CGAL::sqrt(discr))/(2.0*s);
              vcoordinates.push_back(std::make_pair(x, y1));
              vcoordinates.push_back(std::make_pair(x, y2));} }
  else
      for (double x = ws.x_min(); x <= ws.x_max(); x+=pixel_x) {
          double denom = t*x + v;
          if (denom != 0.0) {
              double y = -(r*x*x + u*x + w)/denom;
              vcoordinates.push_back(std::make_pair(x, y)); } }
    
  for(CIT it1 = vcoordinates.begin(); it1!= vcoordinates.end(); it1++){
    ws << Point((*it1).first, (*it1).second);
  }
  vcoordinates.clear();
  // Phase II (drawing in y-direction)  
  // solve conic equation for x
  if (r != 0.0)
      for (double y = ws.y_min(); y <= ws.y_max(); y+=pixel_y) {
          double discr = (t*t-4.0*r*s)*(y*y) + (2.0*t*u-4.0*r*v)*y +
                            u*u - 4.0*r*w;
          if (discr >= 0.0) {
              double x1 = (-t*y - u - CGAL::sqrt(discr))/(2.0*r);
              double x2 = (-t*y - u + CGAL::sqrt(discr))/(2.0*r);
              vcoordinates.push_back(std::make_pair(x1, y));
              vcoordinates.push_back(std::make_pair(x2, y));} }
  else
      for (double y = ws.y_min(); y <= ws.y_max(); y+=pixel_y) {
          double denom = t*y + u;
          if (denom != 0.0) {
              double x = -(s*y*y + v*y + w)/denom;
              vcoordinates.push_back(std::make_pair(x, y));} }
  
  for(CIT it1 = vcoordinates.begin(); it1!= vcoordinates.end(); it1++){
    ws << Point((*it1).first, (*it1).second);
  }
  return( ws);
}
}//end namespace CGAL

#endif
