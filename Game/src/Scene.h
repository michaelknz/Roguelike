#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"
#include <vector>
#include <unordered_map>
#include "Collider.h"

class Scene {
public:
	Scene();
	~Scene();
	static Scene* getInstance();
	static void deleteInstance();
	static void AddEntity(Entity* new_entity);
	static void DeleteEntity(Entity* del_entity);
	void Clear_Scene();
	void UpdateAllEntities();
	static std::vector<Entity*> GetObjectsByTag(const std::string& tag);
	static std::vector<Collider*> CheckCollide(Collider* collider, const std::string& tag);
private:
	std::vector<Entity*> entities;
	static Scene* instance;
	std::unordered_map<Entity*, std::vector<Collider*>*> colliders;
};

#endif