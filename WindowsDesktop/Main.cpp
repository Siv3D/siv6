
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	const auto cpu = GetCPUInfo();

	Logger << cpu.vendor;
	Logger << cpu.brand;
	Logger << U"{}.{}.{}"_fmt(cpu.family, cpu.model, cpu.stepping);

	while (System::Update())
	{

	}
}
