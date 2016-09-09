#line 1661 "/u/sargas/2/prisme/fabri/Cgal/Kernel/web/test_kernel_2.fw"
// Author: Stefan.Schirra@mpi-sb.mpg.de

#ifndef CGAL__TEST_CLS_AFF_TRANSFORMATION_2_CC
#define CGAL__TEST_CLS_AFF_TRANSFORMATION_2_CC
#include <CGAL/_test_cls_aff_transformation_2.h>

template <class R>
bool
CGAL__test_cls_aff_transformation_2(const R& )
{
 cout << "Testing class Aff_transformation_2" ;

 R::Aff_transformation_2 ia;
 CGAL_Aff_transformation_2<R> a1(ia);
 
 R::RT n0 =  0;
 R::RT n1 =-15;
 R::RT n2 = 44;
 R::RT n3 =  4;
 R::RT n4 =  5;
 R::RT n5 = 25;
 R::RT n6 = -2;
 R::RT n7 =  8;
 R::RT n8 = 18;
 R::RT n9 =  9;
 R::RT n10=  3;
 R::RT n11=-12;
 R::RT n12= 20;
 R::RT n13=  1;
 R::RT n14= 35;
 R::RT n100 = 100;

 CGAL_Vector_2<R> vec( n3, n8,  n6 );      // (-2,-9)
 CGAL_Vector_2<R> tvec;
 CGAL_Point_2<R>  pnt( n8, n1, n10 );      // ( 6,-5)
 CGAL_Point_2<R>  tpnt;
 CGAL_Point_2<R>  pvec = CGAL_ORIGIN + vec;
 CGAL_Vector_2<R> vpnt = pnt - CGAL_ORIGIN;
 
 CGAL_Point_2<R>  p1(-n3, n7, n3 );        // (-1, 2) 
 CGAL_Point_2<R>  p2( n5, n4, n4 );        // ( 5, 1)
 CGAL_Point_2<R>  p3( n1, n0, n4 );        // (-3, 0)
 CGAL_Point_2<R>  p4( n7, n2,-n6 );        // ( 4,11)
 
 CGAL_Direction_2<R> d0(n13, n0);
 CGAL_Direction_2<R> d1(n0, n13);
 CGAL_Direction_2<R> dir = (p2 - p4).direction();
 CGAL_Direction_2<R> tdir;

 CGAL_Point_2<R>   tp1;
 CGAL_Point_2<R>   tp2;
 CGAL_Point_2<R>   tp3;
 CGAL_Point_2<R>   tp4;
 CGAL_Segment_2<R> seg(p1,p2);
 CGAL_Segment_2<R> tseg;
 CGAL_Ray_2<R>     ray(p3,p2);
 CGAL_Ray_2<R>     tray;
 CGAL_Line_2<R>    lin(p2,p4);
 CGAL_Line_2<R>    tlin;
 CGAL_Triangle_2<R>     tri( p2,p3,p4);
 CGAL_Triangle_2<R>     ttri;

 CGAL_Circle_2<R>         circ(p2, p3, p4);
 CGAL_Circle_2<R>         tcirc;
 CGAL_Iso_rectangle_2<R>  isor(p3, p4);
 CGAL_Iso_rectangle_2<R>  tisor;

 CGAL_Aff_transformation_2<R> ident(n8,  n0,  n0,
                                    n0,  n8,  n0,
                                              n8 );
 
 CGAL_Aff_transformation_2<R> gat1( n7,  n9,  n2,
                                    n5, n11,  n4,
                                              n3 );
 
 CGAL_Aff_transformation_2<R> gat2( n7,  n9,  n2,
                                    n5, n11,  n4,
                                              n13 );

 CGAL_Aff_transformation_2<R> gat3( n4,  n6,  n0,
                                   n12,  n8,  n0,
                                              n13 );

 CGAL_Aff_transformation_2<R> scale11( CGAL_SCALING, n2, n3 );

 CGAL_Aff_transformation_2<R> gscale(n2,  n0, n0,
                                     n0,  n2, n0,
                                              n3 );
 
 CGAL_Aff_transformation_2<R> gtrans(n10, n0, n8,
                                     n0, n10, n1,
                                              n10 );

 CGAL_Aff_transformation_2<R> translate( CGAL_TRANSLATION, vpnt );

 CGAL_Aff_transformation_2<R> xrefl(-n4,  n0, n0,
                                     n0,  n4, n0,
                                              n4 );

 CGAL_Aff_transformation_2<R> gat4( gat3);

 CGAL_Aff_transformation_2<R> gat5( n7,  n9,
                                    n5, n11,
                                              n13 );

 CGAL_Aff_transformation_2<R> gat6( n4,  n6,
                                   n12,  n8,
                                              n13 );

 CGAL_Aff_transformation_2<R> rot90( CGAL_ROTATION, d1, n13, n100 );

 CGAL_Aff_transformation_2<R> rot2( CGAL_ROTATION, dir, n13, n100 );

 CGAL_Aff_transformation_2<R> rot3( CGAL_ROTATION, R::RT(3),R::RT(4),R::RT(5));


 
 CGAL_Aff_transformation_2<R> a[14];

 cout << '.';

 a[0] = ident;
 a[1] = gat1;
 a[2] = gat2;
 a[3] = gat3;
 a[4] = scale11;
 a[5] = gscale;
 a[6] = gtrans;
 a[7] = translate;
 a[8] = xrefl;
 a[9] = gat5;
 a[10]= gat6;
 a[11]= rot90;
 a[12]= rot2;
 a[13]= rot3;

 CGAL_Aff_transformation_2<R> inv;

 for (int i = 0; i< 14; i++)
 {
    tp1 = p1.transform( a[i] );
    tp2 = p2.transform( a[i] );
    tp3 = p3.transform( a[i] );
    tp4 = p4.transform( a[i] );
    tseg = seg.transform( a[i] );
    tray = ray.transform( a[i] );
    tlin = lin.transform( a[i] );
    ttri = tri.transform( a[i] );
    tisor= isor.transform( a[i]);
    assert( tseg == CGAL_Segment_2<R>(tp1, tp2) );
    assert( tray == CGAL_Ray_2<R>(tp3, tp2) );
    assert( tlin == CGAL_Line_2<R>(tp2, tp4) );
    assert( ttri == CGAL_Triangle_2<R>(tp2, tp3, tp4) );
    assert( tisor== CGAL_Iso_rectangle_2<R>( tp3, tp4 ) );

    inv = a[i].inverse();
    tp4  = tp4.transform(  inv );
    tseg = tseg.transform( inv );
    tray = tray.transform( inv );
    tlin = tlin.transform( inv );
    ttri = ttri.transform( inv );
    assert( tp4  == p4 );
    assert( tseg == seg );
    assert( tray == ray );
    assert( tlin == lin );
    assert( ttri == tri );
 };

 cout << '.';
 
 // ident
 assert( vec.transform(ident) == vec );
 assert( dir.transform(ident) == dir );
 assert( pnt.transform(ident) == pnt );
 assert( lin.transform(ident) == lin );

 // scale11 and gscale
 tpnt = pnt.transform(scale11);
 tvec = vec.transform(scale11);
 tdir = dir.transform(scale11);
 tseg = seg.transform(scale11);
 assert( tseg.squared_length() == R::FT(11)* R::FT(11)* seg.squared_length() );
 assert( R::FT(11)* R::FT(11)* R::FT( vec*vec ) == R::FT( tvec*tvec ) );
 assert( vec.direction() == tvec.direction() );
 assert( dir == tdir );
 tdir = d0.transform(scale11);
 assert( d0 == tdir);
 tpnt = pnt.transform(gscale);
 tvec = vec.transform(gscale);
 tdir = dir.transform(gscale);
 tseg = seg.transform(gscale);
 assert( tseg.squared_length() == R::FT(11)* R::FT(11)* seg.squared_length() );
 assert( R::FT(11)* R::FT(11)* R::FT( vec*vec ) == R::FT( tvec*tvec ) );
 assert( seg.transform(scale11) == seg.transform(gscale) );
 assert( vec.transform(scale11) == vec.transform(gscale) );
 assert( dir.transform(scale11) == dir.transform(gscale) );
 assert( pnt.transform(scale11) == pnt.transform(gscale) );
 assert( lin.transform(scale11) == lin.transform(gscale) );

 // translate and gtrans
 tvec = vec.transform(translate);
 tdir = dir.transform(translate);
 tp2 = p2.transform(translate);
 tp3 = p3.transform(translate);
 assert( vec == tvec );
 assert( dir == tdir );
 assert( tp2  == p2 + vpnt );
 assert( tp3  == p3 + vpnt );
 tvec = vec.transform(gtrans);
 tdir = dir.transform(gtrans);
 tp2 = p2.transform(gtrans);
 tp3 = p3.transform(gtrans);
 assert( vec == tvec );
 assert( dir == tdir );
 assert( tp2  == p2 + vpnt );
 assert( tp3  == p3 + vpnt );
 assert( vec.transform(translate) == vec.transform(gtrans) );
 assert( dir.transform(translate) == dir.transform(gtrans) );
 assert( pnt.transform(translate) == pnt.transform(gtrans) );
 assert( lin.transform(translate) == lin.transform(gtrans) );

 // xrefl
 tdir = d0.transform(xrefl);
 assert( tdir == -d0 );
 tdir = d1.transform(xrefl);
 assert( tdir == d1 );

 cout << '.';

 // composition
 assert( pnt.transform(xrefl).transform(xrefl) == pnt ); 
 assert( dir.transform(xrefl).transform(xrefl) == dir ); 
 assert( vec.transform(xrefl).transform(xrefl) == vec ); 
 assert( lin.transform(xrefl).transform(xrefl) == lin ); 
 CGAL_Aff_transformation_2<R> co1 = xrefl * xrefl;
 assert( pnt.transform(xrefl).transform(xrefl) == pnt.transform(co1) ); 
 assert( dir.transform(xrefl).transform(xrefl) == dir.transform(co1) ); 
 assert( vec.transform(xrefl).transform(xrefl) == vec.transform(co1) ); 
 assert( lin.transform(xrefl).transform(xrefl) == lin.transform(co1) ); 
 co1 = gat2 * gat3;
 assert( pnt.transform(gat3).transform(gat2) == pnt.transform(co1) ); 
 assert( dir.transform(gat3).transform(gat2) == dir.transform(co1) ); 
 assert( vec.transform(gat3).transform(gat2) == vec.transform(co1) ); 
 assert( lin.transform(gat3).transform(gat2) == lin.transform(co1) ); 
 co1 = ident * gat1;
 assert( vec.transform(gat1) == vec.transform(co1) );
 assert( dir.transform(gat1) == dir.transform(co1) );
 assert( pnt.transform(gat1) == pnt.transform(co1) );
 assert( lin.transform(gat1) == lin.transform(co1) );
 co1 = gat1 * ident;
 assert( vec.transform(gat1) == vec.transform(co1) );
 assert( dir.transform(gat1) == dir.transform(co1) );
 assert( pnt.transform(gat1) == pnt.transform(co1) );
 assert( lin.transform(gat1) == lin.transform(co1) );
 co1 = gat1 * gat1.inverse() ;
 assert( vec == vec.transform(co1) );
 assert( pnt == pnt.transform(co1) );
 assert( dir == dir.transform(co1) );
 assert( lin == lin.transform(co1) );

 // even
 assert( translate.is_even() );
 assert( gtrans.is_even() );
 assert( gscale.is_even() );
 assert( scale11.is_even() );
 assert( ident.is_even() );
 assert( rot90.is_even() );
 assert( rot2.is_even() );
 assert( rot3.is_even() );
 assert( xrefl.is_odd() );

 // rotation
 assert( d0.transform( rot90 ) == d1 );
 assert( d1.transform( rot90.inverse() ) == d0 );
 assert( d0.transform( rot3 ) == CGAL_Direction_2<R>( R::RT(4), R::RT(3)) );
 co1 = rot3 * rot90;
 assert( d1.transform( rot3) == d0.transform( co1 ) );
 co1 = rot2 * rot90;
 assert( d1.transform( rot2) == d0.transform( co1 ) );
 co1 = rot90 * rot2;
 assert( d1.transform( rot2) == d0.transform( co1 ) );
 co1 = rot90 * rot90 * rot90 * rot90;
 assert( vec == vec.transform(co1) );
 assert( dir == dir.transform(co1) );
 assert( pnt == pnt.transform(co1) );
 assert( lin == lin.transform(co1) );
 co1 = rot3 * rot3 * rot3.inverse();
 assert( vec.transform(rot3) == vec.transform(co1) );
 assert( dir.transform(rot3) == dir.transform(co1) );
 assert( pnt.transform(rot3) == pnt.transform(co1) );
 assert( lin.transform(rot3) == lin.transform(co1) );

 //circle
 tp2 = p2.transform( translate );
 tp3 = p3.transform( translate );
 tp4 = p4.transform( translate );
 tcirc = circ.orthogonal_transform( translate );
 assert( tcirc == CGAL_Circle_2<R>( tp2, tp3, tp4 ) );
 tp2 = p2.transform( xrefl );
 tp3 = p3.transform( xrefl );
 tp4 = p4.transform( xrefl );
 tcirc = circ.orthogonal_transform( xrefl );
 assert( tcirc == CGAL_Circle_2<R>( tp2, tp3, tp4 ) );
 tp2 = p2.transform( rot3 );
 tp3 = p3.transform( rot3 );
 tp4 = p4.transform( rot3 );
 tcirc = circ.orthogonal_transform( rot3 );
 assert( tcirc == CGAL_Circle_2<R>( tp2, tp3, tp4 ) );
 

 // copy
 assert( vec.transform( gat5 ) == vec.transform( gat2 ) );
 assert( dir.transform( gat5 ) == dir.transform( gat2 ) );

 assert( pnt.transform( gat6 ) == pnt.transform( gat3 ) );
 assert( vec.transform( gat6 ) == vec.transform( gat3 ) );
 assert( dir.transform( gat6 ) == dir.transform( gat3 ) );
 assert( lin.transform( gat6 ) == lin.transform( gat3 ) );

 cout << "done" << endl;
 return true;
}

#endif // CGAL__TEST_CLS_AFF_TRANSFORMATION_2_CC
