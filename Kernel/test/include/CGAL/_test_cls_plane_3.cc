#line 604 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_3.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_PLANE_3_CC
#define CGAL__TEST_CLS_PLANE_3_CC
#include <CGAL/_test_cls_plane_3.h>

template <class R>
bool
CGAL__test_cls_plane_3(const R& )
{
 cout << "Testing class Plane_3" ;

 R::Plane_3  ip;
 CGAL_Plane_3<R> pl0(ip);

 R::RT  x1 = -1;
 R::RT  x2 =  4;

 CGAL_Point_3<R> p1(x1,x1,x1), 
                 p2(x2,x2,x2),
                 px(R::RT(1),R::RT(0),R::RT(0)), 
                 py(R::RT(0),R::RT(1),R::RT(0)), 
                 pz(R::RT(0),R::RT(0),R::RT(1));

 CGAL_Point_3<R> p3(p1);
 CGAL_Direction_3<R> d1( R::RT(5), R::RT(-5), R::RT(10) );
 CGAL_Vector_3<R>    v1 = d1.vector();

 CGAL_Plane_3<R> pld( p1, d1);
 CGAL_Plane_3<R> plv( p1, v1);

 CGAL_Line_3<R>  l, 
                 lp(p1,p2), 
                 lxy(px,py);

 CGAL_Segment_3<R>  s12(p1,p2);
 CGAL_Ray_3<R>      r12(p1,p2);

 CGAL_Plane_3<R> xy_pl(CGAL_ORIGIN,px,py); 
 CGAL_Plane_3<R> plc(xy_pl);
 CGAL_Plane_3<R> pl1(p1,pz,p2); 
 CGAL_Plane_3<R> pls(s12,pz); 
 CGAL_Plane_3<R> plr(r12,pz);
 CGAL_Plane_3<R> pla;
 CGAL_Plane_3<R> xy_pl_eq( R::RT(0), R::RT(0), R::RT(1), R::RT(0) );
 CGAL_Plane_3<R> neg_xy_pl_eq( R::RT(0), R::RT(0), R::RT(-1), R::RT(0) );

 cout << '.';

 pla = xy_pl;
 assert( pla == pla );
 assert( plc ==  xy_pl );
 assert( pla == xy_pl );
 assert( plc == pla );
 assert( xy_pl == xy_pl_eq );
 assert( xy_pl != neg_xy_pl_eq);
 assert( pld == plv );
 assert( pls == plr );

 CGAL_Point_3<R> origo( CGAL_ORIGIN );
 CGAL_Vector_3<R> v_zdir( R::RT(0), R::RT(0), R::RT(12) );
 CGAL_Plane_3<R> xy_pl_v( origo, v_zdir);

 assert( xy_pl == xy_pl_v );

 assert( xy_pl_eq.a() == R::RT(0) );
 assert( xy_pl_eq.b() == R::RT(0) );
 assert( xy_pl_eq.c() == R::RT(1) );
 assert( xy_pl_eq.d() == R::RT(0) );
 assert( CGAL_Plane_3<R>(pl1.a(), pl1.b(), pl1.c(), pl1.d() ) == pl1 );
 
 cout <<'.';

 assert( xy_pl_eq.perpendicular_line(px) == xy_pl.perpendicular_line(px) );
 assert( xy_pl.perpendicular_line(px) == \
         neg_xy_pl_eq.perpendicular_line(px).opposite() );
 assert( neg_xy_pl_eq.opposite() == xy_pl );
 assert( plr != plr.opposite() );
 assert( plc.has_on_boundary(plc.point()) );
 assert( plc.orthogonal_direction() == pla.orthogonal_direction() );
 assert( plc.perpendicular_line( plc.point() ) == \
         CGAL_Line_3<R>( plc.point(), plc.orthogonal_direction()) );
 assert( CGAL_Line_3<R>( pl1.point(), pl1.point() + pl1.orthogonal_vector() ) \
         == CGAL_Line_3<R>( pl1.point(), pl1.orthogonal_direction()) );
 assert( xy_pl.has_on_boundary(CGAL_Point_3<R>(R::RT(345),R::RT(23),R::RT(0))));

 CGAL_Vector_3<R> nov = pl1.orthogonal_vector();
 CGAL_Vector_3<R> vb1 = pl1.base1();
 CGAL_Vector_3<R> vb2 = pl1.base2();
 assert( (nov*pl1.base1()) == R::FT(0)  && (nov*pl1.base2()) == R::FT(0) );
 assert( (pl1.base2()*pl1.base1()) == R::FT(0) );
 assert( pl1.has_on_boundary(pl1.point() + pl1.base1()) );
 assert( pl1.has_on_boundary(pl1.point() + pl1.base2()) );
 
 cout << '.';

 assert( pl1.has_on_boundary( pl1.to_3d( pl1.to_2d( pl1.point() ))) );
 assert( pl1.has_on_boundary( pl1.to_3d( pl1.to_2d( pz ))) );

 assert( neg_xy_pl_eq.oriented_side( p1 ) == CGAL_POSITIVE );
 assert( xy_pl.oriented_side( p1 ) == CGAL_NEGATIVE );
 assert( pl1.oriented_side( p1 ) == CGAL_ZERO );
 assert( xy_pl.has_on_positive_side( p2 ) );
 assert( xy_pl.has_on_negative_side( p1 ) );

 CGAL_Plane_3<R> pldeg(p1, p1, p2);
 assert( pldeg.is_degenerate() );

 cout << "done" << endl;
 return true;
}

#endif // CGAL__TEST_CLS_PLANE_3_CC
