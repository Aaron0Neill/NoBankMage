#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include <algorithm>
#include <vector>
#include <assert.h>
#include <unordered_map>

#include <Entity.h>

/// <summary>
/// All game entities are made up of components (PhysicsBody, Transform, etc.)
/// Each of these components live inside a packed array, [ComponentArray], and can be 
/// identified by their [Entity] ID.
/// </summary>
template<typename COMPONENT_TYPE>
class ComponentArray
{
public:
	void insert(Entity entity, COMPONENT_TYPE component);
	void remove(Entity entity);
	void tryRemove(Entity entity);
	COMPONENT_TYPE& get(Entity entity);
	
	COMPONENT_TYPE operator[](Entity entity) const;

private:
	// This is a packed array, so we must keep the mapping of entities to locations
	std::vector<COMPONENT_TYPE> components;
	std::vector<Entity> indexToEntity;
	std::unordered_map<Entity, size_t> entityToIndex;

	size_t size; // Current size of the array
};


template<typename COMPONENT_TYPE>
inline void ComponentArray<COMPONENT_TYPE>::insert(Entity entity, COMPONENT_TYPE component)
{
	if (entityToIndex.find(entity) != entityToIndex.end()) {
		throw std::exception("Component added to same entity more than once.");
	}
	
	components.push_back(component);
	indexToEntity.push_back(entity);
	entityToIndex[entity] = components.size() - 1;
}


template<typename COMPONENT_TYPE>
inline void ComponentArray<COMPONENT_TYPE>::remove(Entity entity)
{
	if (entityToIndex.find(entity) == entityToIndex.end()) {
		throw std::exception("Trying to remove component from an entity that doesn't have that component.");
	}

	int lastIndex = components.size() - 1;
	int removeIndex = entityToIndex[entity];

	// Overwrite the entity to be deleted with the last active entity
	components[removeIndex] = std::move(components[lastIndex]);

	// Update the mappings
	Entity movedEntity = indexToEntity[lastIndex];
	indexToEntity[removeIndex] = movedEntity;
	entityToIndex[movedEntity] = removeIndex;

	// Pop off the (now duplicated) last entity
	components.pop_back();
	indexToEntity.pop_back();
	entityToIndex.erase(entity);
}


template<typename COMPONENT_TYPE>
inline void ComponentArray<COMPONENT_TYPE>::tryRemove(Entity entity)
{
	if (entityToIndex.find(entity) != entityToIndex.end())
		remove(t_entity);
}


template<typename COMPONENT_TYPE>
inline COMPONENT_TYPE& ComponentArray<COMPONENT_TYPE>::get(Entity entity)
{
	if (entityToIndex.find(entity) == entityToIndex.end()) {
		throw std::Exception("Trying to retrieve a component from an entity that doesn't have it.")
	}
}


template<typename COMPONENT_TYPE>
inline COMPONENT_TYPE ComponentArray<COMPONENT_TYPE>::operator[](Entity entity) const
{
	return get(entity);
}

#endif