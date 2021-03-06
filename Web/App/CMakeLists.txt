cmake_minimum_required(VERSION 3.12)
project(OpenSiv3D_Linux_App CXX C)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -s USE_LIBPNG=1")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ALLOW_MEMORY_GROWTH=1 -s FULL_ES3 -s USE_GLFW=3")

if (SIV3D_RUN_TEST_ON_NODE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ERROR_ON_UNDEFINED_SYMBOLS=0 -lnodefs.js --pre-js \"${CMAKE_SOURCE_DIR}/../../Test/Siv3DTest.js\"")
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --preload-file \"${CMAKE_SOURCE_DIR}/resources@/resources\"")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

if (NOT CMAKE_CONFIGURATION_TYPES AND 
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options ("-fcolor-diagnostics")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options ("-fdiagnostics-color=always")
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

if (SIV3D_RUN_TEST_ON_NODE)
add_executable(Siv3DTest
  TestMain.cpp
  ../../Test/Siv3DTest.cpp
  ../../Test/Siv3DTest_Array.cpp
  ../../Test/Siv3DTest_BinaryReader.cpp
  ../../Test/Siv3DTest_BinaryWriter.cpp
#  ../../Test/Siv3DTest_FileSystem.cpp
  ../../Test/Siv3DTest_Image.cpp
  ../../Test/Siv3DTest_Resource.cpp
  ../../Test/Siv3DTest_TextEncoding.cpp
  ../../Test/Siv3DTest_TextReader.cpp
  ../../Test/Siv3DTest_TextWriter.cpp
  )
else()
add_executable(Siv3DTest
  Main.cpp
  )
endif()


target_include_directories(Siv3DTest PRIVATE
  "../../Siv3D/include"
  "../../Siv3D/include/ThirdParty"
  )
target_link_libraries(Siv3DTest PRIVATE
  ${PROJECT_SOURCE_DIR}/../build/libSiv3D.a
  )


if(BUILD_TESTING)
enable_testing()
add_test(
  NAME Test
  COMMAND node Siv3DTest.js
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  )
endif()
