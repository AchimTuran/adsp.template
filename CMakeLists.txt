include(cmake/addon-template-helpers.cmake)

project(adsp.template C CXX)

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
                    ${PROJECT_SOURCE_DIR}/src/template
                    ${PROJECT_SOURCE_DIR}/src/KodiThreads)
                    
#file (GLOB_RECURSE ADSP_TEMPLATE_SOURCES  "src/*.c"
                                          #"src/*.cpp"
                                          #"src/*.h"
                                          #"src/*.hpp")
                                          
set(ADSP_TEMPLATE_SOURCES     src/ADDONOptional.cpp
                              src/channelUpmixer.cpp
                              src/DSPProcessor.cpp
                              src/Dialogs/GUIDialogMasterProcess.cpp
                              src/Dialogs/GUIDialogOutputResample.cpp
                              src/Dialogs/GUIDialogPostProcess.cpp
                              src/Dialogs/GUIDialogPreProcess.cpp
                              src/KodiThreads/commons/Exception.cpp
                              src/KodiThreads/threads/Atomics.cpp
                              src/KodiThreads/threads/Event.cpp
                              src/KodiThreads/threads/SystemClock.cpp
                              src/KodiThreads/threads/Thread.cpp
                              src/KodiThreads/threads/Timer.cpp
                              #src/KodiThreads/threads/platform/Implementation.cpp
                              #src/KodiThreads/threads/platform/ThreadImpl.cpp
                              #src/KodiThreads/threads/platform/darwin/ThreadSchedImpl.cpp
                              #src/KodiThreads/threads/platform/linux/ThreadSchedImpl.cpp
                              #src/KodiThreads/threads/platform/pthreads/Implementation.cpp
                              #src/KodiThreads/threads/platform/pthreads/ThreadImpl.cpp
                              #src/KodiThreads/threads/platform/win/ThreadImpl.cpp
                              src/KodiThreads/threads/platform/win/Win32Exception.cpp
                              src/template/AddonHelpers.cpp
                              src/template/ADSPAddonHandler.cpp
                              src/template/ADSPHelpers.cpp
                              src/template/ADSPProcessorHandle.cpp
                              src/template/client.cpp
                              src/template/GUIDialogBase.cpp
                              src/template/IADDONOptional.cpp
                              src/template/IADSPProcessor.cpp
                              src/template/Addon/Handler/AddonHandler.cpp
                              src/template/Addon/MessageSystem/Communication/ActorProtocol.cpp
                              src/template/Addon/MessageSystem/Communication/ConnectionPort.cpp
                              src/template/Addon/MessageSystem/Communication/Message.cpp
                              src/template/Addon/MessageSystem/Communication/MessageSystemReceiver.cpp
                              src/template/Addon/MessageSystem/Communication/MessageSystemSender.cpp
                              src/template/Addon/MessageSystem/Interfaces/IMessageHandler.cpp
                              src/template/Addon/Settings/SettingsPool.cpp
                              src/template/Addon/UI/BaseDialog.cpp
                              src/template/Addon/UI/Controller.cpp
                              src/template/Addon/UI/Model.cpp
                              src/template/Addon/UI/Observer.cpp
                              src/template/Addon/UI/View.cpp
                              #src/template/AudioDSP/FactoryADSPModes/adsp_dll_functions.cpp
                              #src/template/AudioDSP/FactoryADSPModes/adsp_functions.cpp
                              src/template/AudioDSP/FactoryADSPModes/FactoryADSPModes.cpp
                              src/template/AudioDSP/Handler/ADSPAddonHandler.cpp
                              src/template/configuration/templateConfiguration.cpp
                              src/template/Messages/ADSPModeMessage.cpp
                              src/template/Settings/SettingsHelpers.cpp
                              src/template/Settings/SettingsManager.cpp
                              
                              src/ADDONOptional.h
                              src/channelUpmixer.h
                              src/DSPProcessor.h
                              src/Dialogs/GUIDialogMasterProcess.h
                              src/Dialogs/GUIDialogOutputResample.h
                              src/Dialogs/GUIDialogPostProcess.h
                              src/Dialogs/GUIDialogPreProcess.h
                              src/KodiThreads/system.h
                              src/KodiThreads/commons/Exception.h
                              src/KodiThreads/threads/Atomics.h
                              src/KodiThreads/threads/Condition.h
                              src/KodiThreads/threads/CriticalSection.h
                              src/KodiThreads/threads/Event.h
                              src/KodiThreads/threads/Helpers.h
                              src/KodiThreads/threads/Lockables.h
                              #src/KodiThreads/threads/MipsAtomics.h
                              src/KodiThreads/threads/SharedSection.h
                              src/KodiThreads/threads/SingleLock.h
                              src/KodiThreads/threads/SystemClock.h
                              src/KodiThreads/threads/Thread.h
                              src/KodiThreads/threads/ThreadImpl.h
                              src/KodiThreads/threads/ThreadLocal.h
                              src/KodiThreads/threads/Timer.h
                              src/KodiThreads/threads/platform/Condition.h
                              src/KodiThreads/threads/platform/CriticalSection.h
                              src/KodiThreads/threads/platform/ThreadImpl.h
                              src/KodiThreads/threads/platform/ThreadLocal.h
                              #src/KodiThreads/threads/platform/pthreads/Condition.h
                              #src/KodiThreads/threads/platform/pthreads/CriticalSection.h
                              #src/KodiThreads/threads/platform/pthreads/ThreadImpl.h
                              #src/KodiThreads/threads/platform/pthreads/ThreadLocal.h
                              #src/KodiThreads/threads/platform/win/Condition.h
                              #src/KodiThreads/threads/platform/win/CriticalSection.h
                              #src/KodiThreads/threads/platform/win/ThreadImpl.h
                              #src/KodiThreads/threads/platform/win/ThreadLocal.h
                              src/KodiThreads/threads/platform/win/Win32Exception.h
                              src/template/ADSPHelpers.h
                              src/template/doxygenDocu.h
                              src/template/Addon/MessageSystem/Communication/ActorProtocol.h
                              src/template/AddonExceptions/IAddonException.h
                              src/template/AddonExceptions/TAddonException.h
                              src/template/configuration/templateConfiguration.h
                              src/template/include/ADSPAddonHandler.h
                              src/template/include/ADSPModeMessage.h
                              src/template/include/ADSPProcessorHandle.h
                              src/template/include/checkTemplateConfig.h
                              src/template/include/client.h
                              src/template/include/GUIDialogBase.h
                              src/template/include/IADDONOptional.h
                              src/template/include/IADSPProcessor.h
                              src/template/include/MACROHelper.h
                              src/template/include/typedefs.h
                              src/template/Settings/ISettingsElement.h
                              src/template/Settings/SettingsHelpers.h
                              src/template/Settings/SettingsManager.h
                              src/template/Settings/TSettingsElement.h
                              src/utils/stdStringUtils.h
                              
                              src/template/Addon/Handler/AddonHandler.hpp
                              src/template/Addon/MessageSystem/Communication/ConnectionManager.hpp
                              src/template/Addon/MessageSystem/Communication/ConnectionPort.hpp
                              src/template/Addon/MessageSystem/Communication/Message.hpp
                              src/template/Addon/MessageSystem/Communication/MessageSystemReceiver.hpp
                              src/template/Addon/MessageSystem/Communication/MessageSystemSender.hpp
                              src/template/Addon/MessageSystem/Communication/TMonoConnectionPort.hpp
                              src/template/Addon/MessageSystem/ControllerListener/ListenerNotify.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TControllerMemcpy.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TControllerMemcpyFeedback.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TControllerMemcpyOffset.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TControllerScaler.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TControllerStruct.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TControllerStructFeedback.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TControllerTaskObject.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TListener.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TListenerScaler.hpp
                              src/template/Addon/MessageSystem/ControllerListener/TListenerTaskObject.hpp
                              src/template/Addon/MessageSystem/Interfaces/IConnectionPort.hpp
                              src/template/Addon/MessageSystem/Interfaces/IController.hpp
                              src/template/Addon/MessageSystem/Interfaces/IListener.hpp
                              src/template/Addon/MessageSystem/Interfaces/IMessageHandler.hpp
                              src/template/Addon/MessageSystem/Interfaces/IObject.hpp
                              src/template/Addon/Settings/SettingsPool.hpp
                              src/template/Addon/UI/BaseDialog.hpp
                              src/template/Addon/UI/Controller.hpp
                              src/template/Addon/UI/Model.hpp
                              src/template/Addon/UI/Observer.hpp
                              src/template/Addon/UI/View.hpp
                              src/template/AudioDSP/FactoryADSPModes/FactoryADSPModes.hpp
                              src/template/AudioDSP/FactoryADSPModes/IADSPMode.hpp
                              src/template/AudioDSP/FactoryADSPModes/TStatisticsADSPModes.hpp
                              src/template/AudioDSP/Handler/ADSPAddonHandler.hpp)
                              
addon_source_group("${ADSP_TEMPLATE_SOURCES}")
                                          
#EXCLUDE_FILES_FROM_DIR_IN_LIST("${ADSP_TEMPLATE_SOURCES}" "/KodiThreads/" TRUE)
#EXCLUDE_FILES_FROM_DIR_IN_LIST("${ADSP_TEMPLATE_SOURCES}" "/MessageSystem/" TRUE)

set(DEPLIBS ${kodiplatform_LIBRARIES}
            ${platform_LIBRARIES}
            winmm.lib)

build_addon(adsp.template ADSP_TEMPLATE DEPLIBS)

# For generating the doxy
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/doxygen_resources/Doxyfile
                    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
                    COMMENT "Generating API documentation" VERBATIM)
endif()

include(CPack)
