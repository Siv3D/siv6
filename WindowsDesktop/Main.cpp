
# include <Siv3D.hpp> // OpenSiv3D v0.6

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	uint128 n = 123;
	n *= 111111;
	n *= 111111;
	n *= 111111;
	n *= 111111;
	n *= 111111;
	Console << n;

	while (System::Update())
	{

	}
}
