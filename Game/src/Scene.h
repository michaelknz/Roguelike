#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"
#include <vector>

class Scene {
public:
	Scene();
	~Scene();
	static Scene* getInstance();
	static void deleteInstance();
	void AddEntity(Entity* new_entity);
	void Clear_Scene();
	void UpdateAllEntities();
	static std::vector<Entity*> GetObjectsByTag(const std::string& tag);
private:
	std::vector<Entity*> entities;
	static Scene* instance;
};

#endif