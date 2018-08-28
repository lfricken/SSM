#include "Pauser.hpp"


Pauser::Pauser(float realTime)
{
	m_realTime = realTime;

	m_mustCalcTime = false;
	m_paused = false;
	m_currentEffectiveTime = m_realTime;
	m_skippedTime = 0.f;
	m_pauseTime = 0.f;
}
Pauser::~Pauser()
{

}
float Pauser::getTime() const
{
	if(m_mustCalcTime)
	{
		m_mustCalcTime = false;
		if(m_paused)
			m_currentEffectiveTime = m_pauseTime - m_skippedTime;
		else
			m_currentEffectiveTime = m_realTime - m_skippedTime;
	}

	return m_currentEffectiveTime;
}
void Pauser::setRealTime(float time)
{
	m_mustCalcTime = true;
	m_realTime = time;
}
bool Pauser::isPaused() const
{
	return m_paused;
}
void Pauser::togglePause(bool pause)
{
	if(m_paused && !pause) // switching to not paused
		m_skippedTime += m_realTime - m_pauseTime;
	else if(!m_paused && pause) // switching to paused
		m_pauseTime = m_realTime;

	m_paused = pause;
}
bool Pauser::togglePause()
{
	togglePause(!m_paused);
	return m_paused;
}











