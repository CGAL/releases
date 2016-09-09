#ifndef CGAL_PIPEBUF_H
#define CGAL_PIPEBUF_H

#include<strstream.h>

/* A stream uses a buffer. We leave the buffering to UNIX and simply
   put our pipe for communicating with geomview in a buffer class.

   The following class defines in fact not only one but two pipe 
   buffers, one for input one for output. It should be split up,
   if one wants to use pipe buffers for other streams.
*/
//_____________________________________________________________________
class CGAL_pipebuf : public streambuf {
  
public:
  CGAL_pipebuf()
  {}

  virtual ~CGAL_pipebuf()
  {}

  void init(int pipe_out_fd, int pipe_in_fd)
  {
    in = pipe_in_fd;
    out = pipe_out_fd;
  }

//private:
  int out;  // these are the file descriptors for the ends of the pipes
  int in;
};

#endif  // CGAL_PIPEBUF_H
