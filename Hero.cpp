#include "Hero.h"
#include "AnimatedSprite.h"
#include "ContainerRenderBehaviour.h"
#include "ContainerSizeBehaviour.h"
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "Utils.h"
#include "Spell.h"

point directions[] = {point(-1, 0), point(0, 1), point(1, 0), point(0, -1)};

Hero::Hero(Context const& c, std::vector<std::vector<int> > const& map, std::string headgear, std::string breastplate, std::string pants): DisplayObject(c),
																	   m_map(map),
																	   m_path(NULL),
																	   m_state(State::Walk),
																	   m_last_point(-1, -1) {
  initVisibleTiles(m_map);

  m_sprites.push_back(new AnimatedSprite(c, "base"));
  m_sprites.push_back(new AnimatedSprite(c, pants));
  m_sprites.push_back(new AnimatedSprite(c, breastplate));
  m_sprites.push_back(new AnimatedSprite(c, headgear));

  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->setParent(this);
  }

  m_render_behaviour = new ContainerRenderBehaviour(m_sprites);
  m_size_behaviour = new ContainerSizeBehaviour(m_sprites);

}

void Hero::initVisibleTiles(std::vector<std::vector<int> > const& map) {
  for (int i = 0; i < m_map.size(); ++i) {
    m_seen.push_back(std::vector<bool>());
    for (int j = 0; j < m_map.at(i).size(); ++j) {
      m_seen.at(i).push_back(false);
    }
  }
}

bool Hero::isTileVisible(int row, int col) const {
  return (m_visible.find(point(col, row)) != m_visible.end());
}

void Hero::animate(std::string dir) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->animate(dir);
  }
}

void Hero::stop() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    AnimatedSprite* as = dynamic_cast<AnimatedSprite*>(m_sprites.at(i));
    as->stop();
    as->setDirection(Animations::down);
  }
  
}

int Hero::posToTile(float p) const {
  return floor(p / m_context.TILE_SIZE);
}

void Hero::gotoFrame(int frame, int time) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    AnimatedSprite* as = dynamic_cast<AnimatedSprite*>(m_sprites.at(i));
    as->gotoFrame(frame, time);
  }
}

int Hero::tileDistance(point const& a, point const& b) const {
  return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
  // taxi metric
  // return abs(a.first - b.first) + abs(a.second - b.second);
}

void Hero::findVisibleTiles() {

  m_visible.clear();
  std::set<point> marked;
  std::queue<point> open_list;

  point start(posToTile(m_x), posToTile(m_y));
  open_list.push(start);

  while (!open_list.empty()) {
    point loc = open_list.front();
    open_list.pop();

    if (tileDistance(start, loc) < 5) {
      m_seen.at(loc.second).at(loc.first) = true;
      m_visible.insert(loc);
    }

    for (int i = 0; i < 4; ++i) {
      point new_loc(loc.first + directions[i].first, loc.second + directions[i].second);
      if (new_loc.first >= 0 && new_loc.first < m_seen.size() && new_loc.second >= 0 && new_loc.second < m_seen.at(0).size()) {
	if (tileDistance(start, new_loc) < 5 && marked.find(new_loc) == marked.end()) {
	  open_list.push(new_loc);
	  marked.insert(new_loc);
	}
      }
    }

  }

}

void Hero::tick(float dt) {
  
  if (m_path && m_path->size()) {
    point dest = m_path->front();

    point diff = Utils::getPositionDiff(point(m_x, m_y), point(dest.first * m_context.TILE_SIZE, dest.second * m_context.TILE_SIZE), dt);

    m_x += diff.first;
    m_y += diff.second;

    float dx = dest.first * m_context.TILE_SIZE - m_x;
    float dy = dest.second * m_context.TILE_SIZE - m_y;
    if (abs(dx) < 1 && abs(dy) < 1) {
      m_x = dest.first * m_context.TILE_SIZE;
      m_y = dest.second * m_context.TILE_SIZE;
      m_path->pop_front();
    }
    else {
      if (diff.first < 0) {
	animate(Animations::left);
      }
      else if (diff.first > 0) {
	animate(Animations::right);
      }
      else if (diff.second > 0) {
	animate(Animations::down);
      }
      else if (diff.second < 0) {
	animate(Animations::up);
      }
	
    }

  }
  else {
    stop();
  }

  findVisibleTiles();

  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->tick(dt);
  }

}

void Hero::onEvent(const Event& e) {
  if (e.event_type == EventType::MouseDown) {
    int x = floor((e.mouse_data.x - m_parent->x()) / m_context.TILE_SIZE);
    int y = floor((e.mouse_data.y - m_parent->y()) / m_context.TILE_SIZE);

    if (m_state == State::Walk) {
      std::deque<point>* path = findPath(x, y);
      if (path->size() > 0) {
	if (m_path) {
	  delete m_path;
	}
	clearGuidePath();
	m_path = path;
      }
    }
    else if (m_state == State::Spell) {
      Spell* spell = new Spell(m_context, "magic-bullet");
      spell->addEventListener(ET::action, this, static_cast<Listener>(&Hero::onSpellCasted));
      m_parent->addChild(spell);
      spell->cast(point(m_x / m_context.TILE_SIZE, m_y / m_context.TILE_SIZE), point(x, y));
      m_state = State::Walk;
      gotoFrame(1, 1);
    }
  }
  else if (e.event_type == EventType::KeyDown) {
    if (e.key_data.key == 'S') {
      m_state = State::Spell;
    }
  }
  else if (e.event_type == EventType::MouseMoved) {
    int x = floor((e.mouse_data.x - m_parent->x()) / m_context.TILE_SIZE);
    int y = floor((e.mouse_data.y - m_parent->y()) / m_context.TILE_SIZE);

    if (m_state == State::Walk) {
      drawPath(x, y);
    }    
  }
}


void Hero::clearGuidePath() {
  for (int i = 0; i < m_guide_path.size(); ++i) {
    Sprite* s = m_guide_path.at(i);
    if (s->parent()) {
      s->parent()->removeChild(s);
    }
  }
  
}

void Hero::drawPath(int col, int row) {


  if (m_last_point.first != col || m_last_point.second != row) {
    m_last_point = point(col, row);
    std::deque<point>* path = findPath(col, row);

    clearGuidePath();
    
    int index = 0;
    int rotation = 0;
    Sprite* s = NULL;
    for (std::deque<point>::iterator it = path->begin(); it != path->end(); ++it) {
      point p = *it;
      if (index < m_guide_path.size()) {
	s = m_guide_path.at(index);
      }
      else {
	s = new Sprite(m_context, "footsteps.png");
	s->setZ(-0.5);
	m_guide_path.push_back(s);
      }
      s->setPosition(p.first * m_context.TILE_SIZE, p.second * m_context.TILE_SIZE);
      parent()->addChild(s);

      if (index > 0) {
	Sprite* prev = m_guide_path.at(index - 1);
	if (prev->x() < s->x()) {
	  rotation = 0;
	}
	else if (prev->x() > s->x()) {
	  rotation = 180;
	}
	else if (prev->y() < s->y()) {
	  rotation = 90;
	}
	else {
	  rotation = -90;
	}
	prev->setRotation(rotation);
	  
      }
      index++;
    }
    if (s) {
      s->setRotation(rotation);
    }
  }
}

void Hero::onSpellCasted(std::string e, EventDispatcher* dispatcher) {
  Spell* spell = dynamic_cast<Spell*>(dispatcher);
  if (spell) {
    gotoFrame(0);
    dispatchEvent(e, dispatcher);

    if (spell->parent()) {
      spell->parent()->removeChild(spell);
    }

    delete spell;
  }

}

std::deque<point>* Hero::findPath(int x, int y) {
  std::set<point> marked;
  std::queue<point> open_list;
  std::map<point, point> parent;
  point to(x, y);

  point start(floor(m_x / m_context.TILE_SIZE), floor(m_y / m_context.TILE_SIZE));
  open_list.push(start);

  while (!open_list.empty()) {
    point loc = open_list.front();
    open_list.pop();
    if (loc == to) {
      std::deque<point>* result = new std::deque<point>();
      point p = to;
      while (p != start) {
	result->push_front(p);
	p = parent[p];
      }

      if (addStartToPath(start, result)) {
	result->push_front(start);
      }

      return result;
    }

    for (int i = 0; i < 4; ++i) {
      point new_loc(loc.first + directions[i].first, loc.second + directions[i].second);
      if (m_seen.at(new_loc.second).at(new_loc.first) && m_map.at(new_loc.second).at(new_loc.first) == 0 && marked.find(new_loc) == marked.end()) {
	parent.insert(std::make_pair(new_loc, loc));
	open_list.push(new_loc);
	marked.insert(new_loc);
      }
    }

  }
  
  return new std::deque<point>();
    

}

bool Hero::addStartToPath(point start, std::deque<point>* path) {
  bool add_start = false;
  if (path->size() > 0) {
    if (m_x < start.first * m_context.TILE_SIZE && start.first * m_context.TILE_SIZE  <= path->front().first * m_context.TILE_SIZE) {
      add_start = true;
    }
    if (m_x > start.first * m_context.TILE_SIZE && start.first * m_context.TILE_SIZE  >= path->front().first * m_context.TILE_SIZE) {
      add_start = true;
    }
    if (m_y < start.second * m_context.TILE_SIZE && start.second * m_context.TILE_SIZE  <= path->front().second * m_context.TILE_SIZE) {
      add_start = true;
    }
    if (m_y > start.second * m_context.TILE_SIZE && start.second * m_context.TILE_SIZE  >= path->front().second * m_context.TILE_SIZE) {
      add_start = true;
    }
  }
  else {
    add_start = true;
  }

  return add_start;
  
}

bool Hero::isMoving() const {
  if (m_path) {
    return !(m_path->empty());
  }

  return false;
}

point Hero::getTileOffset() const {
  return point(m_x - m_context.TILE_SIZE * floor(m_x / m_context.TILE_SIZE), m_y - m_context.TILE_SIZE * floor(m_y / m_context.TILE_SIZE));
}

Hero::~Hero() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    delete m_sprites.at(i);
  }

}

