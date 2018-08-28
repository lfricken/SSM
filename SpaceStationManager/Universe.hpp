#pragma once

#include "stdafx.hpp"
#include "IOComponent.hpp"
#include "LaunchGame.hpp"
#include "NonCopyable.hpp"
#include "Team.hpp"
#include "Clock.hpp"
#include "Resources.hpp"
#include "Pauser.hpp"

class BatchLayers;
class GraphicsComponentUpdater;
class IOManager;
class Chunk;
class BlueprintLoader;
class Decoration;
class ControlFactory;
class ProjectileMan;
class BodyComponent;
class Scoreboard;
class DecorationEngine;
class ModuleParent;
class NetworkComponent;
enum class UpgradeType;

/// Contains everything in the "world". Relaunching a game totally recreates this object.
class Universe : public Core::IClock, Core::INonCopyable
{
public:
	Universe(const IOComponentData& rData);
	virtual ~Universe();

	BatchLayers& getBatchLayers();
	/// Return the GraphicsComponentUpdater for this Universe.
	GraphicsComponentUpdater& getGfxUpdater();
	/// Return the Universe level IOManager.
	IOManager& getUniverseIO();
	/// Return ProjectileMan for this Universe.
	ProjectileMan& getProjMan();
	/// Return the DecorationEngine for this Universe.
	DecorationEngine& getDecors();
	/// Return the BlueprintLoader for this Universe.
	BlueprintLoader& getBlueprints();


	/// Called before the Box2D b2World step. Gets called on the list of Chunk and Projectile
	void prePhysUpdate();
	/// Called to step the physics world.
	void physUpdate();
	/// Called after the Box2D b2World step. Gets called on the list of Chunk and Projectile
	void postPhysUpdate();


	/// Is debug draw on or not?
	bool debugDraw() const;
	/// Set whether debug draw is on or not.
	void toggleDebugDraw();


	/// Load a level using Blueprints.
	void loadLevel(const GameLaunchData& data);

	/// Return list of Chunk.
	//List<sptr<Chunk> > getgoList();
	/// Used to create impact particles.
	void spawnParticles(const String& particleBP, const Vec2& pos, const Vec2& dir, const Vec2& transverse);
	

	bool started = true; //tell whether this is the initial universe created by Game, or a later one

	Pauser pauser;

protected:
	bool listContains(std::list<Team> teams, Team value);
	void loadBlueprints(const String& bluePrints);//loads blueprints
	void input(String rCommand, sf::Packet rData);

private:
	friend class NetworkBoss;
	void pack(sf::Packet& data);
	void unpack(sf::Packet& data);
	
	sptr<NetworkComponent> m_nw;
	sptr<BlueprintLoader> m_spBPLoader;
	sptr<BatchLayers> m_spBatchLayers;
	sptr<GraphicsComponentUpdater> m_spGfxUpdater;
	sptr<IOManager> m_spUniverseIO;//manages IO for the game objects
	sptr<ProjectileMan> m_spProjMan;//manages projectiles
	sptr<DecorationEngine> m_spDecorEngine;//list of decorations for the world
	
	IOComponent m_io;
	float m_lastTime;//used for update method//cant use timer because timer references us!
	bool m_debugDrawEnabled;
};
