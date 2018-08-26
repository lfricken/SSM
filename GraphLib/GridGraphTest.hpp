#pragma once
#include "TestSuite.hpp"
#include "GridGraph.hpp"

using namespace Math;
using namespace Graph;

const static Vec2 gridSize = Vec2(5, 5);

TEST(GridGraph, numberOfVertexes, "The Vertexes (0,0) and (N,N) Exist")
{
	GridGraph grid(gridSize);

	{
		auto a = grid.getVertex(Vec2(0, 0));
		auto b = grid.getVertex(gridSize - Vec2(1, 1));

		a->edges[Vertex::Right] = true;
		b->edges[Vertex::Left] = false;
	}
	{
		auto a = grid.getVertex(Vec2(0, 0));
		auto b = grid.getVertex(gridSize - Vec2(1, 1));


		EXPECT(a->edges[Vertex::Right], == , true);
		EXPECT(b->edges[Vertex::Left], == , false);
	}
}
TEST(GridGraph, allPathExceptEdgesTrue, "All edges default true except edges of graph")
{
	GridGraph grid(gridSize);

	// 1 and -1 to avoid edges
	for(float x = 1; x < gridSize.x - 1; ++x)
	{
		for(float y = 1; y < gridSize.y - 1; ++y)
		{
			auto a = grid.getVertex(Vec2(x, y));
			for(int dir = 0; dir < Vertex::NumDirections; ++dir)
			{
				EXPECT(a->edges[dir], == , true);
			}
		}
	}


	// top
	for(float x = 0; x < gridSize.x; x++)
	{
		auto top = grid.getVertex(Vec2(x, 0));
		EXPECT(top->edges[Vertex::UpLeft], == , false);
		EXPECT(top->edges[Vertex::Up], == , false);
		EXPECT(top->edges[Vertex::UpRight], == , false);

		EXPECT(top->edges[Vertex::Down], == , true);
	}

	// bottom
	for(float x = 0; x < gridSize.x; x++)
	{
		auto bottom = grid.getVertex(Vec2(x, gridSize.y - 1));
		EXPECT(bottom->edges[Vertex::DownLeft], == , false);
		EXPECT(bottom->edges[Vertex::Down], == , false);
		EXPECT(bottom->edges[Vertex::DownRight], == , false);

		EXPECT(bottom->edges[Vertex::Up], == , true);
	}

	// left
	for(float y = 0; y < gridSize.y; y++)
	{
		auto left = grid.getVertex(Vec2(0, y));
		EXPECT(left->edges[Vertex::UpLeft], == , false);
		EXPECT(left->edges[Vertex::Left], == , false);
		EXPECT(left->edges[Vertex::DownLeft], == , false);

		EXPECT(left->edges[Vertex::Right], == , true);
	}

	// right
	for(float y = 0; y < gridSize.y; y++)
	{
		auto right = grid.getVertex(Vec2(gridSize.x - 1, y));
		EXPECT(right->edges[Vertex::UpRight], == , false);
		EXPECT(right->edges[Vertex::Right], == , false);
		EXPECT(right->edges[Vertex::DownRight], == , false);

		EXPECT(right->edges[Vertex::Left], == , true);
	}
}
TEST(Vertex, inactiveVSactiveInitialized, "Inactive vs Active are null initially")
{
	GridGraph grid(gridSize);

	{
		auto vert = grid.getVertex(gridSize - Vec2(1, 1));
		auto activeDataPointer = vert->getActiveStateData();
		auto inactiveDataPointer = vert->getInactiveStateData();
		EXPECT(activeDataPointer, == , inactiveDataPointer);
	}
}
TEST(Vertex, inactiveVSactiveSet, "Inactive vs Active values are different")
{
	GridGraph grid(gridSize);

	auto vert = grid.getVertex(gridSize - Vec2(1, 1));
	vert->setActiveStateData(new int);
	vert->setInactiveStateData(new int);

	{
		auto activeDataPointer = vert->getActiveStateData();
		auto inactiveDataPointer = vert->getInactiveStateData();

		EXPECT(activeDataPointer, != , inactiveDataPointer);
	}
}
TEST(Vertex, flipActive, "Inactive vs Active flip correctly")
{
	GridGraph grid(gridSize);

	{
		auto vert = grid.getVertex(gridSize - Vec2(1, 1));

		auto data1 = new int;
		auto data2 = new int;
		vert->setActiveStateData(data1);
		vert->setInactiveStateData(data2);

		{
			auto activeDataPointer = vert->getActiveStateData();
			auto inactiveDataPointer = vert->getInactiveStateData();

			EXPECT(activeDataPointer, == , data1);
			EXPECT(inactiveDataPointer, == , data2);
			EXPECT(activeDataPointer, != , inactiveDataPointer);
		}

		vert->flipActive();
		{
			auto activeDataPointer = vert->getActiveStateData();
			auto inactiveDataPointer = vert->getInactiveStateData();

			EXPECT(activeDataPointer, == , data2);
			EXPECT(inactiveDataPointer, == , data1);
			EXPECT(activeDataPointer, != , inactiveDataPointer);
		}
	}
}
TEST(Vertex, adjacency, "Adjacents are accurate")
{
	GridGraph grid(gridSize);

	{
		Vec2 center = Vec2(2, 2);
		auto vert = grid.getVertex(center);
		auto adjList = vert->getAdjacents();

		EXPECT(adjList[Vertex::Right], == , center + Vec2(1, 0));
		EXPECT(adjList[Vertex::Up], == , center + Vec2(0, 1));
		EXPECT(adjList[Vertex::Left], == , center + Vec2(-1, 0));
		EXPECT(adjList[Vertex::Down], == , center + Vec2(0, -1));

		EXPECT(adjList[Vertex::UpRight], == , center + Vec2(1, 1));
		EXPECT(adjList[Vertex::UpLeft], == , center + Vec2(-1, 1));
		EXPECT(adjList[Vertex::DownLeft], == , center + Vec2(-1, -1));
		EXPECT(adjList[Vertex::DownRight], == , center + Vec2(1, -1));
	}
}











