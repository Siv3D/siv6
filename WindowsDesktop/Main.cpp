
# include <Siv3D.hpp> // OpenSiv3D v0.6

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	Reseed(12345);
	Logger << UniformIntDistribution<int32>(1, 6)(GetDefaultRNG());
	Logger << UniformIntDistribution<int32>(1, 6)(GetDefaultRNG());
	Logger << UniformIntDistribution<int32>(1, 6)(GetDefaultRNG());
	Logger << UniformIntDistribution<int32>(1, 6)(GetDefaultRNG());
	Logger << UniformIntDistribution<int32>(1, 6)(GetDefaultRNG());

	while (System::Update())
	{

	}
}
