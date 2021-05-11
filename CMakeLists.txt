cmake_minimum_required(VERSION 3.15)

project(uniGame VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Чтобы найти пакеты Qt5
set(CMAKE_PREFIX_PATH "/home/unitedtimur/Qt/5.12.9/gcc_64/lib/")

find_package(Qt5 COMPONENTS Core Widgets Gui Multimedia REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(project_ui
	ui/Matrix.ui
)

set(project_headers 
	include/Configuration.h
	include/GraphicScene.h
	include/GraphicView.h
	include/Matrix.h
	include/Functions.h

	# Triangles levels

	include/levels/ILevel.h
	include/levels/Level_Triangle_1.h
	include/levels/Level_Triangle_1.cpp
	include/levels/Level_Triangle_2.h
	include/levels/Level_Triangle_2.cpp
	include/levels/Level_Triangle_3.h
	include/levels/Level_Triangle_3.cpp

	# Length and distance levels

	include/levels/Level_LengthAndDistance_1.h
	include/levels/Level_LengthAndDistance_1.cpp
	include/levels/Level_LengthAndDistance_2.h
	include/levels/Level_LengthAndDistance_2.cpp
	include/levels/Level_LengthAndDistance_3.h
	include/levels/Level_LengthAndDistance_3.cpp

        # Graphics cells
        include/levels/Point.h
        include/graphicscell.h
        src/graphicscell.cpp

        # Labirints

        include/levels/Level_Labirint_1.h
        include/levels/Level_Labirint_1.cpp
        include/levels/Level_Labirint_2.h
        include/levels/Level_Labirint_2.cpp
        include/levels/Level_Labirint_3.h
        include/levels/Level_Labirint_3.cpp
)

set(project_sources 
	src/main.cpp
	src/Matrix.cpp
	src/GraphicScene.cpp
	src/GraphicView.cpp
)

set(project_resources
	src/resource.qrc
)

qt5_wrap_ui(project_headers_wrapped ${project_ui})
qt5_add_resources(project_sources ${project_resources})

# Устанавливаем режим работы приложения для Windows
IF(WIN32)
	SET(GUI_TYPE WIN32)
ENDIF(WIN32)
# Устанавливаем режим работы приложения для MacOS
IF (APPLE)
	SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

add_executable(${PROJECT_NAME} ${GUI_TYPE}
	${project_headers}
	${project_sources}
	${project_headers_wrapped}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC 
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
        Qt5::Multimedia
)
