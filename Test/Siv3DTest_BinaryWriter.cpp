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

# define CATCH_CONFIG_FAST_COMPILE
# define CATCH_CONFIG_ENABLE_BENCHMARKING
# include <ThirdParty/Catch2/catch.hpp>

# include <Siv3D.hpp>
# include <fstream>
using namespace s3d;
using namespace std::literals;

TEST_CASE("BinaryWriter")
{

}


TEST_CASE("BinaryWriter : benchmark")
{
	Logger.disable();

	BENCHMARK("BinaryWriter | 4 bytes * 16384")
	{
		BinaryWriter writer(U"test/runtime/binarywriter/benckmark/1.bin");

		for (uint32 i = 0; i < 16384; ++i)
		{
			writer.write(i);
		}

		return 0;
	};

	BENCHMARK("std::ofstream | 4 bytes * 16384")
	{
		std::ofstream writer("test/runtime/binarywriter/benckmark/2.bin", std::ios_base::binary);

		for (uint32 i = 0; i < 16384; ++i)
		{
			writer.write((const char*)&i, sizeof(uint32));
		}

		return 0;
	};

	Array<uint32> data(16384);
	std::iota(data.begin(), data.end(), 0);

	BENCHMARK("BinaryWriter | 64 kB * 16")
	{
		BinaryWriter writer(U"test/runtime/binarywriter/benckmark/3.bin");

		for (uint32 i = 0; i < 16; ++i)
		{
			writer.write(data.data(), data.size_bytes());
		}

		return 0;
	};

	BENCHMARK("std::ofstream | 64 kB * 16")
	{
		std::ofstream writer("test/runtime/binarywriter/benckmark/4.bin", std::ios_base::binary);

		for (uint32 i = 0; i < 16; ++i)
		{
			writer.write((const char*)data.data(), data.size_bytes());
		}

		return 0;
	};

	Logger.enable();
}
