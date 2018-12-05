#include "pch.h"

BenchTimer::BenchTimer() : m_AvgSampleCount(0), m_AvgControlTime(0), m_Start(0), m_End(0)
{
	m_CStart = clock();
}

void BenchTimer::Restart()
{
	m_CStart = GetCpuClocks();
}

BenchTimer::~BenchTimer()
{
}

void BenchTimer::StopAndPrint()
{
	m_CEnd = clock();
	//m_End = GetCpuClocks();
	//std::cout << "[BenchTime]: " << (m_End - m_Start) / CLOCKS_PER_SEC << " (Ticks pr second (tps)), " << m_End - m_Start << " (Total ticks)" << " - Average Control Time: " << m_AvgControlTime << std::endl;
	std::cout << "[BenchTime]: " << 1000.0 * (m_CEnd - m_CStart) / CLOCKS_PER_SEC << " ms" << std::endl;
}