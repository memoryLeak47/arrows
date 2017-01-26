// #include "core/Main.hpp"
#include "game/Frame.hpp"
#include "entity/TestKiste.hpp"

int main()
{
	// Main main;
	TestKiste* tk = new TestKiste(GameVector(0,0));

	Frame f;
	f.idlers.push_back(tk);
	f.clone();

	return 0;
}
