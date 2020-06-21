cmake_minimum_required(VERSION 3.5)

project(Siv6 CXX)
enable_language(C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-msse4.1 -D_GLFW_X11")
set(CMAKE_C_FLAGS "-msse4.1 -D_GLFW_X11")

find_package(PkgConfig)

pkg_check_modules(LIBSIV3D REQUIRED glib-2.0 gl x11)

add_library(
  Siv3D STATIC

  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Siv3DMain.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Common/OpenGL.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Cursor/CCursor.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/FileSystem/SivFileSystem_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Renderer/GL4/CRenderer_GL4.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Renderer/RendererFactory.cpp
  
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Renderer2D/Renderer2DFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/System/CSystem.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Time/SivTime.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Window/CWindow.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Window/CWindow_Null.cpp
  ../Siv3D/src/Siv3D-Platform/Linux/Siv3D/Window/WindowFactory.cpp

  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryReader/BinaryReaderDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Console/CConsole.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Date/SivDate_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/DateTime/SivDateTime_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Logger/CLogger.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Unicode/SivUnicode_Platform.cpp

  ../Siv3D/src/Siv3D-Platform/OpenGL4/Siv3D/Renderer2D/GL4/CRenderer2D_GL4.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGL4/Siv3D/Renderer2D/GL4/Vertex2DBatch_GL4.cpp

  ../Siv3D/src/Siv3D/ApplicationOptions/SivApplicationOptions.cpp
  ../Siv3D/src/Siv3D/Byte/SivByte.cpp
  ../Siv3D/src/Siv3D/BinaryReader/SivBinaryReader.cpp
  ../Siv3D/src/Siv3D/Color/SivColor.cpp
  ../Siv3D/src/Siv3D/Common/Siv3DEngine.cpp
  ../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp
  ../Siv3D/src/Siv3D/Console/SivConsole.cpp
  ../Siv3D/src/Siv3D/Cursor/CCursor_Null.cpp
  ../Siv3D/src/Siv3D/Cursor/CursorFactory.cpp
  ../Siv3D/src/Siv3D/Cursor/SivCursor.cpp
  ../Siv3D/src/Siv3D/CPUInfo/SivCPUInfo.cpp
  ../Siv3D/src/Siv3D/DateTime/SivDateTime.cpp
  ../Siv3D/src/Siv3D/Dummy/CDummy.cpp
  ../Siv3D/src/Siv3D/Dummy/DummyFactory.cpp
  ../Siv3D/src/Siv3D/Duration/SivDuration.cpp
  ../Siv3D/src/Siv3D/EngineLog/SivEngineLog.cpp
  ../Siv3D/src/Siv3D/Error/SivError.cpp
  ../Siv3D/src/Siv3D/FormatFloat/SivFormatFloat.cpp
  ../Siv3D/src/Siv3D/FormatInt/SivFormatInt.cpp
  ../Siv3D/src/Siv3D/Formatter/SivFormatter.cpp
  ../Siv3D/src/Siv3D/FormatUtility/SivFormatUtility.cpp
  ../Siv3D/src/Siv3D/Int128/SivInt128.cpp
  ../Siv3D/src/Siv3D/IntFormatter/SivIntFormatter.cpp
  ../Siv3D/src/Siv3D/Logger/LoggerFactory.cpp
  ../Siv3D/src/Siv3D/Logger/SivLogger.cpp
  ../Siv3D/src/Siv3D/Point/SivPoint.cpp
  ../Siv3D/src/Siv3D/Profiler/CProfiler.cpp
  ../Siv3D/src/Siv3D/Profiler/ProfilerFactory.cpp
  ../Siv3D/src/Siv3D/Profiler/SivProfiler.cpp
  ../Siv3D/src/Siv3D/Rectangle/SivRectangle.cpp
  ../Siv3D/src/Siv3D/RegExp/RegExpDetail.cpp
  ../Siv3D/src/Siv3D/RegExp/SivRegExp.cpp
  ../Siv3D/src/Siv3D/Renderer/Null/CRenderer_Null.cpp
  ../Siv3D/src/Siv3D/Renderer2D/Null/CRenderer2D_Null.cpp
  ../Siv3D/src/Siv3D/Scene/CScene.cpp
  ../Siv3D/src/Siv3D/Scene/SceneFactory.cpp
  ../Siv3D/src/Siv3D/Scene/SivScene.cpp
  ../Siv3D/src/Siv3D/String/SivString.cpp
  ../Siv3D/src/Siv3D/StringView/SivStringView.cpp
  ../Siv3D/src/Siv3D/System/SivSystem.cpp
  ../Siv3D/src/Siv3D/System/SystemFactory.cpp
  ../Siv3D/src/Siv3D/System/SystemLog.cpp
  ../Siv3D/src/Siv3D/System/SystemMisc.cpp
  ../Siv3D/src/Siv3D/Threading/SivThreading.cpp
  ../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp
  ../Siv3D/src/Siv3D/Unicode/UnicodeUtility.cpp
  ../Siv3D/src/Siv3D/UserAction/CUserAction.cpp
  ../Siv3D/src/Siv3D/UserAction/UserActionFactory.cpp
  ../Siv3D/src/Siv3D/Vector2D/SivVector2D.cpp
  ../Siv3D/src/Siv3D/Vector3D/SivVector3D.cpp
  ../Siv3D/src/Siv3D/Vector4D/SivVector4D.cpp
  ../Siv3D/src/Siv3D/Window/SivWindow.cpp

  ../Siv3D/src/ThirdParty/absl/numeric/int128.cc

  ../Siv3D/src/ThirdParty/cpu_features/cpuinfo_x86.c

  ../Siv3D/src/ThirdParty/double-conversion/bignum-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/bignum.cc
  ../Siv3D/src/ThirdParty/double-conversion/cached-powers.cc
  ../Siv3D/src/ThirdParty/double-conversion/double-to-string.cc
  ../Siv3D/src/ThirdParty/double-conversion/fast-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/fixed-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/string-to-double.cc
  ../Siv3D/src/ThirdParty/double-conversion/strtod.cc

  ../Siv3D/src/ThirdParty/fmt/format.cc
  
  ../Siv3D/src/ThirdParty/GLEW/glew.c
  ../Siv3D/src/ThirdParty/GLFW/context.c
  ../Siv3D/src/ThirdParty/GLFW/egl_context.c
  ../Siv3D/src/ThirdParty/GLFW/glx_context.c
  ../Siv3D/src/ThirdParty/GLFW/init.c
  ../Siv3D/src/ThirdParty/GLFW/input.c
  ../Siv3D/src/ThirdParty/GLFW/linux_joystick.c
  ../Siv3D/src/ThirdParty/GLFW/monitor.c
  ../Siv3D/src/ThirdParty/GLFW/osmesa_context.c
  ../Siv3D/src/ThirdParty/GLFW/posix_thread.c
  ../Siv3D/src/ThirdParty/GLFW/posix_time.c
  ../Siv3D/src/ThirdParty/GLFW/vulkan.c
  ../Siv3D/src/ThirdParty/GLFW/window.c
  ../Siv3D/src/ThirdParty/GLFW/x11_init.c
  ../Siv3D/src/ThirdParty/GLFW/x11_monitor.c
  ../Siv3D/src/ThirdParty/GLFW/x11_window.c
  ../Siv3D/src/ThirdParty/GLFW/xkb_unicode.c

  ../Siv3D/src/ThirdParty/infoware/src/cpu/architecture/architecture_non_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/architecture/architecture_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/endianness/all.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/frequency/frequency_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/frequency/frequency_non_windows_non_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/frequency/frequency_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/instruction_set/instruction_set.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/instruction_set/instruction_set_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/instruction_set/instruction_set_non_windows_non_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/instruction_set/instruction_set_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/quantities_cache/quantities_cache_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/quantities_cache/quantities_cache_non_windows_non_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/quantities_cache/quantities_cache_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/vendor_model_name/vendor_id.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/vendor_model_name/vendor_model_name_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/vendor_model_name/vendor_model_name_non_windows_non_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/cpu/vendor_model_name/vendor_model_name_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/detail/cpuid_non_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/detail/cpuid_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/detail/scope.cpp
  ../Siv3D/src/ThirdParty/infoware/src/detail/sysctl_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/detail/sysctl_non_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/detail/winstring_non_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/detail/winstring_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/amounts/amounts_non_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/amounts/amounts_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/displays/displays_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/displays/displays_default_blank.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/displays/displays_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/displays/displays_x11.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/kernel_info/kernel_info_non_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/kernel_info/kernel_info_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/memory/memory_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/memory/memory_non_windows_non_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/memory/memory_windows.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/OS_info/os_info_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/OS_info/os_info_non_windows_non_darwin.cpp
  ../Siv3D/src/ThirdParty/infoware/src/system/OS_info/os_info_windows.cpp

  ../Siv3D/src/ThirdParty/Oniguruma/ascii.c
  ../Siv3D/src/ThirdParty/Oniguruma/big5.c
  ../Siv3D/src/ThirdParty/Oniguruma/cp1251.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_jp.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_jp_prop.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_kr.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_tw.c
  ../Siv3D/src/ThirdParty/Oniguruma/gb18030.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_1.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_10.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_11.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_13.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_14.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_15.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_16.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_2.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_3.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_4.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_5.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_6.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_7.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_8.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_9.c
  ../Siv3D/src/ThirdParty/Oniguruma/koi8.c
  ../Siv3D/src/ThirdParty/Oniguruma/koi8_r.c
  ../Siv3D/src/ThirdParty/Oniguruma/onig_init.c
  ../Siv3D/src/ThirdParty/Oniguruma/regcomp.c
  ../Siv3D/src/ThirdParty/Oniguruma/regenc.c
  ../Siv3D/src/ThirdParty/Oniguruma/regerror.c
  ../Siv3D/src/ThirdParty/Oniguruma/regexec.c
  ../Siv3D/src/ThirdParty/Oniguruma/reggnu.c
  ../Siv3D/src/ThirdParty/Oniguruma/regparse.c
  ../Siv3D/src/ThirdParty/Oniguruma/regsyntax.c
  ../Siv3D/src/ThirdParty/Oniguruma/regtrav.c
  ../Siv3D/src/ThirdParty/Oniguruma/regversion.c
  ../Siv3D/src/ThirdParty/Oniguruma/sjis.c
  ../Siv3D/src/ThirdParty/Oniguruma/sjis_prop.c
  ../Siv3D/src/ThirdParty/Oniguruma/st.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold1_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold2_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold3_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_unfold_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf16_be.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf16_le.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf32_be.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf32_le.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf8.c
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
  ../Linux/Main.cpp
  ../Test/Siv3DTest.cpp
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

add_test(
  NAME Siv3DTest
  COMMAND Siv3DTest)
