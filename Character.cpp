#include "Character.h"
#include <cmath>
#include "Utils.h"

Character::Character(Context const& c, std::vector<std::vector<int> > const& map): DisplayObject(c), m_map(map),
										   m_path(NULL) {
  
}

void Character::onAction(Action action) {

  std::deque<point>* path = findPath(action.dest().second, action.dest().first);
  if (path->size() > 0) {
    m_actions.clear();
    
    if (m_path) {
      delete m_path;
    }
    m_path = path;
    
    if (action.type() != Action::WALK && m_path->size() > 1) {
      point p = m_path->back();
      m_path->pop_back();
      
      m_actions.push_back(Action(Action::WALK, m_path->back()));
    }
    m_actions.push_back(action);
  }

}

void Character::tick(float dt) {
  if (m_actions.size()) {
    if (m_actions.at(0).type() == Action::WALK) {
      if (m_path && m_path->size()) {
	point dest = m_path->front();
	
	point diff = Utils::getPositionDiff(point(m_x, m_y), point(dest.first * m_context.TILE_SIZE, dest.second * m_context.TILE_SIZE), dt);
	
	m_x += diff.first;
	m_y += diff.second;
	

	float dx = dest.first * m_context.TILE_SIZE - m_x;
	float dy = dest.second * m_context.TILE_SIZE - m_y;

	if (fabs(dx) < 1 && fabs(dy) < 1) {
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
	dispatchEvent(new GameEvent(ET::came), this);
      }
    }
  }

}

bool Character::isTileVisible(int row, int col) const {
  return true;
}


bool Character::isMoving() const {
  if (m_path) {
    return !(m_path->empty());
  }

  return false;
}


void Character::animate(const std::string& dir, int count) {
  
}

std::deque<point>* Character::findPath(int x, int y) {
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
      point new_loc(loc.first + Utils::directions[i].first, loc.second + Utils::directions[i].second);
      if (m_seen.at(new_loc.second).at(new_loc.first) && m_map.at(new_loc.second).at(new_loc.first) == 0 && marked.find(new_loc) == marked.end()) {
	parent.insert(std::make_pair(new_loc, loc));
	open_list.push(new_loc);
	marked.insert(new_loc);
      }
    }

  }
  
  return new std::deque<point>();
    

}


bool Character::addStartToPath(point start, std::deque<point>* path) {
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
