#include "Tile.h"
#include <cstdlib>
#include "AnimatedSprite.h"
#include <algorithm>
#include <sstream>

Tile::Tile(Context const& c,
           std::string textureName,
           std::string shadowTexture,
           int row,
           int column,
           std::vector<std::vector<int> > const& map,
           std::vector<std::vector<int> > const& destroyed,
           std::vector<std::vector<float> > const& scents): Sprite(c, textureName),
                                                            m_row(row),
                                                            m_column(column),
                                                            m_map(map),
                                                            m_visible(false),
                                                            m_shadow(NULL),
                                                            m_darkness(NULL),
                                                            m_destroyed(destroyed),
                                                            m_torch(NULL),
                                                            m_dead(NULL),
                                                            m_chest(NULL),
                                                            m_action(NULL),
                                                            m_up(1),
                                                            m_right(1),
                                                            m_down(1),
                                                            m_left(1),
                                                            m_memory_up(0),
                                                            m_memory_right(0),
                                                            m_memory_down(0),
                                                            m_memory_left(0),
                                                            m_scents(scents) {

    if (shadowTexture.size()) {
        m_shadow = new Sprite(m_context, shadowTexture);
        m_shadow->setSize(32, 64);
        m_shadow->setParent(this);
        m_shadow->setScale(m_context.DEFAULT_SCALE);
    }
    m_frame->setSize(32, 32);
    float tw = m_frame->textureWidth();
    float th = m_frame->textureHeight();
    m_uvs[0][1][1][0] = std::make_pair(0, 0);
    m_uvs[0][0][1][1] = std::make_pair(32 / tw, 0);
    m_uvs[1][0][0][1] = std::make_pair(64 / tw, 0);
    m_uvs[1][1][0][0] = std::make_pair(96 / tw, 0);
    m_uvs[0][1][0][1] = std::make_pair(0, 32 / th);
    m_uvs[1][0][1][0] = std::make_pair(32 / tw, 32 / th);

    m_uvs[1][1][1][0] = std::make_pair(64 / tw, 32 / th);
    m_uvs[0][1][1][1] = std::make_pair(96 / tw, 32 / th);
    m_uvs[1][0][1][1] = std::make_pair(0, 64 / th);
    m_uvs[1][1][0][1] = std::make_pair(32 / tw, 64 / th);

    m_uvs[0][0][0][1] = std::make_pair(64 / tw, 64 / th);
    m_uvs[1][0][0][0] = std::make_pair(96 / tw, 64 / th);
    m_uvs[0][1][0][0] = std::make_pair(0, 96 / th);
    m_uvs[0][0][1][0] = std::make_pair(32 / tw, 96 / th);

    m_uvs[1][1][1][1] = std::make_pair(64 / tw, 96 / th);
    m_uvs[0][0][0][0] = std::make_pair(0, 160 / th);


    m_destroyed_up = new Sprite(m_context, textureName);
    m_destroyed_up->setUV(32 / tw, 128 / th);
    m_destroyed_up->setSize(32, 32);
    m_destroyed_up->setParent(this);
    m_destroyed_up->setScale(m_context.DEFAULT_SCALE);

    m_destroyed_right = new Sprite(m_context, textureName);
    m_destroyed_right->setUV(96 / tw, 96 / th);
    m_destroyed_right->setSize(32, 32);
    m_destroyed_right->setParent(this);
    m_destroyed_right->setScale(m_context.DEFAULT_SCALE);

    m_destroyed_down = new Sprite(m_context, textureName);
    m_destroyed_down->setUV(64 / tw, 128 / th);
    m_destroyed_down->setSize(32, 32);
    m_destroyed_down->setParent(this);
    m_destroyed_down->setScale(m_context.DEFAULT_SCALE);

    m_destroyed_left = new Sprite(m_context, textureName);
    m_destroyed_left->setUV(0 / tw, 128 / th);
    m_destroyed_left->setSize(32, 32);
    m_destroyed_left->setParent(this);
    m_destroyed_left->setScale(m_context.DEFAULT_SCALE);


    tw = m_shadow->textureWidth();
    th = m_shadow->textureHeight();
    m_shadow_uvs[0][1][1][0] = std::make_pair(0, 0);
    m_shadow_uvs[0][0][1][1] = std::make_pair(32 / tw, 0);
    m_shadow_uvs[1][0][0][1] = std::make_pair(64 / tw, 0);
    m_shadow_uvs[1][1][0][0] = std::make_pair(96 / tw, 0);
    m_shadow_uvs[0][1][0][1] = std::make_pair(0, 64 / th);
    m_shadow_uvs[1][0][1][0] = std::make_pair(32 / tw, 64 / th);

    m_shadow_uvs[1][1][1][0] = std::make_pair(64 / tw, 64 / th);
    m_shadow_uvs[0][1][1][1] = std::make_pair(96 / tw, 64 / th);
    m_shadow_uvs[1][0][1][1] = std::make_pair(0, 128 / th);
    m_shadow_uvs[1][1][0][1] = std::make_pair(32 / tw, 128 / th);

    m_shadow_uvs[0][0][0][1] = std::make_pair(64 / tw, 128 / th);
    m_shadow_uvs[1][0][0][0] = std::make_pair(96 / tw, 128 / th);
    m_shadow_uvs[0][1][0][0] = std::make_pair(0, 192 / th);
    m_shadow_uvs[0][0][1][0] = std::make_pair(32 / tw, 192 / th);

    m_shadow_uvs[1][1][1][1] = std::make_pair(64 / tw, 192 / th);
    // m_shadow_uvs[0][0][0][0] = std::make_pair(0, 320 / th);


    m_darkness = new Sprite(m_context, "darkness.png");
    m_darkness->setParent(this);
    m_darkness->setScale(m_context.DEFAULT_SCALE);
    m_darkness->setZ(1.0f);

    if (m_map.at(m_row).at(m_column) == 1 && horizontal() && rand() % 10 == 0) {
        m_torch = new AnimatedSprite(m_context, "torch");
        dynamic_cast<AnimatedSprite*>(m_torch)->animate(Animations::idle);
        m_torch->setParent(this);

    }
    else if (m_map.at(m_row).at(m_column) == 0 && rand() % 20 == 0) {
        m_chest = new Chest(m_context);
        m_chest->setParent(this);
    }

    if (m_chest) {
        m_action = new Action(Action::OPEN_CHEST, point(m_row, m_column));
    }
    else {
        m_action = new Action(Action::WALK, point(m_row, m_column));
    }

    rebuild();
                                                            }

void Tile::rebuild() {

    m_memory_up = map_up();
    m_memory_right = map_right();
    m_memory_down = map_down();
    m_memory_left = map_left();

}

void Tile::openChest() {
    if (m_chest) {
        m_chest->open();
        delete m_action;
        m_action = new Action(Action::WALK, point(m_row, m_column));
    }
    else {
        m_context.logger->Error("Tried to open chest on tile with no chest.");
    }
}

Action Tile::action() {
    return *m_action;
}

bool Tile::horizontal() {
    return !(map_up() || map_down());
}

void Tile::setVisible(bool value) {
    m_visible = value;
}

int Tile::row() const {
    return m_row;
}

int Tile::column() const {
    return m_column;
}

bool Tile::left() {
    int c = m_column - 1;
    if (c < 0) {
        return 0;
    }

    m_memory_left = std::max(m_memory_left, m_map.at(m_row).at(c));
  
    return m_memory_left;
}

bool Tile::right() {
    int c = m_column + 1;
    if (c >= m_map.at(m_row).size()) {
        return 0;
    }
  
    m_memory_right = std::max(m_memory_right, m_map.at(m_row).at(c));
    return m_memory_right;
}

bool Tile::up() {
    int r = m_row - 1;
    if (r < 0) {
        return 0;
    }

    m_memory_up = std::max(m_memory_up, m_map.at(r).at(m_column));
    return m_memory_up;
}

bool Tile::down() {
    int r = m_row + 1;
    if (r >= m_map.size()) {
        return 0;
    }

    m_memory_down = std::max(m_memory_down, m_map.at(r).at(m_column));
    return m_memory_down;
}

bool Tile::map_left() {
    int c = m_column - 1;
    if (c < 0) {
        return 0;
    }

    m_left = std::min(m_left, m_map.at(m_row).at(c));
    return m_left;
}

bool Tile::map_right() {
    int c = m_column + 1;
    if (c >= m_map.at(m_row).size()) {
        return 0;
    }

    m_right = std::min(m_right, m_map.at(m_row).at(c));
    return m_right;
}

bool Tile::map_up() {
    int r = m_row - 1;
    if (r < 0) {
        return 0;
    }

    m_up = std::min(m_up, m_map.at(r).at(m_column));
    return m_up;;
}

bool Tile::map_down() {
    int r = m_row + 1;
    if (r >= m_map.size()) {
        return 0;
    }

    m_down = std::min(m_down, m_map.at(r).at(m_column));
    return m_down;
}


void Tile::setDarknessOffset(point p) {
    m_darkness->setPosition(p.first, p.second);
}

void Tile::setNeighbours(std::vector<Tile*> neighbours) {
    m_neighbours = neighbours;
}

bool Tile::destroyed() const {
    return m_destroyed.at(row()).at(column());
}

bool Tile::visible() const {
    return m_visible;
}

void Tile::render() {

    if (m_map.at(m_row).at(m_column) == 1) {
        if (m_shadow) {
            m_shadow->render();
        }
        Sprite::render();
    }
    else if (destroyed()) {
        if (map_up()) {
            m_destroyed_up->render();
        }
        if (map_right()) {
            m_destroyed_right->render();
        }
        if (map_down()) {
            m_destroyed_down->render();
        }
        if (map_left()) {
            m_destroyed_left->render();
        }
    }
    if (m_torch && !destroyed()) {
        m_torch->render();
    }
    if (m_dead) {
        m_dead->render();
    }
    if (m_chest) {
        m_chest->render();
    }

    if (!m_visible) {
        bool onBorder = false;
        for (int i = 0; i < m_neighbours.size(); ++i) {
            onBorder = (onBorder || m_neighbours.at(i)->visible());
        }

        if (onBorder) {
            m_darkness->setAlpha(0.7f);
        }
        else {
            m_darkness->setAlpha(1.0f);
        }
        m_darkness->render();
    }


}

void Tile::tick(float dt) {
    if (m_map.at(m_row).at(m_column) == 1) {
        std::pair<float, float> coord = m_uvs[up()][right()][down()][left()];
        std::pair<float, float> shadow_coord = m_shadow_uvs[up()][right()][down()][left()];

        if (m_shadow) {
            m_shadow->setUV(shadow_coord.first, shadow_coord.second);
        }
        m_frame->setUV(coord.first, coord.second);
    }

    if (m_torch && !destroyed()) {
        m_torch->tick(dt);
    }
    if (m_dead) {
        m_dead->tick(dt);
    }
    if (m_chest) {
        m_chest->tick(dt);
    }

}

bool Tile::onDestroy() {
    if (isOnBorder())
    {
        return false;
    }
    m_up = 1;
    m_right = 1;
    m_down = 1;
    m_left = 1;


    AnimatedSprite* dead = new AnimatedSprite(m_context, "walldead");
    dead->animate(Animations::dead, 1);
    dead->setParent(this);
    m_dead = dead;
    m_dead->addEventListener("animationfinish", this, static_cast<Listener>(&Tile::onDestroyed));
    return true;
}

void Tile::onDestroyed(GameEventPointer e, EventDispatcher* dispatcher) {
    if (m_dead && m_dead->parent()) {
        delete m_dead;
        m_dead = NULL;
    }
}
