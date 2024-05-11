###############################################################################
#
# Generic Makefile
# Usage: make [build | proto | clean]
#
###############################################################################

#------------------------------------------------------------------------------
# Include other config file
#------------------------------------------------------------------------------
include ./Makefile.def


EXECUTABLE := train
POSTFIX    := exe #dll #lib
SLICE_MAKE := yes # yes or no 是否需要编译slice文件

GRPC_MAKE   := yes # yes or no 是否需要编译 proto grcp文件
#GRPC_PATH   := ./lib/grpc
GRPC_PATH   := ./lib/grpc-1.33_dynamic
PROTOC      := $(GRPC_PATH)/bin/protoc
GRPC_CPP_PLUGIN_PATH  = $(GRPC_PATH)/bin/grpc_cpp_plugin

#ICE_OUTPUT_DIR  :=  ./src
#ICE_INPUT       :=  ./interface/*.ice

GRPC_OUTPUT_DIR :=  ./src
GRPC_INPUT      :=  ./protos/*.proto

DEST_EXE =  $(PRODUCT_DEST_EXE)
DEST_LIB =  $(PRODUCT_DEST_LIB)

INCLUDE_PATH := ./src \
                ./include \
                $(DEPS_HOME)/grpc-1.33_dynamic/include
 
LIB_PATH     := $(DEPS_HOME)/grpc-1.33_dynamic/lib

LIBS         := protobuf pthread 


#------------------------------------------------------------------------------
# Now alter any implicit rules' variables if you like, e.g.:
#------------------------------------------------------------------------------
CXXFLAGS  := $(PRODUCT_CXXFLAGS)
#CXXFLAGS := $(PRODUCT_CXXFLAGS) -D _DEBUG_PRINT#-fpermissive
#CXXFLAGS := $(PRODUCT_CXXFLAGS) -Wfatal-errors -fpermissive -w

#------------------------------------------------------------------------------
# Include Makefile rule
#------------------------------------------------------------------------------
include ./Makefile.rul

#------------------------------------------------------------------------------
# End of Makefile 
#------------------------------------------------------------------------------
