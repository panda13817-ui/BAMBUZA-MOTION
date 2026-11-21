cmake_minimum_required(VERSION 3.22)
project(BambuzaMotion VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(BAMBUZA_FETCH_JUCE "Fetch JUCE 8.0.10" OFF)
option(BAMBUZA_DSP_ONLY "Build standalone DSP tests without JUCE" OFF)
if(BAMBUZA_DSP_ONLY)
  enable_testing()
  add_executable(BambuzaMotionDSPTests Tests/DSPTests.cpp Source/DSP/PanEngine.cpp Source/DSP/ModulationEngine.cpp)
  target_include_directories(BambuzaMotionDSPTests PRIVATE Source)
  add_test(NAME BambuzaMotionDSPTests COMMAND BambuzaMotionDSPTests)
  return()
endif()
set(JUCE_DIR "" CACHE PATH "Path to JUCE source")
if(BAMBUZA_FETCH_JUCE)
  include(FetchContent)
  FetchContent_Declare(JUCE GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 8.0.10 GIT_SHALLOW TRUE)
  FetchContent_MakeAvailable(JUCE)
elseif(JUCE_DIR)
  add_subdirectory("${JUCE_DIR}" "${CMAKE_BINARY_DIR}/JUCE")
else()
  message(FATAL_ERROR "Set JUCE_DIR or enable BAMBUZA_FETCH_JUCE=ON")
endif()

set(PLUGIN_FORMATS VST3)
if(APPLE)
  list(APPEND PLUGIN_FORMATS AU Standalone)
endif()
juce_add_plugin(BambuzaMotion
  COMPANY_NAME "Bambuza Components"
  BUNDLE_ID "com.bambuza.components.motion"
  PLUGIN_MANUFACTURER_CODE Bmbz
  PLUGIN_CODE BmM1
  PRODUCT_NAME "Bambuza Motion"
  FORMATS ${PLUGIN_FORMATS}
  IS_SYNTH FALSE NEEDS_MIDI_INPUT TRUE NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE EDITOR_WANTS_KEYBOARD_FOCUS FALSE
  COPY_PLUGIN_AFTER_BUILD FALSE
)
juce_generate_juce_header(BambuzaMotion)
target_sources(BambuzaMotion PRIVATE
  Source/Plugin/PluginProcessor.cpp Source/Plugin/PluginProcessor.h
  Source/Plugin/PluginEditor.cpp Source/Plugin/PluginEditor.h
  Source/DSP/PanEngine.cpp Source/DSP/PanEngine.h
  Source/DSP/EnvelopeFollower.h
  Source/DSP/ModulationEngine.cpp Source/DSP/ModulationEngine.h
  Source/DSP/PatternSequencer.h
  Source/DSP/Saturation.h
)
target_compile_definitions(BambuzaMotion PUBLIC JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)
target_link_libraries(BambuzaMotion PRIVATE juce::juce_audio_utils juce::juce_dsp
  PUBLIC juce::juce_recommended_config_flags juce::juce_recommended_warning_flags)
include(CTest)
if(BUILD_TESTING)
  add_executable(BambuzaMotionDSPTests Tests/DSPTests.cpp Source/DSP/PanEngine.cpp Source/DSP/ModulationEngine.cpp)
  target_include_directories(BambuzaMotionDSPTests PRIVATE Source)
  add_test(NAME BambuzaMotionDSPTests COMMAND BambuzaMotionDSPTests)
endif()
