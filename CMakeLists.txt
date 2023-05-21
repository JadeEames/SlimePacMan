cmake_minimum_required(VERSION 3.14)
project(PacmanSFML)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/ResourceHandler.cpp src/ResourceHandler.h src/map/GameMap.cpp
        src/map/GameMap.h src/GameData.h src/map/VertexArrayMap.cpp src/map/VertexArrayMap.h src/states/State.h
        src/states/MainMenu.cpp src/states/MainMenu.h src/states/StateEnum.h src/components/Helper.cpp
        src/components/Helper.h
        src/components/Collider.cpp src/components/Collider.h src/states/GamePlay.cpp
        src/states/GamePlay.h src/map/MapFiles.h
        src/game_objects/Player.cpp src/game_objects/Player.h src/game_objects/Entity.cpp src/game_objects/Entity.h
        src/components/HitBoxSprite.cpp src/components/HitBoxSprite.h "src/game_objects/Collectable.cpp"
        src/game_objects/Collectable.h src/states/WinMenu.cpp src/states/WinMenu.h src/game_objects/enemies/RedEnemy.cpp
        src/game_objects/enemies/RedEnemy.h src/components/behaviour_tree/Node.h src/components/behaviour_tree/Sequence.cpp
        src/components/behaviour_tree/Sequence.h src/components/behaviour_tree/Selector.cpp src/components/behaviour_tree/Selector.h
        src/components/behaviour_tree/InverterDecorator.cpp src/components/behaviour_tree/InverterDecorator.h
        src/components/behaviour_tree/custom_nodes/Chase.cpp src/components/behaviour_tree/custom_nodes/Chase.h
        src/game_objects/enemies/pathfinding/AStarPath.cpp src/game_objects/enemies/pathfinding/AStarPath.h
        src/game_objects/enemies/Enemy.cpp src/game_objects/enemies/Enemy.h
        src/components/behaviour_tree/BehaviourTree.h src/components/behaviour_tree/custom_nodes/Flee.cpp
        src/components/behaviour_tree/custom_nodes/Flee.h src/components/behaviour_tree/custom_nodes/Die.cpp
        src/components/behaviour_tree/custom_nodes/Die.h src/components/behaviour_tree/custom_nodes/Idle.cpp
        src/components/behaviour_tree/custom_nodes/Idle.h src/components/behaviour_tree/custom_nodes/Move.cpp
        src/components/behaviour_tree/custom_nodes/Move.h src/states/LoseMenu.cpp src/states/LoseMenu.h src/states/MapSelectMenu.cpp src/states/MapSelectMenu.h src/game_objects/enemies/PinkEnemy.cpp src/game_objects/enemies/PinkEnemy.h src/game_objects/enemies/OrangeEnemy.cpp src/game_objects/enemies/OrangeEnemy.h src/game_objects/enemies/BlueEnemy.cpp src/game_objects/enemies/BlueEnemy.h src/game_objects/enemies/GreenEnemy.cpp src/game_objects/enemies/GreenEnemy.h)

set(TMX_LITE src/tmxLiteSrc/FreeFuncs.cpp src/tmxLiteSrc/ImageLayer.cpp src/tmxLiteSrc/LayerGroup.cpp src/tmxLiteSrc/Map.cpp
        src/tmxLiteSrc/miniz.c src/tmxLiteSrc/miniz.h src/tmxLiteSrc/Object.cpp src/tmxLiteSrc/ObjectGroup.cpp
        src/tmxLiteSrc/ObjectTypes.cpp src/tmxLiteSrc/Property.cpp src/tmxLiteSrc/TileLayer.cpp src/tmxLiteSrc/Tileset.cpp
        src/detail/pugixml.cpp)

add_executable(PacmanSFML ${SOURCE_FILES} ${TMX_LITE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PacmanSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)