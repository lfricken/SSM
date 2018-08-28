#pragma once

namespace Core
{
	/// <summary>
	/// Can tell time. Used for Timers.
	/// </summary>
	class IClock
	{
	public:
		IClock();
		~IClock();

		/// <summary>
		/// Return current time.
		/// </summary>
		virtual float getTime() const = 0;
	};
}
