#include "Keeper.h"
#include "KeeperHandler.h"

int main()
{
	//AbstractKeeperHandler * handler(new AutoTestKeeperHandler);
	AbstractKeeperHandler * handler(new IOKeeperHandler);
	Keeper containers(handler);
	containers.run();
	return 0;
}