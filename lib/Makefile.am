AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = @ACLOCAL_AMFLAGS@ -I m4

lib_LTLIBRARIES=libhynodeva-component-filesystem-sample.la

libhynodeva_component_filesystem_sample_la_SOURCES = ../filesystem.cpp
libhynodeva_component_filesystem_sample_la_LDFLAGS =@LDFLAGS@ -shared
libhynodeva_component_filesystem_sample_la_LIBADD = $(PTHREAD_LIBS)
libhynodeva_component_filesystem_sample_la_CXXFLAGS = @CXXFLAGS@ $(PTHREAD_CXXFLAGS) -fPIC
libhynodeva_component_filesystem_sample_la_CFLAGS = @CFLAGS@  $(PTHREAD_CFLAGS) -fPIC
libhynodeva_component_filesystem_sample_la_include_HEADERS = ../filesystem.hpp
libhynodeva_component_filesystem_sample_la_includedir = hynodeva/filesystem

noinst_LIBRARIES=libhynodeva-component-filesystem-sample.a

libhynodeva_component_filesystem_sample_a_SOURCES = ../filesystem.cpp
#libhynodeva_component_filesystem_a_LDFLAGS =@LDFLAGS@ 
libhynodeva_component_filesystem_sample_a_LIBADD = $(PTHREAD_LIBS)
libhynodeva_component_filesystem_sample_a_CXXFLAGS = @CXXFLAGS@ $(PTHREAD_CXXFLAGS) -fPIC
libhynodeva_component_filesystem_sample_a_CFLAGS = @CFLAGS@  $(PTHREAD_CFLAGS) -fPIC
libhynodeva_component_filesystem_sample_a_include_HEADERS = ../filesystem.hpp
libhynodeva_component_filesystem_sample_a_includedir = hynodeva/filesystem
