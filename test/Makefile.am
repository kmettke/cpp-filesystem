AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = @ACLOCAL_AMFLAGS@ -I m4

bin_PROGRAMS = hynodeva-component-filesystem-test

hynodeva_component_filesystem_test_SOURCES = ../main.cpp
hynodeva_component_filesystem_test_LDFLAGS =@LDFLAGS@ 
hynodeva_component_filesystem_test_LDADD = $(PTHREAD_LIBS)
hynodeva_component_filesystem_test_CXXFLAGS = @CXXFLAGS@ $(PTHREAD_CXXFLAGS)
hynodeva_component_filesystem_test_CFLAGS = @CFLAGS@  $(PTHREAD_CFLAGS)
