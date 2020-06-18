
# include <Siv3D.hpp> // OpenSiv3D v0.6

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);	// デバッグヒープマネージャ (Windows のみ)
SIV3D_OPTION_HEADLESS_MODE(false);		// 非グラフィックスモード
SIV3D_OPTION_OUTPUT_STDERR(true);		// std::cerr の出力
SIV3D_OPTION_RUN_TEST(true);			// テストの実行

Color Gen(double x, double y)
{
	double d = Vec2(0.5, 0.5).distanceFrom(x, y);
	double a = InRange(d, 0.38, 0.48) + InRange(d, 0.36, 0.5);
	return ColorF(x, y, 1, a * 0.5);
}

void Main()
{
	Cursor::Register(U"MyCursor", Image(48, 48, Arg::generator0_1 = Gen), Point(24, 24));

	while (System::Update())
	{

		Cursor::RequestStyle(U"MyCursor");
	}
}


