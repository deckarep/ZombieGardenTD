#include "particles.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include "game.h"

FixedObjectArray particles;

int rainParticleTimer = 0;

// TODO: Consider adding minSpeed
void CreateParticleExplosion(Vector2 pos, Vector2 size, int maxSpeed, int lifetime, int particleCount, Color colour)
{
    for (int i = 0; i < particleCount; i++) {

        Particle* p = CreateParticle(P_DEFAULT, pos, size, lifetime, colour);
        Vector2 randDir = Vector2Normalize((Vector2){GetRandomFloatValue(-1, 1), GetRandomFloatValue(-1, 1)});
        p->velocity = Vector2Scale(randDir, GetRandomFloatValue(0, maxSpeed));
    }
}

void CreateParticleConfetti(Vector2 pos, Vector2 size, int particleCount)
{
    for (int i = 0; i < particleCount; i++) {
        Color randC = {
            GetRandomValue(0, 255),
            GetRandomValue(0, 255),
            GetRandomValue(0, 255),
            255
        };
        Particle* p = CreateParticle(P_DEFAULT, pos, size, 60, randC);
        Vector2 randDir = Vector2Normalize((Vector2){GetRandomFloatValue(-1, 1), GetRandomFloatValue(-1, 1)});
        p->velocity = Vector2Scale(randDir, GetRandomFloatValue(2, 5));
    }
}

Particle *CreateParticle(ParticleType type, Vector2 pos, Vector2 size, int lifetime, Color colour)
{
    Particle *partArr = (Particle*)particles.array;
    Particle* p = &partArr[particles.next];


    p->type = type;
    p->pos = pos;
    p->size = size;
    p->colour = colour;
    p->startLifetime = lifetime;
    p->lifetime = lifetime;
    p->active = true;


    NextObject(&particles);

    return p;
}

void UpdateDrawParticles(void)
{
    Particle *partArr = (Particle*)particles.array;
    for (int i = 0; i < particles.fixedSize; i++) {
        Particle *p = &partArr[i];
        if (p->active) {
            p->pos = Vector2Add(p->pos, p->velocity);
            p->lifetime--;

            p->colour.a = 255 * (p->lifetime / (float)p->startLifetime);

            DrawRectangleV(p->pos, p->size, p->colour);

            if (p->lifetime <= 0) {
                p->active = false;

                switch (p->type) {
                    case P_RAIN:
                        CreateParticleExplosion(p->pos, (Vector2){2, 2}, 2, 15, 8, (Color){255, 255, 255, 150});
                        break;
                    default:
                        break;
                }
            }

        }
    }
}
