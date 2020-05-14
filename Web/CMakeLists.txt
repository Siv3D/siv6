cmake_minimum_required(VERSION 3.5)

project(Siv6 CXX)
enable_language(C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-D_GLFW_X11")
set(CMAKE_C_FLAGS "-D_GLFW_X11")

add_library(
  Siv3D STATIC
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Console/CConsole.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Logger/CLogger.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Unicode/SivUnicode_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3DMain.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Renderer/GLES3/CRenderer_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Renderer/RendererFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/System/CSystem.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Time/SivTime.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Window/CWindow.cpp
  ../Siv3D/src/Siv3D/Byte/SivByte.cpp
  ../Siv3D/src/Siv3D/Common/ApplicationOptions.cpp
  ../Siv3D/src/Siv3D/Common/Siv3DEngine.cpp
  ../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp
  ../Siv3D/src/Siv3D/Console/SivConsole.cpp
  # ../Siv3D/src/Siv3D/CPUInfo/SivCPUInfo.cpp
  ../Siv3D/src/Siv3D/Dummy/CDummy.cpp
  ../Siv3D/src/Siv3D/Dummy/DummyFactory.cpp
  ../Siv3D/src/Siv3D/EngineLog/SivEngineLog.cpp
  ../Siv3D/src/Siv3D/Error/SivError.cpp
  ../Siv3D/src/Siv3D/FormatFloat/SivFormatFloat.cpp
  ../Siv3D/src/Siv3D/FormatInt/SivFormatInt.cpp
  ../Siv3D/src/Siv3D/Formatter/SivFormatter.cpp
  ../Siv3D/src/Siv3D/IntFormatter/SivIntFormatter.cpp
  ../Siv3D/src/Siv3D/Logger/LoggerFactory.cpp
  ../Siv3D/src/Siv3D/Logger/SivLogger.cpp
  ../Siv3D/src/Siv3D/Point/SivPoint.cpp
  ../Siv3D/src/Siv3D/Profiler/CProfiler.cpp
  ../Siv3D/src/Siv3D/Profiler/ProfilerFactory.cpp
  ../Siv3D/src/Siv3D/Profiler/SivProfiler.cpp
  ../Siv3D/src/Siv3D/Scene/CScene.cpp
  ../Siv3D/src/Siv3D/Scene/SceneFactory.cpp
  ../Siv3D/src/Siv3D/Scene/SivScene.cpp
  ../Siv3D/src/Siv3D/String/SivString.cpp
  ../Siv3D/src/Siv3D/StringView/SivStringView.cpp
  ../Siv3D/src/Siv3D/System/SivSystem.cpp
  ../Siv3D/src/Siv3D/System/SystemFactory.cpp
  ../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp
  ../Siv3D/src/Siv3D/Unicode/UnicodeUtility.cpp
  ../Siv3D/src/Siv3D/UserAction/CUserAction.cpp
  ../Siv3D/src/Siv3D/UserAction/UserActionFactory.cpp
  ../Siv3D/src/Siv3D/Vector2D/SivVector2D.cpp
  ../Siv3D/src/Siv3D/Window/SivWindow.cpp
  ../Siv3D/src/Siv3D/Window/WindowFactory.cpp

  # ../Siv3D/src/ThirdParty/cpu_features/cpuinfo_x86.c

  ../Siv3D/src/ThirdParty/double-conversion/bignum-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/bignum.cc
  ../Siv3D/src/ThirdParty/double-conversion/cached-powers.cc
  ../Siv3D/src/ThirdParty/double-conversion/double-to-string.cc
  ../Siv3D/src/ThirdParty/double-conversion/fast-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/fixed-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/string-to-double.cc
  ../Siv3D/src/ThirdParty/double-conversion/strtod.cc

  ../Siv3D/src/ThirdParty/fmt/format.cc
  
  # ../Siv3D/src/ThirdParty/GLEW/glew.c
  # ../Siv3D/src/ThirdParty/GLFW/context.c
  # ../Siv3D/src/ThirdParty/GLFW/egl_context.c
  # ../Siv3D/src/ThirdParty/GLFW/glx_context.c
  # ../Siv3D/src/ThirdParty/GLFW/init.c
  # ../Siv3D/src/ThirdParty/GLFW/input.c
  # ../Siv3D/src/ThirdParty/GLFW/linux_joystick.c
  # ../Siv3D/src/ThirdParty/GLFW/monitor.c
  # ../Siv3D/src/ThirdParty/GLFW/osmesa_context.c
  # ../Siv3D/src/ThirdParty/GLFW/posix_thread.c
  # ../Siv3D/src/ThirdParty/GLFW/posix_time.c
  # ../Siv3D/src/ThirdParty/GLFW/vulkan.c
  # ../Siv3D/src/ThirdParty/GLFW/window.c
  # ../Siv3D/src/ThirdParty/GLFW/x11_init.c
  # ../Siv3D/src/ThirdParty/GLFW/x11_monitor.c
  # ../Siv3D/src/ThirdParty/GLFW/x11_window.c
  # ../Siv3D/src/ThirdParty/GLFW/xkb_unicode.c

  ../Siv3D/src/Test/Siv3DTest.cpp
  )

target_include_directories(
  Siv3D
  PUBLIC
  ../Siv3D/include
  ../Siv3D/include/ThirdParty
  ../Siv3D/src
  ../Siv3D/src/Siv3D-Platform/macOS_Linux
  ../Siv3D/src/Siv3D-Platform/Linux
  ../Siv3D/src/ThirdParty
  ${LIBSIV3D_INCLUDE_DIRS}
  )

enable_testing()

add_executable(
  Siv3DTest
  ../Web/Main.cpp
  )

target_link_libraries(Siv3DTest PRIVATE
  Siv3D
  pthread
  ${LIBSIV3D_LIBRARIES}
  ${CMAKE_DL_LIBS}
  )

target_include_directories(
  Siv3DTest
  PRIVATE ../Siv3D/src/ThirdParty)

set_target_properties(
  Siv3DTest
  PROPERTIES
  LINK_FLAGS "-s FULL_ES3=1 -s USE_GLFW=3 -s ERROR_ON_UNDEFINED_SYMBOLS=0"
)

add_test(
  NAME Siv3DTest
  COMMAND Siv3DTest)
