#Define version of cmake
cmake_minimum_required(VERSION 3.19)

#Define project name and version
project(UWEGAMESJAM2025 VERSION 1.0)

#Fetch sfml libraries
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 3.0.1
)
FetchContent_MakeAvailable(SFML)

#Set version of C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

#Define executable files
add_executable(
	UWEGAMESJAM2025
	"src/main.cpp" "src/game.cpp" "src/Game.h"  "src/ThreadPool.h" "src/ThreadPool.cpp" "src/audio/Audio.h" "src/audio/Audio.cpp" "src/audio/Sound.cpp" "src/audio/Sound.h"  "src/Enums.h" "src/Structs.h" "src/mech/Gauge.cpp" "src/mech/Gauge.h" "src/mech/TypeCheck.cpp" "src/mech/TypeCheck.h" "src/states/Menu.cpp" "src/states/Menu.h" "src/states/Menu.h")

#Link the acquired libraries for use
target_link_libraries(
 UWEGAMESJAM2025
 sfml-graphics sfml-window sfml-system sfml-network sfml-audio
)

#Copy the data directory to the project for build to allow executable access
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
