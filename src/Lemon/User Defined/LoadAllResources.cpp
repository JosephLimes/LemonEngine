#include "..\Lemon.h"
#include "..\Lemon\Asset Management\ModelManager.h"
#include "..\Lemon\Asset Management\ShaderManager.h"
#include "..\Lemon\Asset Management\TextureManager.h"
#include "..\Lemon\Asset Management\ImageManager.h"
#include "..\Lemon\Asset Management\FontManager.h"
#include "..\Lemon\Asset Management\TerrainManager.h"
#include "..\Lemon\Scene\SceneManager.h"
#include "..\Game\TestScene.h"
#include "..\Game\DemoStartScene.h"
#include "..\Game\DemoBossScene.h"
#include "..\Game\ExampleScene.h"
#include "Tools\Editor\LevelObjectManager.h"
#include "Tools\Editor\EditorScene.h"

#include "..\Game\Frigate.h"
#include "..\Game\Barrel.h"
#include "..\Game\TelephonePole.h"
#include "..\Game\BuildingA.h"
#include "..\Game\BuildingB.h"
#include "..\Game\Container.h"
#include "..\Game\WallA.h"
#include "..\Game\WallB.h"
#include "..\Game\InanimateTank.h"
#include "..\Game\Rock1.h"
#include "..\Game\Rock2.h"
#include "..\Game\Rock3.h"
#include "..\Game\Rock4.h"
#include "..\Game\Rock5.h"
#include "..\Game\Rock6.h"

void Lemon::LoadAllResources()
{
	//LevelObjectManager::RegisterType<Frigate>();
	LevelObjectManager::RegisterType<Barrel>();
	LevelObjectManager::RegisterType<TelephonePole>();
	LevelObjectManager::RegisterType<BuildingA>();
	LevelObjectManager::RegisterType<BuildingB>();
	LevelObjectManager::RegisterType<Container>();
	LevelObjectManager::RegisterType<WallA>();
	LevelObjectManager::RegisterType<WallB>();
	LevelObjectManager::RegisterType<InanimateTank>();
	LevelObjectManager::RegisterType<Rock1>();
	LevelObjectManager::RegisterType<Rock2>();
	LevelObjectManager::RegisterType<Rock3>();
	LevelObjectManager::RegisterType<Rock4>();
	LevelObjectManager::RegisterType<Rock5>();
	LevelObjectManager::RegisterType<Rock6>();

	SceneManager::SetNextScene(new DemoStartScene());
	//SceneManager::SetNextScene(new DemoBossScene());
	//SceneManager::SetNextScene(new TestScene());
	//SceneManager::SetNextScene(new ExampleScene());
	//SceneManager::SetNextScene(new EditorScene());

	ModelManager::Load("widget", "widget.azul");
	ModelManager::Load("translate", "move.azul");
	ModelManager::Load("rotate", "rotate.azul");
	ModelManager::Load("scale", "scale.azul");

	ModelManager::Load("Plane", 400, 2, 2);
	ModelManager::Load("SpaceFrigate", "space_frigate.azul");

	ModelManager::Load("rock1", "rock1.azul");
	ModelManager::Load("rock2", "rock2.azul");
	ModelManager::Load("rock3", "rock3.azul");
	ModelManager::Load("rock4", "rock4.azul");
	ModelManager::Load("rock5", "rock5.azul");
	ModelManager::Load("rock6", "rock6.azul");

	ModelManager::Load("barrel", "l_barrel.azul");
	ModelManager::Load("telephone_pole", "l_telephone_pole.azul");
	ModelManager::Load("building_a", "l_building_a.azul");
	ModelManager::Load("building_b", "l_building_b.azul");
	ModelManager::Load("container_base", "l_container_base.azul");
	ModelManager::Load("container_door_l", "l_container_door_l.azul");
	ModelManager::Load("container_door_r", "l_container_door_r.azul");
	ModelManager::Load("wall_a", "l_wall_a.azul");
	ModelManager::Load("wall_b", "l_wall_b.azul");
	ModelManager::Load("tank_hull", "l_tank_hull_b.azul");
	ModelManager::Load("tank_turret", "l_tank_turret_c.azul");
	ModelManager::Load("tank_gun", "l_tank_gun_b.azul");
	ModelManager::Load("tank_hull_boss", "l_tank_hull_boss.azul");
	ModelManager::Load("tank_turret_boss", "l_tank_turret_boss.azul");
	ModelManager::Load("tank_gun_boss", "l_tank_gun_boss.azul");

	TextureManager::Load("nucket", "nucket.tga");
	TextureManager::Load("SpaceFrigate", "space_frigate.tga");
	TextureManager::Load("Plane", "grid.tga");
	TextureManager::Load("sandy_gravel", "sandy_gravel.tga");
	TextureManager::Load("rock1", "rock1.tga");
	TextureManager::Load("rock2", "rock2.tga");
	TextureManager::Load("rock3", "rock3.tga");
	TextureManager::Load("rock4", "rock4.tga");
	TextureManager::Load("rock5", "rock5.tga");
	TextureManager::Load("rock6", "rock6.tga");
	TextureManager::Load("rotate", "rotate.tga");
	TextureManager::Load("widget", "widget.tga");
	TextureManager::Load("move", "move.tga");
	TextureManager::Load("scale", "scale.tga");
	TextureManager::Load("FrigateCube", "FrigateCube.tga");
	TextureManager::Load("barrel", "l_barrel.tga");
	TextureManager::Load("telephone_pole", "l_telephone_pole.tga");
	TextureManager::Load("building_a", "l_building_a.tga");
	TextureManager::Load("building_b", "l_building_b.tga");
	TextureManager::Load("container_base", "l_container_base.tga");
	TextureManager::Load("container_door_l", "l_container_door_l.tga");
	TextureManager::Load("container_door_r", "l_container_door_r.tga");
	TextureManager::Load("wall_a", "l_wall_a.tga");
	TextureManager::Load("wall_b", "l_wall_b.tga");
	TextureManager::Load("tank_player_hull", "l_tank_player_hull.tga");
	TextureManager::Load("tank_player_turretgun", "l_tank_player_turretgun.tga");
	TextureManager::Load("tank_enemy_hull", "l_tank_enemy_hull.tga");
	TextureManager::Load("tank_enemy_turretgun", "l_tank_enemy_turretgun.tga");
	TextureManager::Load("red", "red.tga");

	ShaderManager::Load("colorNoTextureRender", "colorNoTextureRender");
	//ShaderManager::Load("colorNoTextureRender", "colorNoTextureRenderNew");
	ShaderManager::Load("colorNoTextureLightRender", "colorNoTextureLightRender");
	ShaderManager::Load("colorVaryRender", "colorVaryRender");

	ImageManager::Load("nucket", TextureManager::Get("nucket"));
	ImageManager::Load("red", TextureManager::Get("red"));

	FontManager::Load("stencil_36", "stencil_36");

	TerrainManager::Load("4", "HM4x4.tga", "Plane", 512, 32, 0, 3, 3);
	TerrainManager::Load("64", "HM64x64.tga", "Plane", 512, 32, 0, 3, 3);
	TerrainManager::Load("desert", "HMandre.tga", "sandy_gravel", 16384, 256, -25, 3, 3);
}