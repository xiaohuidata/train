AUTOMAX_OPTIONS=train

SRC_DIR=src
#SRC_CPP = $(wildcard $(SRC_DIR)/*.cpp)
#SRC_C = $(wildcard $(SRC_DIR)/*.c)
#SRC_CC = $(wildcard $(SRC_DIR)/*.cc)
#PROTO_CC = $(wildcard $(SRC_DIR)/gen/*.cc)
SRC_CPP = src/common.cpp  src/Descriptor.cpp  src/Header.cpp  src/main.cpp  src/Solution.cpp  src/Source.cpp
SRC_C =
SRC_CC =
PROTO_CC = src/gen/function.pb.cc
SRC_FILES = $(SRC_CPP) $(SRC_C) $(SRC_CC) $(PROTO_CC)

bin_PROGRAMS=train

train_SOURCES = $(SRC_FILES)

train_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src/gen -I$(top_srcdir)/$(PROTOC_FORMATTER) -I$(top_srcdir)/$(PROTOBUF_PATH)/include

train_LDADD = -L$(top_srcdir)/lib/grpc-1.33_dynamic/lib -lprotobuf
#train_LDADD = -lprotobuf

AM_CXXFLAGS = -Wall -std=c++11 -fpermissive

CLEANFILES = somefile.tmp
