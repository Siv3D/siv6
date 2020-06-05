
# include <Siv3D.hpp> // OpenSiv3D v0.6

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);	// デバッグヒープマネージャ (Windows のみ)
SIV3D_OPTION_HEADLESS_MODE(false);		// 非グラフィックスモード
SIV3D_OPTION_OUTPUT_STDERR(true);		// std::cerr の出力
SIV3D_OPTION_RUN_TEST(false);			// テストの実行

template <class T0, class... Ts>
auto MakeArray(T0&& first, Ts&&... args)
{
	using Type = std::decay_t<T0>;
	return Array<Type>{ std::forward<T0>(first), std::forward<Ts>(args)... };
}

void Main()
{
	Array v = MakeArray(10, 20, 30, 5);
	v = MakeArray(20);
	v = MakeArray();

	Console << Format(v);

	while (System::Update())
	{

	}
}
