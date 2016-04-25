// Tiny T
//
// TinyT.6
//

static const float GameInterface::MAX_T = 1;

void GameInterface::tick()
{
	float t = 0;
	std::vector<Collision*> collisions;
	addAllCollisions(&collisions); // Errechnet alle Collisions, die in diesem Frame passieren würden, wenn sich die zugehörigen Entities mit konstanter Geschwindigkeit bewegen würden
	while (collisions.size() > 0)
	{
		Collision* c = getTinyT(collisions); // Returnt die Collision mit kleinstem t. Also die Collision, die als nächstes ausgeführt werden muss.
		moveAllEntities(c->getTime() - t); // bewegt alle Entities bis zu der Situation, in der die nächste "globale" Collision passiert
		t = c->getTime();

		// Reaktion auf die Collision
		// Falls eine der Entities beschleunigt wurde, werden die Collisions der Entity neu berechnet (Die alten werden gelöscht)(auch beide Entities können betroffen sein)
		// Die Collision, auf die gerade reagiert wurde, wird auf alle Fälle gelöscht, auch wenn keine der beiden Entities 
		applyCollision(c, collisions, t); 
	}
	moveAllEntities(MAX_T-t);
}

void GameInterface::addAllCollisions(std::vector<Collision*>* collisions)
{
	for entity as non-tile-entity: addCollisionFrom(entity, collisions, MAX_T);
}

void GameInterface::applyCollision(Collision* c, std::vector<Collision*>* collisions, float t)
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
			addCollisionFrom(e, collisions, t);
		}
	}
	delete c;
}

void GameInterface::addCollisionFrom(Entity* e, std::vector<Collision*>* collisions, float t)
{
	for entity in entities
	{
		if (e != entity && e->getCollisionPriority(entity) + entity->getCollisionPriority(e) >= 0 && collision doesnt exist)
		{
			Collision *c = CollisionDetector::getCollisionWithT(entity, e, t);
			if (c != NULL)
			{
				collisions->push_back(c);
			}
		}	
	}
}

Collision* CollisionDetector::getCollisionWithT(Entity*, Entity*, float t)
{
	Collision* c = // get collision anyhow
	c->setTime(c->getTime() + t);
	return c;
}
