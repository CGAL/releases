 
// Source: Iso_rectangleH2.h
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL_ISO_RECTANGLEH2_H
#define CGAL_ISO_RECTANGLEH2_H

#include <CGAL/Twotuple.h>
#include <CGAL/PointH2.h>
#include <CGAL/predicates_on_pointsH2.h>

 
template <class FT, class RT>
class CGAL_Iso_rectangleH2 : public handle_base
{
public:
            CGAL_Iso_rectangleH2();
            CGAL_Iso_rectangleH2(const CGAL_Iso_rectangleH2<FT,RT> &);
            CGAL_Iso_rectangleH2(const CGAL_PointH2<FT,RT> &p,
                                 const CGAL_PointH2<FT,RT> &q);
            ~CGAL_Iso_rectangleH2();

  CGAL_Iso_rectangleH2<FT,RT>&
            operator=(const CGAL_Iso_rectangleH2<FT,RT> &r);

  bool      operator==(const CGAL_Iso_rectangleH2<FT,RT> &s) const;
  bool      operator!=(const CGAL_Iso_rectangleH2<FT,RT> &s) const;
  bool      identical(const CGAL_Iso_rectangleH2<FT,RT> &s) const;

  CGAL_PointH2<FT,RT>  min() const;
  CGAL_PointH2<FT,RT>  max() const;
  CGAL_PointH2<FT,RT>  vertex(int i) const;
  CGAL_PointH2<FT,RT>  operator[](int i) const;

  CGAL_Iso_rectangleH2<FT,RT>
            transform(const CGAL_Aff_transformationH2<FT,RT> &t) const;

  CGAL_Side where_is(const CGAL_PointH2<FT,RT> &p) const;
  bool      is_on(const CGAL_PointH2<FT,RT> &p) const;
  bool      is_inside(const CGAL_PointH2<FT,RT> &p) const;
  bool      is_outside(const CGAL_PointH2<FT,RT> &p) const;
  bool      is_degenerate() const;

  CGAL_Bbox_2
            bbox() const;

  FT        xmin() const;
  FT        ymin() const;
  FT        xmax() const;
  FT        ymax() const;


#ifdef CGAL_CHECK_PRECONDITIONS
  bool      is_defined() const;
#endif // CGAL_CHECK_PRECONDITIONS

protected:

  CGAL__Twotuple< CGAL_PointH2<FT,RT> >*
            ptr() const;
};
 


 
#ifdef CGAL_CHECK_PRECONDITIONS
template < class FT, class RT >
inline
bool
CGAL_Iso_rectangleH2<FT,RT>::is_defined() const
{
 return (PTR == NULL)? false : true;
}
#endif // CGAL_CHECK_PRECONDITIONS

template < class FT, class RT >
inline
CGAL__Twotuple< CGAL_PointH2<FT,RT> > *
CGAL_Iso_rectangleH2<FT,RT>::ptr() const
{
 return (CGAL__Twotuple< CGAL_PointH2<FT,RT> >*)PTR;
}
 


 
template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>::CGAL_Iso_rectangleH2()
{
#ifdef CGAL_CHECK_PRECONDITIONS
  PTR = NULL;
#else
  PTR = new CGAL__Twotuple< CGAL_PointH2<FT,RT> >;
#endif // CGAL_CHECK_PRECONDITIONS
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>::CGAL_Iso_rectangleH2(
                                 const CGAL_Iso_rectangleH2<FT,RT> &r)
  : handle_base((handle_base&)r)
{
  CGAL_kernel_precondition( r.is_defined() );
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>::CGAL_Iso_rectangleH2(const CGAL_PointH2<FT,RT> &p,
                                                  const CGAL_PointH2<FT,RT> &q)
{
 CGAL_kernel_precondition( p.is_defined() && q.is_defined() );

 bool px_g_qx = ( p.hx()*q.hw() > q.hx()*p.hw() );
 bool py_g_qy = ( p.hy()*q.hw() > q.hy()*p.hw() );

 if ( px_g_qx || py_g_qy)
 {
    if ( px_g_qx && py_g_qy )
    {
        PTR = new CGAL__Twotuple<CGAL_PointH2<FT,RT> >(q,p);
    }
    else
    {
       if ( px_g_qx )
       {
           PTR = new CGAL__Twotuple<CGAL_PointH2<FT,RT> >(
             CGAL_PointH2<FT,RT>(q.hx()*p.hw(), p.hy()*q.hw(), q.hw()*p.hw() ),
             CGAL_PointH2<FT,RT>(p.hx()*q.hw(), q.hy()*p.hw(), q.hw()*p.hw() ));
       }
       if ( py_g_qy )
       {
           PTR = new CGAL__Twotuple<CGAL_PointH2<FT,RT> >(
             CGAL_PointH2<FT,RT>(p.hx()*q.hw(), q.hy()*p.hw(), q.hw()*p.hw() ),
             CGAL_PointH2<FT,RT>(q.hx()*p.hw(), p.hy()*q.hw(), q.hw()*p.hw() ));
       }
    }
 }
 else
 {
    PTR = new CGAL__Twotuple< CGAL_PointH2<FT,RT> >(p,q);
 }
  CGAL_nondegeneracy_assertion;
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>::~CGAL_Iso_rectangleH2()
{
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT> &CGAL_Iso_rectangleH2<FT,RT>::operator=(
                                  const CGAL_Iso_rectangleH2<FT,RT> &r)
{
 CGAL_kernel_precondition( r.is_defined() );
 handle_base::operator=(r);
 return *this;
}
 
template < class FT, class RT >
bool
CGAL_Iso_rectangleH2<FT,RT>::operator==(const CGAL_Iso_rectangleH2<FT,RT> &r)
                                                                          const
{
 CGAL_kernel_precondition( is_defined() && r.is_defined() );
 return  vertex(0) == r.vertex(0) && vertex(2) == r.vertex(2);
}

template < class FT, class RT >
inline
bool
CGAL_Iso_rectangleH2<FT,RT>::operator!=(const CGAL_Iso_rectangleH2<FT,RT> &r)
                                                                          const
{
 CGAL_kernel_precondition( is_defined() && r.is_defined() );
 return !(*this == r);
}

template < class FT, class RT >
bool
CGAL_Iso_rectangleH2<FT,RT>::identical(const CGAL_Iso_rectangleH2<FT,RT> &r)
                                                                          const
{
 CGAL_kernel_precondition( is_defined() && r.is_defined() );
 return (PTR == t.PTR);
}
 
template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::min() const
{
 CGAL_kernel_precondition( is_defined() );
 return  ptr()->e0;
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::max() const
{
 CGAL_kernel_precondition( is_defined() );
 return  ptr()->e1;
}

template < class FT, class RT >
inline
FT
CGAL_Iso_rectangleH2<FT,RT>::xmin() const
{
 CGAL_kernel_precondition( is_defined() );
 return  FT( min().hx() ) / FT( min().hw() );
}

template < class FT, class RT >
inline
FT
CGAL_Iso_rectangleH2<FT,RT>::ymin() const
{
 CGAL_kernel_precondition( is_defined() );
 return  FT( min().hy() ) / FT( min().hw() );
}

template < class FT, class RT >
inline
FT
CGAL_Iso_rectangleH2<FT,RT>::xmax() const
{
 CGAL_kernel_precondition( is_defined() );
 return  FT( max().hx() ) / FT( max().hw() );
}

template < class FT, class RT >
inline
FT
CGAL_Iso_rectangleH2<FT,RT>::ymax() const
{
 CGAL_kernel_precondition( is_defined() );
 return  FT( max().hy() ) / FT( max().hw() );
}

template < class FT, class RT >
CGAL_PointH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::vertex(int i) const
{
 CGAL_kernel_precondition( is_defined() );
 switch (i%4)
 {
    case 0:
        return min();
    case 1:
        return CGAL_PointH2<FT,RT>( max().hx()*min().hw(),
                                    min().hy()*max().hw(),
                                    min().hw()*max().hw() );
    case 2:
        return max();
    case 3:
        return CGAL_PointH2<FT,RT>( min().hx()*max().hw(),
                                    max().hy()*min().hw(),
                                    min().hw()*max().hw() );
 }
 return CGAL_PointH2<FT,RT>();
}

template < class FT, class RT >
inline
CGAL_PointH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::operator[](int i) const
{
 CGAL_kernel_precondition( is_defined() );
 return vertex(i);
}
 
template < class FT, class RT >
CGAL_Side CGAL_Iso_rectangleH2<FT,RT>::where_is(const CGAL_PointH2<FT,RT> &p)
                                                                          const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined() );
 CGAL_Side wrt_min = CGAL__where_wrt_L_wedge(min(),p);
 CGAL_Side wrt_max = CGAL__where_wrt_L_wedge(p,max());
 if (( wrt_min == CGAL_OUTSIDE )||( wrt_max == CGAL_OUTSIDE))
 {
    return CGAL_OUTSIDE;
 }
 if (( wrt_min == CGAL_ON )||( wrt_max == CGAL_ON))
 {
    return CGAL_ON;
 }
 return CGAL_INSIDE;
}

template < class FT, class RT >
inline
bool
CGAL_Iso_rectangleH2<FT,RT>::is_on(const CGAL_PointH2<FT,RT> &p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined());
 return ( where_is(p) == CGAL_ON );
}

template < class FT, class RT >
inline
bool
CGAL_Iso_rectangleH2<FT,RT>::is_inside(const CGAL_PointH2<FT,RT> &p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined());
 return ( where_is(p) == CGAL_INSIDE );
}

template < class FT, class RT >
bool
CGAL_Iso_rectangleH2<FT,RT>::is_outside(const CGAL_PointH2<FT,RT> &p) const
{
 CGAL_kernel_precondition( is_defined() && p.is_defined());
 return (  (CGAL__where_wrt_L_wedge(min(),p) == CGAL_OUTSIDE)
         ||(CGAL__where_wrt_L_wedge(p,max()) == CGAL_OUTSIDE) );
}

template < class FT, class RT >
bool
CGAL_Iso_rectangleH2<FT,RT>::is_degenerate() const
{
 CGAL_kernel_precondition( is_defined() );
 return (   ( min().hx()*max().hw() == max().hx()*min().hw() )
         || ( min().hy()*max().hw() == max().hy()*min().hw() ) );
}
 
template < class FT, class RT >
CGAL_Bbox_2
CGAL_Iso_rectangleH2<FT,RT>::bbox() const
{
 CGAL_kernel_precondition( is_defined() );
 return  min().bbox() + max().bbox();
}

template < class FT, class RT >
CGAL_Iso_rectangleH2<FT,RT>
CGAL_Iso_rectangleH2<FT,RT>::transform(const CGAL_Aff_transformationH2<FT,RT>&t)
                                                                          const
{
 CGAL_kernel_precondition( is_defined() && t.is_defined() );
 return CGAL_Iso_rectangleH2<FT,RT>(t.transform(min() ),
                                    t.transform(max() ) );
}
 


#endif // CGAL_ISO_RECTANGLEH2_H
