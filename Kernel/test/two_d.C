
extern void  Points();
extern void  Vectors();
extern void  Directions();
extern void  Lines();
extern void  Rays();
extern void  Segments();

extern void  Triangles();
extern void  Iso_rectangles();
//extern void  Intersections();
extern void  Transformations();


int main()

{
  Points();
  Vectors();
  Directions();

  Lines();
  Rays();
  Segments();

  Triangles();  
  Iso_rectangles();

  //  Intersections();
  Transformations();
  return 1;
}
