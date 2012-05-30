#include "Level.h"
#include <cstdio>
#include <iostream>
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"
#include <cmath>
#include <cstdlib>
#include <time.h>
#include "Spell.h"
#include "SpellEvent.h"
#include <queue>
#include "Utils.h"
#include "ChangePlayerEvent.h"



point dirs[] = {point(-1, 0), point(0, 1), point(1, 0), point(0, -1)};

Level::Level(Context const& c): DisplayObject(c),
                                m_camera_moved(false),
                                m_reset_camera(false)  {
    m_keys[Keyboard::Up] = false;
    m_keys[Keyboard::Right] = false;
    m_keys[Keyboard::Down] = false;
    m_keys[Keyboard::Left] = false;

    m_spell_handlers[SpellType::magic_bullet] = &Level::magicBullet;
    m_spell_handlers[SpellType::build_wall] = &Level::buildWall;
    m_spell_handlers[SpellType::mind_control] = &Level::mindControl;

    m_render_behaviour = new ContainerRenderBehaviour(m_children);
    m_size_behaviour = new ContainerSizeBehaviour(m_children);

    setBounds(new Rectangle(0, 0, m_context.screen_width - 250, m_context.screen_height));
                                }

void Level::loadFromFile(std::string filename) {
    FILE *file = NULL;

    file = fopen(filename.c_str(), "r");

    fscanf(file, "%d", &m_level_width);
    m_level_height = m_level_width;

    for (int i = 0; i < m_level_height; ++i) {
        m_data.push_back(std::vector<int>());
        m_destroyed.push_back(std::vector<int>());
        m_scents.push_back(std::vector<float>());
        for (int j = 0; j < m_level_width; ++j) {
            int block = 0;
            fscanf(file, "%d", &block);
            m_data.at(i).push_back(block);
            m_destroyed.at(i).push_back(0);
            m_scents.at(i).push_back(0.0f);
        }
        fscanf(file, "\n");
    }

    fclose(file);

    initData();

}

void Level::initData() {

    Sprite* floor = new Sprite(m_context, "floor.png");
    floor->setSize(m_level_width * m_context.TILE_SIZE, m_level_height * m_context.TILE_SIZE);
    floor->setScale(m_context.DEFAULT_SCALE);
    floor->setZ(-1);
    addChild(floor);

    for (unsigned int i = 0; i < m_data.size(); ++i) {
        for (unsigned int j = 0; j < m_data.at(i).size(); ++j) {
            Tile* tile = new Tile(m_context, "tileset2.png", "tileset2-shadows.png", i, j, m_data, m_destroyed, m_scents);
            tile->setScale(m_context.DEFAULT_SCALE);
            tile->setPosition(j * tile->width() * tile->scaleX(), i * tile->height() * tile->scaleY());
            addChild(tile);
            m_tiles.push_back(tile);
        }
    }

    for (unsigned int i = 0; i < m_data.size(); ++i) {
        for (unsigned int j = 0; j < m_data.at(i).size(); ++j) {
            std::vector<Tile*> neighbours;
            if (j > 0) {
                neighbours.push_back(m_tiles.at(j - 1 + i * m_data.at(i).size()));
            }
            if (j < m_data.at(i).size() - 1) {
                neighbours.push_back(m_tiles.at(j + 1 + i * m_data.at(i).size()));
            }
            if (i > 0) {
                neighbours.push_back(m_tiles.at(j + (i - 1) * m_data.at(i).size()));
            }
            if (i < m_data.size() - 1) {
                neighbours.push_back(m_tiles.at(j + (i + 1) * m_data.at(i).size()));
            }

            m_tiles.at(j + i * m_data.at(i).size())->setNeighbours(neighbours);
        }
    }

}

void Level::setPlayers(std::vector<Hero*>* players) {
    m_players = players;
}

void Level::spawnNpcs(int count) {
    srand ( time(NULL) );
    std::set<std::pair<int, int> > marked;
    for (int i = 0; i < count; ++i) {
        Npc* npc = new Npc(m_context, 10, m_data);

        int row = 0;
        int col = 0;
        do {
            row = rand() % m_data.size();
            col = rand() % m_data.at(0).size();
        } while (m_data.at(row).at(col) == 1 || marked.find(std::make_pair(row, col)) != marked.end());

        marked.insert(std::make_pair(row, col));
        npc->setPosition(m_context.TILE_SIZE * col, m_context.TILE_SIZE * row);
        npc->animate(Animations::idle);
        m_npcs.push_back(npc);
        addChild(npc);
    }

}

std::vector<std::vector<int> > const& Level::getData() {
    return m_data;
}

Character* Level::currentPlayer() const {
    return m_current_player;
}


void Level::tick(float dt) {
    float dx = 0;
    float dy = 0;
    float diff = dt / 1000.0f * 512.0f;
    if (m_keys.at(Keyboard::Right)) {
        dx -= diff;
    }
    if (m_keys.at(Keyboard::Left)) {
        dx += diff;
    }
    if (m_keys.at(Keyboard::Down)) {
        dy -= diff;
    }
    if (m_keys.at(Keyboard::Up)) {
        dy += diff;
    }

    if (m_x + dx <= 0 && m_x + dx >= m_context.screen_width - m_level_width * m_context.TILE_SIZE) {
        m_x += dx;
    }
    if (m_y + dy <= 0 && m_y + dy >= m_context.screen_height - m_level_height * m_context.TILE_SIZE) {
        m_y += dy;
    }

    for (int i = 0; i < m_tiles.size(); ++i) {
        int row = m_tiles.at(i)->row();
        int col = m_tiles.at(i)->column();
        bool visible = m_current_player->isTileVisible(row, col);
        m_tiles.at(i)->setVisible(visible);
        //    m_tiles.at(i)->setDarknessOffset(m_hero->getTileOffset());
    }

    for (int i = 0; i < m_children.size(); ++i) {
        m_children.at(i)->tick(dt);
    }


    if ((m_current_player->isMoving() || m_reset_camera) && !m_camera_moved) {
        moveCamera(dt);
    }
    else if (!m_current_player->isMoving()) {
        m_camera_moved = false;
    }

    computeScents();
}

void Level::setCurrentPlayer(Character* player) {
    m_current_player = player;
    m_current_player->addEventListener(ET::spell, this, static_cast<Listener>(&Level::onSpellCasted));
    m_current_player->addEventListener(ET::open_chest, this, static_cast<Listener>(&Level::onChestOpened));
    resetCamera();
}

void Level::resetCamera() {
    m_reset_camera = true;
}

bool Level::inRangedSpellRange(int spellX, int spellY, int x, int y, int range) {
    int dx = spellX - x;
    if (dx < 0) {
        dx *= -1;
    }

    int dy = spellY - y;
    if (dy < 0) {
        dy *= -1;
    }

    int dist = dx - dy;
    if (dist < 0) {
        dist *= -1;
    }

    dx = dy = dx > dy ? dy : dx;

    if (!dx % 2) {
        dist += 3 * dx / 2;
    }
    else {
        dist += 3 * (dx - 1) / 2;
        dist++;
    }

    return dist <= range;
}

void Level::fireball(SpellEvent* e) {
    for (int i = 0; i < m_npcs.size(); ++i) {
        if (inRangedSpellRange(e->x(), e->y(), m_npcs.at(i)->col(), m_npcs.at(i)->row(), 3)) {
            m_npcs.at(i)->damage(5);
            if (m_npcs.at(i)->health() <= 0) {
                m_npcs.at(i)->die();
                m_npcs.erase(m_npcs.begin() + i);
            }
        }
    }

    for (int i = 0; i < m_tiles.size(); ++i) {
        if (inRangedSpellRange(e->x(), e->y(), m_tiles.at(i)->col(), m_tiles.at(i)->row(), 3)) {
            if (m_tiles.at(i)->parent()) {
                if (m_data.at(e->y()).at(e->x()) == 1) {
                    m_destroyed.at(e->y()).at(e->x()) = 1;
                }
                if (m_tiles.at(i)->onDestroy()) {
                    m_data.at(e->y()).at(e->x()) = 0;
                }
            }
        }
    }
}

void Level::magicBullet(SpellEvent* e) {
    for (int i = 0; i < m_npcs.size(); ++i) {
        if (m_npcs.at(i)->row() == e->y() && m_npcs.at(i)->col() == e->x()) {
            m_npcs.at(i)->damage(5);
            if (m_npcs.at(i)->health() <= 0) {
                m_npcs.at(i)->die();
                m_npcs.erase(m_npcs.begin() + i);
            }
            break;
        }
    }

    for (int i = 0; i < m_tiles.size(); ++i) {
        if (m_tiles.at(i)->row() == e->y() && m_tiles.at(i)->col() == e->x()) {
            if (m_tiles.at(i)->parent()) {
                if (m_data.at(e->y()).at(e->x()) == 1) {
                    m_destroyed.at(e->y()).at(e->x()) = 1;
                }
                if (m_tiles.at(i)->onDestroy()) {
                    m_data.at(e->y()).at(e->x()) = 0;
                }
            }
        }
    }
}

void Level::buildWall(SpellEvent* e) {
    for (int i = 0; i < m_tiles.size(); ++i) {
        if (m_tiles.at(i)->row() == e->y() && m_tiles.at(i)->col() == e->x()) {
            m_destroyed.at(e->y()).at(e->x()) = 0;
            m_data.at(e->y()).at(e->x()) = 1;
            m_tiles.at(i)->rebuild();
        }
    }
}

void Level::mindControl(SpellEvent* e) {
    for (int i = 0; i < m_npcs.size(); ++i) {
        if (m_npcs.at(i)->row() == e->y() && m_npcs.at(i)->col() == e->x()) {
            dispatchEvent(new ChangePlayerEvent(m_npcs.at(i)), this);
            break;
        }
    }
}

void Level::onSpellCasted(GameEventPointer event, EventDispatcher* dispatcher) {
    SpellEvent* e = dynamic_cast<SpellEvent*>(event.get());
    if (e == NULL) {
        m_context.logger->Error("LEVEL.CPP: upcasting spell event failed.");
        return;
    }
    (this->*m_spell_handlers[e->type()])(e);
}

void Level::onChestOpened(GameEventPointer e, EventDispatcher* dispatcher) {
    for (int i = 0; i < m_tiles.size(); ++i) {
        if (m_tiles.at(i)->row() == e->x() && m_tiles.at(i)->col() == e->y()) {
            m_tiles.at(i)->openChest();
        }
    }
}

void Level::moveCamera(float dt) {

    Rectangle* b = bounds();

    float dx = -(m_current_player->x() - b->width / 2) / 2 ;
    if (fabs(dx) > 3) {
        dx *= (dt / 200.0f);
    }

    float x = m_x + dx;
    if (x <= 0 && x >= b->width - m_level_width * m_context.TILE_SIZE) {
        m_x = x;
    }
    else if ( x > 0) {
        m_x = 0;
    }
    else {
        m_x = b->width - m_level_width * m_context.TILE_SIZE;
    }

    float dy = -(m_current_player->y() - b->height / 2) / 2;
    if (fabs(dy) > 3) {
        dy *= dt / 200.0f;
    }
    float y = m_y + dy ;
    if (y <= 0 && y >= b->height - m_level_height * m_context.TILE_SIZE) {
        m_y = y;
    }
    else if (y > 0) {
        m_y = 0;
    }
    else {
        m_y = b->height - m_level_height * m_context.TILE_SIZE;
    }


    float adx = fabs(m_current_player->x() - b->width / 2) / 2;
    float ady = fabs(m_current_player->y() - b->height / 2) / 2;
    if (adx < 1 && ady < 1) {
        m_reset_camera = false;
    }
}



void Level::onEvent(const Event& e) {
    if (e.event_type == EventType::KeyDown || e.event_type == EventType::KeyUp)  {
        Keyboard::KEY key = static_cast<Keyboard::KEY>(e.key_data.key);
        if (m_keys.find(key) != m_keys.end()) {
            m_keys[static_cast<Keyboard::KEY>(e.key_data.key)] = e.key_data.pressed_down;
            m_camera_moved = true;
        }
    }
    else if (e.event_type == EventType::Resize) {
        setBounds(new Rectangle(0, 0, m_context.screen_width - 250, m_context.screen_height));
    }
    else if (e.event_type == EventType::MouseDown) {
        int x = floor((e.mouse_data.x - this->x()) / m_context.TILE_SIZE);
        int y = floor((e.mouse_data.y - this->y()) / m_context.TILE_SIZE);

        for (int i = 0; i < m_tiles.size(); ++i) {
            int row = m_tiles.at(i)->row();
            int col = m_tiles.at(i)->column();
            if (y == row && x == col) {
                Action a = m_tiles.at(i)->action();
                m_current_player->onAction(a);
                break;
            }
        }
    }

    Hero* h = dynamic_cast<Hero*>(m_current_player);
    if (h) {
        h->onEvent(e);
    }
}

void Level::npcTurn() {
    computeScents();

    m_current_npc = 0;
    for (int i = 0; i < m_npcs.size(); ++i) {
        Npc* npc = m_npcs.at(i);
        if (m_scents.at(npc->row()).at(npc->col()) > 0) {
            float max_scent = m_scents.at(npc->row()).at(npc->col());
            point pos = point(npc->row(), npc->col());
            for (int j = 0; j < 4; ++j) {
                if (m_scents.at(npc->row() + dirs[j].first).at(npc->col() + dirs[j].second) > max_scent) {
                    max_scent = m_scents.at(npc->row() + dirs[j].first).at(npc->col() + dirs[j].second);
                    pos = point(npc->row() + dirs[j].first, npc->col() + dirs[j].second);
                }
            }

            if (pos.first != npc->row() || pos.second != npc->col()) {
                m_current_player = npc;
                m_current_npc = i;
                npc->addEventListener(ET::came, this, static_cast<Listener>(&Level::npcCame));
                npc->onAction(Action(Action::WALK, point(pos.first, pos.second)));
                return;
            }
        }
    }

}

void Level::npcCame(GameEventPointer event, EventDispatcher* dispatcher) {
    m_current_player->removeEventListener(ET::came, this, static_cast<Listener>(&Level::npcCame));

    for (int i = m_current_npc + 1; i < m_npcs.size(); ++i) {
        Npc* npc = m_npcs.at(i);
        if (m_scents.at(npc->row()).at(npc->col()) > 0) {
            float max_scent = m_scents.at(npc->row()).at(npc->col());
            point pos = point(npc->row(), npc->col());
            for (int j = 0; j < 4; ++j) {
                if (m_scents.at(npc->row() + dirs[j].first).at(npc->col() + dirs[j].second) > max_scent) {
                    max_scent = m_scents.at(npc->row() + dirs[j].first).at(npc->col() + dirs[j].second);
                    pos = point(npc->row() + dirs[j].first, npc->col() + dirs[j].second);
                }
            }

            if (pos.first != npc->row() || pos.second != npc->col()) {
                m_current_player = npc;
                m_current_npc = i;
                npc->addEventListener(ET::came, this, static_cast<Listener>(&Level::npcCame));
                npc->onAction(Action(Action::WALK, point(pos.first, pos.second)));
                return;
            }
        }
    }


    dispatchEvent(new GameEvent(ET::npc_turn_ended), this);

}

void Level::computeScents() {
    for (int i = 0; i < m_scents.size(); ++i) {
        for (int j = 0; j < m_scents.at(i).size(); ++j) {
            m_scents.at(i).at(j) = 0.0f;
        }
    }

    std::set<point> marked;
    std::queue<point> open_list;

    for (int i = 0; i < m_players->size(); ++i) {
        point p(m_players->at(i)->row(), m_players->at(i)->col());
        open_list.push(p);
        marked.insert(p);
        m_scents.at(p.first).at(p.second) = 1000;
    }

    while (!open_list.empty()) {
        point loc = open_list.front();
        open_list.pop();

        for (int i = 0; i < 4; ++i) {
            point new_loc(loc.first + dirs[i].first, loc.second + dirs[i].second);
            if (marked.find(new_loc) == marked.end() && m_data.at(new_loc.first).at(new_loc.second) == 0) {

                float scent = 0.0f;
                for (int j = 0; j < 4; ++j) {
                    scent += m_scents.at(new_loc.first + dirs[j].first).at(new_loc.second + dirs[j].second);
                }

                scent *= 0.25f;

                if (scent >= 0.1) {
                    marked.insert(new_loc);
                    open_list.push(new_loc);
                    m_scents.at(new_loc.first).at(new_loc.second) = scent;
                }
            }
        }
    }
}


Level::~Level() {
    for (unsigned int i = 0; i < m_children.size(); ++i) {
        delete m_children.at(i);
    }
}
