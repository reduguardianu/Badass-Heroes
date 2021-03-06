#ifndef LEVEL_H__
#define LEVEL_H__

#include <string>
#include <vector>
#include "Context.h"
#include "Sprite.h"
#include <map>
#include <vector>
#include "Event.h"
#include "Texture.h"
#include "Tile.h"
#include "Hero.h"
#include "Npc.h"
#include "Character.h"

class Level;
class SpellEvent;

typedef void(Level::*LevelMethod) (SpellEvent*);

class Level : public DisplayObject  {
public:
    explicit Level(Context const& c);
    void loadFromFile(std::string filename);
    void tick(float dt);
    void onEvent(const Event& e);
    ~Level();
    std::vector<std::vector<int> > const& getData();

    void setCurrentPlayer(Character* player);
    void spawnNpcs(int count);
    void setPlayers(std::vector<Hero*>* players);
    void npcTurn();
    Character* currentPlayer() const;
private:
    void initData();
    void moveCamera(float dt);
    void onSpellCasted(GameEventPointer e, EventDispatcher* dispatcher);
    void onChestOpened(GameEventPointer e, EventDispatcher* dispatcher);
    void resetCamera();
    void computeScents();
    void npcCame(GameEventPointer, EventDispatcher* dispatcher);
    void magicBullet(SpellEvent* e);
    void buildWall(SpellEvent* e);
    void mindControl(SpellEvent* e);
    void fireball(SpellEvent* e);
    bool inRangedSpellRange(int spellX, int spellY, int x, int y, int range);
private:
    std::vector<std::vector<int> > m_data;
    std::vector<std::vector<int> > m_destroyed;
    std::map<Keyboard::KEY, bool> m_keys;
    std::map<std::string, LevelMethod> m_spell_handlers;
    std::vector<Tile*> m_tiles;
    int m_level_width;
    int m_level_height;
    Character* m_current_player;
    bool m_camera_moved;
    bool m_reset_camera;
    std::vector<Npc*> m_npcs;
    std::vector<std::vector<float> > m_scents;
    std::vector<Hero*>* m_players;
    int m_current_npc;
};

#endif
