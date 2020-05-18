#include "game_manager.h"
#include <iostream>

// void* operator new(size_t size)
// {
// 	std::cout << "Allocating " << size << " bytes\n";
// 	return malloc(size);
// }


int main(int argc, char* argv[])
{

	game_manager gm;
	gm.update();

	return 0;
}
