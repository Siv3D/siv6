
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	HashTable<String, int> table =
	{
		{U"Zero",0},
		{U"One",1},
		{U"Two",2},
		{U"Three",3},
		{U"Four",4},
		{U"Five",5},
		{U"Six",6},
		{U"Seven",7},
	};

	HashSet<String> set =
	{
		U"one",U"two",U"three",U"four",U"five"
	};

	HashSet<String> b;

	//for (auto [a, b] : table)
	//{
	//	Logger << a << b;
	//}

	//for (auto it = table.begin(); it != table.end(); ++it)
	//{
	//	++it->second;
	//}

	//Logger << U"---";

	//Format(table);

	Logger << table;

	Logger << set;

	//for (auto [a, b] : table)
	//{
	//	Logger << a << b;
	//}

	while (System::Update())
	{

	}
}
