CGAL_DIR = /KM/projects/CGAL/Work_in_Progress/test_version_8_11_96/CGAL-0.5

all: sun4OS4_CC sun4OS5_CC sun4OS4_g++ sun4OS5_g++ irix5_CC

everything: all KernelMakefile ApplicationMakefile
#-------------------------------------------------------------------------

sun4OS4_CC_SOURCES = make.nw common.nw make_sun4OS4_CC.nw

sun4OS4_CC: $(CGAL_DIR)/MAKE/sun4OS4_CC/lib \
            $(CGAL_DIR)/MAKE/sun4OS4_CC/sharedlib  \
	    $(CGAL_DIR)/MAKE/sun4OS4_CC/application

$(CGAL_DIR)/MAKE/sun4OS4_CC/lib: $(sun4OS4_CC_SOURCES)
	notangle -t8 -R"sun4OS4_CC/lib" $(sun4OS4_CC_SOURCES) > $@


$(CGAL_DIR)/MAKE/sun4OS4_CC/sharedlib: $(sun4OS4_CC_SOURCES)
	notangle -t8 -R"sun4OS4_CC/sharedlib" $(sun4OS4_CC_SOURCES) > $@


$(CGAL_DIR)/MAKE/sun4OS4_CC/application: $(sun4OS4_CC_SOURCES)
	notangle -t8 -R"sun4OS4_CC/application" $(sun4OS4_CC_SOURCES) > $@

#-------------------------------------------------------------------------

sun4OS5_CC_SOURCES = make.nw common.nw make_sun4OS5_CC.nw

sun4OS5_CC: $(CGAL_DIR)/MAKE/sun4OS5_CC/lib \
            $(CGAL_DIR)/MAKE/sun4OS5_CC/sharedlib  \
	    $(CGAL_DIR)/MAKE/sun4OS5_CC/application

$(CGAL_DIR)/MAKE/sun4OS5_CC/lib: $(sun4OS5_CC_SOURCES)
	notangle -t8 -R"sun4OS5_CC/lib" $(sun4OS5_CC_SOURCES) > $@


$(CGAL_DIR)/MAKE/sun4OS5_CC/sharedlib: $(sun4OS5_CC_SOURCES)
	notangle -t8 -R"sun4OS5_CC/sharedlib" $(sun4OS5_CC_SOURCES) > $@


$(CGAL_DIR)/MAKE/sun4OS5_CC/application: $(sun4OS5_CC_SOURCES)
	notangle -t8 -R"sun4OS5_CC/application" $(sun4OS5_CC_SOURCES) > $@

#-------------------------------------------------------------------------

sun4OS4_g++_SOURCES = make.nw common.nw make_sun4OS4_g++.nw

sun4OS4_g++: $(CGAL_DIR)/MAKE/sun4OS4_g++/lib \
            $(CGAL_DIR)/MAKE/sun4OS4_g++/sharedlib  \
	    $(CGAL_DIR)/MAKE/sun4OS4_g++/application

$(CGAL_DIR)/MAKE/sun4OS4_g++/lib: $(sun4OS4_g++_SOURCES)
	notangle -t8 -R"sun4OS4_g++/lib" $(sun4OS4_g++_SOURCES) > $@


$(CGAL_DIR)/MAKE/sun4OS4_g++/sharedlib: $(sun4OS4_g++_SOURCES)
	notangle -t8 -R"sun4OS4_g++/sharedlib" $(sun4OS4_g++_SOURCES) > $@


$(CGAL_DIR)/MAKE/sun4OS4_g++/application: $(sun4OS4_g++_SOURCES)
	notangle -t8 -R"sun4OS4_g++/application" $(sun4OS4_g++_SOURCES) > $@

#-------------------------------------------------------------------------

sun4OS5_g++_SOURCES = make.nw common.nw make_sun4OS5_g++.nw

sun4OS5_g++: $(CGAL_DIR)/MAKE/sun4OS5_g++/lib \
            $(CGAL_DIR)/MAKE/sun4OS5_g++/sharedlib  \
	    $(CGAL_DIR)/MAKE/sun4OS5_g++/application

$(CGAL_DIR)/MAKE/sun4OS5_g++/lib: $(sun4OS5_g++_SOURCES)
	notangle -t8 -R"sun4OS5_g++/lib" $(sun4OS5_g++_SOURCES) > $@


$(CGAL_DIR)/MAKE/sun4OS5_g++/sharedlib: $(sun4OS5_g++_SOURCES)
	notangle -t8 -R"sun4OS5_g++/sharedlib" $(sun4OS5_g++_SOURCES) > $@


$(CGAL_DIR)/MAKE/sun4OS5_g++/application: $(sun4OS5_g++_SOURCES)
	notangle -t8 -R"sun4OS5_g++/application" $(sun4OS5_g++_SOURCES) > $@

#-------------------------------------------------------------------------

irix5_CC_SOURCES = make.nw common.nw make_irix5_CC.nw

irix5_CC: $(CGAL_DIR)/MAKE/irix5_CC/lib \
            $(CGAL_DIR)/MAKE/irix5_CC/sharedlib  \
	    $(CGAL_DIR)/MAKE/irix5_CC/application

$(CGAL_DIR)/MAKE/irix5_CC/lib: $(irix5_CC_SOURCES)
	notangle -t8 -R"irix5_CC/lib" $(irix5_CC_SOURCES) > $@


$(CGAL_DIR)/MAKE/irix5_CC/sharedlib: $(irix5_CC_SOURCES)
	notangle -t8 -R"irix5_CC/sharedlib" $(irix5_CC_SOURCES) > $@


$(CGAL_DIR)/MAKE/irix5_CC/application: $(irix5_CC_SOURCES)
	notangle -t8 -R"irix5_CC/application" $(irix5_CC_SOURCES) > $@

#-------------------------------------------------------------------------
KernelMakefile: $(CGAL_DIR)/src/makefile

$(CGAL_DIR)/src/makefile: make.nw 
	notangle -t8 -R" Toplevel Kernel Makefile " make.nw > $@
 
#-------------------------------------------------------------------------
ApplicationMakefile: $(CGAL_DIR)/makefile

$(CGAL_DIR)/makefile: make.nw 
	notangle -t8 -R" Master Application Makefile " make.nw > $@
