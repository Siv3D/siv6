//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"

# if SIV3D_PLATFORM(WINDOWS)

# include <Siv3D/Windows/Windows.hpp>

namespace s3d
{
	namespace DLL
	{
		[[nodiscard]]
		HMODULE LoadSystemLibrary(const wchar_t* library);

		class GetFunctionNoThrow
		{
		private:

			void* p;

		public:

			SIV3D_NODISCARD_CXX20
			GetFunctionNoThrow(HMODULE module, const char* name);

			template <class Type>
			operator Type() const
			{
				return reinterpret_cast<Type>(p);
			}
		};

		class GetFunction
		{
		private:

			void* p;

		public:

			SIV3D_NODISCARD_CXX20
			GetFunction(HMODULE module, const char* name);

			template <class Type>
			operator Type() const
			{
				return reinterpret_cast<Type>(p);
			}
		};
	}
}

# endif

# if SIV3D_PLATFORM(MACOS) || SIV3D_PLATFORM(LINUX)

# include <dlfcn.h>

namespace s3d
{
	namespace DLL
	{
		[[nodiscard]]
		void* LoadLibrary(const char* path);

		class GetFunctionNoThrow
		{
		private:

			void* p;

		public:

			SIV3D_NODISCARD_CXX20
			GetFunctionNoThrow(void* module, const char* name);

			template <class Type>
			operator Type() const
			{
				return reinterpret_cast<Type>(p);
			}
		};

		class GetFunction
		{
		private:

			void* p;

		public:

			SIV3D_NODISCARD_CXX20
			GetFunction(void* module, const char* name);

			template <class Type>
			operator Type() const
			{
				return reinterpret_cast<Type>(p);
			}
		};
	}
}

# endif