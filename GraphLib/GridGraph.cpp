#include "GridGraph.hpp"

using namespace Math;

namespace Graph
{
	// This is the constructor of a class that has been exported.
	// see GraphLib.h for the class definition
	GridGraph::GridGraph(const Math::Vec2& dimensions)
	{
		vertexes.resize(dimensions.x);
		for(auto it = vertexes.begin(); it != vertexes.end(); ++it)
		{
			it->resize(dimensions.y);
		}

		// disable edges of graph
		// top
		for(int x = 0; x < dimensions.x; x++)
		{
			auto top = getVertex(Vec2(x, 0));
			top->edges[Vertex::UpLeft] = false;
			top->edges[Vertex::Up] = false;
			top->edges[Vertex::UpRight] = false;
		}

		// bottom
		for(int x = 0; x < dimensions.x; x++)
		{
			auto bottom = getVertex(Vec2(x, dimensions.y - 1));
			bottom->edges[Vertex::DownLeft] = false;
			bottom->edges[Vertex::Down] = false;
			bottom->edges[Vertex::DownRight] = false;
		}

		// left
		for(int y = 0; y < dimensions.y; y++)
		{
			auto left = getVertex(Vec2(0, y));
			left->edges[Vertex::UpLeft] = false;
			left->edges[Vertex::Left] = false;
			left->edges[Vertex::DownLeft] = false;
		}

		// right
		for(int y = 0; y < dimensions.y; y++)
		{
			auto right = getVertex(Vec2(dimensions.x - 1, y));
			right->edges[Vertex::UpRight] = false;
			right->edges[Vertex::Right] = false;
			right->edges[Vertex::DownRight] = false;
		}

		// give vertexes their positions
		for(int x = 0; x < dimensions.x; ++x)
		{
			for(int y = 0; y < dimensions.y; ++y)
			{
				Vec2 pos(x, y);
				getVertex(pos)->thisPosition = pos;
			}
		}
	}

	Vertex* GridGraph::getVertex(const Math::Vec2& cell)
	{
		return &vertexes[cell.x][cell.y];
	}

}
