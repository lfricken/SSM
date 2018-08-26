#pragma once
//#include "TestSuite.hpp"
#include "GridGraph.hpp"

using namespace Math;
using namespace Graph;

const static Vec2 gridSize = Vec2(5,5);

TEST(GridGraph, numberOfVertexes)
{
	GridGraph grid(gridSize);
	{
		auto a = grid.getVertex(Vec2(0, 0));
		auto b = grid.getVertex(gridSize - Vec2(1,1));

		a->edges[Vertex::Right] = true;
		b->edges[Vertex::Left] = false;
	}
	{
		auto a = grid.getVertex(Vec2(0, 0));
		auto b = grid.getVertex(gridSize - Vec2(1, 1));


		EXPECT(a->edges[Vertex::Right], == , true);
		EXPECT(a->edges[Vertex::Left], == , false);
	}
}
TEST(GridGraph, allPathExceptEdgesTrue)
{
	GridGraph grid(gridSize);
	for(int x = 0; x < gridSize.x; ++x)
	{
		for(int y = 0; y < gridSize.y; ++y)
		{
			auto a = grid.getVertex(Vec2(x, y));
			for(int dir = 0; dir < Vertex::NumDirections; ++dir)
			{
				EXPECT(a->edges[dir], == , true);
			}
		}
	}
}











