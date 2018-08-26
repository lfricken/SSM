#pragma once

#include <vector>
#include "GraphLibCore.hpp"
#include "Vec2.hpp"
#include "Vertex.hpp"

#ifdef GRAPHLIB_EXPORTS
#define GRAPHLIB_API __declspec(dllexport)
#else
#define GRAPHLIB_API __declspec(dllimport)
#endif


namespace Graph
{
	/// <summary>
	/// Grid of vertexes.
	/// </summary>
	class GRAPHLIB_API GridGraph
	{
	public:
		GridGraph(const Math::Vec2& dimensions);
		
		/// <summary>
		/// Returns vertex at coordinate. 0 indexed.
		/// </summary>
		Vertex* getVertex(const Math::Vec2& cell);
		
	protected:
		/// <summary>
		/// 0 indexed.
		/// </summary>
		std::vector<std::vector<Vertex> > vertexes;
	};
}




