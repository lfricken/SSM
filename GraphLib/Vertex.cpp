#include "Vertex.hpp"

const Math::Vec2 right(1, 0);
const Math::Vec2 upright(1, 1);
const Math::Vec2 up(0, 1);
const Math::Vec2 upleft(-1, 1);

const Math::Vec2 left(-1, 0);
const Math::Vec2 downleft(-1, -1);
const Math::Vec2 down(0, -1);
const Math::Vec2 downright(1, -1);


namespace Graph
{
	Vertex::Vertex()
	{
		std::fill(edges, edges + NumDirections, true); // make all edges true
	}

	Vertex::~Vertex()
	{

	}

	std::vector<Math::Vec2> Vertex::getAdjacents() const
	{
		std::vector<Math::Vec2> pos;

		if(edges[Right])
			pos.push_back(right);
		if(edges[UpRight])
			pos.push_back(upright);
		if(edges[Up])
			pos.push_back(up);
		if(edges[UpLeft])
			pos.push_back(upleft);

		if(edges[Left])
			pos.push_back(left);
		if(edges[DownLeft])
			pos.push_back(downleft);
		if(edges[Down])
			pos.push_back(down);
		if(edges[DownRight])
			pos.push_back(downright);

		return pos;
	}

	const void* Vertex::getActiveStateData()
	{
		return vertexStateData.get();
	}

	void* Vertex::getInactiveStateData()
	{
		return vertexStateDataTemp.get();
	}

	void* Vertex::getUserData()
	{
		return userData.get();
	}

	void Vertex::setActiveStateData(void* stateData)
	{
		return vertexStateData.reset(stateData);
	}

	void Vertex::setInactiveStateData(void* stateData)
	{
		return vertexStateDataTemp.reset(stateData);
	}

	void Vertex::setUserData(void* data)
	{
		userData.reset(data);
	}

	void Vertex::flipActive()
	{
		sp<void> temp = vertexStateData;
		vertexStateData = vertexStateDataTemp;
		vertexStateDataTemp = temp;
	}

}