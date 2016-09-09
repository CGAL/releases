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
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/generic_sweep.h
// package       : Nef_2 (0.9.25)
// chapter       : Nef Polyhedra
//
// source        : nef_2d/generic_sweep.lw
// revision      : $Revision: 1.1 $
// revision_date : $Date: 2001/07/06 08:17:18 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: generic plane sweep framework
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
#ifndef CGAL_GENERIC_SWEEP_H
#define CGAL_GENERIC_SWEEP_H

/*{\Moptions print_title=yes}*/
/*{\Moptions section=subsection}*/

#ifndef _MSC_VER
#include <CGAL/sweep_observer.h>

namespace CGAL {

/*{\Manpage {generic_sweep}{T}{A Generic Plane Sweep Framework}{PS}}*/

template <typename T>
class generic_sweep {

typedef generic_sweep<T>  Self;

/*{\Mdefinition
The data type |\Mname| provides a general framework for algorithms
following the plane sweep paradigm. The plane sweep paradigm can be
described as follows. A vertical line sweeps the plane from left to
right and constructs the desired output incrementally left behind the
sweep line. The sweep line maintains knowledge of the scenery of
geometric objects and stops at points where changes of this knowledge
relevant for the output occur. These points are called events.

A general plane sweep framework structures the execution of the
sweep into phases and provides a storage place for all data structures
necessary to execute the sweep. An object |\Mvar| of type |\Mname|
maintains an object of type |T| which generally can be used to store
necessary structures. The content is totally dependent of the sweep
specification and thereby varies within the application domain of the
framework.

The traits class |T| has to provide a set of types which define
the input/output interface of the sweep: the input type |INPUT|, 
the output type |OUTPUT|, and a geometry kernel type |GEOMETRY|.

The natural phases which determine a sweep are
\begin{Mverb}
  // INITIALIZATION
  initialize_structures();
  check_invariants();

  // SWEEP LOOP
  while ( event_exists() ) {
    process_event();
    check_invariants();
    procede_to_next_event();
  }

  // COMPLETION
  complete_structures();
  check_final();
\end{Mverb}

\begin{description}
\item[ Initialization ] -- initializing the data structures,
ensuring preconditions, checking invariants
\item[ Sweep Loop ] -- iterating over all events, while handling
the event stops, ensuring invariants and the soundness of all
data structures and maybe triggering some animation tasks.
\item[ Completion ] -- cleaning up some data structures and
completing the output.
\end{description}

The above subtasks are members of the class |T| which a 
model of our traits concept has to provide:
\begin{Mverb}
  void T::initialize_structures();
  bool T::event_exists();
  void T::process_event();
  void T::procede_to_next_event();
  void T::complete_structures();
  void T::check_invariants();
  void T::check_final();
\end{Mverb}
See specification of the traits class for |\Mname|.


}*/

T traits;

/*{\Mtypes 5}*/
public :

typedef T TRAITS;
/*{\Mtypemember the traits class}*/ 

typedef typename TRAITS::INPUT  INPUT;
/*{\Mtypemember the input interface.}*/ 

typedef typename TRAITS::OUTPUT OUTPUT;
/*{\Mtypemember the output container.}*/ 

typedef typename TRAITS::GEOMETRY GEOMETRY;
/*{\Mtypemember the geometry kernel.}*/ 

/*{\Mevents 6.5}*/

/*{\Mtext To enable animation of the sweep there are event hooks
inserted which allow an observer to attach certain visualization
actions to them. There are four such hooks: }*/

Event_hook<TRAITS&>   post_init_hook;
/*{\Mevent triggered just after initialization.}*/

Event_hook<TRAITS&>   pre_event_hook;
/*{\Mevent triggered just before the sweep event.}*/

Event_hook<TRAITS&>   post_event_hook;
/*{\Mevent triggered just after the sweep event.}*/

Event_hook<TRAITS&>   post_completion_hook;
/*{\Mevent triggered just after the completion phase.}*/

/*{\Mtext All of these are triggered during the sweep with the instance
of the |TRAITS| class that is stored inside the plane sweep object.
Thus any animation operation attached to a hook can work on that class
object which maintains the sweep status.}*/


/*{\Mcreation PS}*/

generic_sweep(const INPUT& input, OUTPUT& output, 
  const GEOMETRY& geometry = GEOMETRY()) : 
  traits(input,output,geometry) {}

/*{\Mcreate creates a plane sweep object for a sweep on objects determined by
|input| and delivers the result of the sweep in |output|. The traits
class |T| specifies the models of all types and the implementations of all
methods used by |\Mname|. At this point, it suffices to say that
|INPUT| represents the input data type and |OUTPUT| represents the
result data type. The |geometry| is an object providing object bound,
geometry traits access.}*/

generic_sweep(OUTPUT& output, const GEOMETRY& geometry = GEOMETRY()) : 
  traits(output,geometry) {}
/*{\Mcreate a simpler call of the above where |output| carries also
the input.}*/

/*{\Moperations}*/

void sweep()
/*{\Mop execute the plane sweep.}*/
{
  traits.initialize_structures();
  traits.check_invariants();
      post_init_hook(traits);

  while ( traits.event_exists() ) {
        pre_event_hook(traits);
    traits.process_event();
        post_event_hook(traits);
    traits.check_invariants();
    traits.procede_to_next_event();
  }
  traits.complete_structures();
  traits.check_final();
      post_completion_hook(traits);
}


/*{\Mexample
A typical sweep based on |\Mname| looks like the following little
program:
\begin{Mverb}
  typedef std::list<POINT>::const_iterator iterator;
  typedef std::pair<iterator,iterator> iterator_pair;
  std::list<POINT>  P; // fill input
  GRAPH<POINT,LINE> G; // the output
  generic_sweep<triang_sweep_traits> 
    triangulation(iterator_pair(P.begin(),P.end()),G);
  triangulation.sweep();
\end{Mverb}}*/

}; // generic_sweep<T>
} // namespace CGAL

#else // _MSC_VER

namespace CGAL {

template <typename T>
class generic_sweep {
  typedef generic_sweep<T>  Self;
  T traits;
public :

typedef T TRAITS;
typedef typename TRAITS::INPUT  INPUT;
typedef typename TRAITS::OUTPUT OUTPUT;
typedef typename TRAITS::GEOMETRY GEOMETRY;

generic_sweep(const INPUT& input, OUTPUT& output, 
  const GEOMETRY& geometry = GEOMETRY()) : 
  traits(input,output,geometry) {}

generic_sweep(OUTPUT& output, const GEOMETRY& geometry = GEOMETRY()) : 
  traits(output,geometry) {}

void sweep()
{
  traits.initialize_structures();
  traits.check_invariants();
  while ( traits.event_exists() ) {
    traits.process_event();
    traits.check_invariants();
    traits.procede_to_next_event();
  }
  traits.complete_structures();
  traits.check_final();
}

}; // generic_sweep<T>

} // namespace CGAL

#endif // _MSC_VER

#endif // CGAL_GENERIC_SWEEP_H
