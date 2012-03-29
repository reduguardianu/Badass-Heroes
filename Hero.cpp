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

point directions[] = {point(-1, 0), point(0, 1), point(1, 0), point(0, -1)};

Hero::Hero(Context const& c, std::vector<std::vector<int> > const& map): DisplayObject(c),
									 m_map(map),
									 m_path(NULL) {
  m_sprites.push_back(new AnimatedSprite(c, "base_walking.png"));
  m_sprites.push_back(new AnimatedSprite(c, "tights_01.png"));
  m_sprites.push_back(new AnimatedSprite(c, "breastplate_01.png"));
  m_sprites.push_back(new AnimatedSprite(c, "headgear_01.png"));

  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->setParent(this);
  }

  m_render_behaviour = new ContainerRenderBehaviour(m_sprites);
  m_size_behaviour = new ContainerSizeBehaviour(m_sprites);
}


void Hero::animate(Anim::DIRECTION dir) {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->animate(dir);
  }
}

void Hero::stop() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    dynamic_cast<AnimatedSprite*>(m_sprites.at(i))->stop();
  }
  
}

void Hero::tick(float dt) {
  if (m_path && m_path->size()) {
    point dest = m_path->front();
    float dx = dest.first * 32 - m_x;
    float dy = dest.second * 32 - m_y;

    if (abs(dx) < 2 && abs(dy) < 2) {
      m_path->pop_front();
      m_x = dest.first * 32;
      m_y = dest.second * 32;
    }
    else {
      float dv = 300 * dt / 1000.f;
      if (dx > 0) {
	m_x += dv;
      }
      else if (dx < 0) {
	m_x -= dv;
      }
      if (dy > 0) {
	m_y += dv;
      }
      else if (dy < 0) {
	m_y -= dv;
      }
    }
  }
}

void Hero::onEvent(const Event& e) {
  if (e.event_type == EventType::MouseDown) {
    int x = (e.mouse_data.x - m_parent->x()) / 32;
    int y = (e.mouse_data.y - m_parent->y()) / 32;
    if (m_path) {
      delete m_path;
    }
    m_path = findPath(x, y);
  }
}

std::deque<point>* Hero::findPath(int x, int y) {
  std::set<point> marked;
  std::queue<point> open_list;
  std::map<point, point> parent;
  point to(x, y);

  point start(m_x / 32, m_y / 32);
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
      result->push_front(start);
      return result;
    }

    for (int i = 0; i < 4; ++i) {
      point new_loc(loc.first + directions[i].first, loc.second + directions[i].second);
      if (m_map.at(new_loc.second).at(new_loc.first) == 0 && marked.find(new_loc) == marked.end()) {
	parent.insert(std::make_pair(new_loc, loc));
	open_list.push(new_loc);
	marked.insert(new_loc);
      }
    }

  }
  
  return new std::deque<point>();
    

}

Hero::~Hero() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    delete m_sprites.at(i);
  }

}

