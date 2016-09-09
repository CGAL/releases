 
#ifndef CGAL_OSTREAMH2_H
#define CGAL_OSTREAMH2_H

 
#ifdef CGAL_VECTORH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_VectorH2<FT,RT> &v)
{
 return
 os << "VectorH2(" << v.hx() << ", " << v.hy() << ", " << v.hw() << ")";
}
#endif // CGAL_VECTORH2_H

#ifdef CGAL_POINTH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_PointH2<FT,RT> &p)
{
 return
 os << "PointH2(" << p.hx() << ", " << p.hy() << ", " << p.hw() << ")";
}
#endif // CGAL_POINTH2_H

#ifdef CGAL_DIRECTIONH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_DirectionH2<FT,RT> &d)
{
 return
 os << "DirectionH2(" << d.x() << ", " << d.y() << ")";
}
#endif // CGAL_DIRECTIONH2_H

#ifdef CGAL_LINEH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_LineH2<FT,RT> &l)
{
 return
 os << "LineH2(" << l.a() << ", " << l.b() << ", " << l.c() << ")";
}
#endif // CGAL_LINEH2_H

#ifdef CGAL_SEGMENTH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_SegmentH2<FT,RT> &s)
{
 return
 os << "SegmentH2(" << s.start() <<  ", " << s.end() << " )";
}
#endif // CGAL_SEGMENTH2_H

#ifdef CGAL_RAYH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_RayH2<FT,RT> &r)
{
 return
 os << "RayH2(" << r.start() << ", " << r.direction() << " )";
}
#endif // CGAL_RAYH2_H

#ifdef CGAL_TRIANGLEH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_TriangleH2<FT,RT> &t)
{
 return
 os << "TriangleH2(" << t[0] <<  ", " << t[1] <<   ", " << t[2] <<" )";
}
#endif // CGAL_TRIANGLEH2_H

#ifdef CGAL_ISO_RECTANGLEH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_Iso_rectangle<FT,RT> &ir)
{
 return
 os << "Iso_rectangleH2(" << r[0] <<  ", " << r[2] << " )";
}
#endif // CGAL_ISO_RECTANGLEH2_H
 
#ifdef CGAL_AFF_TRANSFORMATIONH2_H
template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL_Aff_transformationH2<FT,RT> &t)
{
 return
 os << "Aff_transformationH2(" << t.general_form() << ")";
}

template < class FT, class RT >
ostream&
operator<<( ostream& os, const CGAL__Aff_transformation_repH2<FT,RT> &tr)
{
 return
 os << '\n'
    << tr.a    << ", " << tr.b    << ", " << tr.c << '\n'
    << tr.d    << ", " << tr.e    << ", " << tr.f << '\n'
    << RT(0)   << ", " << RT(0)   << ", " << tr.g << '\n';
}
#endif // CGAL_AFF_TRANSFORMATIONH2_H
 


#endif // CGAL_OSTREAMH2_H
