#include "Scene.h"

Scene* Scene::instance = nullptr;

Scene* Scene::getInstance() {
	if (instance == nullptr) {
		instance = new Scene;
	}
	return instance;
}

void Scene::deleteInstance() {
	if (instance != nullptr) {
		delete instance;
	}
}

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::AddEntity(Entity* new_entity) {
	entities.push_back(new_entity);
}

void Scene::Clear_Scene() {
	entities.clear();
}

std::vector<Entity*> Scene::GetObjectsByTag(const std::string& tag) {
	std::vector<Entity*> output;
	for (int i = 0; i < instance->entities.size(); ++i) {
		if (tag == instance->entities[i]->Get_Tag()) {
			output.push_back(instance->entities[i]);
		}
	}
	return output;
}

void Scene::UpdateAllEntities() {
	for (int i = 0; i < instance->entities.size(); ++i) {
		instance->entities[i]->Update();
	}
}