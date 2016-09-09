//  Copyright CGAL 1996
//
//  cgal@cs.ruu.nl
//
//  This file is part of an internal release of the CGAL kernel.
//  The code herein may be used and/or copied only in accordance
//  with the terms and conditions stipulated in the agreement
//  under which the code has been supplied or with the written
//  permission of the CGAL Project.
//
//  Look at http://www.cs.ruu.nl/CGAL/ for more information.
//  Please send any bug reports and comments to cgal@cs.ruu.nl
//
//  The code comes WITHOUT ANY WARRANTY; without even the implied
//  warranty of FITNESS FOR A PARTICULAR PURPOSE.
//

// Source: Object.h
// Author: Andreas.Fabri@sophia.inria.fr

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

  CGAL_Object::CGAL_Object(const CGAL_Object &o)
    : CGAL_Handle((CGAL_Handle&)o)
  {}

  CGAL_Object &CGAL_Object::operator=(const CGAL_Object &o)
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
T* CGAL_dynamic_cast(CGAL_Base *base, const T*)
{
    T dummy;
    if (base == 0)
        return (T*) 0;
    if (dummy.type_id() != base->type_id())
        return (T*) 0;
    return (T*) base;
}

template <class T>
const T* CGAL_dynamic_cast(const CGAL_Base *base, const T*)
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
        CGAL_dynamic_cast(o.ptr()->base(), (CGAL_Wrapper<T>*) 0);
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
