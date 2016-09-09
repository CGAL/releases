// ============================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
//
// release       :
// release_date  :
//
// file          : src/GeoWin/geo_rem.c
// package       : GeoWin (1.0.8)
// revision      : 1.0.8
// revision_date : 17 December 1999 
// author(s)     : Matthias Baesken, Ulrike Bartuschka, Stefan Naeher
//
// coordinator   : Matthias Baesken, Halle  (<baesken@informatik.uni-halle.de>)
// ============================================================================

#include <LEDA/geowin.h>
#include "geo_localdefs.h"

GEOWIN_BEGIN_NAMESPACE

// ******************* remarks for geoscenes *************************

string GeoRemark::set_remark(string st)
{
 string oldrem=remark;
 remark=st;
 return oldrem;
}

string GeoRemark::get_remark() const
{
  return remark;  
}


ostream& operator<<(ostream& o,const GeoRemark& g)
{
 o << g.get_remark();
 return o;
}

istream& operator>>(istream& i,GeoRemark& g)
{
 return i;
}


// ****************************** end remarks for geoscenes ****************************

GEOWIN_END_NAMESPACE
