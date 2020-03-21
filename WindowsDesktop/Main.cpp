
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(true);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(true);

void Main()
{
	Console(U"かきくけこ");
	Console(String(U"あいうえお"));
	Console(StringView(U"さしすせそ"));

	Logger << Time::GetNanosec();
	Logger << Time::GetNanosec();
	Logger << Time::GetNanosec();
	Logger << Time::GetNanosec();

	int n;
	std::cin >> n;
}
