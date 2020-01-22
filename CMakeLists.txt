cmake_minimum_required(VERSION 3.15)

project(uniGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Чтобы найти пакеты Qt5
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.13.0\\msvc2017_64")

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(project_ui
	ui/UniMainWindow.ui
)

set(project_headers 
	include/UniMainWindow.h
	include/Configuration.h
)

set(project_sources 
	src/main.cpp
	src/UniMainWindow.cpp
)

set(project_resources
	src/resource.qrc
)

qt5_wrap_ui(project_headers_wrapped ${project_ui})
#qt5_wrap_cpp(project_sources_moc ${project_headers})
qt5_add_resources(project_sources ${project_resources})

add_executable(${PROJECT_NAME}
	${project_headers}
	${project_sources}
	#${project_sources_moc}
	${project_headers_wrapped}
)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)