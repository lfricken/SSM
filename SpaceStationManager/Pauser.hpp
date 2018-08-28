#pragma once

/// <summary>
/// Handles pausing.
/// </summary>
class Pauser
{
public:
	Pauser(float realTime);
	~Pauser();

	/// <summary>
	/// Sets the real time.
	/// </summary>
	void setRealTime(float time);

	/// <summary>
	/// Returns time including pauses.
	/// </summary>
	float getTime() const;

	/// <summary>
	/// Set whether this is paused.
	/// </summary>
	void togglePause(bool pause);

	/// <summary>
	/// Toggle whether this is paused. Returns new value.
	/// </summary>
	bool togglePause();

	/// <summary>
	/// True if the game is paused.
	/// </summary>
	bool isPaused() const;

private:
	/// <summary>
	/// Time since application start.
	/// </summary>
	float m_realTime;

	/// <summary>
	/// When the last pause started.
	/// </summary>
	float m_pauseTime;

	/// <summary>
	/// How much total time has been skipped since being paused?
	/// </summary>
	float m_skippedTime;

	/// <summary>
	/// True if we are paused now.
	/// </summary>
	bool m_paused;

	/// <summary>
	/// True if we need to recalculate m_currentEffectiveTime.
	/// </summary>
	mutable bool m_mustCalcTime;

	/// <summary>
	/// What effective time is it?
	/// </summary>
	mutable float m_currentEffectiveTime;
};

