// Copyright (c) 1997-2000  Max-Planck-Institute Saarbruecken (Germany).
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
// $Source: /CVSROOT/CGAL/Packages/Nef_3/include/CGAL/Nef_3/Progress_indicator.h,v $
// $Revision: 1.5.4.1 $ $Date: 2004/12/06 15:22:15 $
// $Name:  $
//
// Author(s)     : Miguel Granados <granados@mpi-sb.mpg.de>

#ifndef PROGRESS_INDICATOR_H
#define PROGRESS_INDICATOR_H

#include <iostream>
#include <CGAL/assertions.h>

class Progress_indicator
{
 protected:
  long total, current;
 public:
  Progress_indicator( long n) : total(n), current(0) {}

  void operator++(int) { 
    CGAL_assertion( total > 0);
    CGAL_assertion( current != total);
    ++current; 
  }
  void operator++() {
    operator++(0);
  }
  float percentage() { 
    CGAL_assertion( total > 0);
    return 100.0*current/total; 
  }
};

class Progress_indicator_ostream : public Progress_indicator
{
  typedef Progress_indicator Base;
 protected:
  std::ostream& os;
  char separator;
 public:
  Progress_indicator_ostream( std::ostream& o, long n, char *msg, char s='\n') 
    : Base(n), os(o), separator(s) {
    os<<msg<<std::endl;
    os.precision(2);
    os.setf( std::ios::fixed | std::ios::right);    
  }
  void operator++(int) {
    Base::operator++();
#ifdef CGAL_ENABLE_PROGRESS_INDICATOR_STATUS
    os.width(6);
    os<<percentage()<<'%'<<separator;
    os<<separator;
    os.flush();
#endif
  }
  void operator++() {
    operator++(0);
  }
};

class Progress_indicator_clog
: public Progress_indicator_ostream
{
  typedef Progress_indicator_ostream Base;
 public:
  Progress_indicator_clog( long n, char *msg, char s='\r') 
    : Base( std::clog, n, msg, s) {}
};

class Progress_indicator_cout
: public Progress_indicator_ostream
{
  typedef Progress_indicator_ostream Base;
 public:
  Progress_indicator_cout( long n, char *msg, char s='\r') 
    : Base( std::cout, n, msg, s) {}
};

#endif // PROGRESS_INDICATOR_H
