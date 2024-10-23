#include "boid.h"

Boid::Boid(vec3 _pos, vec3 vel, BoidType t, int id) {
    pos = _pos;
    velocity = vel;
    vec3 nVel = normalize(velocity);
    dir = nVel;
    velocity = nVel;
    lastVelocity = nVel;
    type = t;
    ID = id;
}

Boid::~Boid() {
}

void Boid::process(std::deque<Boid*> boids) {
    dir = normalize(velocity);
    move(boids);
    limitSpeed();
    update();
}

void Boid::move(std::deque<Boid*> boids) {
    int numNeighbors = boids.size() - 1;

    // only move by family rules if near family. otherwise, boid will move towards origin due to
    // subtraction in alignment and cohesion checks
    int numFamily = 0;

    // alignment variables
    // float avgXVel = 0;
    // float avgYVel = 0;
    vec3 avgVel(0);

    // cohesion variables
    // int centerX = 0;
    // int centerY = 0;
    vec3 avgCentre(0);

    // separation variables
    // float moveX = 0;
    // float moveY = 0;
    vec3 avgMove(0);

    float minSepDistance = 10;
    float matchingFactor = 0.05;
    float centeringFactor = 0.005;
    float avoidFactor = 0.01;

    // // if being chased, ignore all prey. define separate attacking and fleeing so that any behaviour defined
    // // before fully seen (i.e., deciding to chase before finding a predator in boid list) can be undone
    // float attackingMoveX = 0;
    // float attackingMoveY = 0;
    // float fleeingMoveX = 0;
    // float fleeingMoveY = 0;

    // isBeingChased = false;                // reset immediate fleeing variable
    // vec3 closestPrey = nullptr;  // chase closest prey instead of group if it's within chase distance
    // float closestPreyDist = -1;

    for (Boid* otherBoid : boids) {
        if (otherBoid->ID != ID) {
            float distFromBoid = distance(pos, otherBoid->pos);

            // alignment
            if (distFromBoid < Boid::FAMILY_RANGE) {
                numFamily += 1;
                // avgXVel += otherBoid.velocity.x;
                // avgYVel += otherBoid.velocity.y;
                avgVel += otherBoid->velocity;

                // cohesion
                // centerX += otherBoid.pos.x;
                // centerY += otherBoid.pos.y;
                avgCentre += otherBoid->pos;
                
                // separation
                if (distFromBoid < minSepDistance) {
                    // moveX += pos.x - otherBoid.pos.x;
                    // moveY += pos.y - otherBoid.pos.y;
                    avgMove += pos - otherBoid->pos;
                }
            }

        }
    }

    if (numNeighbors != 0) {
        if (numFamily != 0) {
            // alignment
            avgVel /= numFamily;
            velocity += (avgVel - velocity) * matchingFactor;

            // cohesion
            avgCentre /= numFamily;
            velocity += (avgCentre - pos) * centeringFactor;
            
            // separation
            velocity += avgMove * avoidFactor;
        }

    }
}

void Boid::limitSpeed() {
    float tspeed = length(velocity);
    if (tspeed > Boid::MAX_SPEED) {
        velocity = (velocity / vec3(tspeed)) * Boid::MAX_SPEED;
    }
}

void Boid::update() {
    float lm = -100, rm = 100, tf = 0.2;
    velocity = normalize(velocity);
    if (pos.x < lm)
        velocity.x += tf;
    if (pos.x > rm)
        velocity.x -= tf;
    if (pos.y < lm)
        velocity.y += tf;
    if (pos.y > rm)
        velocity.y -= tf;
    if (pos.z < lm)
        velocity.z += tf;
    if (pos.z > rm)
        velocity.z -= tf;
    // velocity = normalize(velocity);
    pos += velocity * Boid::MAX_SPEED * SM::delta;
    lastVelocity = velocity;
}