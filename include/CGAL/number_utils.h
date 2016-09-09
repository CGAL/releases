 
#ifndef CGAL_NUMBER_UTILS_H
#define CGAL_NUMBER_UTILS_H


template <class NT>
inline bool CGAL_is_zero(const NT &x)
{
    return x == NT(0);
}

template <class NT>
inline bool CGAL_is_negative(const NT &x)
{
    return x < NT(0);
}

template <class NT>
inline bool CGAL_is_positive(const NT &x)
{
    return x > NT(0);
}

template <class NT>
int CGAL_sign(const NT &x)
{
    return (x < NT(0)) ? -1: (x > NT(0)) ? 1 : 0;
}

template <class NT>
NT CGAL_abs(const NT &x)
{
    return (x >= NT(0)) ? x: -x;
}

template <class NT>
NT CGAL_min(const NT &x, const NT &y)
{
    return (x <= y) ? x: y;
}

template <class NT>
NT CGAL_max(const NT &x, const NT &y)
{
    return (x >= y) ? x: y;
}
#endif
