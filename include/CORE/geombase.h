/******************************************************************
 * Core Library Version 1.6, June 2003
 * Copyright (c) 1995-2002 Exact Computation Project
 * 
 * File: geombase.h
 * Synopsis:
 *      Code that is common to (and included by) geometry2d.h 
 *      and geometry3d.h
 *
 * Written by
 *       Shubin Zhao (shubinz@cs.nyu.edu) (2001)
 *
 * WWW URL: http://cs.nyu.edu/exact/
 * Email: exact@cs.nyu.edu
 *
 * $Id: geombase.h,v 1.2 2003/08/06 12:59:28 afabri Exp $
 *****************************************************************/

#ifndef CORE_GEOMETRY_H
#define CORE_GEOMETRY_H

#include <CORE/CORE.h>


//base class for geom2d and geom3d classes
class GeomObj {

public:

  // Exceptions

  class Exception {
  	public:
  	  virtual void print_message( char* msg ) { std::cerr << msg <<std::endl; }
  };

  class NoIntersection : public Exception { };

  class IllegalOperation : public Exception { };

  virtual int dim() const { return -1; }

}; //class GeomObj

#endif
