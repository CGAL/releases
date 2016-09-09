/* Copyright 2004
   Stanford University

   This file is part of the DSR PDB Library.

   The DSR PDB Library is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or (at your
   option) any later version.

   The DSR PDB Library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with the DSR PDB Library; see the file LICENSE.LGPL.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA. */

#include <CGAL/PDB/PDB.h>
#include <CGAL/PDB/internal/pdb_utils.h>
#include <cassert>
#include <CGAL/PDB/internal/Error_logger.h>
#include <cctype>
#include <cstdio>

namespace CGAL { namespace PDB {

PDB::PDB(std::istream &in, bool print_errors) {
  load(in, print_errors);
}
PDB::PDB(){}
PDB::~PDB(){}
  
void PDB::load(std::istream &in, bool print_errors){
  char line[600];
  
  internal::error_logger.set_is_output(print_errors);
  std::map<char, std::string> names;
  std::string last_name;
  Model_key cur_model(1);
  bool done_with_model=false;
  char dummy_char;
  while (in.getline (line, 600)) {
      
    internal::Line_type lt= internal::line_type(line);
    if (lt== internal::HEADER) {
      header_.push_back(std::string(line));
    } if (lt == internal::CONECT) {
      // do something
      std::istringstream iss(line+6);
      int base;
      iss >> base;
      if (!iss) {
        CGAL_LOG(Log::SOME, "Error parsing CONECT record: " << line << std::endl);
        continue;
      }
      else do {
        int o;
        iss >> o;
        if (!iss) {
	  break;
	}
	else {
	  connections_.push_back(std::make_pair(base, o));
	}
      } while (true);
    } else if (lt == internal::COMPND) {
      header_.push_back(std::string(line));
      int ti;
      char dummychain;
      // need dummychain to enforce matching of the CHAIN part of the string
      if (sscanf(line, "COMPND %d CHAIN: %c", &ti,&dummychain) == 2) {
        std::istringstream iss(line+17);
        //std::cout << "Line is " << line+17 << std::endl;
        //std::cout << "Name is " << last_name << std::endl;
        while (true) {
          char chain='\0';
          iss >> chain;
          if (chain == '\0') break;
          if (chain == ' ') continue;
          if (chain == ',') continue;
          if (chain == ';') break;
          //std::cout << "Chain is " << chain << std::endl;
          names[chain]=last_name;
        }
	
      } else if (sscanf(line, "COMPND %d MOLECULE: %c", &ti, &dummy_char) ==2) {
	int len= std::strlen(line);
	CGAL_assertion(line[len]=='\0');
	--len;
	while (std::isspace(line[len])
	       || std::ispunct(line[len])
	       /*|| std::isctrl(line[len])*/) {
	  line[len]='\0';
	  --len;
	  if (len==0) break;
	}
	int offset=20;
	while (std::isspace(line[offset]) && !line[offset]=='\0'){
	  ++offset;
	}
	last_name= std::string(line+offset);
      }
    } else if (lt== internal::DBREF){
      header_.push_back(std::string(line));
    } else if (lt== internal::SEQRES){
      header_.push_back(std::string(line));
    } else if (lt== internal::MODEL) {
      int mnum=0;
      char buf[81];
      std::sscanf(line, "%s %d", buf, &mnum);
      //new_model(Model_key(mnum), Model());
      cur_model= Model_key(mnum);
      done_with_model=false;
    } else if (  lt== internal::HETATM 
		 || lt== internal::ATOM ) {
      if (done_with_model) {
        // charlie carter hack
        cur_model= Model_key(cur_model.index()+1);
        done_with_model=false;
      }
      models_[cur_model].process_line(line);
    } else if (lt== internal::TER){
      models_[cur_model].process_line(line);
    } else if (lt== internal::ENDMDL){
      done_with_model=true;
      models_[cur_model].process_line(line);
    } else if (lt== internal::MASTER){
    } else if (lt == internal::END){
    }
  }

  CGAL_PDB_FOREACH(Model_pair &m, models()) {
    CGAL_PDB_FOREACH(Model::Chain_pair &c, m.model().chains()) {
      c.chain().set_has_bonds(true);
      if (names.find(c.key().index()) != names.end()) {
	c.chain().set_name(names[c.key().index()]);
      }
    }
  }
  
  build_heterogens();
  
  internal::error_logger.dump();
}


void PDB::swap_with(PDB &o) {
  swap(header_, o.header_);
  swap(models_, o.models_);
  swap(connections_, o.connections_);
}


void PDB::build_heterogens() {
  CGAL_LOG(Log::SOME, "Building connections for " << connections_.size()
           << " connections" << std::endl);
  for (unsigned int i=0; i< connections_.size(); ++i) {
    int a= connections_[i].first;
    int b= connections_[i].second;
    CGAL_PDB_FOREACH(Model_pair &m, models()) {
      bool found=false;
      CGAL_PDB_FOREACH(Model::Heterogen_pair &h, m.model().heterogens()) {
        if (h.heterogen().connect(Atom::Index(a), Atom::Index(b))) {
          found=true;
          break;
        }
      }
      if (!found) {
        CGAL_LOG(Log::SOME, "Could not connect atoms " << a << " and " << b 
                << std::endl);
      }
    }
  }
  connections_.clear();
}

std::ostream& PDB::write(std::ostream &out) const {
  for (unsigned int i=0; i< header_.size(); ++i){
    out << header_[i] << std::endl;
  }
  CGAL_PDB_FOREACH(const Model_pair &m, models()) {
    m.model().write(m.key().index(), out);
  }
  out << "END   \n";
  return out;
}


PDB::Model_key PDB::push_back(const Model &m) {
  Model_key k(0);
  if (!empty()) k= Model_key(models_.rbegin()->key().index()+1);
  insert(k, m);
  return k;
}

}}
