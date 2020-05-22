
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	constexpr auto a = Date(2020, 1, 1);
	constexpr auto b = Date(2020, 12, 31);
	constexpr auto c = b - a;
	Logger << c;

	while (System::Update())
	{

	}
}
