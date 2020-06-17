
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

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
		const auto state = Window::GetState();
		const double uiScaling = double(state.frameBufferSize.x) / state.virtualSize.x;
		
		Window::SetTitle(U"S:{} R:{} PF:{:.1f} P:{} WS:{} UIS:{}"_fmt(
			Cursor::ScreenPos(), Cursor::PosRaw(), Cursor::PosF(), Cursor::Pos(),
			Window::GetState().scaling, uiScaling));
	}
}
