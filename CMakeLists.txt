cmake_minimum_required(VERSION 3.16)
project(SecondGeantProject)

# Use modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_RPATH "/home/mihnwq/Geant4/geant4-v11.3.2-install/lib")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)


# --- Find Geant4 package ---
find_package(Geant4 REQUIRED ui_all vis_all)

# --- Include Geant4 macros ---
include(${Geant4_USE_FILE})
set(Geant4_DIR "/home/mihnwq/Geant4/geant4-v11.3.2-install/lib/Geant4-11.3.2")

# --- Add your include directories ---
include_directories(${PROJECT_SOURCE_DIR}/B4a/include)

# --- Define your executable and sources ---
add_executable(SecondGeantProject
        B4a/include/ActionInitialization.hh
        B4a/include/DataVector.hh
        B4a/include/DetectorConstruction.hh
        B4a/include/EventAction.hh
        B4a/include/PrimaryGeneratorAction.hh
        B4a/include/HitAction.hh
        B4a/include/RunAction.hh
        B4a/include/SteppingAction.hh
        B4a/src/ActionInitialization.cc
        B4a/src/DataVector.cc
        B4a/src/DetectorConstruction.cc
        B4a/src/EventAction.cc
        B4a/src/PrimaryGeneratorAction.cc
        B4a/src/RunAction.cc
        B4a/src/SteppingAction.cc
        B4a/exampleB4a.cc
)

# --- Link against Geant4 libraries ---
target_link_libraries(SecondGeantProject ${Geant4_LIBRARIES})
