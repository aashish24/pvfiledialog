cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

project(pvFileDialogModelWrapper)

# Set search path for cmake modules
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

# Only build shared library
set(BUILD_SHARED_LIBS ON)

# Python libraries are required
set(Python_ADDITIONAL_VERSIONS 2.6 2.7)
find_package(PythonLibs)

# ParaView is required
find_package(ParaView REQUIRED)

# VTK is required
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

# Qt4 is required
find_package(Qt4 REQUIRED)

# Build pvFileDialogModel
include_directories(
  ${PARAVIEW_INCLUDE_DIRS}
  ${ParaView_BINARY_DIR}/Qt/Core
  ${QT_INCLUDE_DIR}
  ${PARAVIEW_GUI_INCLUDE_DIRS}
)

qt4_wrap_cpp(mocSouces pqSessionFileDialogModel.h pvFileDialogModelWrapper.h)

add_library(pvFileDialogModel ${mocSouces} pqSessionFileDialogModel.cxx pvFileDialogModelWrapper.cxx)
target_link_libraries(pvFileDialogModel
  ${QT_LIBRARIES}
  vtkPVClientServerCore
  vtkPVServerManager
  pqComponents
)

# Python is requird
find_package(PythonInterp REQUIRED)

# SIP is required
find_package(SIP REQUIRED)

# Find PyQt SIP directory
find_path(PYQT_SIP_DIR QtCore/qstring.sip
  PATHS /System/Library/Frameworks/Python.framework/Versions/2.6
  ${SIP_DEFAULT_SIP_DIR}
  PATH_SUFFIXES share/sip/PyQt4 share/sip ../share/sip share/py-sip/
)

# Set SIP flags
set(PYQT_SIP_FLAGS
    "-x" "VendorID"
    "-x" "PyQt_NoPrintRangeBug"
    "-o"
)

if(WIN32)
  list(APPEND PYQT_SIP_FLAGS "-t" "Qt_4_6_2")
  list(APPEND PYQT_SIP_FLAGS "-t" "WS_WIN")
elseif(APPLE)
  list(APPEND PYQT_SIP_FLAGS "-t" "Qt_4_7_1")
  list(APPEND PYQT_SIP_FLAGS "-t" "WS_MACX")
else(WIN32)
  list(APPEND PYQT_SIP_FLAGS "-t" "Qt_4_6_2")
  list(APPEND PYQT_SIP_FLAGS "-t" "WS_X11")
endif(WIN32)

# Gather list of generated files
set(source pvFileDialogModelWrapper.sip)
get_filename_component(source_directory ${source} PATH)
get_filename_component(source_basename ${source} NAME)
get_filename_component(source_module ${source} NAME_WE)

set(outputs
  "${CMAKE_CURRENT_BINARY_DIR}/sip${source_module}cmodule.cpp"
  "${CMAKE_CURRENT_BINARY_DIR}/sipAPI${source_module}.h"
)

# Find any included files
execute_process(
  COMMAND "awk" "/^%Include/ {ORS=\";\"; print \"${source_directory}/\" $2}"
    "${CMAKE_CURRENT_SOURCE_DIR}/${source}"
  OUTPUT_VARIABLE included_files
)

foreach(included_file ${included_files} ${source})
  # Sip creates 1 file per class... so we have to figure out what classes
  # it will generate
  execute_process(
    COMMAND "awk" "/^\\s*(class|namespace|struct) +([A-Za-z0-9]+)/ {ORS=\";\"; print $2}"
      "${CMAKE_CURRENT_SOURCE_DIR}/${included_file}"
      OUTPUT_VARIABLE classes
  )

  foreach(class ${classes})
    list(APPEND outputs "${CMAKE_CURRENT_BINARY_DIR}/sip${source_module}${class}.cpp")
  endforeach(class)
endforeach(included_file)

add_custom_command(OUTPUT
  ${outputs}
  COMMAND ${SIP_EXECUTABLE} ${PYQT_SIP_FLAGS} -I ${PYQT_SIP_DIR}
    -c ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/${source}
  DEPENDS ${included_files} "${source}")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PYTHON_INCLUDE_DIRS}
  ${SIP_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}
  ${QT_INCLUDE_DIR}/QtCore
  ${QT_INCLUDE_DIR}/QtGui
)

add_library(pvFileDialogModelWrapper ${outputs})
set_target_properties(pvFileDialogModelWrapper PROPERTIES PREFIX "")
target_link_libraries(pvFileDialogModelWrapper pvFileDialogModel)

install(TARGETS pvFileDialogModel pvFileDialogModelWrapper
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
