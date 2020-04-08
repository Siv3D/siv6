project(Siv6 CXX)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
  Siv3D STATIC
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Console/CConsole.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Logger/CLogger.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Unicode/SivUnicode_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3DMain.cpp
  ../Siv3D/src/Siv3D/Common/ApplicationOptions.cpp
  ../Siv3D/src/Siv3D/Common/Siv3DEngine.cpp
  ../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp
  ../Siv3D/src/Siv3D/Console/SivConsole.cpp
  ../Siv3D/src/Siv3D/Dummy/CDummy.cpp
  ../Siv3D/src/Siv3D/Dummy/DummyFactory.cpp
  ../Siv3D/src/Siv3D/String/SivString.cpp
  ../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp
  ../Siv3D/src/Siv3D/Unicode/UnicodeUtility.cpp
  )

target_include_directories(
  Siv3D
  PUBLIC
  ../Siv3D/include
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
