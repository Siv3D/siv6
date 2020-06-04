
# include <Siv3D.hpp> // OpenSiv3D v0.6

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);	// デバッグヒープマネージャ (Windows のみ)
SIV3D_OPTION_HEADLESS_MODE(false);		// 非グラフィックスモード
SIV3D_OPTION_OUTPUT_STDERR(true);		// std::cerr の出力
SIV3D_OPTION_RUN_TEST(false);			// テストの実行

void Main()
{
	const auto matches = U"(\\d+)-(\\d+)-(\\d+)"_re.match(U"2020-06-04");
	Console << U"{}年{}月{}日"_fmt(matches[1], matches[2], matches[3]);

	const String text = U"<html><body text=\"#000000\"><p>Hello!</p></body></html>";
	for (const auto& match : UR"(<(".*?"|'.*?'|[^'"])*?>)"_re.findAll(text))
	{
		Console << match[0];
	}

	while (System::Update())
	{

	}
}
