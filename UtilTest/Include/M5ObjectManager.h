#ifndef M5OBJECT_MANAGER_H
#define M5OBJECT_MANAGER_H

#include "M5ComponentFactory.h"
#include "M5ComponentTypes.h"
#include "M5ArcheTypes.h"

class M5Object;
class M5ComponentBuilder;


class M5ObjectManager
{
public:
	friend class M5App;


	static M5Object* CreateObject(M5ComponentTypes type);
	static void DestroyObject(M5Object* pToDestroy);
	static void DestroyAllObjects(void);
	static void AddComponent(M5ComponentTypes type, M5ComponentBuilder* pBuilder);
	static void RemoveComponent(M5ComponentTypes type);
	static M5Object* AddArchetype(M5ArcheTypes type, const char* fileName);
private:
	static void Init(void);
	static void Shutdown(void);
};


#endif //M5OBJECT_MANAGER