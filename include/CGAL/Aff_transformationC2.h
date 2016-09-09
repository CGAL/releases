// Source: Aff_transformationC2.h
// Author: Andreas.Fabri@sophia.inria.fr

#ifndef CGAL_AFF_TRANSFORMATIONC2_H
#define CGAL_AFF_TRANSFORMATIONC2_H
#include <math.h>
#include <LEDA/basic.h>
#include <CGAL/cartesian_classes.h>
#include <CGAL/determinant.h>
#include <CGAL/Onetuple.h>
#include <CGAL/Twotuple.h>
#include <CGAL/Sixtuple.h>


//#ifndef CGAL_REPCLASS
template < class FT >
  class CGAL_Aff_transformation_baseC2
{
public:
  virtual                      ~CGAL_Aff_transformation_baseC2() {}

  virtual CGAL_PointC2<FT>     transform(const CGAL_PointC2<FT> &p) const  = 0;
  virtual CGAL_VectorC2<FT>    transform(const CGAL_VectorC2<FT> &v) const  = 0;
  virtual CGAL_DirectionC2<FT> transform(const CGAL_DirectionC2<FT> &d) const  = 0;

  CGAL_LineC2<FT>      transform(const CGAL_LineC2<FT> &l) const;

  CGAL_RayC2<FT>       transform(const CGAL_RayC2<FT> &r) const;

  CGAL_SegmentC2<FT>   transform(const CGAL_SegmentC2<FT> &s) const;

  CGAL_TriangleC2<FT>  transform(const CGAL_TriangleC2<FT> &t) const;

  CGAL_Iso_rectangleC2<FT> transform(const CGAL_Iso_rectangleC2<FT> &r) const;


  virtual CGAL_Aff_transformationC2<FT> general_form() const  = 0;

  virtual bool                 is_even() const  = 0;
  virtual bool                 is_odd() const = 0;
#ifdef CGAL_KERNEL_PRECONDITION
  virtual bool                 is_defined() const = 0;
#endif // CGAL_KERNEL_PRECONDITION
    virtual ostream              &print(ostream &os) const { os << "base class print" << endl; return os;}
};
//#endif //CGAL_REPCLASS



//#ifndef CGAL_REPCLASS
template < class FT >
inline CGAL_LineC2<FT> CGAL_Aff_transformation_baseC2<FT>::transform(const CGAL_LineC2<FT> &l) const
{
  return l.transform(*this);
}

template < class FT >
inline CGAL_RayC2<FT> CGAL_Aff_transformation_baseC2<FT>::transform(const CGAL_RayC2<FT> &r) const
{
  return r.transform(*this);
}

template < class FT >
inline CGAL_SegmentC2<FT> CGAL_Aff_transformation_baseC2<FT>::transform(const CGAL_SegmentC2<FT> &s) const
{
  return s.transform(*this);
}


template < class FT >
inline CGAL_TriangleC2<FT> CGAL_Aff_transformation_baseC2<FT>::transform(const CGAL_TriangleC2<FT> &t) const
{
  return t.transform(*this);
}


template < class FT >
inline CGAL_Iso_rectangleC2<FT> CGAL_Aff_transformation_baseC2<FT>::transform(const CGAL_Iso_rectangleC2<FT> &r) const
{
  return r.transform(*this);
}
//#endif //CGAL_REPCLASS



template < class FT >
ostream &operator<<(ostream &os, const CGAL_Aff_transformation_baseC2<FT> &t)
{
  return t.print(os);
}

#ifdef CGAL_WORKAROUND_0002
// the above output operator should be enough for the derived classes as well
// the Sun Pro C++ compiler does not match it.

template < class FT >
ostream &operator<<(ostream &os, const CGAL_TranslationC2<FT> &t)
{
  return t.print(os);
}

template < class FT >
ostream &operator<<(ostream &os, const CGAL_RotationC2<FT> &t)
{
  return t.print(os);
}

template < class FT >
ostream &operator<<(ostream &os, const CGAL_ScalingC2<FT> &t)
{
  return t.print(os);
}

template < class FT >
ostream &operator<<(ostream &os, const CGAL_Aff_transformationC2<FT> &t)
{
  return t.print(os);
}
#endif // CGAL_WORKAROUND_0002




template < class FT >
class CGAL_Aff_transformationC2 :
  //#ifndef CGAL_REPCLASS
  virtual public CGAL_Aff_transformation_baseC2<FT>,
  //#endif //CGAL_REPCLASS
  public handle_base
{
public:

  CGAL_Aff_transformationC2()
  {
#ifdef CGAL_KERNEL_PRECONDITION
  PTR = NULL;
#else
  PTR = new CGAL__Sixtuple<FT>;
#endif // CGAL_KERNEL_PRECONDITION
  }

#ifdef CGAL_KERNEL_PRECONDITION
bool is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_KERNEL_PRECONDITION

  CGAL_Aff_transformationC2( const FT& m11, const FT& m12,
                             const FT& m21, const FT& m22, const FT& m33 = FT(1.0))


  {
    if ( m33 != FT(1.0)){
    PTR = new CGAL__Sixtuple<FT>(m11/m33, m12/m33, FT(0.0),
                                 m21/m33, m22/m33, FT(0.0));
    }else{
      PTR = new CGAL__Sixtuple<FT>(m11, m12, FT(0.0),
                                   m21, m22, FT(0.0));
    }
  }

  CGAL_Aff_transformationC2( const FT& m11, const FT& m12, const FT& m13,
                             const FT& m21, const FT& m22, const FT& m23,
                             const FT& m33 = FT(1.0))
  {
    if ( m33 != FT(1.0)){
    PTR = new CGAL__Sixtuple<FT>(m11/m33, m12/m33, m13/m33,
                                 m21/m33, m22/m33, m23/m33);
    }else{
      PTR = new CGAL__Sixtuple<FT>(m11, m12, m13,
                                   m21, m22, m23);
    }
}

  CGAL_Aff_transformationC2(const CGAL_Aff_transformationC2<FT> &t)
    : handle_base(t)
  {}

  ~CGAL_Aff_transformationC2()
  {}

  CGAL_Aff_transformationC2<FT> &operator=(const CGAL_Aff_transformationC2<FT> &t)
  {
    //CGAL_kernel_precondition(t.is_defined());
    handle_base::operator=(t);
  return *this;
  }

  CGAL_PointC2<FT> transform(const CGAL_PointC2<FT>& p) const
  {
    return CGAL_PointC2<FT>(_m11() * p.x() + _m12() * p.y() + _m13(),
                            _m21() * p.x() + _m22() * p.y() + _m23());
  }


  // note that a vector is not translated
  CGAL_VectorC2<FT> transform(const CGAL_VectorC2<FT>& v) const
  {
    return CGAL_VectorC2<FT>(_m11() * v.x() + _m12() * v.y(),
                             _m21() * v.x() + _m22() * v.y());
  }


  // note that a direction is not translated
  CGAL_DirectionC2<FT> transform(const CGAL_DirectionC2<FT>& dir) const
  {
    CGAL_VectorC2<FT> v = dir.vector();
    return CGAL_DirectionC2<FT>(_m11() * v.x() + _m12() * v.y(),
                                _m21() * v.x() + _m22() * v.y());
  }

  CGAL_Aff_transformationC2<FT> inverse() const
  {
    FT det = FT(1.0) / (_m11() * _m22() - _m12() * _m21());

    return CGAL_Aff_transformationC2<FT>(
      det * _m22(),    det * (-_m12()), det * (_m12()*_m23()-_m13()*_m22()),
      det * (-_m21()), det * _m11() ,   det * (_m13()*_m21()-_m11()*_m23()));

  }


  CGAL_Aff_transformationC2<FT> general_form() const
  {
    return *this;
  }

 bool is_even() const
  {
    return ( CGAL_sign(_m11() * _m22() - _m12() * _m21()) == 1 );
  }

 bool is_odd() const
 {
   return !is_even();
 }

 CGAL_Aff_transformationC2<FT> operator*(const CGAL_Aff_transformationC2<FT> &t) const
  {
    return CGAL_Aff_transformationC2<FT>(_m11()*t._m11() + _m12()*t._m21(),
                                         _m11()*t._m12() + _m12()*t._m22(),
                                         _m11()*t._m13() + _m12()*t._m23() + _m13(),

                                         _m21()*t._m11() + _m22()*t._m21(),
                                         _m21()*t._m12() + _m22()*t._m22(),
                                         _m21()*t._m13() + _m22()*t._m23() + _m23());
  }

 ostream &print(ostream &os) const
  {
    os << "Aff_transformationC2(" << _m11() << " " << _m12() << " " << _m13() << endl;
    os << "                     " << _m21() << " " << _m22() << " " << _m23() << ")";
    return os;
  }

private:
  CGAL__Sixtuple<FT>*  ptr() const
  {
    return (CGAL__Sixtuple<FT>*)PTR;
  }

  FT _m11() const
  {
    return ptr()->e0;
  }

  FT _m12() const
  {
    return ptr()->e1;
  }

  FT _m13() const
  {
    return ptr()->e2;
  }

  FT _m21() const
  {
    return ptr()->e3;
  }

  FT _m22() const
  {
    return ptr()->e4;
  }

  FT _m23() const
  {
    return ptr()->e5;
  }

};

template < class FT >
class CGAL_TranslationC2 :
                                        //#ifndef CGAL_REPCLASS
  virtual public CGAL_Aff_transformation_baseC2<FT>,
                                        //#endif //CGAL_REPCLASS
  public handle_base

{
public:
  CGAL_TranslationC2()
  {
#ifdef CGAL_KERNEL_PRECONDITION
    PTR = NULL;
#else
    PTR = new CGAL__Onetuple< CGAL_VectorC2<FT> >;
#endif // CGAL_KERNEL_PRECONDITION
}

#ifdef CGAL_KERNEL_PRECONDITION
bool is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_KERNEL_PRECONDITION

  CGAL_TranslationC2(const CGAL_VectorC2<FT> &tv)
  {
    PTR = new CGAL__Onetuple< CGAL_VectorC2<FT> > (tv);
  }

  CGAL_TranslationC2(const CGAL_TranslationC2<FT> &t)
    : handle_base(t)
  {}

  ~CGAL_TranslationC2()
  {}

  CGAL_TranslationC2<FT> &operator=(const CGAL_TranslationC2<FT> &t)
  {
    handle_base::operator=(t);
    return *this;
  }

  CGAL_PointC2<FT>        transform(const CGAL_PointC2<FT> &p) const
  {
    return p + _translationvector();
  }

  CGAL_VectorC2<FT>        transform(const CGAL_VectorC2<FT> &v) const
  {
    return v;
  }

  CGAL_DirectionC2<FT>    transform(const CGAL_DirectionC2<FT> &d) const
  {
    return d;
  }


  CGAL_TranslationC2<FT> inverse() const
  {
    return CGAL_TranslationC2<FT>(- _translationvector());
  }


  CGAL_Aff_transformationC2<FT> general_form() const
  {
    FT ft0(0.0), ft1(1.0);

    return CGAL_Aff_transformationC2<FT>(ft1, ft0, _translationvector().x(),
                                         ft0, ft1, _translationvector().y());
  }


  bool                 is_even() const
  {
    return true;
  }

 bool is_odd() const
 {
   return !is_even();
 }

 ostream &print(ostream &os) const
  {
    os << "TranslationC2(" << _translationvector() <<  ")";
    return os;
  }

  CGAL_TranslationC2<FT> operator*(const CGAL_TranslationC2<FT> &t) const
  {
    return CGAL_TranslationC2<FT>(_translationvector() + t._translationvector());
  }

private:
  CGAL__Onetuple< CGAL_VectorC2<FT> > *ptr() const
  {
    return (CGAL__Onetuple< CGAL_VectorC2<FT>  >*)PTR;
  }

  CGAL_VectorC2<FT>  _translationvector() const
  {
    return ptr()->e0;
  }
};

template < class FT >
class CGAL_RotationC2 :
                                     //#ifndef CGAL_REPCLASS
  virtual public CGAL_Aff_transformation_baseC2<FT>,
                                     //#endif //CGAL_REPCLASS
  public handle_base
{
public:
  CGAL_RotationC2()
  {
#ifdef CGAL_KERNEL_PRECONDITION
    PTR = NULL;
#else
    PTR = new CGAL__Twotuple<FT>;
#endif // CGAL_KERNEL_PRECONDITION}
  }

#ifdef CGAL_KERNEL_PRECONDITION
bool is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_KERNEL_PRECONDITION

  CGAL_RotationC2(const FT &sinus, const FT &cosinus, const FT &hw = FT(1.0))
  {
    if (hw != FT(1.0)){
      PTR = new CGAL__Twotuple<FT>(sinus/hw, cosinus/hw);
    }else{
      PTR = new CGAL__Twotuple<FT>(sinus/hw, cosinus/hw);
    }
  }

  CGAL_RotationC2(const CGAL_DirectionC2<FT> &d)
  {
    const FT &x = d.vector().x();
    const FT &y = d.vector().y();
    const FT hypothenuse = sqrt(x*x + y*y);

    PTR = new CGAL__Twotuple<FT>(y/hypothenuse,
                                 x/hypothenuse);
  }

  CGAL_RotationC2(const CGAL_RotationC2 &t)
    : handle_base(t)
  {}

  ~CGAL_RotationC2()
  {}

  CGAL_RotationC2<FT> &operator=(const CGAL_RotationC2<FT> &t)
  {
    handle_base::operator=(t);
    return *this;
  }

  CGAL_PointC2<FT>      transform(const CGAL_PointC2<FT> &p) const
  {
    return CGAL_PointC2<FT>(_cosinus() * p.x() - _sinus() * p.y(),
                            _sinus() * p.x() + _cosinus() * p.y());
  }

  CGAL_VectorC2<FT>  transform(const CGAL_VectorC2<FT> &v) const
  {
    return CGAL_VectorC2<FT>(_cosinus() * v.x() - _sinus() * v.y(),
                             _sinus() * v.x() + _cosinus() * v.y());
  }

  CGAL_DirectionC2<FT>  transform(const CGAL_DirectionC2<FT> &d) const
  {
    CGAL_VectorC2<FT>  v = d.vector();
    return CGAL_DirectionC2<FT>(_cosinus() * v.x() - _sinus() * v.y(),
                                _sinus() * v.x() + _cosinus() * v.y());
  }

  CGAL_RotationC2<FT> inverse() const
  {
    return CGAL_RotationC2<FT>(- _sinus(), _cosinus(), FT(1.0));
  }


  CGAL_Aff_transformationC2<FT> general_form() const
  {
    FT ft0(0.0);

    return CGAL_Aff_transformationC2<FT>(_cosinus(), -_sinus(),  ft0,
                                         _sinus(),   _cosinus(), ft0);
  }

  bool                 is_even() const
  {
    return true;
  }

 bool is_odd() const
 {
   return !is_even();
 }

 ostream &print(ostream &os) const
  {
    os << "RotationC2(" << _sinus() << ", " << _cosinus() <<  ")";
    return os;
  }

  CGAL_RotationC2<FT> operator*(const CGAL_RotationC2<FT> &t) const
  {
    return CGAL_RotationC2<FT>(_sinus() * t._sinus(),
                               _cosinus() * t._cosinus());
  }
private:
  CGAL__Twotuple<FT> *ptr() const
  {
    return (CGAL__Twotuple<FT>*)PTR;
  }

  FT _sinus() const
  {
    return ptr()->e0;
  }

  FT _cosinus() const
  {
    return ptr()->e1;
  }
};

template < class FT >
class CGAL_ScalingC2 :
                                    //#ifndef CGAL_REPCLASS
  virtual public CGAL_Aff_transformation_baseC2<FT>,
                                    //#endif //CGAL_REPCLASS
  public handle_base
{
public:
  CGAL_ScalingC2()
  {
#ifdef CGAL_KERNEL_PRECONDITION
    PTR = NULL;
#else
    PTR = new CGAL__Onetuple<FT>;
#endif // CGAL_KERNEL_PRECONDITION
  }

#ifdef CGAL_KERNEL_PRECONDITION
bool is_defined() const
{
  return (PTR == NULL)? false : true;
}
#endif // CGAL_KERNEL_PRECONDITION

  CGAL_ScalingC2(const FT &scalefactor, const FT &hw = FT(1.0))
  {
    if (hw != FT(1.0)){
      PTR = new CGAL__Onetuple<FT>(scalefactor/hw);
    }else{
      PTR = new CGAL__Onetuple<FT>(scalefactor);
    }
  }

  CGAL_ScalingC2(const CGAL_ScalingC2<FT> &t)
    : handle_base(t)
  {}

  CGAL_ScalingC2<FT> &operator=(const CGAL_ScalingC2<FT> &t)
  {
    handle_base::operator=(t);
    return *this;
  }

  CGAL_PointC2<FT>      transform(const CGAL_PointC2<FT> &p) const
  {
    return CGAL_PointC2<FT>(_scalefactor() * p.x(), _scalefactor() * p.y());
  }

  CGAL_VectorC2<FT>      transform(const CGAL_VectorC2<FT> &p) const
  {
    return CGAL_VectorC2<FT>(_scalefactor() * p.x(), _scalefactor() * p.y());
  }

  CGAL_DirectionC2<FT>  transform(const CGAL_DirectionC2<FT> &d) const
  {
    return d;
  }
    /*
  CGAL_Aff_transformationC2<FT> operator*(CGAL_TranslationC2<FT> *tp)
  {
    const CGAL_TranslationC2<FT> &t = *tp;
    return this->general_form()  * t.general_form();
  }
  */
  CGAL_ScalingC2<FT> inverse() const
  {
    return CGAL_ScalingC2<FT>(1/_scalefactor());
  }


  CGAL_Aff_transformationC2<FT> general_form() const
  {
    FT ft0(0.0);

    return CGAL_Aff_transformationC2<FT>(_scalefactor(), ft0,
                                         ft0 ,           _scalefactor());
  }


  bool                 is_even() const
  {
    return true;
  }

 bool is_odd() const
 {
   return !is_even();
 }

 ostream &print(ostream &os) const
  {
    os << "ScalingC2(" << _scalefactor() <<  ")";
    return os;
  }

  CGAL_ScalingC2<FT> operator*(const CGAL_ScalingC2<FT> &t) const
  {
    return CGAL_ScalingC2<FT>(_scalefactor() + t._scalefactor());
  }
private:
  CGAL__Onetuple<FT> *ptr() const
  {
    return (CGAL__Onetuple<FT> *)PTR;
  }

  FT _scalefactor() const
  {
    return ptr()->e0;
  }
};


#endif
