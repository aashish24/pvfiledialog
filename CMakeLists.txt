cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

project(pvFileDialogModule)

# ParaView is required
find_package(ParaView REQUIRED)
if(ParaView_FOUND)
  set(VTK_DIR ${PARAVIEW_VTK_DIR})
endif()
#include(${ParaView_USE_FILE})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

# SIP is required
find_program(SIP_EXECUTABLE sip)

#include_directories(${PARAVIEW_INCLUDE_DIRS}
#  ${ParaView_BINARY_DIR}/Qt/Core
#  ${QT_INCLUDE_DIR}
#  ${PARAVIEW_GUI_INCLUDE_DIRS}
#)

#qt4_wrap_cpp(mocSouces pqSessionFileDialogModel.h pvFileDialogModelWrapper.h)

#add_library(pvFileDialogModelWrapper ${mocSouces} pqSessionFileDialogModel.cxx pvFileDialogModelWrapper.cxx)
#target_link_libraries(pvFileDialogModelWrapper)
