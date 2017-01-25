// #include "core/Main.hpp"
#include "game/Frame.hpp"
#include "entity/TestKiste.hpp"

int main()
{
	// Main main;
	Frame f;
	f.idlers.push_back(new TestKiste(GameVector(0,0)));
	f.clone();

	return 0;
}
