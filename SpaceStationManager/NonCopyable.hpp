#pragma once

namespace Core
{
	/// <summary>
	/// Prevents a class from being copied, by producing a compile time error.
	/// </summary>
	class INonCopyable
	{
	protected:
		////////////////////////////////////////////////////////////
		/// \brief Default constructor
		///
		/// Because this class has a copy constructor, the compiler
		/// will not automatically generate the default constructor.
		/// That's why we must define it explicitly.
		///
		////////////////////////////////////////////////////////////
		INonCopyable() {}
	private:
		////////////////////////////////////////////////////////////
		/// \brief Disabled copy constructor
		///
		/// By making the copy constructor private, the compiler will
		/// trigger an error if anyone outside tries to use it.
		/// To prevent NonCopyable or friend classes from using it,
		/// we also give no definition, so that the linker will
		/// produce an error if the first protection was inefficient.
		///
		////////////////////////////////////////////////////////////
		INonCopyable(const INonCopyable&);
		////////////////////////////////////////////////////////////
		/// \brief Disabled assignment operator
		///
		/// By making the assignment operator private, the compiler will
		/// trigger an error if anyone outside tries to use it.
		/// To prevent NonCopyable or friend classes from using it,
		/// we also give no definition, so that the linker will
		/// produce an error if the first protection was inefficient.
		///
		////////////////////////////////////////////////////////////
		INonCopyable& operator =(const INonCopyable&);
	};
}
