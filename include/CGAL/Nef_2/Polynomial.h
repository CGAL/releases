// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/Nef_2/Polynomial.h
// package       : Nef_2 (1.18)
// chapter       : Nef Polyhedra
//
// revision      : $Revision: 1.16 $
// revision_date : $Date: 2002/05/02 08:34:37 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Polynomials in one variable
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_POLYNOMIAL_H
#define CGAL_POLYNOMIAL_H

#include <CGAL/basic.h>
#include <CGAL/kernel_assertions.h>
#include <CGAL/Handle_for.h>
#include <CGAL/number_type_basic.h>
#include <CGAL/number_utils.h>
#include <CGAL/Number_type_traits.h>
#include <CGAL/IO/io.h>
#include <cstddef>
#undef _DEBUG
#define _DEBUG 3
#include <CGAL/Nef_2/debug.h>

#if (defined(_MSC_VER) && (_MSC_VER <= 1200)) || \
      defined(__SUNPRO_CC) // || defined(__BORLANDC__)
#include <CGAL/Nef_2/vector_MSC.h>
#define CGAL_SIMPLE_NEF_INTERFACE
#define SNIHACK ,char,char
#define SNIINST ,'c','c'
#else
#include <vector>
#if (!defined(_MSC_VER))
#if defined( __BORLANDC__)
#define SNIHACK ,char,char
#define SNIINST ,'c','c'
#else
#define SNIHACK
#define SNIINST
#endif
#else
#define SNIHACK ,char,char
#define SNIINST ,'c','c'
#endif
#endif

CGAL_BEGIN_NAMESPACE

template <class NT> class Polynomial_rep;

// SPECIALIZE_CLASS(NT,int double) START
// CLASS TEMPLATE NT: 
template <class NT> class Polynomial;
// CLASS TEMPLATE int: 
CGAL_TEMPLATE_NULL class Polynomial<int> ;
// CLASS TEMPLATE double: 
CGAL_TEMPLATE_NULL class Polynomial<double> ;
// SPECIALIZE_CLASS(NT,int double) END

/*{\Mtext \headerline{Range template}}*/
#ifndef CGAL_SIMPLE_NEF_INTERFACE

template <class Forward_iterator>
typename std::iterator_traits<Forward_iterator>::value_type 
gcd_of_range(Forward_iterator its, Forward_iterator ite)
{
  typedef typename std::iterator_traits<Forward_iterator>::value_type NT;
  typedef typename Number_type_traits<NT>::Has_gcd Has_gcd;
  return gcd_of_range(its,ite,Has_gcd());
}

template <class Forward_iterator>
typename std::iterator_traits<Forward_iterator>::value_type 
gcd_of_range(Forward_iterator its, Forward_iterator ite, Tag_true)
/*{\Mfunc calculates the greates common divisor of the
set of numbers $\{ |*its|, |*++its|, \ldots, |*it| \}$ of type |NT|,
where |++it == ite| and |NT| is the value type of |Forward_iterator|. 
\precond there exists a pairwise gcd operation |NT gcd(NT,NT)| and 
|its!=ite|.}*/
{ CGAL_assertion(its!=ite);
  typedef typename std::iterator_traits<Forward_iterator>::value_type NT;
  NT res = *its++;
  for(; its!=ite; ++its) res = 
    (*its==0 ? res : CGAL_NTS gcd(res, *its));
  if (res==0) res = 1;
  return res;
}

template <class Forward_iterator>
typename std::iterator_traits<Forward_iterator>::value_type 
gcd_of_range(Forward_iterator its, Forward_iterator ite, Tag_false)
/*{\Mfunc calculates the greates common divisor of the
set of numbers $\{ |*its|, |*++its|, \ldots, |*it| \}$ of type |NT|,
where |++it == ite| and |NT| is the value type of |Forward_iterator|. 
\precond |its!=ite|.}*/
{ CGAL_assertion(its!=ite);
  typedef typename std::iterator_traits<Forward_iterator>::value_type NT;
  NT res = *its++;
  for(; its!=ite; ++its) res = 
    (*its==0 ? res : 1);
  if (res==0) res = 1;
  return res;
}
#else

template <class NT>
NT
get_gcd(const NT& n1, const NT& n2, Tag_true)
{
   return CGAL_NTS gcd(n1, n2);
}

template <class NT>
NT
get_gcd(const NT& n1, const NT& n2, Tag_false)
{
   return NT(1);
}

#endif // CGAL_SIMPLE_NEF_INTERFACE


template <class NT>  Polynomial<NT>
  operator - (const Polynomial<NT>&);
template <class NT>  Polynomial<NT>
  operator + (const Polynomial<NT>&, const Polynomial<NT>&);
template <class NT>  Polynomial<NT>
  operator - (const Polynomial<NT>&, const Polynomial<NT>&);
template <class NT>  Polynomial<NT>
  operator * (const Polynomial<NT>&, const Polynomial<NT>&);
template <class NT> inline Polynomial<NT>
  operator / (const Polynomial<NT>&, const Polynomial<NT>&);

#if ! defined(_MSC_VER)
template<class NT> CGAL::Sign 
  sign(const Polynomial<NT>& p);
#endif // collides with global CGAL sign

template <class NT> double 
  to_double(const Polynomial<NT>& p) ;
template <class NT> bool 
  is_valid(const Polynomial<NT>& p) ;
template <class NT> bool 
  is_finite(const Polynomial<NT>& p) ;

template<class NT>  
  std::ostream& operator << (std::ostream& os, const Polynomial<NT>& p);
template <class NT>  
  std::istream& operator >> (std::istream& is, Polynomial<NT>& p);

#if ! defined(_MSC_VER) || _MSC_VER >= 1300
  // lefthand side
template<class NT> inline Polynomial<NT> operator + 
  (const NT& num, const Polynomial<NT>& p2);
template<class NT> inline Polynomial<NT> operator - 
  (const NT& num, const Polynomial<NT>& p2);
template<class NT> inline Polynomial<NT> operator * 
  (const NT& num, const Polynomial<NT>& p2);
template<class NT> inline Polynomial<NT> operator / 
  (const NT& num, const Polynomial<NT>& p2);

  // righthand side
template<class NT> inline Polynomial<NT> operator + 
  (const Polynomial<NT>& p1, const NT& num);
template<class NT> inline Polynomial<NT> operator - 
  (const Polynomial<NT>& p1, const NT& num);
template<class NT> inline Polynomial<NT> operator * 
  (const Polynomial<NT>& p1, const NT& num);
template<class NT> inline Polynomial<NT> operator / 
  (const Polynomial<NT>& p1, const NT& num);

  // lefthand side
template<class NT> inline bool operator ==  
  (const NT& num, const Polynomial<NT>& p);
template<class NT> inline bool operator != 
  (const NT& num, const Polynomial<NT>& p);
template<class NT> inline bool operator <  
  (const NT& num, const Polynomial<NT>& p);
template<class NT> inline bool operator <=  
  (const NT& num, const Polynomial<NT>& p);
template<class NT> inline bool operator >  
  (const NT& num, const Polynomial<NT>& p);
template<class NT> inline bool operator >=  
  (const NT& num, const Polynomial<NT>& p);

  // righthand side
template<class NT> inline bool operator ==
  (const Polynomial<NT>& p, const NT& num);
template<class NT> inline bool operator !=
  (const Polynomial<NT>& p, const NT& num);
template<class NT> inline bool operator < 
  (const Polynomial<NT>& p, const NT& num);
template<class NT> inline bool operator <= 
  (const Polynomial<NT>& p, const NT& num);
template<class NT> inline bool operator > 
  (const Polynomial<NT>& p, const NT& num);
template<class NT> inline bool operator >=
  (const Polynomial<NT>& p, const NT& num);

#endif // _MSC_VER

template <class pNT> class Polynomial_rep { 
  typedef pNT NT;
  #ifndef CGAL_SIMPLE_NEF_INTERFACE
  typedef std::vector<NT> Vector;
  #else
  typedef CGAL::vector_MSC<NT> Vector;
  #endif
  typedef typename Vector::size_type      size_type;
  typedef typename Vector::iterator       iterator;
  typedef typename Vector::const_iterator const_iterator;
  Vector coeff;

  Polynomial_rep() : coeff() {}
  Polynomial_rep(const NT& n) : coeff(1) { coeff[0]=n; }
  Polynomial_rep(const NT& n, const NT& m) : coeff(2)
    { coeff[0]=n; coeff[1]=m; }
  Polynomial_rep(const NT& a, const NT& b, const NT& c) : coeff(3)
    { coeff[0]=a; coeff[1]=b; coeff[2]=c; }
  Polynomial_rep(size_type s) : coeff(s,NT(0)) {}

  #ifndef CGAL_SIMPLE_NEF_INTERFACE

  template <class Forward_iterator>
  Polynomial_rep(Forward_iterator first, Forward_iterator last SNIHACK) 
    : coeff(first,last) {}

  #else
  template <class Forward_iterator>
  Polynomial_rep(Forward_iterator first, Forward_iterator last SNIHACK) 
    : coeff() 
  { while (first!=last) coeff.push_back(*first++); }

  #endif

  void reduce() 
  { while ( coeff.size()>1 && coeff.back()==NT(0) ) coeff.pop_back(); }

  friend class Polynomial<pNT>;
  friend class Polynomial<int>;
  friend class Polynomial<double>;
  friend std::istream& operator >> CGAL_NULL_TMPL_ARGS  
         (std::istream&, Polynomial<NT>&);


};

// SPECIALIZE_CLASS(NT,int double) START
// CLASS TEMPLATE NT: 
/*{\Msubst 
typename iterator_traits<Forward_iterator>::value_type#NT
CGAL_NULL_TMPL_ARGS#
}*/

/*{\Manpage{Polynomial}{NT}{Polynomials in one variable}{p}}*/

template <class pNT> class Polynomial : 
  public Handle_for< Polynomial_rep<pNT> >
{
/*{\Mdefinition An instance |\Mvar| of the data type |\Mname| represents
a polynomial $p = a_0 + a_1 x + \ldots a_d x^d $ from the ring |NT[x]|. 
The data type offers standard ring operations and a sign operation which 
determines the sign for the limit process $x \rightarrow \infty$. 

|NT[x]| becomes a unique factorization domain, if the number type
|NT| is either a field type (1) or a unique factorization domain
(2). In both cases there's a polynomial division operation defined.}*/

  /*{\Mtypes 5}*/
  public:
  typedef pNT NT;
  /*{\Mtypemember the component type representing the coefficients.}*/

  typedef Handle_for< Polynomial_rep<NT> > Base;
  typedef Polynomial_rep<NT> Rep;
  typedef typename Rep::Vector    Vector;
  typedef typename Rep::size_type size_type;
  typedef typename Rep::iterator  iterator;

  typedef typename Rep::const_iterator const_iterator;
  /*{\Mtypemember a random access iterator for read-only access to the
  coefficient vector.}*/

  protected:
  void reduce() { ptr()->reduce(); }
  Vector& coeffs() { return ptr()->coeff; }
  const Vector& coeffs() const { return ptr()->coeff; }
  Polynomial(size_type s) : Base( Polynomial_rep<NT>(s) ) {}
  // creates a polynomial of degree s-1

  static NT R_; // for visualization only

  /*{\Mcreation 3}*/
  public:

  Polynomial()
  /*{\Mcreate introduces a variable |\Mvar| of type |\Mname| of undefined
  value. }*/
    : Base( Polynomial_rep<NT>() ) {}
   
  Polynomial(const NT& a0)
  /*{\Mcreate introduces a variable |\Mvar| of type |\Mname| representing
  the constant polynomial $a_0$.}*/
    : Base(Polynomial_rep<NT>(a0)) { reduce(); }

  Polynomial(NT a0, NT a1) //af 
  /*{\Mcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial $a_0 + a_1 x$. }*/
    : Base(Polynomial_rep<NT>(a0,a1)) { reduce(); }

  Polynomial(const NT& a0, const NT& a1,const NT& a2)
  /*{\Mcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial $a_0 + a_1 x + a_2 x^2$. }*/
    : Base(Polynomial_rep<NT>(a0,a1,a2)) { reduce(); }

  #ifndef CGAL_SIMPLE_NEF_INTERFACE
  template <class Forward_iterator>
  Polynomial(Forward_iterator first, Forward_iterator last) 
  /*{\Mcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial whose coefficients are determined by the iterator range,
  i.e. let $(a_0 = |*first|, a_1 = |*++first|, \ldots a_d = |*it|)$, 
  where |++it == last| then |\Mvar| stores the polynomial $a_1 + a_2 x + 
  \ldots a_d x^d$.}*/
    : Base(Polynomial_rep<NT>(first,last SNIINST)) { reduce(); }

  #else
  #define RPOL(I)\
  Polynomial(I first, I last) : \
  Base(Polynomial_rep<NT>(first,last SNIINST)) { reduce(); }
  RPOL(const NT*)
  // KILL int START
  RPOL(const int*)
  // KILL int END
  // KILL double START
  RPOL(const double*)
  // KILL double END
  #undef RPOL
  #endif // CGAL_SIMPLE_NEF_INTERFACE

  // KILL double START
  Polynomial(double n) : Base(Polynomial_rep<NT>(NT(n))) { reduce(); }
  Polynomial(double n1, double n2) 
    : Base(Polynomial_rep<NT>(NT(n1),NT(n2))) { reduce(); }
  // KILL double END

  // KILL int START
  Polynomial(int n) : Base(Polynomial_rep<NT>(NT(n))) { reduce(); }
  Polynomial(int n1, int n2)
    : Base(Polynomial_rep<NT>(NT(n1),NT(n2))) { reduce(); }
  // KILL int END

  Polynomial(const Polynomial<NT>& p) : Base(p) {}

  protected: // accessing coefficients internally:
  NT& coeff(unsigned int i) 
  { CGAL_assertion(!is_shared() && i<(ptr()->coeff.size()));
    return ptr()->coeff[i]; 
  }
  public:

  /*{\Moperations 3 3 }*/
  const_iterator begin() const { return ptr()->coeff.begin(); }
  /*{\Mop a random access iterator pointing to $a_0$.}*/
  const_iterator end()   const { return ptr()->coeff.end(); }
  /*{\Mop a random access iterator pointing beyond $a_d$.}*/

  int degree() const 
  { return ptr()->coeff.size()-1; } 
  /*{\Mop the degree of the polynomial.}*/

  const NT& operator[](unsigned int i) const 
  { CGAL_assertion( i<(ptr()->coeff.size()) );
    return ptr()->coeff[i]; }
  /*{\Marrop the coefficient $a_i$ of the polynomial.}*/

  const NT& operator[](unsigned int i) 
  { CGAL_assertion( i<(ptr()->coeff.size()) );
    return ptr()->coeff[i]; }

  NT eval_at(const NT& r) const
  /*{\Mop evaluates the polynomial at |r|.}*/
  { CGAL_assertion( degree()>=0 );
    NT res = ptr()->coeff[0], x = r;
    for(int i=1; i<=degree(); ++i) 
    { res += ptr()->coeff[i]*x; x*=r; }
    return res; 
  }

  CGAL::Sign sign() const
  /*{\Mop returns the sign of the limit process for $x \rightarrow \infty$
  (the sign of the leading coefficient).}*/
  { const NT& leading_coeff = ptr()->coeff.back();
    if (leading_coeff < NT(0)) return (CGAL::NEGATIVE);
    if (leading_coeff > NT(0)) return (CGAL::POSITIVE);
    return CGAL::ZERO;
  }

  bool is_zero() const
  /*{\Mop returns true iff |\Mvar| is the zero polynomial.}*/
  { return degree()==0 && ptr()->coeff[0]==NT(0); }

  Polynomial<NT> abs() const
  /*{\Mop returns |-\Mvar| if |\Mvar.sign()==NEGATIVE| and |\Mvar| 
  otherwise.}*/
  { if ( sign()==CGAL::NEGATIVE ) return -*this; return *this; }

#ifndef CGAL_SIMPLE_NEF_INTERFACE

  NT content() const
  /*{\Mop returns the content of |\Mvar| (the gcd of its coefficients).}*/
  { CGAL_assertion( degree()>=0 );
    return gcd_of_range(ptr()->coeff.begin(),ptr()->coeff.end());
  }

#else // CGAL_SIMPLE_NEF_INTERFACE

  NT content() const
  { CGAL_assertion( degree()>=0 );
    const_iterator its=ptr()->coeff.begin(),ite=ptr()->coeff.end();
    NT res = *its++;
    for(; its!=ite; ++its) res = 
      (*its==0 ? res : get_gcd(res, *its, Number_type_traits<NT>::Has_gcd()));
    if (res==0) res = 1;
    return res;
  }

#endif

  static void set_R(const NT& R) { R_ = R; }

  /*{\Mtext Additionally |\Mname| offers standard arithmetic ring
  opertions like |+,-,*,+=,-=,*=|. By means of the sign operation we can
  also offer comparison predicates as $<,>,\leq,\geq$. Where $p_1 < p_2$
  holds iff $|sign|(p_1 - p_2) < 0$. This data type is fully compliant
  to the requirements of CGAL number types. \setopdims{3cm}{2cm}}*/

  friend Polynomial<NT>
    operator - CGAL_NULL_TMPL_ARGS  (const Polynomial<NT>&);   
                          
  friend Polynomial<NT>
    operator + CGAL_NULL_TMPL_ARGS (const Polynomial<NT>&, 
                                    const Polynomial<NT>&);

  friend Polynomial<NT>
    operator - CGAL_NULL_TMPL_ARGS (const Polynomial<NT>&, 
                                    const Polynomial<NT>&);

  friend Polynomial<NT>
    operator * CGAL_NULL_TMPL_ARGS (const Polynomial<NT>&, 
                                    const Polynomial<NT>&);

  friend 
  Polynomial<NT>  operator / CGAL_NULL_TMPL_ARGS 
  (const Polynomial<NT>& p1, const Polynomial<NT>& p2);
  /*{\Mbinopfunc implements polynomial division of |p1| and |p2|. if
  |p1 = p2 * p3| then |p2| is returned. The result is undefined if |p3|
  does not exist in |NT[x]|.  The correct division algorithm is chosen
  according to a traits class |ring_or_field<NT>| provided by the user.
  If |Number_type_traits<NT>::Has_gcd == Tag_true| then the division is
  done by \emph{pseudo division} based on a |gcd| operation of |NT|.  If
  |Number_type_traits<NT>::Has_gcd == Tag_false| then the division is done
  by \emph{euclidean division} based on the division operation of the
  field |NT|.

  \textbf{Note} that |NT=int| quickly leads to overflow
  errors when using this operation.}*/

  /*{\Mtext \headerline{Static member functions}}*/

  static Polynomial<NT> gcd
    (const Polynomial<NT>& p1, const Polynomial<NT>& p2);
  /*{\Mstatic returns the greatest common divisor of |p1| and |p2|.
  \textbf{Note} that |NT=int| quickly leads to overflow errors when
  using this operation.  \precond Requires |NT| to be a unique
  factorization domain, i.e. to provide a |gcd| operation.}*/

  static void pseudo_div
    (const Polynomial<NT>& f, const Polynomial<NT>& g, 
     Polynomial<NT>& q, Polynomial<NT>& r, NT& D);
  /*{\Mstatic implements division with remainder on polynomials of 
  the ring |NT[x]|: $D*f = g*q + r$.  \precond |NT| is a unique
  factorization domain, i.e., there exists a |gcd| operation and an
  integral division operation on |NT|.}*/

  static void euclidean_div 
    (const Polynomial<NT>& f, const Polynomial<NT>& g, 
     Polynomial<NT>& q, Polynomial<NT>& r);
  /*{\Mstatic implements division with remainder on polynomials of 
  the ring |NT[x]|: $f = g*q + r$.  \precond |NT| is a field, i.e.,
  there exists a division operation on |NT|.  }*/

  friend double to_double
  CGAL_NULL_TMPL_ARGS (const Polynomial<NT>& p);


  Polynomial<NT>& operator += (const Polynomial<NT>& p1)
  { copy_on_write();
    int d = std::min(degree(),p1.degree()), i;
    for(i=0; i<=d; ++i) coeff(i) += p1[i];
    while (i<=p1.degree()) ptr()->coeff.push_back(p1[i++]);
    reduce(); return (*this); }

  Polynomial<NT>& operator -= (const Polynomial<NT>& p1)
  { copy_on_write();
    int d = std::min(degree(),p1.degree()), i;
    for(i=0; i<=d; ++i) coeff(i) -= p1[i];
    while (i<=p1.degree()) ptr()->coeff.push_back(-p1[i++]);
    reduce(); return (*this); }

  Polynomial<NT>& operator *= (const Polynomial<NT>& p1)
  { (*this)=(*this)*p1; return (*this); }

  Polynomial<NT>& operator /= (const Polynomial<NT>& p1)
  { (*this)=(*this)/p1; return (*this); }


  //------------------------------------------------------------------
  // SPECIALIZE_MEMBERS(int double) START
    
  Polynomial<NT>& operator += (const NT& num)
  { copy_on_write();
    coeff(0) += (NT)num; return *this; }

  Polynomial<NT>& operator -= (const NT& num)
  { copy_on_write();
    coeff(0) -= (NT)num; return *this; }

  Polynomial<NT>& operator *= (const NT& num)
  { copy_on_write();
    for(int i=0; i<=degree(); ++i) coeff(i) *= (NT)num; 
    reduce(); return *this; }

  Polynomial<NT>& operator /= (const NT& num)
  { copy_on_write(); CGAL_assertion(num!=0);
    for(int i=0; i<=degree(); ++i) coeff(i) /= (NT)num; 
    reduce(); return *this; }
// SPECIALIZING_MEMBERS FOR const int& 
    
  Polynomial<NT>& operator += (const int& num)
  { copy_on_write();
    coeff(0) += (NT)num; return *this; }

  Polynomial<NT>& operator -= (const int& num)
  { copy_on_write();
    coeff(0) -= (NT)num; return *this; }

  Polynomial<NT>& operator *= (const int& num)
  { copy_on_write();
    for(int i=0; i<=degree(); ++i) coeff(i) *= (NT)num; 
    reduce(); return *this; }

  Polynomial<NT>& operator /= (const int& num)
  { copy_on_write(); CGAL_assertion(num!=0);
    for(int i=0; i<=degree(); ++i) coeff(i) /= (NT)num; 
    reduce(); return *this; }
// SPECIALIZING_MEMBERS FOR const double& 
    
  Polynomial<NT>& operator += (const double& num)
  { copy_on_write();
    coeff(0) += (NT)num; return *this; }

  Polynomial<NT>& operator -= (const double& num)
  { copy_on_write();
    coeff(0) -= (NT)num; return *this; }

  Polynomial<NT>& operator *= (const double& num)
  { copy_on_write();
    for(int i=0; i<=degree(); ++i) coeff(i) *= (NT)num; 
    reduce(); return *this; }

  Polynomial<NT>& operator /= (const double& num)
  { copy_on_write(); CGAL_assertion(num!=0);
    for(int i=0; i<=degree(); ++i) coeff(i) /= (NT)num; 
    reduce(); return *this; }

  // SPECIALIZE_MEMBERS(int double) END
  //------------------------------------------------------------------

  void minus_offsetmult(const Polynomial<NT>& p, const NT& b, int k)
  { CGAL_assertion(!is_shared());
    Polynomial<NT> s(size_type(p.degree()+k+1)); // zero entries
    for (int i=k; i <= s.degree(); ++i) s.coeff(i) = b*p[i-k];
    operator-=(s);
  }

};

/*{\Mimplementation This data type is implemented as an item type
via a smart pointer scheme. The coefficients are stored in a vector of
|NT| entries.  The simple arithmetic operations $+,-$ take time
$O(d*T(NT))$, multiplication is quadratic in the maximal degree of the
arguments times $T(NT)$, where $T(NT)$ is the time for a corresponding
operation on two instances of the ring type.}*/


// CLASS TEMPLATE int: 
/*{\Xsubst 
 iterator_traits<Forward_iterator>::value_type#int
CGAL_NULL_TMPL_ARGS#
}*/

/*{\Xanpage{Polynomial}{int}{Polynomials in one variable}{p}}*/

CGAL_TEMPLATE_NULL class Polynomial<int> : 
  public Handle_for< Polynomial_rep<int> >
{
/*{\Xdefinition An instance |\Mvar| of the data type |\Mname| represents
a polynomial $p = a_0 + a_1 x + \ldots a_d x^d $ from the ring |int[x]|. 
The data type offers standard ring operations and a sign operation which 
determines the sign for the limit process $x \rightarrow \infty$. 

|int[x]| becomes a unique factorization domain, if the number type
|int| is either a field type (1) or a unique factorization domain
(2). In both cases there's a polynomial division operation defined.}*/

  /*{\Xtypes 5}*/
  public:
  typedef int NT;
  /*{\Xtypemember the component type representing the coefficients.}*/

  typedef Handle_for< Polynomial_rep<int> > Base;
  typedef Polynomial_rep<int> Rep;
  typedef  Rep::Vector    Vector;
  typedef  Rep::size_type size_type;
  typedef  Rep::iterator  iterator;

  typedef  Rep::const_iterator const_iterator;
  /*{\Xtypemember a random access iterator for read-only access to the
  coefficient vector.}*/

  protected:
  void reduce() { ptr()->reduce(); }
  Vector& coeffs() { return ptr()->coeff; }
  const Vector& coeffs() const { return ptr()->coeff; }
  Polynomial(size_type s) : Base( Polynomial_rep<int>(s) ) {}
  // creates a polynomial of degree s-1

  static int R_; // for visualization only

  /*{\Xcreation 3}*/
  public:

  Polynomial()
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| of undefined
  value. }*/
    : Base( Polynomial_rep<int>() ) {}
   
  Polynomial(const int& a0)
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| representing
  the constant polynomial $a_0$.}*/
    : Base(Polynomial_rep<int>(a0)) { reduce(); }

  Polynomial(int a0, int a1) // af: was const&
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial $a_0 + a_1 x$. }*/
    : Base(Polynomial_rep<int>(a0,a1)) { reduce(); }

  Polynomial(const int& a0, const int& a1,const int& a2)
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial $a_0 + a_1 x + a_2 x^2$. }*/
    : Base(Polynomial_rep<int>(a0,a1,a2)) { reduce(); }

  #ifndef CGAL_SIMPLE_NEF_INTERFACE
  template <class Forward_iterator>
  Polynomial(Forward_iterator first, Forward_iterator last ) 
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial whose coefficients are determined by the iterator range,
  i.e. let $(a_0 = |*first|, a_1 = |*++first|, \ldots a_d = |*it|)$, 
  where |++it == last| then |\Mvar| stores the polynomial $a_1 + a_2 x + 
  \ldots a_d x^d$.}*/
    : Base(Polynomial_rep<int>(first,last SNIINST)) { reduce(); }

  #else
  #define RPOL(I)\
  Polynomial(I first, I last) : \
  Base(Polynomial_rep<int>(first,last SNIINST)) { reduce(); }
  RPOL(const int*)
  // KILL double START
  RPOL(const double*)
  // KILL double END
  #undef RPOL
  #endif // CGAL_SIMPLE_NEF_INTERFACE

  // KILL double START
  Polynomial(double n) : Base(Polynomial_rep<int>(int(n))) { reduce(); }
  Polynomial(double n1, double n2) 
    : Base(Polynomial_rep<int>(int(n1),int(n2))) { reduce(); }
  // KILL double END

  Polynomial(const Polynomial<int>& p) : Base(p) {}

  protected: // accessing coefficients internally:
  int& coeff(unsigned int i) 
  { CGAL_assertion(!is_shared() && i<(ptr()->coeff.size()));
    return ptr()->coeff[i]; 
  }
  public:

  /*{\Xoperations 3 3 }*/
  const_iterator begin() const { return ptr()->coeff.begin(); }
  /*{\Xop a random access iterator pointing to $a_0$.}*/
  const_iterator end()   const { return ptr()->coeff.end(); }
  /*{\Xop a random access iterator pointing beyond $a_d$.}*/

  int degree() const 
  { return ptr()->coeff.size()-1; } 
  /*{\Xop the degree of the polynomial.}*/

  const int& operator[](unsigned int i) const 
  { CGAL_assertion( i<(ptr()->coeff.size()) );
    return ptr()->coeff[i]; }
  /*{\Xarrop the coefficient $a_i$ of the polynomial.}*/

  const int& operator[](unsigned int i) 
  { CGAL_assertion( i<(ptr()->coeff.size()) );
    return ptr()->coeff[i]; }

  int eval_at(const int& r) const
  /*{\Xop evaluates the polynomial at |r|.}*/
  { CGAL_assertion( degree()>=0 );
    int res = ptr()->coeff[0], x = r;
    for(int i=1; i<=degree(); ++i) 
    { res += ptr()->coeff[i]*x; x*=r; }
    return res; 
  }

  CGAL::Sign sign() const
  /*{\Xop returns the sign of the limit process for $x \rightarrow \infty$
  (the sign of the leading coefficient).}*/
  { const int& leading_coeff = ptr()->coeff.back();
    if (leading_coeff < int(0)) return (CGAL::NEGATIVE);
    if (leading_coeff > int(0)) return (CGAL::POSITIVE);
    return CGAL::ZERO;
  }

  bool is_zero() const
  /*{\Xop returns true iff |\Mvar| is the zero polynomial.}*/
  { return degree()==0 && ptr()->coeff[0]==int(0); }

  Polynomial<int> abs() const
  /*{\Xop returns |-\Mvar| if |\Mvar.sign()==NEGATIVE| and |\Mvar| 
  otherwise.}*/
  { if ( sign()==CGAL::NEGATIVE ) return -*this; return *this; }

  #ifndef CGAL_SIMPLE_NEF_INTERFACE

  int content() const
  /*{\Xop returns the content of |\Mvar| (the gcd of its coefficients).
  \precond Requires |int| to provide a |gcd| operation.}*/
  { CGAL_assertion( degree()>=0 );
    return gcd_of_range(ptr()->coeff.begin(),ptr()->coeff.end());
  }

  #else // CGAL_SIMPLE_NEF_INTERFACE

  int content() const
  { CGAL_assertion( degree()>=0 );
    const_iterator its=ptr()->coeff.begin(),ite=ptr()->coeff.end();
    int res = *its++;
    for(; its!=ite; ++its) res = 
      (*its==0 ? res : get_gcd(res, *its, Number_type_traits<NT>::Has_gcd()));
    if (res==0) res = 1;
    return res;
  }

  #endif

  static void set_R(const int& R) { R_ = R; }

  /*{\Xtext Additionally |\Mname| offers standard arithmetic ring
  opertions like |+,-,*,+=,-=,*=|. By means of the sign operation we can
  also offer comparison predicates as $<,>,\leq,\geq$. Where $p_1 < p_2$
  holds iff $|sign|(p_1 - p_2) < 0$. This data type is fully compliant
  to the requirements of CGAL number types. \setopdims{3cm}{2cm}}*/

  friend  Polynomial<int>
    operator - CGAL_NULL_TMPL_ARGS  (const Polynomial<int>&);   
                          
  friend Polynomial<int>
    operator + CGAL_NULL_TMPL_ARGS (const Polynomial<int>&, 
                                    const Polynomial<int>&);

  friend Polynomial<int>
    operator - CGAL_NULL_TMPL_ARGS (const Polynomial<int>&, 
                                    const Polynomial<int>&);

  friend Polynomial<int>
    operator * CGAL_NULL_TMPL_ARGS (const Polynomial<int>&, 
                                    const Polynomial<int>&);

  friend 

  Polynomial<int>  operator / CGAL_NULL_TMPL_ARGS 
  (const Polynomial<int>& p1, const Polynomial<int>& p2);
  /*{\Xbinopfunc implements polynomial division of |p1| and |p2|. if
  |p1 = p2 * p3| then |p2| is returned. The result is undefined if |p3|
  does not exist in |int[x]|.  The correct division algorithm is chosen
  according to a traits class |ring_or_field<int>| provided by the user.
  If |Number_type_traits<int>::Has_gcd == Tag_true| then the division is
  done by \emph{pseudo division} based on a |gcd| operation of |int|.  If
  |Number_type_traits<int>::Has_gcd == Tag_false| then the division is done
  by \emph{euclidean division} based on the division operation of the
  field |int|.

  \textbf{Note} that |int=int| quickly leads to overflow
  errors when using this operation.}*/

  /*{\Xtext \headerline{Static member functions}}*/

  static Polynomial<int> gcd
    (const Polynomial<int>& p1, const Polynomial<int>& p2);
  /*{\Xstatic returns the greatest common divisor of |p1| and |p2|.
  \textbf{Note} that |int=int| quickly leads to overflow errors when
  using this operation.  \precond Requires |int| to be a unique
  factorization domain, i.e. to provide a |gcd| operation.}*/

  static void pseudo_div
    (const Polynomial<int>& f, const Polynomial<int>& g, 
     Polynomial<int>& q, Polynomial<int>& r, int& D);
  /*{\Xstatic implements division with remainder on polynomials of 
  the ring |int[x]|: $D*f = g*q + r$.  \precond |int| is a unique
  factorization domain, i.e., there exists a |gcd| operation and an
  integral division operation on |int|.}*/

  static void euclidean_div 
    (const Polynomial<int>& f, const Polynomial<int>& g, 
     Polynomial<int>& q, Polynomial<int>& r);
  /*{\Xstatic implements division with remainder on polynomials of 
  the ring |int[x]|: $f = g*q + r$.  \precond |int| is a field, i.e.,
  there exists a division operation on |int|.  }*/

  friend double to_double
  CGAL_NULL_TMPL_ARGS (const Polynomial<int>& p);


  Polynomial<int>& operator += (const Polynomial<int>& p1)
  { copy_on_write();
    int d = std::min(degree(),p1.degree()), i;
    for(i=0; i<=d; ++i) coeff(i) += p1[i];
    while (i<=p1.degree()) ptr()->coeff.push_back(p1[i++]);
    reduce(); return (*this); }

  Polynomial<int>& operator -= (const Polynomial<int>& p1)
  { copy_on_write();
    int d = std::min(degree(),p1.degree()), i;
    for(i=0; i<=d; ++i) coeff(i) -= p1[i];
    while (i<=p1.degree()) ptr()->coeff.push_back(-p1[i++]);
    reduce(); return (*this); }

  Polynomial<int>& operator *= (const Polynomial<int>& p1)
  { (*this)=(*this)*p1; return (*this); }

  Polynomial<int>& operator /= (const Polynomial<int>& p1)
  { (*this)=(*this)/p1; return (*this); }


  //------------------------------------------------------------------
  // SPECIALIZE_MEMBERS(int double) START
    
  Polynomial<int>& operator += (const int& num)
  { copy_on_write();
    coeff(0) += (int)num; return *this; }

  Polynomial<int>& operator -= (const int& num)
  { copy_on_write();
    coeff(0) -= (int)num; return *this; }

  Polynomial<int>& operator *= (const int& num)
  { copy_on_write();
    for(int i=0; i<=degree(); ++i) coeff(i) *= (int)num; 
    reduce(); return *this; }

  Polynomial<int>& operator /= (const int& num)
  { copy_on_write(); CGAL_assertion(num!=0);
    for(int i=0; i<=degree(); ++i) coeff(i) /= (int)num; 
    reduce(); return *this; }
// SPECIALIZING_MEMBERS FOR const double& 
    
  Polynomial<int>& operator += (const double& num)
  { copy_on_write();
    coeff(0) += (int)num; return *this; }

  Polynomial<int>& operator -= (const double& num)
  { copy_on_write();
    coeff(0) -= (int)num; return *this; }

  Polynomial<int>& operator *= (const double& num)
  { copy_on_write();
    for(int i=0; i<=degree(); ++i) coeff(i) *= (int)num; 
    reduce(); return *this; }

  Polynomial<int>& operator /= (const double& num)
  { copy_on_write(); CGAL_assertion(num!=0);
    for(int i=0; i<=degree(); ++i) coeff(i) /= (int)num; 
    reduce(); return *this; }

  // SPECIALIZE_MEMBERS(int double) END
  //------------------------------------------------------------------

  void minus_offsetmult(const Polynomial<int>& p, const int& b, int k)
  { CGAL_assertion(!is_shared());
    Polynomial<int> s(size_type(p.degree()+k+1)); // zero entries
    for (int i=k; i <= s.degree(); ++i) s.coeff(i) = b*p[i-k];
    operator-=(s);
  }

};

/*{\Ximplementation This data type is implemented as an item type
via a smart pointer scheme. The coefficients are stored in a vector of
|int| entries.  The simple arithmetic operations $+,-$ take time
$O(d*T(int))$, multiplication is quadratic in the maximal degree of the
arguments times $T(int)$, where $T(int)$ is the time for a corresponding
operation on two instances of the ring type.}*/


// CLASS TEMPLATE double: 
/*{\Xsubst 
 iterator_traits<Forward_iterator>::value_type#double
CGAL_NULL_TMPL_ARGS#
}*/

/*{\Xanpage{Polynomial}{double}{Polynomials in one variable}{p}}*/

CGAL_TEMPLATE_NULL class Polynomial<double> : 
  public Handle_for< Polynomial_rep<double> >
{
/*{\Xdefinition An instance |\Mvar| of the data type |\Mname| represents
a polynomial $p = a_0 + a_1 x + \ldots a_d x^d $ from the ring |double[x]|. 
The data type offers standard ring operations and a sign operation which 
determines the sign for the limit process $x \rightarrow \infty$. 

|double[x]| becomes a unique factorization domain, if the number type
|double| is either a field type (1) or a unique factorization domain
(2). In both cases there's a polynomial division operation defined.}*/

  /*{\Xtypes 5}*/
  public:
  typedef double NT;
  /*{\Xtypemember the component type representing the coefficients.}*/

  typedef Handle_for< Polynomial_rep<double> > Base;
  typedef Polynomial_rep<double> Rep;
  typedef  Rep::Vector    Vector;
  typedef  Rep::size_type size_type;
  typedef  Rep::iterator  iterator;

  typedef  Rep::const_iterator const_iterator;
  /*{\Xtypemember a random access iterator for read-only access to the
  coefficient vector.}*/

  protected:
  void reduce() { ptr()->reduce(); }
  Vector& coeffs() { return ptr()->coeff; }
  const Vector& coeffs() const { return ptr()->coeff; }
  Polynomial(size_type s) : Base( Polynomial_rep<double>(s) ) {}
  // creates a polynomial of degree s-1

  static double R_; // for visualization only

  /*{\Xcreation 3}*/
  public:

  Polynomial()
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| of undefined
  value. }*/
    : Base( Polynomial_rep<double>() ) {}
   
  Polynomial(const double& a0)
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| representing
  the constant polynomial $a_0$.}*/
    : Base(Polynomial_rep<double>(a0)) { reduce(); }

  Polynomial(const double& a0, const double& a1)
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial $a_0 + a_1 x$. }*/
    : Base(Polynomial_rep<double>(a0,a1)) { reduce(); }

  Polynomial(const double& a0, const double& a1,const double& a2)
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial $a_0 + a_1 x + a_2 x^2$. }*/
    : Base(Polynomial_rep<double>(a0,a1,a2)) { reduce(); }

  #ifndef CGAL_SIMPLE_NEF_INTERFACE
  template <class Forward_iterator>
  Polynomial(Forward_iterator first, Forward_iterator last ) 
  /*{\Xcreate introduces a variable |\Mvar| of type |\Mname| representing
  the polynomial whose coefficients are determined by the iterator range,
  i.e. let $(a_0 = |*first|, a_1 = |*++first|, \ldots a_d = |*it|)$, 
  where |++it == last| then |\Mvar| stores the polynomial $a_1 + a_2 x + 
  \ldots a_d x^d$.}*/
    : Base(Polynomial_rep<double>(first,last SNIINST)) { reduce(); }

  #else
  #define RPOL(I)\
  Polynomial(I first, I last) : \
  Base(Polynomial_rep<double>(first,last SNIINST)) { reduce(); }
  RPOL(const double*)
  // KILL int START
  RPOL(const int*)
  // KILL int END
  #undef RPOL
  #endif // CGAL_SIMPLE_NEF_INTERFACE

  // KILL int START
  Polynomial(int n) : Base(Polynomial_rep<double>(double(n))) { reduce(); }
  Polynomial(int n1, int n2)
    : Base(Polynomial_rep<double>(double(n1),double(n2))) { reduce(); }
  // KILL int END

  Polynomial(const Polynomial<double>& p) : Base(p) {}

  protected: // accessing coefficients internally:
  double& coeff(unsigned int i) 
  { CGAL_assertion(!is_shared() && i<(ptr()->coeff.size()));
    return ptr()->coeff[i]; 
  }
  public:

  /*{\Xoperations 3 3 }*/
  const_iterator begin() const { return ptr()->coeff.begin(); }
  /*{\Xop a random access iterator pointing to $a_0$.}*/
  const_iterator end()   const { return ptr()->coeff.end(); }
  /*{\Xop a random access iterator pointing beyond $a_d$.}*/

  int degree() const 
  { return ptr()->coeff.size()-1; } 
  /*{\Xop the degree of the polynomial.}*/

  const double& operator[](unsigned int i) const 
  { CGAL_assertion( i<(ptr()->coeff.size()) );
    return ptr()->coeff[i]; }
  /*{\Xarrop the coefficient $a_i$ of the polynomial.}*/

  const double& operator[](unsigned int i) 
  { CGAL_assertion( i<(ptr()->coeff.size()) );
    return ptr()->coeff[i]; }

  double eval_at(const double& r) const
  /*{\Xop evaluates the polynomial at |r|.}*/
  { CGAL_assertion( degree()>=0 );
    double res = ptr()->coeff[0], x = r;
    for(int i=1; i<=degree(); ++i) 
    { res += ptr()->coeff[i]*x; x*=r; }
    return res; 
  }

  CGAL::Sign sign() const
  /*{\Xop returns the sign of the limit process for $x \rightarrow \infty$
  (the sign of the leading coefficient).}*/
  { const double& leading_coeff = ptr()->coeff.back();
    if (leading_coeff < double(0)) return (CGAL::NEGATIVE);
    if (leading_coeff > double(0)) return (CGAL::POSITIVE);
    return CGAL::ZERO;
  }

  bool is_zero() const
  /*{\Xop returns true iff |\Mvar| is the zero polynomial.}*/
  { return degree()==0 && ptr()->coeff[0]==double(0); }

  Polynomial<double> abs() const
  /*{\Xop returns |-\Mvar| if |\Mvar.sign()==NEGATIVE| and |\Mvar| 
  otherwise.}*/
  { if ( sign()==CGAL::NEGATIVE ) return -*this; return *this; }

  #ifndef CGAL_SIMPLE_NEF_INTERFACE

  double content() const
  /*{\Xop returns the content of |\Mvar| (the gcd of its coefficients).
  \precond Requires |double| to provide a |gdc| operation.}*/
  { CGAL_assertion( degree()>=0 );
    return gcd_of_range(ptr()->coeff.begin(),ptr()->coeff.end());
  }

  #else // CGAL_SIMPLE_NEF_INTERFACE

  double content() const
  { CGAL_assertion( degree()>=0 );
    const_iterator its=ptr()->coeff.begin(),ite=ptr()->coeff.end();
    double res = *its++;
    for(; its!=ite; ++its) res = 
      (*its==0 ? res : get_gcd(res, *its, Number_type_traits<NT>::Has_gcd()));
    if (res==0) res = 1;
    return res;
  }

  #endif

  static void set_R(const double& R) { R_ = R; }

  /*{\Xtext Additionally |\Mname| offers standard arithmetic ring
  opertions like |+,-,*,+=,-=,*=|. By means of the sign operation we can
  also offer comparison predicates as $<,>,\leq,\geq$. Where $p_1 < p_2$
  holds iff $|sign|(p_1 - p_2) < 0$. This data type is fully compliant
  to the requirements of CGAL number types. \setopdims{3cm}{2cm}}*/

  friend  Polynomial<double>
    operator - CGAL_NULL_TMPL_ARGS  (const Polynomial<double>&);   
                          
  friend Polynomial<double>
    operator + CGAL_NULL_TMPL_ARGS (const Polynomial<double>&, 
                                    const Polynomial<double>&);

  friend Polynomial<double>
    operator - CGAL_NULL_TMPL_ARGS (const Polynomial<double>&, 
                                    const Polynomial<double>&);

  friend Polynomial<double>
    operator * CGAL_NULL_TMPL_ARGS (const Polynomial<double>&, 
                                    const Polynomial<double>&);

  friend 

  Polynomial<double>  operator / CGAL_NULL_TMPL_ARGS 
  (const Polynomial<double>& p1, const Polynomial<double>& p2);
  /*{\Xbinopfunc implements polynomial division of |p1| and |p2|. if
  |p1 = p2 * p3| then |p2| is returned. The result is undefined if |p3|
  does not exist in |double[x]|.  The correct division algorithm is chosen
  according to a traits class |ring_or_field<double>| provided by the user.
  If |Number_type_traits<double>::Has_gcd == Tag_true| then the division is
  done by \emph{pseudo division} based on a |gcd| operation of |double|.  If
  |Number_type_traits<double>::Has_gcd == Tag_false| then the division is done
  by \emph{euclidean division} based on the division operation of the
  field |double|.

  \textbf{Note} that |double=int| quickly leads to overflow
  errors when using this operation.}*/

  /*{\Xtext \headerline{Static member functions}}*/

  static Polynomial<double> gcd
    (const Polynomial<double>& p1, const Polynomial<double>& p2);
  /*{\Xstatic returns the greatest common divisor of |p1| and |p2|.
  \textbf{Note} that |double=int| quickly leads to overflow errors when
  using this operation.  \precond Requires |double| to be a unique
  factorization domain, i.e. to provide a |gdc| operation.}*/

  static void pseudo_div
    (const Polynomial<double>& f, const Polynomial<double>& g, 
     Polynomial<double>& q, Polynomial<double>& r, double& D);
  /*{\Xstatic implements division with remainder on polynomials of 
  the ring |double[x]|: $D*f = g*q + r$.  \precond |double| is a unique
  factorization domain, i.e., there exists a |gcd| operation and an
  integral division operation on |double|.}*/

  static void euclidean_div 
    (const Polynomial<double>& f, const Polynomial<double>& g, 
     Polynomial<double>& q, Polynomial<double>& r);
  /*{\Xstatic implements division with remainder on polynomials of 
  the ring |double[x]|: $f = g*q + r$.  \precond |double| is a field, i.e.,
  there exists a division operation on |double|.  }*/

  friend double to_double
  CGAL_NULL_TMPL_ARGS (const Polynomial<double>& p);


  Polynomial<double>& operator += (const Polynomial<double>& p1)
  { copy_on_write();
    int d = std::min(degree(),p1.degree()), i;
    for(i=0; i<=d; ++i) coeff(i) += p1[i];
    while (i<=p1.degree()) ptr()->coeff.push_back(p1[i++]);
    reduce(); return (*this); }

  Polynomial<double>& operator -= (const Polynomial<double>& p1)
  { copy_on_write();
    int d = std::min(degree(),p1.degree()), i;
    for(i=0; i<=d; ++i) coeff(i) -= p1[i];
    while (i<=p1.degree()) ptr()->coeff.push_back(-p1[i++]);
    reduce(); return (*this); }

  Polynomial<double>& operator *= (const Polynomial<double>& p1)
  { (*this)=(*this)*p1; return (*this); }

  Polynomial<double>& operator /= (const Polynomial<double>& p1)
  { (*this)=(*this)/p1; return (*this); }


  //------------------------------------------------------------------
  // SPECIALIZE_MEMBERS(int double) START
    
  Polynomial<double>& operator += (const double& num)
  { copy_on_write();
    coeff(0) += (double)num; return *this; }

  Polynomial<double>& operator -= (const double& num)
  { copy_on_write();
    coeff(0) -= (double)num; return *this; }

  Polynomial<double>& operator *= (const double& num)
  { copy_on_write();
    for(int i=0; i<=degree(); ++i) coeff(i) *= (double)num; 
    reduce(); return *this; }

  Polynomial<double>& operator /= (const double& num)
  { copy_on_write(); CGAL_assertion(num!=0);
    for(int i=0; i<=degree(); ++i) coeff(i) /= (double)num; 
    reduce(); return *this; }
// SPECIALIZING_MEMBERS FOR const int& 
    
  Polynomial<double>& operator += (const int& num)
  { copy_on_write();
    coeff(0) += (double)num; return *this; }

  Polynomial<double>& operator -= (const int& num)
  { copy_on_write();
    coeff(0) -= (double)num; return *this; }

  Polynomial<double>& operator *= (const int& num)
  { copy_on_write();
    for(int i=0; i<=degree(); ++i) coeff(i) *= (double)num; 
    reduce(); return *this; }

  Polynomial<double>& operator /= (const int& num)
  { copy_on_write(); CGAL_assertion(num!=0);
    for(int i=0; i<=degree(); ++i) coeff(i) /= (double)num; 
    reduce(); return *this; }

  // SPECIALIZE_MEMBERS(int double) END
  //------------------------------------------------------------------

  void minus_offsetmult(const Polynomial<double>& p, const double& b, int k)
  { CGAL_assertion(!is_shared());
    Polynomial<double> s(size_type(p.degree()+k+1)); // zero entries
    for (int i=k; i <= s.degree(); ++i) s.coeff(i) = b*p[i-k];
    operator-=(s);
  }

};

/*{\Ximplementation This data type is implemented as an item type
via a smart pointer scheme. The coefficients are stored in a vector of
|double| entries.  The simple arithmetic operations $+,-$ take time
$O(d*T(double))$, multiplication is quadratic in the maximal degree of the
arguments times $T(double)$, where $T(double)$ is the time for a corresponding
operation on two instances of the ring type.}*/


// SPECIALIZE_CLASS(NT,int double) END

template <class NT> NT Polynomial<NT>::R_;
int    Polynomial<int>::R_;
double Polynomial<double>::R_;

template <class NT> double to_double 
  (const Polynomial<NT>& p) 
  { return (CGAL::to_double(p.eval_at(Polynomial<NT>::R_))); }

template <class NT> bool is_valid 
  (const Polynomial<NT>& p) 
  { return (CGAL::is_valid(p[0])); }

template <class NT> bool is_finite 
  (const Polynomial<NT>& p) 
  { return CGAL::is_finite(p[0]); }

template <class NT> CGAL::io_Operator 
  io_tag(const Polynomial<NT>&) 
  { return CGAL::io_Operator(); }


template <class NT> 
Polynomial<NT> operator - (const Polynomial<NT>& p)
{
  CGAL_assertion(p.degree()>=0);
  Polynomial<NT> res(p.coeffs().begin(),p.coeffs().end()); 
  typename Polynomial<NT>::iterator it, ite=res.coeffs().end();
  for(it=res.coeffs().begin(); it!=ite; ++it) *it = -*it;
  return res;
}

#if defined(_MSC_VER)
Polynomial<int> operator - (const Polynomial<int>& p)
{
  CGAL_assertion(p.degree()>=0);
  Polynomial<int> res(p.coeffs().begin(),p.coeffs().end());
  Polynomial<int>::iterator it, ite=res.coeffs().end();
  for(it=res.coeffs().begin(); it!=ite; ++it) *it = -*it;
  return res;
}

Polynomial<double> operator - (const Polynomial<double>& p)
{
  CGAL_assertion(p.degree()>=0);
  Polynomial<double> res(p.coeffs().begin(),p.coeffs().end());
  Polynomial<double>::iterator it, ite=res.coeffs().end();
  for(it=res.coeffs().begin(); it!=ite; ++it) *it = -*it;
  return res;
}
#endif

template <class NT> 
Polynomial<NT> operator + (const Polynomial<NT>& p1, 
                            const Polynomial<NT>& p2)
{ 
  typedef typename Polynomial<NT>::size_type size_type;
  CGAL_assertion(p1.degree()>=0 && p2.degree()>=0);
  bool p1d_smaller_p2d = p1.degree() < p2.degree();
  int min,max,i;
  if (p1d_smaller_p2d) { min = p1.degree(); max = p2.degree(); }
  else                 { max = p1.degree(); min = p2.degree(); }
  Polynomial<NT>  p( size_type(max + 1));
  for (i = 0; i <= min; ++i ) p.coeff(i) = p1[i]+p2[i];
  if (p1d_smaller_p2d)  for (; i <= max; ++i ) p.coeff(i)=p2[i];
  else /* p1d >= p2d */ for (; i <= max; ++i ) p.coeff(i)=p1[i];
  p.reduce();
  return p;
}

template <class NT> 
Polynomial<NT> operator - (const Polynomial<NT>& p1, 
                            const Polynomial<NT>& p2)
{ 
  typedef typename Polynomial<NT>::size_type size_type;
  CGAL_assertion(p1.degree()>=0 && p2.degree()>=0);
  bool p1d_smaller_p2d = p1.degree() < p2.degree();
  int min,max,i;
  if (p1d_smaller_p2d) { min = p1.degree(); max = p2.degree(); }
  else                 { max = p1.degree(); min = p2.degree(); }
  Polynomial<NT>  p( size_type(max+1) );
  for (i = 0; i <= min; ++i ) p.coeff(i)=p1[i]-p2[i];
  if (p1d_smaller_p2d)  for (; i <= max; ++i ) p.coeff(i)= -p2[i];
  else /* p1d >= p2d */ for (; i <= max; ++i ) p.coeff(i)=  p1[i];
  p.reduce();
  return p;
}

template <class NT> 
Polynomial<NT> operator * (const Polynomial<NT>& p1, 
                            const Polynomial<NT>& p2)
{
  typedef typename Polynomial<NT>::size_type size_type;
  CGAL_assertion(p1.degree()>=0 && p2.degree()>=0);
  Polynomial<NT>  p( size_type(p1.degree()+p2.degree()+1) ); 
  // initialized with zeros
  for (int i=0; i <= p1.degree(); ++i)
    for (int j=0; j <= p2.degree(); ++j)
      p.coeff(i+j) += (p1[i]*p2[j]); 
  p.reduce();
  return p;
}

template <class NT> inline
Polynomial<NT> operator / (const Polynomial<NT>& p1, 
                            const Polynomial<NT>& p2)
{ return divop(p1,p2,Number_type_traits<NT>::Has_gcd()); }


template <class NT> 
Polynomial<NT> divop (const Polynomial<NT>& p1, 
                       const Polynomial<NT>& p2,
                       Tag_false)
{ CGAL_assertion(!p2.is_zero());
  if (p1.is_zero()) return 0;
  Polynomial<NT> q,r;
  Polynomial<NT>::euclidean_div(p1,p2,q,r);
  CGAL_postcondition( (p2*q+r==p1) );
  return q;
}


template <class NT> 
Polynomial<NT> divop (const Polynomial<NT>& p1, const Polynomial<NT>& p2,
                       Tag_true)
{ CGAL_assertion(!p2.is_zero());
  if (p1.is_zero()) return 0;
  Polynomial<NT> q,r; NT D; 
  Polynomial<NT>::pseudo_div(p1,p2,q,r,D); 
  CGAL_postcondition( (p2*q+r==p1*Polynomial<NT>(D)) );
  return q/=D;
}


template <class NT> 
inline Polynomial<NT> 
gcd(const Polynomial<NT>& p1, const Polynomial<NT>& p2)
{ return Polynomial<NT>::gcd(p1,p2); }

template <class NT> bool operator == 
  (const Polynomial<NT>& p1, const Polynomial<NT>& p2)
  { return ( (p1-p2).sign() == CGAL::ZERO ); }    

template <class NT> bool operator != 
  (const Polynomial<NT>& p1, const Polynomial<NT>& p2)
  { return ( (p1-p2).sign() != CGAL::ZERO ); }    

template <class NT> bool operator <  
  (const Polynomial<NT>& p1, const Polynomial<NT>& p2)
  { return ( (p1-p2).sign() == CGAL::NEGATIVE ); }    

template <class NT> bool operator <= 
  (const Polynomial<NT>& p1, const Polynomial<NT>& p2)
  { return ( (p1-p2).sign() != CGAL::POSITIVE ); }    

template <class NT> bool operator >  
  (const Polynomial<NT>& p1, const Polynomial<NT>& p2)
  { return ( (p1-p2).sign() == CGAL::POSITIVE ); }    

template <class NT> bool operator >= 
  (const Polynomial<NT>& p1, const Polynomial<NT>& p2)
  { return ( (p1-p2).sign() != CGAL::NEGATIVE ); }    

#if ! defined(_MSC_VER)
template <class NT> CGAL::Sign 
  sign(const Polynomial<NT>& p)
  { return p.sign(); }
#endif // collides with global CGAL sign

#if ! defined(_MSC_VER) || _MSC_VER >= 1300
//------------------------------------------------------------------
// SPECIALIZE_FUNCTION(NT,int double) START
// SPECIALIZING inline to :

  // lefthand side
  inline    Polynomial<int> operator + 
  (const int& num, const Polynomial<int>& p2)
  { return (Polynomial<int>(num) + p2); }
  inline    Polynomial<int> operator - 
  (const int& num, const Polynomial<int>& p2)
  { return (Polynomial<int>(num) - p2); }
  inline    Polynomial<int> operator * 
  (const int& num, const Polynomial<int>& p2)
  { return (Polynomial<int>(num) * p2); }
  inline    Polynomial<int> operator / 
  (const int& num, const Polynomial<int>& p2)
  { return (Polynomial<int>(num)/p2); }

  // righthand side
  inline    Polynomial<int> operator + 
  (const Polynomial<int>& p1, const int& num)
  { return (p1 + Polynomial<int>(num)); }
  inline    Polynomial<int> operator - 
  (const Polynomial<int>& p1, const int& num)
  { return (p1 - Polynomial<int>(num)); }
  inline    Polynomial<int> operator * 
  (const Polynomial<int>& p1, const int& num)
  { return (p1 * Polynomial<int>(num)); }
  inline    Polynomial<int> operator / 
  (const Polynomial<int>& p1, const int& num)
  { return (p1 / Polynomial<int>(num)); }


  // lefthand side
  inline    bool operator ==  
  (const int& num, const Polynomial<int>& p) 
  { return ( (Polynomial<int>(num)-p).sign() == CGAL::ZERO );}
  inline    bool operator != 
  (const int& num, const Polynomial<int>& p) 
  { return ( (Polynomial<int>(num)-p).sign() != CGAL::ZERO );}
  inline    bool operator <  
  (const int& num, const Polynomial<int>& p) 
  { return ( (Polynomial<int>(num)-p).sign() == CGAL::NEGATIVE );}
  inline    bool operator <=  
  (const int& num, const Polynomial<int>& p) 
  { return ( (Polynomial<int>(num)-p).sign() != CGAL::POSITIVE );}
  inline    bool operator >  
  (const int& num, const Polynomial<int>& p) 
  { return ( (Polynomial<int>(num)-p).sign() == CGAL::POSITIVE );}
  inline    bool operator >=  
  (const int& num, const Polynomial<int>& p) 
  { return ( (Polynomial<int>(num)-p).sign() != CGAL::NEGATIVE );}

  // righthand side
  inline    bool operator ==
  (const Polynomial<int>& p, const int& num) 
  { return ( (p-Polynomial<int>(num)).sign() == CGAL::ZERO );}
  inline    bool operator !=
  (const Polynomial<int>& p, const int& num) 
  { return ( (p-Polynomial<int>(num)).sign() != CGAL::ZERO );}
  inline    bool operator < 
  (const Polynomial<int>& p, const int& num) 
  { return ( (p-Polynomial<int>(num)).sign() == CGAL::NEGATIVE );}
  inline    bool operator <= 
  (const Polynomial<int>& p, const int& num) 
  { return ( (p-Polynomial<int>(num)).sign() != CGAL::POSITIVE );}
  inline    bool operator > 
  (const Polynomial<int>& p, const int& num) 
  { return ( (p-Polynomial<int>(num)).sign() == CGAL::POSITIVE );}
  inline    bool operator >=
  (const Polynomial<int>& p, const int& num) 
  { return ( (p-Polynomial<int>(num)).sign() != CGAL::NEGATIVE );}

// SPECIALIZING pure int params:

  // lefthand side
  template <class NT>    Polynomial<NT> operator + 
  (const int& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) + p2); }
  template <class NT>    Polynomial<NT> operator - 
  (const int& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) - p2); }
  template <class NT>    Polynomial<NT> operator * 
  (const int& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) * p2); }
  template <class NT>    Polynomial<NT> operator / 
  (const int& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num)/p2); }

  // righthand side
  template <class NT>    Polynomial<NT> operator + 
  (const Polynomial<NT>& p1, const int& num)
  { return (p1 + Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator - 
  (const Polynomial<NT>& p1, const int& num)
  { return (p1 - Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator * 
  (const Polynomial<NT>& p1, const int& num)
  { return (p1 * Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator / 
  (const Polynomial<NT>& p1, const int& num)
  { return (p1 / Polynomial<NT>(num)); }


  // lefthand side
  template <class NT>    bool operator ==  
  (const int& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::ZERO );}
  template <class NT>    bool operator != 
  (const int& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::ZERO );}
  template <class NT>    bool operator <  
  (const int& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::NEGATIVE );}
  template <class NT>    bool operator <=  
  (const int& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::POSITIVE );}
  template <class NT>    bool operator >  
  (const int& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::POSITIVE );}
  template <class NT>    bool operator >=  
  (const int& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::NEGATIVE );}

  // righthand side
  template <class NT>    bool operator ==
  (const Polynomial<NT>& p, const int& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::ZERO );}
  template <class NT>    bool operator !=
  (const Polynomial<NT>& p, const int& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::ZERO );}
  template <class NT>    bool operator < 
  (const Polynomial<NT>& p, const int& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::NEGATIVE );}
  template <class NT>    bool operator <= 
  (const Polynomial<NT>& p, const int& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::POSITIVE );}
  template <class NT>    bool operator > 
  (const Polynomial<NT>& p, const int& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::POSITIVE );}
  template <class NT>    bool operator >=
  (const Polynomial<NT>& p, const int& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::NEGATIVE );}

// SPECIALIZING inline to :

  // lefthand side
  inline    Polynomial<double> operator + 
  (const double& num, const Polynomial<double>& p2)
  { return (Polynomial<double>(num) + p2); }
  inline    Polynomial<double> operator - 
  (const double& num, const Polynomial<double>& p2)
  { return (Polynomial<double>(num) - p2); }
  inline    Polynomial<double> operator * 
  (const double& num, const Polynomial<double>& p2)
  { return (Polynomial<double>(num) * p2); }
  inline    Polynomial<double> operator / 
  (const double& num, const Polynomial<double>& p2)
  { return (Polynomial<double>(num)/p2); }

  // righthand side
  inline    Polynomial<double> operator + 
  (const Polynomial<double>& p1, const double& num)
  { return (p1 + Polynomial<double>(num)); }
  inline    Polynomial<double> operator - 
  (const Polynomial<double>& p1, const double& num)
  { return (p1 - Polynomial<double>(num)); }
  inline    Polynomial<double> operator * 
  (const Polynomial<double>& p1, const double& num)
  { return (p1 * Polynomial<double>(num)); }
  inline    Polynomial<double> operator / 
  (const Polynomial<double>& p1, const double& num)
  { return (p1 / Polynomial<double>(num)); }


  // lefthand side
  inline    bool operator ==  
  (const double& num, const Polynomial<double>& p) 
  { return ( (Polynomial<double>(num)-p).sign() == CGAL::ZERO );}
  inline    bool operator != 
  (const double& num, const Polynomial<double>& p) 
  { return ( (Polynomial<double>(num)-p).sign() != CGAL::ZERO );}
  inline    bool operator <  
  (const double& num, const Polynomial<double>& p) 
  { return ( (Polynomial<double>(num)-p).sign() == CGAL::NEGATIVE );}
  inline    bool operator <=  
  (const double& num, const Polynomial<double>& p) 
  { return ( (Polynomial<double>(num)-p).sign() != CGAL::POSITIVE );}
  inline    bool operator >  
  (const double& num, const Polynomial<double>& p) 
  { return ( (Polynomial<double>(num)-p).sign() == CGAL::POSITIVE );}
  inline    bool operator >=  
  (const double& num, const Polynomial<double>& p) 
  { return ( (Polynomial<double>(num)-p).sign() != CGAL::NEGATIVE );}

  // righthand side
  inline    bool operator ==
  (const Polynomial<double>& p, const double& num) 
  { return ( (p-Polynomial<double>(num)).sign() == CGAL::ZERO );}
  inline    bool operator !=
  (const Polynomial<double>& p, const double& num) 
  { return ( (p-Polynomial<double>(num)).sign() != CGAL::ZERO );}
  inline    bool operator < 
  (const Polynomial<double>& p, const double& num) 
  { return ( (p-Polynomial<double>(num)).sign() == CGAL::NEGATIVE );}
  inline    bool operator <= 
  (const Polynomial<double>& p, const double& num) 
  { return ( (p-Polynomial<double>(num)).sign() != CGAL::POSITIVE );}
  inline    bool operator > 
  (const Polynomial<double>& p, const double& num) 
  { return ( (p-Polynomial<double>(num)).sign() == CGAL::POSITIVE );}
  inline    bool operator >=
  (const Polynomial<double>& p, const double& num) 
  { return ( (p-Polynomial<double>(num)).sign() != CGAL::NEGATIVE );}

// SPECIALIZING pure double params:

  // lefthand side
  template <class NT>    Polynomial<NT> operator + 
  (const double& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) + p2); }
  template <class NT>    Polynomial<NT> operator - 
  (const double& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) - p2); }
  template <class NT>    Polynomial<NT> operator * 
  (const double& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) * p2); }
  template <class NT>    Polynomial<NT> operator / 
  (const double& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num)/p2); }

  // righthand side
  template <class NT>    Polynomial<NT> operator + 
  (const Polynomial<NT>& p1, const double& num)
  { return (p1 + Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator - 
  (const Polynomial<NT>& p1, const double& num)
  { return (p1 - Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator * 
  (const Polynomial<NT>& p1, const double& num)
  { return (p1 * Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator / 
  (const Polynomial<NT>& p1, const double& num)
  { return (p1 / Polynomial<NT>(num)); }


  // lefthand side
  template <class NT>    bool operator ==  
  (const double& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::ZERO );}
  template <class NT>    bool operator != 
  (const double& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::ZERO );}
  template <class NT>    bool operator <  
  (const double& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::NEGATIVE );}
  template <class NT>    bool operator <=  
  (const double& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::POSITIVE );}
  template <class NT>    bool operator >  
  (const double& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::POSITIVE );}
  template <class NT>    bool operator >=  
  (const double& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::NEGATIVE );}

  // righthand side
  template <class NT>    bool operator ==
  (const Polynomial<NT>& p, const double& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::ZERO );}
  template <class NT>    bool operator !=
  (const Polynomial<NT>& p, const double& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::ZERO );}
  template <class NT>    bool operator < 
  (const Polynomial<NT>& p, const double& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::NEGATIVE );}
  template <class NT>    bool operator <= 
  (const Polynomial<NT>& p, const double& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::POSITIVE );}
  template <class NT>    bool operator > 
  (const Polynomial<NT>& p, const double& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::POSITIVE );}
  template <class NT>    bool operator >=
  (const Polynomial<NT>& p, const double& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::NEGATIVE );}

// SPECIALIZE_FUNCTION ORIGINAL

  // lefthand side
  template <class NT>    Polynomial<NT> operator + 
  (const NT& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) + p2); }
  template <class NT>    Polynomial<NT> operator - 
  (const NT& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) - p2); }
  template <class NT>    Polynomial<NT> operator * 
  (const NT& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num) * p2); }
  template <class NT>    Polynomial<NT> operator / 
  (const NT& num, const Polynomial<NT>& p2)
  { return (Polynomial<NT>(num)/p2); }

  // righthand side
  template <class NT>    Polynomial<NT> operator + 
  (const Polynomial<NT>& p1, const NT& num)
  { return (p1 + Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator - 
  (const Polynomial<NT>& p1, const NT& num)
  { return (p1 - Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator * 
  (const Polynomial<NT>& p1, const NT& num)
  { return (p1 * Polynomial<NT>(num)); }
  template <class NT>    Polynomial<NT> operator / 
  (const Polynomial<NT>& p1, const NT& num)
  { return (p1 / Polynomial<NT>(num)); }


  // lefthand side
  template <class NT>    bool operator ==  
  (const NT& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::ZERO );}
  template <class NT>    bool operator != 
  (const NT& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::ZERO );}
  template <class NT>    bool operator <  
  (const NT& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::NEGATIVE );}
  template <class NT>    bool operator <=  
  (const NT& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::POSITIVE );}
  template <class NT>    bool operator >  
  (const NT& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() == CGAL::POSITIVE );}
  template <class NT>    bool operator >=  
  (const NT& num, const Polynomial<NT>& p) 
  { return ( (Polynomial<NT>(num)-p).sign() != CGAL::NEGATIVE );}

  // righthand side
  template <class NT>    bool operator ==
  (const Polynomial<NT>& p, const NT& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::ZERO );}
  template <class NT>    bool operator !=
  (const Polynomial<NT>& p, const NT& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::ZERO );}
  template <class NT>    bool operator < 
  (const Polynomial<NT>& p, const NT& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::NEGATIVE );}
  template <class NT>    bool operator <= 
  (const Polynomial<NT>& p, const NT& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::POSITIVE );}
  template <class NT>    bool operator > 
  (const Polynomial<NT>& p, const NT& num) 
  { return ( (p-Polynomial<NT>(num)).sign() == CGAL::POSITIVE );}
  template <class NT>    bool operator >=
  (const Polynomial<NT>& p, const NT& num) 
  { return ( (p-Polynomial<NT>(num)).sign() != CGAL::NEGATIVE );}

// SPECIALIZE_FUNCTION(NT,int double) END
//------------------------------------------------------------------
#endif // _MSC_VER CGAL_CFG_MATCHING_BUG_2


template <class NT> 
void print_monomial(std::ostream& os, const NT& n, int i)
{
  if (i==0) os << n;
  if (i==1) os << n << "R";
  if (i>1)  os << n << "R^" << i;
}

#define POLYNOMIAL_EXPLICIT_OUTPUT

// I/O 
template <class NT>
std::ostream& operator << (std::ostream& os, const Polynomial<NT>& p)
{
  int i;
  switch( os.iword(CGAL::IO::mode) )
  {
    case CGAL::IO::ASCII :
      os << p.degree() << ' ';
      for(i=0; i<=p.degree(); ++i) 
        os << p[i] << ' ';
      return os;
    case CGAL::IO::BINARY :
      CGAL::write(os, p.degree());
      for(i=0; i<=p.degree(); ++i) 
        CGAL::write(os, p[i]);
      return os;
    default: 
#ifndef POLYNOMIAL_EXPLICIT_OUTPUT
      os << "Polynomial(" << p.degree() << ", ";
      for(i=0; i<=p.degree(); ++i) {
        os << p[i];
        if (i < p.degree()) os << ", ";
      }
      os << ")";
#else
      print_monomial(os,p[p.degree()],p.degree());
      for(i=p.degree()-1; i>=0; --i) {
        if (p[i]!=NT(0)) { os << " + "; print_monomial(os,p[i],i); }
      }    
#endif
      return os;
  }
}

template <class NT>
std::istream& operator >> (std::istream& is, Polynomial<NT>& p)
{ 
  int i,d;
  NT c;
  switch( is.iword(CGAL::IO::mode) )
  { 
    case CGAL::IO::ASCII : 
      is >> d;
      if (d < 0) p = Polynomial<NT>();
      else {
        typename Polynomial<NT>::Vector coeffs(d+1);
        for(i=0; i<=d; ++i) is >> coeffs[i];
        p = Polynomial<NT>(coeffs.begin(),coeffs.end() ); // af removed SNIINST
      }
      break;
    case CGAL::IO::BINARY :
      CGAL::read(is, d);
      if (d < 0) p = Polynomial<NT>();
      else {
        typename Polynomial<NT>::Vector coeffs(d+1);
        for(i=0; i<=d; ++i) 
        { CGAL::read(is,c); coeffs[i]=c; }
        p = Polynomial<NT>(coeffs.begin(),coeffs.end() ); // af removed SNIINST
      }
      break;
    default:
      CGAL_assertion_msg(0,"\nStream must be in ascii or binary mode\n");
      break;
  }
  return is;
}



// SPECIALIZE_IMPLEMENTATION(NT,int double) START
// SPECIALIZING to :

void Polynomial<int>::euclidean_div(
  const Polynomial<int>& f, const Polynomial<int>& g,
  Polynomial<int>& q, Polynomial<int>& r)
{
  r = f; r.copy_on_write();
  int rd=r.degree(), gd=g.degree(), qd;
  if ( rd < gd ) { q = Polynomial<int>(int(0)); }
  else { qd = rd-gd+1; q = Polynomial<int>(std::size_t(qd)); }
  while ( rd >= gd ) {
    int S = r[rd] / g[gd];
    qd = rd-gd;
    q.coeff(qd) += S;
    r.minus_offsetmult(g,S,qd);
    rd = r.degree();
  }
  CGAL_postcondition( f==q*g+r );
}



void Polynomial<int>::pseudo_div(
  const Polynomial<int>& f, const Polynomial<int>& g, 
  Polynomial<int>& q, Polynomial<int>& r, int& D)
{
  TRACEN("pseudo_div "<<f<<" , "<< g);
  int fd=f.degree(), gd=g.degree();
  if ( fd<gd ) 
  { q = Polynomial<int>(0); r = f; D = 1; 
    CGAL_postcondition(Polynomial<int>(D)*f==q*g+r); return; 
  }
  // now we know fd >= gd and f>=g
  int qd=fd-gd, delta=qd+1, rd=fd;
  { q = Polynomial<int>( std::size_t(delta) ); }; // workaround for SUNPRO
  int G = g[gd]; // highest order coeff of g
  D = G; while (--delta) D*=G; // D = G^delta
  Polynomial<int> res = Polynomial<int>(D)*f;
  TRACEN("  pseudo_div start "<<res<<" "<<qd<<" "<<q.degree());
  while (qd >= 0) {
    int F = res[rd]; // highest order coeff of res
    int t = F/G;     // ensured to be integer by multiplication of D
    q.coeff(qd) = t;    // store q coeff
    res.minus_offsetmult(g,t,qd); 
    if (res.is_zero()) break;
    rd = res.degree();
    qd = rd - gd;
  }
  r = res;
  CGAL_postcondition(Polynomial<int>(D)*f==q*g+r);
  TRACEN("  returning "<<q<<", "<<r<<", "<< D);
}



Polynomial<int> Polynomial<int>::gcd(
  const Polynomial<int>& p1, const Polynomial<int>& p2)
{ TRACEN("gcd("<<p1<<" , "<<p2<<")");
  if ( p1.is_zero() )
    if ( p2.is_zero() ) return Polynomial<int>(int(1));
    else return p2.abs();
  if ( p2.is_zero() )
    return p1.abs();

  Polynomial<int> f1 = p1.abs();
  Polynomial<int> f2 = p2.abs();
  int f1c = f1.content(), f2c = f2.content();
  f1 /= f1c; f2 /= f2c;
  int F = CGAL_NTS gcd(f1c,f2c);
  Polynomial<int> q,r; int M=1,D;
  bool first = true;
  while ( ! f2.is_zero() ) { 
    Polynomial<int>::pseudo_div(f1,f2,q,r,D);
    if (!first) M*=D;
    TRACEV(f1);TRACEV(f2);TRACEV(q);TRACEV(r);TRACEV(M);
    r /= r.content();
    f1=f2; f2=r;
    first=false;
  }
  TRACEV(f1.content());
  return Polynomial<int>(F)*f1.abs();
}


// SPECIALIZING to :

void Polynomial<double>::euclidean_div(
  const Polynomial<double>& f, const Polynomial<double>& g,
  Polynomial<double>& q, Polynomial<double>& r)
{
  r = f; r.copy_on_write();
  int rd=r.degree(), gd=g.degree(), qd;
  if ( rd < gd ) { q = Polynomial<double>(double(0)); }
  else { qd = rd-gd+1; q = Polynomial<double>(std::size_t(qd)); }
  while ( rd >= gd ) {
    double S = r[rd] / g[gd];
    qd = rd-gd;
    q.coeff(qd) += S;
    r.minus_offsetmult(g,S,qd);
    rd = r.degree();
  }
  CGAL_postcondition( f==q*g+r );
}



void Polynomial<double>::pseudo_div(
  const Polynomial<double>& f, const Polynomial<double>& g, 
  Polynomial<double>& q, Polynomial<double>& r, double& D)
{
  TRACEN("pseudo_div "<<f<<" , "<< g);
  int fd=f.degree(), gd=g.degree();
  if ( fd<gd ) 
  { q = Polynomial<double>(0); r = f; D = 1; 
    CGAL_postcondition(Polynomial<double>(D)*f==q*g+r); return; 
  }
  // now we know fd >= gd and f>=g
  int qd=fd-gd, delta=qd+1, rd=fd;
  q = Polynomial<double>( std::size_t(delta) );
  double G = g[gd]; // highest order coeff of g
  D = G; while (--delta) D*=G; // D = G^delta
  Polynomial<double> res = Polynomial<double>(D)*f;
  TRACEN("  pseudo_div start "<<res<<" "<<qd<<" "<<q.degree());
  while (qd >= 0) {
    double F = res[rd]; // highest order coeff of res
    double t = F/G;     // ensured to be integer by multiplication of D
    q.coeff(qd) = t;    // store q coeff
    res.minus_offsetmult(g,t,qd); 
    if (res.is_zero()) break;
    rd = res.degree();
    qd = rd - gd;
  }
  r = res;
  CGAL_postcondition(Polynomial<double>(D)*f==q*g+r);
  TRACEN("  returning "<<q<<", "<<r<<", "<< D);
}

Polynomial<double> Polynomial<double>::gcd(
  const Polynomial<double>& p1, const Polynomial<double>& p2)
{ TRACEN("gcd("<<p1<<" , "<<p2<<")");
  if ( p1.is_zero() )
    if ( p2.is_zero() ) return Polynomial<double>(double(1));
    else return p2.abs();
  if ( p2.is_zero() )
    return p1.abs();

  Polynomial<double> f1 = p1.abs();
  Polynomial<double> f2 = p2.abs();
  double f1c = f1.content(), f2c = f2.content();
  f1 /= f1c; f2 /= f2c;
  Polynomial<double> q,r; double M=1,D;
  bool first = true;
  while ( ! f2.is_zero() ) { 
    Polynomial<double>::pseudo_div(f1,f2,q,r,D);
    if (!first) M*=D;
    TRACEV(f1);TRACEV(f2);TRACEV(q);TRACEV(r);TRACEV(M);
    r /= r.content();
    f1=f2; f2=r;
    first=false;
  }
  TRACEV(f1.content());
  return Polynomial<double>(1)*f1.abs();
}


// SPECIALIZE_FUNCTION ORIGINAL
template <class NT> 
void Polynomial<NT>::euclidean_div(
  const Polynomial<NT>& f, const Polynomial<NT>& g,
  Polynomial<NT>& q, Polynomial<NT>& r)
{
  r = f; r.copy_on_write();
  int rd=r.degree(), gd=g.degree(), qd;
  if ( rd < gd ) { q = Polynomial<NT>(NT(0)); }
  else { qd = rd-gd+1; q = Polynomial<NT>(std::size_t(qd)); }
  while ( rd >= gd ) {
    NT S = r[rd] / g[gd];
    qd = rd-gd;
    q.coeff(qd) += S;
    r.minus_offsetmult(g,S,qd);
    rd = r.degree();
  }
  CGAL_postcondition( f==q*g+r );
}


template <class NT> 
void Polynomial<NT>::pseudo_div(
  const Polynomial<NT>& f, const Polynomial<NT>& g, 
  Polynomial<NT>& q, Polynomial<NT>& r, NT& D)
{
  TRACEN("pseudo_div "<<f<<" , "<< g);
  int fd=f.degree(), gd=g.degree();
  if ( fd<gd ) 
  { q = Polynomial<NT>(0); r = f; D = 1; 
    CGAL_postcondition(Polynomial<NT>(D)*f==q*g+r); return; 
  }
  // now we know fd >= gd and f>=g
  int qd=fd-gd, delta=qd+1, rd=fd;
  { q = Polynomial<NT>( std::size_t(delta) ); }; // workaround for SunPRO
  NT G = g[gd]; // highest order coeff of g
  D = G; while (--delta) D*=G; // D = G^delta
  Polynomial<NT> res = Polynomial<NT>(D)*f;
  TRACEN("  pseudo_div start "<<res<<" "<<qd<<" "<<q.degree());
  while (qd >= 0) {
    NT F = res[rd]; // highest order coeff of res
    NT t = F/G;     // ensured to be integer by multiplication of D
    q.coeff(qd) = t;    // store q coeff
    res.minus_offsetmult(g,t,qd); 
    if (res.is_zero()) break;
    rd = res.degree();
    qd = rd - gd;
  }
  r = res;
  CGAL_postcondition(Polynomial<NT>(D)*f==q*g+r);
  TRACEN("  returning "<<q<<", "<<r<<", "<< D);
}


template <class NT> 
Polynomial<NT> Polynomial<NT>::gcd(
  const Polynomial<NT>& p1, const Polynomial<NT>& p2)
{ TRACEN("gcd("<<p1<<" , "<<p2<<")");
  if ( p1.is_zero() )
    if ( p2.is_zero() ) return Polynomial<NT>(NT(1));
    else return p2.abs();
  if ( p2.is_zero() )
    return p1.abs();

  Polynomial<NT> f1 = p1.abs();
  Polynomial<NT> f2 = p2.abs();
  NT f1c = f1.content(), f2c = f2.content();
  f1 /= f1c; f2 /= f2c;
  NT F = CGAL_NTS gcd(f1c,f2c);
  Polynomial<NT> q,r; NT M=1,D;
  bool first = true;
  while ( ! f2.is_zero() ) { 
    Polynomial<NT>::pseudo_div(f1,f2,q,r,D);
    if (!first) M*=D;
    TRACEV(f1);TRACEV(f2);TRACEV(q);TRACEV(r);TRACEV(M);
    r /= r.content();
    f1=f2; f2=r;
    first=false;
  }
  TRACEV(f1.content());
  return Polynomial<NT>(F)*f1.abs();
}


// SPECIALIZE_IMPLEMENTATION(NT,int double) END

CGAL_END_NAMESPACE

#endif  // CGAL_POLYNOMIAL_H


