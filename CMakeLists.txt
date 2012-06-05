cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

project(pvFileDialogModelWrapper)

# Set search path for cmake modules
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

# Only build shared library
set(BUILD_SHARED_LIBS ON)

# ParaView is required
find_package(ParaView REQUIRED)

# Qt4 is required
find_package(Qt4 REQUIRED)

# Python is requird
find_package(PythonInterp REQUIRED)

# SIP is required
find_package(SIP REQUIRED)

# pvFileDialogModel is required
find_library(PV_FILE_DIALOG_MODEL_LIB pvFileDialogModel)
find_path(PV_FILE_DIALOG_MODEL_INCLUDE pvFileDialogModel.h)

set(SIP_PATH /usr/share/sip/PyQt4)
set(SIP_OUTPUT
  ${CMAKE_CURRENT_BINARY_DIR}/pvFileDialogModelWrapper.h
  ${CMAKE_CURRENT_BINARY_DIR}/sipAPIpvFileDialogModelWrapper.h
  ${CMAKE_CURRENT_BINARY_DIR}/sippvFileDialogModelWrappercmodule.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/sippvFileDialogModelWrapperpvFileDialogModelWrapper.cpp
)

add_custom_command(OUTPUT
  ${SIP_OUTPUT}
  COMMAND ${SIP_EXECUTABLE} -c ${CMAKE_CURRENT_BINARY_DIR} -I ${SIP_PATH} -t WS_X11 -t Qt_4_6_0
  ${CMAKE_CURRENT_SOURCE_DIR}/pvFileDialogModelWrapper.sip
  DEPENDS)

include_directories(
  ${SIP_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}/QtCore
  ${QT_INCLUDE_DIR}/QtGui
  ${PV_FILE_DIALOG_MODEL_INCLUDE}
)

add_library(pvFileDialogModelWrapper ${SIP_OUTPUT})
set_target_properties(pvFileDialogModelWrapper PROPERTIES PREFIX "")
target_link_libraries(pvFileDialogModelWrapper ${PV_FILE_DIALOG_MODEL_LIB} )
