
# include <Siv3D.hpp> // OpenSiv3D v0.6

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);	// デバッグヒープマネージャ (Windows のみ)
SIV3D_OPTION_HEADLESS_MODE(true);		// 非グラフィックスモード
SIV3D_OPTION_OUTPUT_STDERR(true);		// std::cerr の出力
SIV3D_OPTION_RUN_TEST(false);			// テストの実行

void Main()
{
	int32 a, b;

	Console >> a >> b;

	Console << (a + b);

	while (System::Update())
	{
		Logger << Scene::FrameCount();

		System::Sleep(16ms);

		if (Scene::FrameCount() > 50)
		{
			System::Exit();
		}
	}
}
