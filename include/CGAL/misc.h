// Source: misc.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_MISC_H
#define CGAL_MISC_H

template < class FT >
inline int CGAL_sign(const FT &n)
{
  return (n > FT(0.0)) ? 1 : ((n == FT(0.0)) ? 0 : -1);
}



#endif // CGAL_MISC_H
