#pragma once

#include <queue>
#include <array>
#include <iostream>
#include "Entity.h"
#include "Components.h"

/// <summary>
/// Entity Manager will be responsible for storing / updating and removing information that is relevant to the entities
/// This information includes names (which can be used to search and componentId's which are used to sort systems
/// </summary>
class EntityManager
{
public: 
	EntityManager()
	{
		init();
	}

	Entity createEntity() {
		if (m_availableEntities.size() <= 0) 
			throw std::runtime_error("You have exceeded the number of available Entities");

		Entity id = m_availableEntities.front();
		m_availableEntities.pop();
		return id;
	}

	void destroyEntity(Entity t_id) {
		if (t_id < MAX_ENTITIES && t_id > 0) {
			m_signatues[t_id] = 0; 
			m_availableEntities.push(t_id);
		}
	}

	void setComponentID(Entity t_entity, ComponentId t_component) {
		if (t_entity < MAX_ENTITIES)
			m_signatues[t_entity] = t_component;
	}

	void addComponentID(Entity t_entity, ComponentId t_component) {
		if (t_entity < MAX_ENTITIES)
			m_signatues[t_entity] = t_component;
	}

	ComponentId &const getComponentID(Entity t_entity) {
		if (t_entity > MAX_ENTITIES or t_entity <= 0)
			throw std::runtime_error("You have requested a ComponentID outside the current limits");

		return m_signatues[t_entity];
	}

	void setEntityName(Entity t_entity, std::string t_name) {
		if (t_entity < MAX_ENTITIES)
			m_names[t_entity] = t_name;
	}

	std::string& const getEntityName(Entity t_entity) {
		if (t_entity > MAX_ENTITIES or t_entity <= 0)
			throw std::runtime_error("You have requested a ComponentID outside the current limits");

		return m_names[t_entity];
	}

private:

	void init() {
		for (Entity id = 0; id < MAX_ENTITIES; ++id) {
			m_availableEntities.push(id);

			m_names[id] = "";
			m_signatues[id] = 0;
		}
	}
	std::queue<Entity> m_availableEntities;

	std::array<ComponentId, MAX_ENTITIES> m_signatues;
	std::array<std::string, MAX_ENTITIES> m_names;
};