
# include <Siv3D.hpp>
# include <Siv3D/Windows/Windows.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(true);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);


void Main()
{
	::Sleep(4000);

	//Console(U"かきくけこ");
	//Console(String(U"あいうえお"));
	//Console(StringView(U"さしすせそ"));

	//Logger << Time::GetNanosec();
	//Logger << Time::GetNanosec();
	//Logger << Time::GetNanosec();
	//Logger << Time::GetNanosec();

	//auto s = Format(U"aaa", 20, U"aaa", std::wstring{});

	//Apply(10, 20);

	//int n;
	//std::cin >> n;
}
