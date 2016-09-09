#ifndef CGAL_STREAM_BASE
#define CGAL_STREAM_BASE



//_____________________________________________________________________
// This should the base class for all visualization streams,
// in order to obtain code which does not depend from the 
// visualization tool used. 

class CGAL_stream_base {
public:

  virtual char* isa() = 0;

};


#endif
