#pragma once

#include "Vec2.hpp"
#include "OOCore.hpp"
#include <vector>

#ifdef GRAPHLIB_EXPORTS
#define GRAPHLIB_API __declspec(dllexport)
#else
#define GRAPHLIB_API __declspec(dllimport)
#endif


namespace Graph
{

	class GridGraph;

	class GRAPHLIB_API Vertex
	{
	public:
		Vertex();
		virtual ~Vertex();

		Math::Vec2 thisPosition;

		std::vector<Math::Vec2> getAdjacents() const;

		/// <summary>
		/// Indexes the edges list so you know which way you are going.
		/// </summary>
		enum
		{
			Right = 0,
			UpRight,
			Up,
			UpLeft,

			Left,
			DownLeft,
			Down,
			DownRight,
			
			NumDirections,
		};

		/// <summary>
		/// List of edges starting right and going counter clockwise. Has edge if true.
		/// </summary>
		bool edges[NumDirections];

		/// <summary>
		/// Return readable information about the vertex that changes over time.
		/// </summary>
		virtual const void* getActiveStateData();

		/// <summary>
		/// Return writable information about the vertex that changes over time.
		/// </summary>
		virtual void* getInactiveStateData();

		/// <summary>
		/// Set information about the vertex that changes over time.
		/// </summary>
		virtual void setActiveStateData(void* stateData);

		/// <summary>
		/// Set information about the vertex that changes over time.
		/// </summary>
		virtual void setInactiveStateData(void* stateData);

		/// <summary>
		/// Permanent information that lives on this vertex.
		/// </summary>
		virtual void* getUserData();

		/// <summary>
		/// Permanent information that lives on this vertex.
		/// </summary>
		virtual void setUserData(void* userData);

		/// <summary>
		/// Switches the inactive and active data;
		/// </summary>
		virtual void flipActive();
	protected:

		/// <summary>
		/// Stores information about the vertex.
		/// </summary>
		sp<void> vertexStateData;

		/// <summary>
		/// Stores information about the vertex.
		/// </summary>
		sp<void> vertexStateDataTemp;

		/// <summary>
		/// Stores permanent user data.
		/// </summary>
		sp<void> userData;
	};
}
