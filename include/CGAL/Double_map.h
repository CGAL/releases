// Copyright (c) 2003-2004  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Mesh_2/include/CGAL/Double_map.h,v $
// $Revision: 1.16 $ $Date: 2004/10/13 01:29:13 $
// $Name:  $
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_DOUBLE_MAP_H
#define CGAL_DOUBLE_MAP_H

#include <map>
#include <utility>
#include <algorithm>
#include <CGAL/assertions.h>

namespace CGAL {

template <class _Key, class _Data, class _Direct_order = std::less<_Key>, 
	  class _Reverse_order = std::less<_Data> >
class Double_map
{
public:
  typedef _Key Key;
  typedef _Data Data;
  typedef _Direct_order Direct_order;
  typedef _Reverse_order Reverse_order;
  
  typedef std::map <Key, Data, Direct_order> Direct_func;
  typedef std::multimap <Data, Key, Reverse_order> Reverse_func;

  typedef std::pair<Key, Data> Direct_entry;
  typedef std::pair<Data, Key> Reverse_entry;

  typedef typename Direct_func::size_type size_type;

  typedef typename Reverse_func::iterator reverse_iterator;
  typedef typename Direct_func::iterator direct_iterator;
  typedef reverse_iterator iterator;
  typedef typename Direct_func::const_iterator direct_const_iterator;

  typedef direct_const_iterator const_iterator;

private:
  // Private members
  Direct_func direct_func;
  Reverse_func reverse_func;

public :
  // The default constructor
  Double_map () {}

  // Queries
  bool empty() const
  {
    CGAL_assertion(is_valid());
    return(direct_func.empty());
  }

  size_type size() const
  {
    CGAL_assertion(is_valid());
    return direct_func.size();
  }

  bool is_valid() const
  {
    return(direct_func.size()==reverse_func.size());
  }
  
  void clear()
    {
      direct_func.clear();
      reverse_func.clear();
    }

  // Assignation
  bool insert(const Key& k, const Data& d)
    {
      std::pair<direct_iterator, bool> 
	direct_result = direct_func.insert(Direct_entry(k, d));

      if (direct_result.second != true)
	return false;

      reverse_func.insert(Reverse_entry(d, k));

      CGAL_assertion(is_valid());
      return(true);
    }

  void erase(Key& k);

  // Access
  reverse_iterator front()
    {
      CGAL_assertion(is_valid() && !empty());
      return(reverse_func.begin());
    }

  void pop_front()
    {
      CGAL_assertion(is_valid());
      reverse_iterator rit = reverse_func.begin();
      direct_iterator pos = direct_func.find(rit->second);
      assert(pos != direct_func.end());
      
      direct_func.erase(pos);
      reverse_func.erase(rit);
      CGAL_assertion(is_valid());
    }

  const_iterator begin() const
  {
    return direct_func.begin();
  }
    
  const_iterator end() const
  {
    return direct_func.end();
  }

  class Second_is {
    Key k;
  public:
    Second_is(const Key& _k): k(_k) {};
    bool operator()(const Reverse_entry& p) const 
      {
	return p.second == k;
      }
  };

  void dump_direct_func(std::ostream& out)
    {
      for(typename Direct_func::iterator it = direct_func.begin();
	  it != direct_func.end();
	  ++it)
	out << it->second << " " 
	    << "("
	    << it->first->vertex(0)->point() << ", "
	    << it->first->vertex(1)->point() << ", "
	    << it->first->vertex(2)->point()
	    << ")" << std::endl;
    }

  void dump_reverse_func(std::ostream& out)
    {
      for(typename Reverse_func::iterator it = reverse_func.begin();
	  it != reverse_func.end();
	  ++it)
        out << it->first << " " 
            << "("
            << it->second->vertex(0)->point() << ", "
            << it->second->vertex(1)->point() << ", "
            << it->second->vertex(2)->point()
	    << ")" << std::endl;
    }
};

template <class _Key, class _Data, class _Direct_order, 
  class _Reverse_order>
void
Double_map<_Key, _Data, _Direct_order, _Reverse_order>::
erase(Key& k)
{
  direct_iterator pos = direct_func.find(k);
  if (pos == direct_func.end())
    return;
  else
    {
      const Data& d = pos->second;

      reverse_iterator lb = reverse_func.lower_bound(d);
      reverse_iterator ub = reverse_func.upper_bound(d);

      direct_func.erase(pos);
      reverse_func.erase(std::find_if(lb, ub, Second_is(k)));
    }
  CGAL_assertion(is_valid());
}

} // end namespace CGAL

#endif // CGAL_DOUBLE_MAP_H
