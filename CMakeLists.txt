
cmake_minimum_required(VERSION 3.16)
project(SecondGeantProject)

# --- Use modern C++ ---
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Find Geant4 package ---
find_package(Geant4 REQUIRED ui_all vis_all)

# --- Include Geant4 macros (only after find_package) ---
include(${Geant4_USE_FILE})

# --- Add include directories for your project ---
include_directories(
        ${PROJECT_SOURCE_DIR}/B4a/include
)

# --- Define your sources ---
set(SOURCES
        B4a/src/ActionInitialization.cc
        B4a/src/DataVector.cc
        B4a/src/DetectorConstruction.cc
        B4a/src/EventAction.cc
        B4a/src/PrimaryGeneratorAction.cc
        B4a/src/RunAction.cc
        B4a/src/SteppingAction.cc
        B4a/exampleB4a.cc
        B4a/src/EventCounter.cc
        B4a/src/TrackingAction.cc
        B4a/src/PhotonMuonHelper.cc
)

# --- Define headers (optional, but good practice) ---
set(HEADERS
        B4a/include/ActionInitialization.hh
        B4a/include/DataVector.hh
        B4a/include/DetectorConstruction.hh
        B4a/include/EventAction.hh
        B4a/include/PrimaryGeneratorAction.hh
        B4a/include/HitAction.hh
        B4a/include/RunAction.hh
        B4a/include/SteppingAction.hh
        B4a/include/EventCounter.hh
        B4a/include/PhotonMuonHelper.hh
        B4a/include/TrackingAction.hh
)

# --- Create the executable ---
add_executable(SecondGeantProject ${SOURCES} ${HEADERS})

# --- Link Geant4 libraries ---
target_link_libraries(SecondGeantProject ${Geant4_LIBRARIES})

# --- (Optional) Install rules ---
install(TARGETS SecondGeantProject DESTINATION bin)

