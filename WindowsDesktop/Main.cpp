
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

class MicrosecClock
{
private:

	const uint64 m_start = Time::GetMicrosec();

public:

	/// <summary>
	/// 経過時間（マイクロ秒）
	/// </summary>
	[[nodiscard]] uint64 us() const
	{
		return Time::GetMicrosec() - m_start;
	}

	/// <summary>
	/// ログに経過時間を出力します。
	/// </summary>
	/// <returns>
	/// なし
	/// </returns>
	void log() const { Logger(us(), U"us"_sv); }
};

void Main()
{
	for (size_t k = 0; k < 5; ++k)
	{
		{
			MicrosecClock ms;
			double a = 0;

			for (size_t i = 0; i < 100000; ++i)
			{
				a += Random();
			}

			ms.log();
			Logger << a;
		}
	}

	while (System::Update())
	{

	}
}
