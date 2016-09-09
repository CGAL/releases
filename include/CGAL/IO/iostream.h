#ifndef CGAL_IOSTREAM
#define CGAL_IOSTREAM

#include<CGAL/IO/istream.h>
#include<CGAL/IO/ostream.h>

//_____________________________________________________________________
// This should the base class for all visualization streams,
// in order to obtain code which does not depend from the 
// visualization tool used. 

class CGAL_iostream : public CGAL_istream, public CGAL_ostream {
public:

};


#endif
