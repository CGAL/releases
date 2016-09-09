// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// Copyright (c) 2002 ENS de Paris
//
// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// The Qt widget we provide for CGAL is distributed under the QPL,
// which is Trolltech's open source license. For more information see 
//     http://www.trolltech.com/developer/licensing/qpl.html
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// file          : include/CGAL/IO/Qt_widget_history.h
// package       : Qt_widget (1.2.30)
// author(s)     : Radu Ursu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_QT_WIDGET_HISTORY_H
#define CGAL_QT_WIDGET_HISTORY_H

#include <list>

namespace CGAL {
  class History_atom{
  public:
    History_atom(double xmin, double xmax, double ymin, double ymax,
                 double xcenter, double ycenter, double xscal, double yscal)
      : m_x1(xmin), m_x2(xmax), m_y1(ymin), m_y2(ymax),
        m_xcenter(xcenter), m_ycenter(ycenter), m_xscal(xscal),
        m_yscal(yscal){};
    double x1(){return m_x1;}
    double x2(){return m_x2;}
    double y1(){return m_y1;}
    double y2(){return m_y2;}
    double xcenter(){return m_xcenter;}
    double ycenter(){return m_ycenter;}
    double xscal(){return m_xscal;}
    double yscal(){return m_yscal;}
  private:
    double  m_x1,
            m_x2,
            m_y1,
            m_y2,
            m_xcenter,
            m_ycenter,
            m_xscal,
            m_yscal;
  };

  class Qt_widget_history{
    public:
      Qt_widget_history() :  current_item(0), nr_of_items(0)
      {
        it = history_list.begin();
      };
      ~Qt_widget_history(){};

    bool back(){
      if(nr_of_items > 1 && current_item > 1){
        current_item--;
        it--;
        return true;
      }
      return false;
    }
    bool forward(){
      if(current_item < nr_of_items){
        current_item++;
        it++;
        return true;
      }
      return false;
    }
    History_atom* get_atom(){
      return &(*it);
    }
    void add_to_history(double xmin, double xmax, 
		                double ymin, double ymax,
                        double xcenter, double ycenter,
						double xscal, double yscal)
    {
      if(nr_of_items > 1){
        it++;
        history_list.erase(it, history_list.end());
      }
      History_atom atom(xmin, xmax, ymin, ymax, xcenter,
		                ycenter, xscal, yscal);
      history_list.push_back(atom);
      nr_of_items = history_list.size();
      current_item = nr_of_items;
      it = history_list.end();
      it--;
    }
    void clear(){
      history_list.erase(history_list.begin(), history_list.end());
      nr_of_items = history_list.size();
      current_item = nr_of_items;
      it = history_list.end();
      it--;
    }
    inline int get_current_item(){return current_item;}
    inline int get_nr_of_items(){return nr_of_items;}
      
    private:
      std::list<History_atom> history_list;
      std::list<History_atom>::iterator it;
      int current_item;
      int nr_of_items;
    protected:
  };
  
} // namespace CGAL end

#endif // CGAL_QT_WIDGET_HISTORY_H
