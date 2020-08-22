cmake_minimum_required(VERSION 3.5)

project(Siv6 CXX)
enable_language(C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-D_GLFW_X11")
set(CMAKE_C_FLAGS "-D_GLFW_X11")

add_library(
  Siv3D STATIC
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Siv3DMain.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Common/OpenGL.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/FileSystem/SivFileSystem_Platform.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/GLES3/CRenderer_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/RendererFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/System/CSystem.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Time/SivTime.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Window/CWindow.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Window/WindowFactory.cpp

  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryReader/BinaryReaderDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryWriter/BinaryWriterDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Console/CConsole.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Date/SivDate_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/DateTime/SivDateTime_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/EnvironmentVariable/SivEnvironmentVariable.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Logger/CLogger.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/System/SivSystem_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Unicode/SivUnicode_macOS_Linux.cpp

  ../Siv3D/src/Siv3D/ApplicationOptions/SivApplicationOptions.cpp
  # ../Siv3D/src/Siv3D/BigFloat/SivBigFloat.cpp
  # ../Siv3D/src/Siv3D/BigInt/SivBigInt.cpp
  ../Siv3D/src/Siv3D/Blob/SivBlob.cpp
  ../Siv3D/src/Siv3D/Byte/SivByte.cpp
  ../Siv3D/src/Siv3D/BinaryReader/SivBinaryReader.cpp
  ../Siv3D/src/Siv3D/BinaryWriter/SivBinaryWriter.cpp
  ../Siv3D/src/Siv3D/Color/SivColor.cpp
  ../Siv3D/src/Siv3D/Common/Siv3DEngine.cpp
  ../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp
  ../Siv3D/src/Siv3D/Console/SivConsole.cpp
  ../Siv3D/src/Siv3D/Cursor/CCursor_Null.cpp
  ../Siv3D/src/Siv3D/Cursor/CursorFactory.cpp
  ../Siv3D/src/Siv3D/Cursor/SivCursor.cpp
  # ../Siv3D/src/Siv3D/CPUInfo/SivCPUInfo.cpp
  ../Siv3D/src/Siv3D/DateTime/SivDateTime.cpp
  ../Siv3D/src/Siv3D/Dummy/CDummy.cpp
  ../Siv3D/src/Siv3D/Dummy/DummyFactory.cpp
  ../Siv3D/src/Siv3D/Duration/SivDuration.cpp
  ../Siv3D/src/Siv3D/EngineLog/SivEngineLog.cpp
  ../Siv3D/src/Siv3D/Error/SivError.cpp
  ../Siv3D/src/Siv3D/FileSystem/SivFileSystem.cpp
  ../Siv3D/src/Siv3D/FormatFloat/SivFormatFloat.cpp
  ../Siv3D/src/Siv3D/FormatInt/SivFormatInt.cpp
  ../Siv3D/src/Siv3D/Formatter/SivFormatter.cpp
  ../Siv3D/src/Siv3D/FormatUtility/SivFormatUtility.cpp
  ../Siv3D/src/Siv3D/Hash/SivHash.cpp
  ../Siv3D/src/Siv3D/Image/SivImage.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/CImageDecoder.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/ImageDecoderFactory.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/SivImageDecoder.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/CImageEncoder.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/ImageEncoderFactory.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/SivImageEncoder.cpp 
  ../Siv3D/src/Siv3D/ImageFormat/BMPDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/BMPEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PNGDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PNGEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/SVGDecoder.cpp
  ../Siv3D/src/Siv3D/INIData/SivINIData.cpp
  ../Siv3D/src/Siv3D/Int128/SivInt128.cpp
  ../Siv3D/src/Siv3D/IntFormatter/SivIntFormatter.cpp
  ../Siv3D/src/Siv3D/LicenseManager/CLicenseManager.cpp
  ../Siv3D/src/Siv3D/LicenseManager/LicenseManagerFactory.cpp
  ../Siv3D/src/Siv3D/LicenseManager/SivLicenseManager.cpp
  ../Siv3D/src/Siv3D/Logger/LoggerFactory.cpp
  ../Siv3D/src/Siv3D/Logger/SivLogger.cpp
  # ../Siv3D/src/Siv3D/MathParser/MathParserDetail.cpp
  # ../Siv3D/src/Siv3D/MathParser/SivMathParser.cpp
  ../Siv3D/src/Siv3D/Point/SivPoint.cpp
  # ../Siv3D/src/Siv3D/PrimeNumber/SivPrimeNumber.cpp
  ../Siv3D/src/Siv3D/Profiler/CProfiler.cpp
  ../Siv3D/src/Siv3D/Profiler/ProfilerFactory.cpp
  ../Siv3D/src/Siv3D/Profiler/SivProfiler.cpp
  ../Siv3D/src/Siv3D/QR/SivQR.cpp
  ../Siv3D/src/Siv3D/Random/SivRandom.cpp
  ../Siv3D/src/Siv3D/Rectangle/SivRectangle.cpp
  ../Siv3D/src/Siv3D/RegExp/RegExpDetail.cpp
  ../Siv3D/src/Siv3D/RegExp/SivRegExp.cpp
  ../Siv3D/src/Siv3D/Renderer/Null/CRenderer_Null.cpp
  ../Siv3D/src/Siv3D/Renderer2D/Null/CRenderer2D_Null.cpp
  ../Siv3D/src/Siv3D/Resource/ResourceFactory.cpp
  ../Siv3D/src/Siv3D/Resource/SivResource.cpp
  ../Siv3D/src/Siv3D/Scene/CScene.cpp
  ../Siv3D/src/Siv3D/Scene/SceneFactory.cpp
  ../Siv3D/src/Siv3D/Scene/SivScene.cpp
  ../Siv3D/src/Siv3D/String/SivString.cpp
  # ../Siv3D/src/Siv3D/String/Levenshtein.cpp
  ../Siv3D/src/Siv3D/StringView/SivStringView.cpp
  ../Siv3D/src/Siv3D/System/SivSystem.cpp
  ../Siv3D/src/Siv3D/System/SystemFactory.cpp
  ../Siv3D/src/Siv3D/System/SystemLog.cpp
  ../Siv3D/src/Siv3D/System/SystemMisc.cpp
  ../Siv3D/src/Siv3D/TextEncoding/SivTextEncoding.cpp
  ../Siv3D/src/Siv3D/TextReader/SivTextReader.cpp
  ../Siv3D/src/Siv3D/TextReader/TextReaderDetail.cpp
  ../Siv3D/src/Siv3D/TextWriter/SivTextWriter.cpp
  ../Siv3D/src/Siv3D/TextWriter/TextWriterDetail.cpp  
  ../Siv3D/src/Siv3D/Threading/SivThreading.cpp
  ../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp
  ../Siv3D/src/Siv3D/UnicodeConverter/SivUnicodeConverter.cpp
  ../Siv3D/src/Siv3D/Unicode/UnicodeUtility.cpp
  ../Siv3D/src/Siv3D/UserAction/CUserAction.cpp
  ../Siv3D/src/Siv3D/UserAction/UserActionFactory.cpp
  ../Siv3D/src/Siv3D/Vector2D/SivVector2D.cpp
  ../Siv3D/src/Siv3D/Vector3D/SivVector3D.cpp
  ../Siv3D/src/Siv3D/Vector4D/SivVector4D.cpp
  ../Siv3D/src/Siv3D/Window/SivWindow.cpp
  ../Siv3D/src/Siv3D/Window/Null/CWindow_Null.cpp

  ../Siv3D/src/ThirdParty/absl/numeric/int128.cc

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
  )

target_include_directories(
  Siv3D
  PUBLIC
  ../Siv3D/include
  ../Siv3D/include/ThirdParty
  ../Siv3D/src
  ../Siv3D/src/Siv3D-Platform/macOS_Linux
  ../Siv3D/src/Siv3D-Platform/Web
  ../Siv3D/src/ThirdParty
  ${LIBSIV3D_INCLUDE_DIRS}
  )
