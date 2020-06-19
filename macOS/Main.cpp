
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	//Cursor::Register(U"MyCursor", Image(48, 48, Arg::generator0_1 = Gen), Point(24, 24));

	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(20 + i * 20, 20, 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
