#pragma once
class BenchTimer
{
private:
	int m_AvgSampleCount;
	__int64 m_AvgControlTime;
	__int64 m_Start = 0;
	__int64 m_End = 0;
	clock_t m_CStart;
	clock_t m_CEnd;

public:
	BenchTimer();
	~BenchTimer();

	void Restart();
	void StopAndPrint();

	inline __int64 GetCpuClocks()
	{

		// Counter
		struct { __int32 low, high; } counter;

		// Use RDTSC instruction to get clocks count
		__asm push EAX
		__asm push EDX
		__asm __emit 0fh __asm __emit 031h // RDTSC
		__asm mov counter.low, EAX
		__asm mov counter.high, EDX
		__asm pop EDX
		__asm pop EAX

		// Return result
		return *(__int64 *)(&counter);

	}
};
