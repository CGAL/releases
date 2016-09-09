/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 * generic.h -
 *    Misc' things of mine....    
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef  __GENERIC__H
#define  __GENERIC__H

#ifndef  USE_ARGUMENT
#define  USE_ARGUMENT( X )  (void)(X);
#endif  
#ifndef  USE_VARIABLE
#define  USE_VARIABLE( X )  (void)(&(X));
#endif  


/* dblRand - a random number between 0..1 */
#ifndef  RAND_MAX
#define  RAND_MAX    0x7fffffff
#endif  // RAND_MAX

static inline  double    dblRand( void )
{
    return  (double)rand() / (double)RAND_MAX;
}



/* measuring times */
#ifndef  CLOCKS_PER_SEC
#define   CLOCKS_PER_SEC  1000000.0
#endif 

class  Timer
{
private:
  long int    start_t, end_t;

  static inline float  SECONDS( long int   time ) 
  {
      return  ( (double)time ) / ((double)CLOCKS_PER_SEC);
  }

public:
  void  start( void )
  {
    start_t = clock();
  }

  void  end( void )
  {
    end_t = clock();
  }

  float  seconds( void )
  {
    return  SECONDS( end_t - start_t ); 
  }
};


#else   /* __GENERIC__H */
#error  Header file mygeneric.h included twice
#endif  /* __GENERIC__H */

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
 *     
 * generic.h - End of File
\*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
