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
																	   m_state(State::Stand),
																	   m_last_point(-1, -1),
																	   m_spell(NULL) {
  initVisibleTiles(m_map);

  m_figure = new Figure(c, headgear, breastplate, pants);
  m_avatar = new Figure(*m_figure);
  m_avatar->setDirection(Animations::down);
  m_avatar->setScale(8.0f);
  addChild(m_figure);
  m_render_behaviour = new ContainerRenderBehaviour(m_children);
  m_size_behaviour = new ContainerSizeBehaviour(m_children);

}

Figure* Hero::getAvatar() {
  return m_avatar;
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
  m_figure->animate(dir);
}

void Hero::stop() {
  if (m_state == State::Walk) {
    setState(State::Stand);
  }
  m_figure->stop();
  m_figure->setDirection(Animations::down);
}

int Hero::posToTile(float p) const {
  return floor(p / m_context.TILE_SIZE);
}

void Hero::gotoFrame(int frame, int time) {
  m_figure->gotoFrame(frame, time);
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
  
  if (m_actions.size()) {
    if (m_actions.at(0).type() == Action::WALK) {
      if (m_path && m_path->size()) {
	m_state = State::Walk;
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
	m_actions.erase(m_actions.begin());
      }
    }
    else if (m_actions.at(0).type() == Action::OPEN_CHEST) {
      Action a = m_actions.at(0);
      dispatchEvent(new GameEvent(ET::open_chest, a.dest().first, a.dest().second), this);
      
      m_actions.erase(m_actions.begin());
    }
  }
  else {
    stop();
  }

  findVisibleTiles();

  m_figure->tick(dt);
}

void Hero::onEvent(const Event& e) {
  if (e.event_type == EventType::MouseDown) {
    int x = floor((e.mouse_data.x - m_parent->x()) / m_context.TILE_SIZE);
    int y = floor((e.mouse_data.y - m_parent->y()) / m_context.TILE_SIZE);

    if (m_state == State::Spell && m_spell) {
      m_spell->addEventListener(ET::spell, this, static_cast<Listener>(&Hero::onSpellCasted));
      m_spell->cast(point(m_x / m_context.TILE_SIZE, m_y / m_context.TILE_SIZE), point(x, y));
      m_state = State::Stand;
      gotoFrame(1, 1);
    }
  }
  else if (e.event_type == EventType::MouseMoved) {
    int x = floor((e.mouse_data.x - m_parent->x()) / m_context.TILE_SIZE);
    int y = floor((e.mouse_data.y - m_parent->y()) / m_context.TILE_SIZE);

    if (m_state == State::Stand) {
      drawPath(x, y);
    }    
    if (m_state == State::Spell) {
      m_spell->onEvent(e);
    }
  }
}

void Hero::onAction(Action& action) {
  if (m_state == State::Stand) {
    std::deque<point>* path = findPath(action.dest().second, action.dest().first);
    if (path->size() > 0) {
      m_actions.clear();
      
      if (m_path) {
	delete m_path;
      }
      clearGuidePath();
      m_path = path;
      
      if (action.type() != Action::WALK && m_path->size() > 1) {
	point p = m_path->back();
	m_path->pop_back();
	
	m_actions.push_back(Action(Action::WALK, m_path->back()));
      }
      m_actions.push_back(action);
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

void Hero::onSpellCasted(GameEventPointer e, EventDispatcher* dispatcher) {
  if (m_spell) {
    gotoFrame(0);
    dispatchEvent(e, dispatcher);

    if (m_spell->parent()) {
      m_spell->parent()->removeChild(m_spell);
    }

    m_spell = NULL;


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

void Hero::setState(State::STATE value) {
  m_state = value;
  if (m_state != State::Stand) {
    clearGuidePath();
  }
}

State::STATE Hero::state() const {
  return m_state;
}

void Hero::spell(Spell* s) {
  if (m_spell) {
    if (m_spell->parent()) {
      m_spell->parent()->removeChild(m_spell);
    }
    delete m_spell;
  }

  m_spell = s;
  m_parent->addChild(m_spell);
  setState(State::Spell);
}

Hero::~Hero() {
  delete m_figure;
}

