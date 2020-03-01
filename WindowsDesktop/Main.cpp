
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(true);
SIV3D_OPTION_OUTPUT_STDERR(true);

void Main()
{
	Console.open();

	std::cout << "Siv3D for Windows\n";
	std::cerr << "Err\n";

	int n;
	std::cin >> n;
}
