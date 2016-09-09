#ifndef CGAL_ISTREAM
#define CGAL_ISTREAM

#include<CGAL/cartesian.h>
#include<CGAL/Point_3.h>
#include<CGAL/Segment_3.h>
//#include<CGAL/Triangle_3.h>
#include<CGAL/IO/stream_base.h>

#include<stream.h>

//_____________________________________________________________________
// This should the base class for all visualization input streams,
// in order to obtain code which does not depend from the 
// visualization tool used. 

class CGAL_istream : public virtual CGAL_stream_base  
{
public:
  /*
  virtual CGAL_istream& operator>>(CGAL_Point_3<double> &p) = 0;
  virtual CGAL_istream& operator>>(CGAL_Segment_3<double> &s) = 0;

    virtual CGAL_istream& operator>>(CGAL_Triangle_3<double> &t) = 0;
  */
};


#endif
