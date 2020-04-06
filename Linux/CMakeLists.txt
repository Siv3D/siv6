project(Siv6 CXX)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
  Siv3D
  ../Siv3D/src/Siv3D-Platform/Linux/Console/CConsole.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Logger/CLogger.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Renderer/GL4/CRenderer_GL4.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Renderer/RendererFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3DMain.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/System/CSystem.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/System/SivSystem_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Time/SivTime.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Unicode/SivUnicode_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Window/CWindow.cpp
  ../Siv3D/src/Siv3D/Common/ApplicationOptions.cpp
  ../Siv3D/src/Siv3D/Common/Siv3DEngine.cpp
  ../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp
  ../Siv3D/src/Siv3D/Console/SivConsole.cpp
  ../Siv3D/src/Siv3D/Dummy/CDummy.cpp
  ../Siv3D/src/Siv3D/Dummy/DummyFactory.cpp
  ../Siv3D/src/Siv3D/EngineLog/SivEngineLog.cpp
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
  ../Siv3D/src/Siv3D/UserAction/CUserAction.cpp
  ../Siv3D/src/Siv3D/UserAction/UserActionFactory.cpp
  ../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp
  ../Siv3D/src/Siv3D/Unicode/UnicodeUtility.cpp

  ../Siv3D/src/ThirdParty/fmt/format.cc
  )

target_include_directories(
  Siv3D
  PUBLIC
  ../Siv3D/include
  ../Siv3D/include/ThirdParty
  ../Siv3D/src
  ../Siv3D/src/Siv3D-Platform/Linux
  ../Siv3D/src/ThirdParty
  )

enable_testing()

add_executable(
  Siv3DTest
  ../Siv3D/src/Test/Siv3DTest.cpp
  ../Linux/Main.cpp
  )
target_link_libraries(Siv3DTest PRIVATE Siv3D)
target_include_directories(
  Siv3DTest
  PRIVATE ../Siv3D/src/ThirdParty)
add_test(
  NAME Siv3DTest
  COMMAND Siv3DTest)
