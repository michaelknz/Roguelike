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
	instance->entities.push_back(new_entity);
	instance->colliders[new_entity] = (new_entity->GetColliders());
}

void Scene::DeleteEntity(Entity* del_entity) {
	instance->entities.erase(std::find(instance->entities.begin(), instance->entities.end(), del_entity));
	instance->colliders.erase(del_entity);
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

std::vector<Collider*> Scene::CheckCollide(Collider* collider, const std::string& tag) {
	std::vector<Collider*> output;
	for (std::unordered_map<Entity*, std::vector<Collider*>*>::iterator i = instance->colliders.begin(); i != instance->colliders.end(); ++i) {
		if ((*i).first == collider->GetObject()) {
			continue;
		}
		std::vector<Collider*> tmp = *(*i).second;
		for (int j = 0; j < tmp.size(); ++j) {
			if ((tmp[j]->GetTag() == tag) && (collider->IsCollide(tmp[j]))) {
				output.push_back(tmp[j]);
			}
		}
	}
	return output;
}