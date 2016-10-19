#include "Actions.hpp"

bool getAction(Actions actions, Action action)
{
	return (actions >> action) & 1;
}

void setAction(Actions* actions, Action action, bool value)
{
	(*actions) ^= (-value ^ (*actions)) & (1 << action);
}
