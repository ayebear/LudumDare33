// Copyright (C) 2015 Eric Hebert (ayebear)
// This code is licensed under GPLv3, see LICENSE.txt for details.

#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>
#include <vector>
#include <set>
#include <SFML/Graphics.hpp>
#include "nage/graphics/animatedsprite.h"
#include "nage/graphics/spriteloader.h"
#include "nage/graphics/colorcode.h"
#include "es/component.h"
#include "es/serialize.h"
#include "es/internal/id.h"

struct Position: public es::Component
{
    static constexpr auto name = "Position";

    float x, y;

    Position(float x = 0, float y = 0): x{x}, y{y} {}

    void load(const std::string& str)
    {
        es::unpack(str, x, y);
    }

    std::string save() const
    {
        return es::pack(x, y);
    }
};

struct Velocity: public es::Component
{
    static constexpr auto name = "Velocity";

    float x, y;

    Velocity(float x = 0, float y = 0): x{x}, y{y} {}

    void load(const std::string& str)
    {
        es::unpack(str, x, y);
    }

    std::string save() const
    {
        return es::pack(x, y);
    }
};

struct Size: public es::Component
{
    static constexpr auto name = "Size";

    float x, y;

    Size(float x = 0, float y = 0): x{x}, y{y} {}

    void load(const std::string& str)
    {
        es::unpack(str, x, y);
    }

    std::string save() const
    {
        return es::pack(x, y);
    }
};

// The axis-aligned bounding box, used for collisions
struct AABB: public es::Component
{
    static constexpr auto name = "AABB";

    sf::FloatRect rect; // The actual AABB. Note: This has the relative position of the AABB,
        // which is (0, 0) in a lot of cases. You need to add the object's position to get
        // a bounding box with its global position. The reason for this is so the AABB
        // component does not change when the object moves around.

    std::vector<es::ID> collisions; // Entity IDs currently colliding with

    void load(const std::string& str)
    {
        es::unpack(str, rect.left, rect.top, rect.width, rect.height);
    }

    std::string save() const
    {
        return es::pack(rect.left, rect.top, rect.width, rect.height);
    }

    // Returns a global AABB based on a position
    sf::FloatRect getGlobalBounds(Position* position = nullptr)
    {
        if (position)
        {
            // Add the position to the position of the AABB
            sf::FloatRect tempAABB(rect);
            tempAABB.left += position->x;
            tempAABB.top += position->y;
            return tempAABB;
        }

        // When the position component is not specified, the original AABB will be returned.
        return rect;
    }
};

// Circular bounding area
struct CBA: public es::Component
{
    static constexpr auto name = "CBA";

    float radius{0.0f};
};

struct Sprite: public es::Component
{
    static constexpr auto name = "Sprite";

    sf::Sprite sprite;
    std::string filename;
    bool visible{true};

    void load(const std::string& str)
    {
        auto values = strlib::split(str, " ");
        values.resize(2);
        filename = values.front();
        visible = (values.back().empty() || strlib::strToBool(values.back()));
        ng::SpriteLoader::load(sprite, filename, true);
    }

    std::string save() const
    {
        auto str = filename;
        if (!visible)
            str += " false";
        return str;
    }
};

struct CircleShape: public es::Component
{
    static constexpr auto name = "CircleShape";

    sf::CircleShape shape;
    ng::ColorCode fillColor;
    ng::ColorCode outlineColor;

    void load(const std::string& str)
    {
        float radius;
        size_t pointCount;
        std::string fillColorStr;
        std::string outlineColorStr;
        float outlineThickness;
        es::unpack(str, radius, pointCount, fillColorStr, outlineColorStr, outlineThickness);
        fillColor = fillColorStr;
        outlineColor = outlineColorStr;
        shape.setRadius(radius);
        shape.setPointCount(pointCount);
        shape.setFillColor(fillColor.toColor());
        shape.setOutlineColor(outlineColor.toColor());
        shape.setOutlineThickness(outlineThickness);
        updateOriginPoint();
    }

    std::string save() const
    {
        float radius = shape.getRadius();
        size_t pointCount = shape.getPointCount();
        float outlineThickness = shape.getOutlineThickness();
        return es::pack(radius, pointCount, fillColor.toString(), outlineColor.toString(), outlineThickness);
    }

    void updateOriginPoint()
    {
        // Center the origin point
        float radius = shape.getRadius();
        shape.setOrigin(radius, radius);
    }
};

struct RectangleShape: public es::Component
{
    static constexpr auto name = "RectangleShape";

    sf::RectangleShape shape;

    void load(const std::string& str)
    {
        float width;
        float height;
        std::string fillColor;
        std::string outlineColor;
        float outlineThickness;
        es::unpack(str, width, height, fillColor, outlineColor, outlineThickness);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(ng::ColorCode(fillColor).toColor());
        shape.setOutlineColor(ng::ColorCode(outlineColor).toColor());
        shape.setOutlineThickness(outlineThickness);
    }

    std::string save() const
    {
        auto size = shape.getSize();
        std::string fillColor = ng::ColorCode(shape.getFillColor()).toString();
        std::string outlineColor = ng::ColorCode(shape.getOutlineColor()).toString();
        float outlineThickness = shape.getOutlineThickness();
        return es::pack(size.x, size.y, fillColor, outlineColor, outlineThickness);
    }
};

struct Selectable: public es::Component
{
    static constexpr auto name = "Selectable";

    bool selected{false};
    std::string prototype; // Which prototype name to clone for highlighting
    es::ID id{0}; // Entity ID of highlighting

    void load(const std::string& str)
    {
        es::unpack(str, selected, prototype);
    }

    std::string save() const
    {
        return es::pack(selected, prototype);
    }

    void reset()
    {
        selected = false;
        id = 0;
    }
};

// Like Size, but for circular entities
struct Radius: public es::Component
{
    static constexpr auto name = "Radius";

    float radius{1.0f};

    void load(const std::string& str)
    {
        es::unpack(str, radius);
    }

    std::string save() const
    {
        return es::pack(radius);
    }
};

// Implies that the entity is damageable
// Max is a soft limit, current can go over (so cells can duplicate)
struct Health: public es::Component
{
    static constexpr auto name = "Health";

    float current{0.0f};
    float max{0.0f};

    void load(const std::string& str)
    {
        es::unpack(str, current, max);
    }

    std::string save() const
    {
        return es::pack(current, max);
    }

    void change(float amount)
    {
        current += amount;
        if (current > max)
            current = max;
    }
};

// How much health is reduced per second
struct Damager: public es::Component
{
    static constexpr auto name = "Damager";

    float amount{0.0f}; // Damage per second
    float lifeSteal{0.0f}; // Health regen % of damage per second

    void load(const std::string& str)
    {
        es::unpack(str, amount, lifeSteal);
    }

    std::string save() const
    {
        return es::pack(amount, lifeSteal);
    }
};

// Used as max speed (velocity contains current speed and direction)
struct Speed: public es::Component
{
    static constexpr auto name = "Speed";

    float speed{0.0f};

    void load(const std::string& str)
    {
        es::unpack(str, speed);
    }

    std::string save() const
    {
        return es::pack(speed);
    }
};

// How much per second the radius changes
struct RadiusRegen: public es::Component
{
    static constexpr auto name = "RadiusRegen";

    float amount{0.0f};

    void load(const std::string& str)
    {
        es::unpack(str, amount);
    }

    std::string save() const
    {
        return es::pack(amount);
    }
};

// How much per second the health changes
struct HealthRegen: public es::Component
{
    static constexpr auto name = "HealthRegen";

    float amount{0.0f};

    void load(const std::string& str)
    {
        es::unpack(str, amount);
    }

    std::string save() const
    {
        return es::pack(amount);
    }
};

// Stores player ID of entity (for use with damager component)
struct Player: public es::Component
{
    static constexpr auto name = "Player";

    int id{0};

    void load(const std::string& str)
    {
        es::unpack(str, id);
    }

    std::string save() const
    {
        return es::pack(id);
    }
};

// A point that the entity will move to, based on the speed
struct Destination: public es::Component
{
    static constexpr auto name = "Destination";

    float x, y;

    Destination(float x = 0, float y = 0): x(x), y(y) {}

    void load(const std::string& str)
    {
        es::unpack(str, x, y);
    }

    std::string save() const
    {
        return es::pack(x, y);
    }
};

struct ZIndex: public es::Component
{
    static constexpr auto name = "ZIndex";

    int layer;

    ZIndex(int layer = 0): layer(layer) {}

    void load(const std::string& str)
    {
        es::unpack(str, layer);
    }

    std::string save() const
    {
        return es::pack(layer);
    }
};

struct Follower: public es::Component
{
    static constexpr auto name = "Follower";

    int id;

    Follower(int id = 0): id(id) {}

    void load(const std::string& str)
    {
        es::unpack(str, id);
    }

    std::string save() const
    {
        return es::pack(id);
    }
};

struct Splittable: public es::Component
{
    static constexpr auto name = "Splittable";

    float splitAtRadius{100.0f};
    float radiusMultiplier{1.5f};

    void load(const std::string& str)
    {
        es::unpack(str, splitAtRadius, radiusMultiplier);
    }

    std::string save() const
    {
        return es::pack(splitAtRadius, radiusMultiplier);
    }
};

// TODO: Add Rotation


// COMPONENT FLAGS

// If an entity has this component, it can select other entities
struct Selector: public es::Component
{
    static constexpr auto name = "Selector";
};

// Means an entity is the actual highlighted selection
struct Selection: public es::Component
{
    static constexpr auto name = "Selection";
};

// Health affects speed (initially for viruses)
struct HealthAffectsSpeed: public es::Component
{
    static constexpr auto name = "HealthAffectsSpeed";
};

// Health affects color, max health affects radius
struct CellProperties: public es::Component
{
    static constexpr auto name = "CellProperties";
};

#endif
