
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(true);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	const auto cpu = GetCPUInfo();
	Logger << cpu.vendor;
	Logger << cpu.brand;
	Logger << U"{}.{}.{}"_fmt(cpu.family, cpu.model, cpu.stepping);

	try
	{
		const Point pos = Parse<Point>(U"123");
	}
	catch (const Error& e)
	{
		Logger << e;
	}
	
	while (System::Update())
	{
		Logger << Scene::FrameCount();
		
		System::Sleep(16ms);
		
		if (Scene::FrameCount() > 100)
		{
			System::Exit();
		}
	}
}
