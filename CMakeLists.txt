project(adsp.template)

cmake_minimum_required(VERSION 2.6)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(kodi REQUIRED)
find_package(kodiplatform REQUIRED)
find_package(platform REQUIRED)
find_package(TinyXML REQUIRED)

include_directories(${kodiplatform_INCLUDE_DIRS}
                    ${platform_INCLUDE_DIRS}
                    ${KODI_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/src
                    ${PROJECT_SOURCE_DIR}/src/template)
                    
file (GLOB_RECURSE ADSP_TEMPLATE_SOURCES  "src/*.c"
                                          "src/*.cpp"
                                          "src/*.h"
                                          "src/*.hpp")

# set(TEMPLATE_SOURCES  src/ADDONOptional.cpp
                      # src/channelUpmixer.cpp
                      # src/DSPProcessor.cpp
                      # src/Dialogs/GUIDialogMasterProcess.cpp
                      # src/Dialogs/GUIDialogOutputResample.cpp
                      # src/Dialogs/GUIDialogPreProcess.cpp
                      # src/Dialogs/GUIDialogPostProcess.cpp
                      # src/template/AddonHelpers.cpp
                      # src/template/ADSPAddonHandler.cpp
                      # src/template/ADSPHelpers.cpp
                      # src/template/ADSPProcessorHandle.cpp
                      # src/template/client.cpp
                      # src/template/GUIDialogBase.cpp
                      # src/template/IADDONOptional.cpp
                      # src/template/IADSPProcessor.cpp
                      # src/template/Settings/SettingsManager.cpp
                      # src/template/Settings/SettingsHelpers.cpp
                      # src/template/Messages/ADSPModeMessage.cpp
                      # src/template/configuration/templateConfiguration.cpp
                      
                      # src/template/AddonExceptions/IAddonException.h
                      # src/template/AddonExceptions/TAddonException.h
                      # src/template/configuration/templateConfiguration.h
                      
                      # src/template/include/ADSPAddonHandler.h
                      # src/template/include/ADSPModeMessage.h
                      # src/template/include/ADSPProcessorHandle.h
                      # src/template/include/checkTemplateConfig.h
                      # src/template/include/client.h
                      # src/template/include/GUIDialogBase.h
                      # src/template/include/IADDONOptional.h
                      # src/template/include/IADSPProcessor.h
                      # src/template/include/MACROHelper.h
                      # src/template/include/typedefs.h
                      
                      # src/template/Settings/ISettingsElement.h
                      # src/template/Settings/SettingsHelpers.h
                      # src/template/Settings/SettingsManager.h
                      # src/template/Settings/TSettingsElement.h
                      
                      # src/Dialogs/GUIDialogMasterProcess.h
                      # src/Dialogs/GUIDialogOutputResample.h
                      # src/Dialogs/GUIDialogPostProcess.h
                      # src/Dialogs/GUIDialogPreProcess.h
                      
                      # src/ADDONOptional.h
                      # src/channelUpmixer.h
                      # src/DSPProcessor.h)

set(DEPLIBS ${kodiplatform_LIBRARIES}
            ${platform_LIBRARIES})

build_addon(adsp.template ADSP_TEMPLATE DEPLIBS)

# For generating the doxy
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/doxygen_resources/Doxyfile
                    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                    COMMENT "Generating API documentation" VERBATIM)
endif()

include(CPack)
