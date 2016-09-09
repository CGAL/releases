#ifndef CGAL_OSTREAM
#define CGAL_OSTREAM

#include<LEDA/list.h>


#include<CGAL/cartesian.h>
#include<CGAL/Segment_2.h>
#include<CGAL/Segment_3.h>

#include<CGAL/Triangle_3.h>
#include<CGAL/Tetrahedron_3.h>

#include<CGAL/Bbox_2.h>
#include<CGAL/Bbox_3.h>

#include<CGAL/IO/stream_base.h>
#include<CGAL/IO/Color.h>

#include<stream.h>

//_____________________________________________________________________
// This should the base class for all visualization outputstreams,
// in order to obtain code which does not depend from the 
// visualization tool used. 

class CGAL_ostream : public virtual CGAL_stream_base
{
public:

  virtual CGAL_ostream &operator<<(const CGAL_Bbox_2 &bbox) {return (*this); }
  virtual CGAL_ostream &operator<<(const CGAL_Bbox_3 &bbox) {return (*this); }

  virtual CGAL_ostream &operator<<(const CGAL_Point_2< C<double> > &p) = 0;
  virtual CGAL_ostream &operator<<(const CGAL_Point_3< C<double> > &p) = 0;

  virtual CGAL_ostream &operator<<(const CGAL_Segment_2< C<double> > &s) = 0;
  virtual CGAL_ostream &operator<<(const CGAL_Segment_3< C<double> > &s) = 0;
  
  virtual CGAL_ostream &operator<<(const CGAL_Triangle_3< C<double> > &t) = 0;

  virtual CGAL_ostream &operator<<(const CGAL_Tetrahedron_3< C<double> > &t) = 0;
  
  virtual CGAL_ostream &operator<<(const CGAL_Color &c) = 0; 

};


#endif
