// Tiny T
//
// TinyT.6
//

void GameInterface::tick()
{
	float t = 0;
	std::vector<Collision*> collisions;
	addAllCollisions(&collisions);
	while (collisions.size() > 0)
	{
		Collision* c = getTinyT(collisions); // Returnt die Collision mit kleinstem t. Also die Collision, die als nächstes ausgeführt werden muss.
		t += c->getTime();
		moveAllEntities(c->getTime()); // bewegt alle Entities bis zu der Situation, in der die nächste "globale" Collision passiert

		// Reaktion auf die Collision
		// Falls eine der Entities beschleunigt wurde, werden die Collisions der Entity neu berechnet (Die alten werden gelöscht)(auch beide Entities können betroffen sein)
		// Die Collision, auf die gerade reagiert wurde, wird auf alle Fälle gelöscht, auch wenn keine der beiden Entities 
		applyCollision(c, collisions); 
	}
	moveAllEntities(1-t);
}

void GameInterface::addAllCollisions(std::vector<Collision*>* collisions)
{
	for entity as non-tile-entity: addCollisionFrom(entity, collisions);
}

void GameInterface::updateCollisions(std::vector<Collision*>* collisions, Collision* c, float t)
{
	remove c-entities collisions from collisions
	for entity as c->getEntities(): addCollisionFrom(entity, collisions);
}

void GameInterface::applyCollision(Collision* c, std::vector<Collision*>* collisions)
{
	// Collision wird aus Liste entfernt
	EntferneDieCollisionAusListe(c, collisions);
	// Beide Entities reagieren auf die Collision
	for e in c->getEntities()
	{
		// Collisions neu berechnen, wenn eine der Entities beschleunigt wurde
		if (e.applyCollision(c))
		{
			LöscheAlleCollisionsMit(e);
			addCollisionFrom(e, collisions);
		}
	}
	delete c;
}

void GameInterface::addCollisionFrom(Entity* e, std::vector<Collision*>* collisions)
{
	for entity in entities
	{
		if (e->getCollisionPriority(entity) + entity->getCollisionPriority(e) >= 0 && collision doesnt exist)
		{
			Collision *c = CollisionDetector::getCollision(entity, e);
			collisions->push_back(c);
		}	
	}
}
