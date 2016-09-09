/* 

Copyright (c) 1997 The CGAL Consortium

This software and related documentation is part of the 
Computational Geometry Algorithms Library (CGAL).

Permission to use, copy, and distribute this software and its 
documentation is hereby granted free of charge, provided that 
(1) it is not a component of a commercial product, and 
(2) this notice appears in all copies of the software and
    related documentation. 

CGAL may be distributed by any means, provided that the original
files remain intact, and no charge is made other than for
reasonable distribution costs.

CGAL may not be distributed as a component of any commercial
product without a prior license agreement with the authors.

This software and documentation is provided "as-is" and without 
warranty of any kind. In no event shall the CGAL Consortium be
liable for any damage of any kind.

The CGAL Consortium consists of Utrecht University (The Netherlands), 
ETH Zurich (Switzerland), Free University of Berlin (Germany), 
INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
(Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).

*/


// Source: Object.h
// Author: Andreas Fabri

#ifndef CGAL_OBJECT_H
#define CGAL_OBJECT_H

class CGAL_Base {
public:
  virtual ~CGAL_Base() {}
#ifdef CGAL_WORKAROUND_012
    virtual int* type_id() const {return 0;}
#endif  // CGAL_WORKAROUND_012
};


template < class T >
class CGAL_Wrapper : public CGAL_Base {
public:
  CGAL_Wrapper(const T& object)
    : _object(object)
  {}
  CGAL_Wrapper() {}

  operator T()
  {
    return _object;
  }

  virtual ~CGAL_Wrapper() {}
#ifdef CGAL_WORKAROUND_012
    virtual int* type_id() const {return &_typebase;}
#endif  // CGAL_WORKAROUND_012
private:
  T _object;
#ifdef CGAL_WORKAROUND_012
    static int _typebase;
#endif  // CGAL_WORKAROUND_012
};

#ifdef CGAL_WORKAROUND_012
template <class T>
  //static
int CGAL_Wrapper<T>::_typebase = 42;
#endif // CGAL_WORKAROUND_012


class CGAL__Object : public CGAL_Rep
{
public:
  CGAL__Object()
    : _base(0)
  {}

  CGAL__Object(CGAL_Base *base)
    : _base(base)
  {}

  ~CGAL__Object()
  {
    if (_base != 0 ){
      delete _base;
    }
  }

  CGAL_Base *base() const
  {
    return _base;
  }

private:
  CGAL_Base *_base;
};


class CGAL_Object : public CGAL_Handle
{
public:
  CGAL_Object()
  {
    PTR = new CGAL__Object();
  }

  CGAL_Object(CGAL_Base *base)
  {
    PTR = new CGAL__Object(base);
  }

  CGAL_Object(const CGAL_Object &o)
    : CGAL_Handle((CGAL_Handle&)o)
  {}

  CGAL_Object &operator=(const CGAL_Object &o)
  {
    CGAL_Handle::operator=(o);
    return *this;
  }

  CGAL__Object *ptr() const
  {
    return (CGAL__Object *)PTR;
  }
};


template <class T>
CGAL_Object CGAL_make_object(const T & t)
{
  return CGAL_Object(new CGAL_Wrapper< T >(t));
}


#ifdef CGAL_WORKAROUND_012
template <class T>
T* CGAL__dynamic_cast(CGAL_Base *base, const T*)
{
    T dummy;
    if (base == 0)
        return (T*) 0;
    if (dummy.type_id() != base->type_id())
        return (T*) 0;
    return (T*) base;
}

template <class T>
const T* CGAL__dynamic_cast(const CGAL_Base *base, const T*)
{
    T* dummy;
    if (t->type_id() != base->type_id())
        return (const T*) 0;
    return (const T*) base;
}
#endif // CGAL_WORKAROUND_012

template < class T >
bool CGAL_assign(T &t, const CGAL_Object &o)
{
#ifdef CGAL_WORKAROUND_012
    CGAL_Wrapper<T> *wp =
        CGAL__dynamic_cast(o.ptr()->base(), (CGAL_Wrapper<T>*) 0);
#else

    CGAL_Wrapper<T> *wp = 0;
    if ((o.ptr()->base()) != 0){
      wp = dynamic_cast< CGAL_Wrapper<T>* >(o.ptr()->base());
    }
#endif // CGAL_WORKAROUND_012
  if( wp == 0 ){
    return false;
  }
  t = *(wp);
  return true;
}

#endif // CGAL_OBJECT_H
