#include "BatchLayers.hpp"

BatchLayers::BatchLayers()
{

}
BatchLayers::~BatchLayers()
{

}
QuadData BatchLayers::request(const String& rTexName, GraphicsLayer layer)
{
	return m_batches[layer].request(rTexName);
}
void BatchLayers::drawWorld(sf::RenderTarget& rTarget)
{
	for(auto it = m_batches.begin(); (it != m_batches.end()) && (it->first != GraphicsLayer::OverlayBottom); ++it)
	{
		rTarget.draw(it->second);
	}
}
