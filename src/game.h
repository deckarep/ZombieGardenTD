#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include <raymath.h>
#include "plant.h"
#include "ui.h"
#include <stdbool.h>

extern const int virtualScreenWidth;
extern const int virtualScreenHeight;

void GameOver(void);

#define EXPAND_V2(v2) v2.x, v2.y

// Plant Grid globals
#define GRID_WIDTH 9
#define GRID_HEIGHT 5
extern Plant gardenGrid[GRID_WIDTH][GRID_HEIGHT];
extern Vector2 gridDrawOffset;
extern Vector2 gridCellSize;


typedef struct {
    int fixedSize;
    void* array;
    int next;
} FixedObjectArray;

// Get a pointer to the next free FixedObjectArray object
#define GET_NEXT_OBJECT(fixedObjArray, type) &((type*)fixedObjArray.array)[fixedObjArray.next]

typedef struct {
    Vector2 pos;
    bool active;
} Projectile;

extern FixedObjectArray projectiles;


void NextObject(FixedObjectArray *array);
bool TickCooldown(int *timer, int cooldownTime);
int GetUniqueRandomValue(int exludedValue, int min, int max);
float GetRandomFloatValue(float min, float max);
void DrawTextureCentered(Texture2D sprite, Vector2 pos, Vector2 origin, Color tint, float scale);
Vector2 GetTextureCenterPoint(Texture2D sprite);
Vector2 GetMousePosVirtual(void);
int GetButtonHeight(ButtonOptions bOpt, TextOptions tOpt);

#endif
