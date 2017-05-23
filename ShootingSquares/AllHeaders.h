#pragma once

// System libraries
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <Windows.h>
#include <wtypes.h>
#include <iostream>
#include <fstream>

#define DEBUG false
#define PI 3.14159265
#define _OUT

#define SCREENWIDTH 1920
#define SCREENHEIGHT 1200


// Custom libraries
#include "StructsAndEnums.h"
#include "QuadTree.h"
#include "Tools.h"
#include "BoxCollider.h"
#include "Weapon.h"
#include "Controller.h"
#include "Player.h"
#include "Item.h"
#include "PickUp.h"
#include "Killer.h"
#include "Scene.h"
#include "GUI.h"
#include "Config.h"
#include "Game.h"