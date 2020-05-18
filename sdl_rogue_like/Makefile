CXXFLAGS = -g -O0 -Wextra -Wall -IC:\libsdl\include -std=c++0x
LXXFLAGS = -g -O0 -LC:\libsdl\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

output: main.o game_window.o player.o enemy.o ADT/Vector2/Vector2.o game_manager.o time_manager.o collider.o sprite.o game_object.o character.o projectile.o UI_element.o
	g++ main.o game_window.o player.o enemy.o ADT/Vector2/Vector2.o game_manager.o time_manager.o collider.o sprite.o game_object.o character.o projectile.o UI_element.o -o output $(LXXFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(CXXFLAGS)

game_manager.o: game_manager.cpp game_manager.h
	g++ -c game_manager.cpp $(CXXFLAGS)

game_window.o: game_window.cpp game_window.h
	g++ -c game_window.cpp $(CXXFLAGS)

player.o: player.cpp player.h game_object.h
	g++ -c player.cpp $(CXXFLAGS)

enemy.o: enemy.cpp enemy.h
	g++ -c enemy.cpp $(CXXFLAGS)

time_manager.o: time_manager.cpp time_manager.h
	g++  -c time_manager.cpp $(CXXFLAGS)

collider.o: collider.cpp collider.h
	g++ -c collider.cpp $(CXXFLAGS) 

sprite.o: sprite.cpp sprite.h
	g++ -c sprite.cpp $(CXXFLAGS)

game_object.o: game_object.cpp game_object.h
	g++ -c game_object.cpp $(CXXFLAGS)

character.o: character.cpp game_object.h
	g++ -c character.cpp $(CXXFLAGS)

projectile.o: projectile.cpp projectile.h
	g++ -c projectile.cpp $(CXXFLAGS)

UI_element.o: UI_element.cpp UI_element.h
	g++ -c UI_element.cpp $(CXXFLAGS)


clean:
	rm *.o output
