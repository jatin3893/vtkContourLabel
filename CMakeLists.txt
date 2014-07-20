cmake_minimum_required(VERSION 2.8.5 FATAL_ERROR)

project ( vtkContourLabel )

set(VTK_REQUIRED_COMPONENTS
	# Core components
	vtkRenderingCore
	vtkRenderingOpenGL
	vtkCommonCore
	vtkInteractionStyle
	vtkRenderingLabel
)

find_package(VTK NO_MODULE REQUIRED COMPONENTS ${VTK_REQUIRED_COMPONENTS})

include (${VTK_USE_FILE})

set (SOURCES
		main.cpp
		vtkContourLabel.cxx
		vtkContourLabel.h)

add_executable(run ${SOURCES})

target_link_libraries(run ${VTK_LIBRARIES} )
