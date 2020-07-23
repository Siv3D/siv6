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
# include <execution>
using namespace s3d;
using namespace std::literals;

TEST_CASE("Array::parallel_count_if()")
{
	{
		Array<double> v(8);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; })
			== v.parallel_count_if([](double x) { return x < 0.5; }));

		BENCHMARK("std::count_if() | 8")
		{
			return std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; });
		};

		BENCHMARK("Array::parallel_count_if() | 8")
		{
			return v.parallel_count_if([](double x) { return x < 0.5; });
		};
	}

	{
		Array<double> v(1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; })
			== v.parallel_count_if([](double x) { return x < 0.5; }));

		BENCHMARK("std::count_if() | 1K")
		{
			return std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; });
		};

		BENCHMARK("Array::parallel_count_if() | 1K")
		{
			return v.parallel_count_if([](double x) { return x < 0.5; });
		};
	}

	{
		Array<double> v(64 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; })
			== v.parallel_count_if([](double x) { return x < 0.5; }));

		BENCHMARK("std::count_if() | 64K")
		{
			return std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; });
		};

		BENCHMARK("Array::parallel_count_if() | 64K")
		{
			return v.parallel_count_if([](double x) { return x < 0.5; });
		};
	}

	{
		Array<double> v(1024 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = Random();
		}

		REQUIRE(std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; })
			== v.parallel_count_if([](double x) { return x < 0.5; }));

		BENCHMARK("std::count_if() | 1M")
		{
			return std::count_if(v.begin(), v.end(), [](double x) { return x < 0.5; });
		};

		BENCHMARK("Array::parallel_count_if() | 1M")
		{
			return v.parallel_count_if([](double x) { return x < 0.5; });
		};
	}
}


TEST_CASE("Array::parallel_map()")
{
	{
		Array<int32> v(64 * 1024);
		for (size_t i = 0; i < v.size(); ++i)
		{
			v[i] = RandomInt32();
		}

		REQUIRE(v.map([](int32 n) { return n / 10.0 + std::sin(n / 10.0) + std::sqrt(n / 10.0); })
			== v.parallel_map([](int32 n) { return n / 10.0 + std::sin(n / 10.0) + std::sqrt(n / 10.0); }));

		BENCHMARK("Array::map() | 64K")
		{
			return v.map([](int32 n) { return n / 10.0 + std::sin(n / 10.0) + std::sqrt(n / 10.0); });
		};

		BENCHMARK("Array::parallel_map() | 64K")
		{
			return v.parallel_map([](int32 n) { return n / 10.0 + std::sin(n / 10.0) + std::sqrt(n / 10.0); });
		};
	}
}
