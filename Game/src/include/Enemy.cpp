#include "Enemy.h"

#include "iostream"

void Enemy::shift(float frame_time, int64_t time_stamp)
{
    if (this->routing)
    {
        this->patrol(frame_time);
    }
    if (this->returning)
    {
        if (this->location == this->LastPosition)
        {
            this->returning = false;
            this->LastPosition = nullptr;
            this->routing = true;
        }
        else
        {
            this->traceback(frame_time);
        }
    }
    if (this->engaging)
    {
        if (this->target != nullptr)
        {
            // Always check that player target has not entered a safe spot
            if (this->target->getLocation()->data.chunk_type != ChunkType::safe)
            {
                if (this->rangeToEntity(this->target, true))
                {
                    if (time_stamp % this->attributes.cooldown == 0)
                    {
                        this->attack();
                    }
                }
                else
                {
                    this->follow(frame_time);
                }
            }
            else
            { // If the target has entered the safe spot then disengage the offensiveness
                this->disengage();
            }
        }
    }
}

void Enemy::attack()
{
    if (this->target->shieldActive && this->target->ShieldPoints > 0)
    {
        this->target->addShieldPoints(-this->attributes.damage[1]);
    }
    else
    {
        this->target->addHealthPoints(-this->attributes.damage[1]);
    }
};

void Enemy::follow(float frame_time)
{
    if (this->target->breadcrumbs->getSize() > 0)
    {
        MapChunk chunk = this->target->breadcrumbs->get(this->target->breadcrumbs->getSize() - 1);
        this->moveTo(chunk, frame_time);
    }
    // this->moveTo(this->target->getLocation()->data, frame_time);
};

void Enemy::patrol(float frameTime)
{
    if (sub_route.size() == 0)
    {
        G_Node<MapChunk> fictional_point(this->route.peek());

        this->device.search(this->location, &fictional_point);
        for (auto point : this->device.obt)
        {
            this->sub_route.enqueue(point->data);
        }
    }
    else if (sub_route.size() > 0)
    {
        auto chunk = this->sub_route.peek();
        this->moveTo(chunk, frameTime);
        if (this->graphY == chunk.coordinates[0] && this->graphX == chunk.coordinates[1])
        {
            this->sub_route.dequeue();
        }
        if (this->graphY == this->route.peek().coordinates[0] && this->graphX == this->route.peek().coordinates[1])
        {
            this->route.enqueue(this->route.dequeue().data);
        }
    }
}

void Enemy::traceback(float frameTime)
{
    if (sub_route.size() == 0)
    {
        this->device.non_weight_search(this->location, this->LastPosition);
        for (auto point : this->device.obt)
        {
            this->sub_route.enqueue(point->data);
        }
    }
    else
    {
        auto chunk = this->sub_route.peek();
        this->moveTo(chunk, frameTime);
        if (graphY == chunk.coordinates[0] && graphX == chunk.coordinates[1])
        {
            this->sub_route.dequeue();
        }
    }
}

void Enemy::engage()
{
    // Clear the sub route if there was any queued chunks to visit
    while (this->sub_route.size() > 0)
    {
        this->sub_route.dequeue();
    }

    // Change the pointer to the location of entity before engaging
    this->LastPosition = this->location;
    // Change conditions
    this->engaging = true;
    this->returning = false;
    this->routing = false;
};

void Enemy::disengage()
{
    this->setTarget(nullptr);
    this->engaging = false;
    this->returning = true;
    this->routing = false;
}

void Enemy::setTarget(Entity *entity)
{
    this->target = entity;
};

bool Enemy::rangeToEntity(Entity *entity, bool attacking)
{
    int range = this->attributes.range[1] * 40;
    if (attacking)
    {
        range = 15;
    }
    Vector2 other = entity->getPosition();
    Vector2 current = this->getPosition();
    // [ VALIDATION IN X ]
    bool conditionX = (other.x < current.x + range) && (other.x > current.x - range);
    // [ VALIDATION IN Y ]
    bool conditionY = (other.y < current.y + range) && (other.y > current.y - range);

    return conditionX && conditionY;
};

void Enemy::moveTo(MapChunk &newMapChunk, float frameTime)
{
    if (this->getPosition().x < newMapChunk.center().x - 20.0f)
    {
        this->move(frameTime, Entity::mvRight);
    }

    if (this->getPosition().x > newMapChunk.center().x + 20.0f)
    {
        this->move(frameTime, Entity::mvLeft);
    }

    if (this->getPosition().y < newMapChunk.center().y - 20.0f)
    {
        this->move(frameTime, Entity::mvDown);
    }

    if (this->getPosition().y > newMapChunk.center().y + 20.0f)
    {
        this->move(frameTime, Entity::mvUp);
    }
}

void Enemy::generateRoute(Map2D *map)
{
    int site[] = {this->graphY, this->graphX};
    int offset = this->attributes.distance[1];
    for (int i = 0; i < this->attributes.route_size[1]; i++)
    {
        int displacement[] = {random.gen(site[0] - offset, site[0] + offset), random.gen(site[1] - offset, site[1] + offset)};
        // Horizontal verifications
        if (displacement[0] >= map->grid_size[0] - 1)
        {
            displacement[0] = map->grid_size[0] - 2;
        }
        else if (displacement[0] < 1)
        {
            displacement[0] = 1;
        }
        // Vertical verifications
        if (displacement[1] >= map->grid_size[1] - 1)
        {
            displacement[1] = map->grid_size[1] - 2;
        }
        else if (displacement[1] < 1)
        {
            displacement[1] = 1;
        }
        // Verify route is not wall
        MapChunk chunk_to_add = map->get(displacement[0], displacement[1]);
        int variation[] = {displacement[0], displacement[1]};
        while (chunk_to_add.chunk_type == ChunkType::wall || chunk_to_add.chunk_type == ChunkType::fake)
        {
            int move_where = random.gen(0, 1);
            if (move_where == 0)
            { // Move vertical units
                if (displacement[0] == 1)
                {
                    variation[0] += 1;
                }
                else if (displacement[0] == map->grid_size[0] - 2)
                {
                    variation[0] -= 1;
                }
                else
                {
                    int dir = random.gen(0, 1);
                    if (dir == 0)
                    {
                        variation[1] -= 1;
                    }
                    else
                    {
                        variation[1] += 1;
                    }
                }
            }
            else if (move_where == 1)
            { // Mover horizontal units
                if (displacement[1] == 1)
                {
                    variation[1] += 1;
                }
                else if (displacement[0] == map->grid_size[1] - 2)
                {
                    variation[1] -= 1;
                }
                else
                {
                    int dir = random.gen(0, 1);
                    if (dir == 0)
                    {
                        variation[1] -= 1;
                    }
                    else
                    {
                        variation[1] += 1;
                    }
                }
            }
            chunk_to_add = map->get(variation[0], variation[1]);
        }
        // Add point to route
        this->route.enqueue(chunk_to_add);
    }
    this->route.enqueue(this->location->data);
}
