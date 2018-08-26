#include "GridGraph.hpp"


namespace Graph
{
	// This is the constructor of a class that has been exported.
	// see GraphLib.h for the class definition
	GridGraph::GridGraph(const Math::Vec2& dimensions)
	{
		vertexes.resize(dimensions.x);
		for (auto it = vertexes.begin(); it !=vertexes.end(); ++it)
		{
			it->resize(dimensions.y);
		}
	}

	Vertex* GridGraph::getVertex(const Math::Vec2& cell)
	{
		return &vertexes[cell.x][cell.y];
	}

}
