#include "Tile.h"



Tile::Tile(Context const& c, std::string textureName, std::string shadowTexture, int row, int column, std::vector<std::vector<int> > const& map): Sprite(c, textureName),
														       m_row(row),
														       m_column(column),
														       m_map(map),
														       m_visible(false),
														       m_shadow(NULL),
														       m_darkness(NULL) {

  if (shadowTexture.size()) {
    m_shadow = new Sprite(m_context, shadowTexture);
    m_shadow->setSize(32, 64);
    m_shadow->setParent(this);
    m_shadow->setScale(m_context.DEFAULT_SCALE);
  }
  m_frame->setSize(32, 32);
  m_uvs[0][1][1][0] = std::make_pair(0, 0);
  m_uvs[0][0][1][1] = std::make_pair(0.25, 0);
  m_uvs[1][0][0][1] = std::make_pair(0.5, 0);
  m_uvs[1][1][0][0] = std::make_pair(0.75, 0);
  m_uvs[0][1][0][1] = std::make_pair(0, 0.25);
  m_uvs[1][0][1][0] = std::make_pair(0.25, 0.25);

  m_uvs[1][1][1][0] = std::make_pair(0.5, 0.25);
  m_uvs[0][1][1][1] = std::make_pair(0.75, 0.25);
  m_uvs[1][0][1][1] = std::make_pair(0, 0.5);
  m_uvs[1][1][0][1] = std::make_pair(0.25, 0.5);

  m_uvs[0][0][0][1] = std::make_pair(0.5, 0.5);
  m_uvs[1][0][0][0] = std::make_pair(0.75, 0.5);
  m_uvs[0][1][0][0] = std::make_pair(0, 0.75);
  m_uvs[0][0][1][0] = std::make_pair(0.25, 0.75);

  m_uvs[1][1][1][1] = std::make_pair(0.5, 0.75);
  //  m_uvs[1][1][1][1] = std::make_pair(0.75, 0.75);
  
  m_darkness = new Sprite(m_context, "darkness.png");
  m_darkness->setParent(this);
  m_darkness->setScale(m_context.DEFAULT_SCALE);
  m_darkness->setZ(1.0f);
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

int Tile::left() {
  int c = m_column - 1;
  if (c < 0) {
    return 0;
  }
  
  return m_map.at(m_row).at(c);
}

int Tile::right() {
  int c = m_column + 1;
  if (c >= m_map.at(m_row).size()) {
    return 0;
  }
  
  return m_map.at(m_row).at(c);
}

int Tile::up() {
  int r = m_row - 1;
  if (r < 0) {
    return 0;
  }

  return m_map.at(r).at(m_column);
}

int Tile::down() {
  int r = m_row + 1;
  if (r >= m_map.size()) {
    return 0;
  }

  return m_map.at(r).at(m_column) == 1;
}

void Tile::setDarknessOffset(point p) {
  m_darkness->setPosition(p.first, p.second);
}

void Tile::render() {
  if (m_map.at(m_row).at(m_column) == 1) {
    if (m_shadow) {
      m_shadow->render();
    }
    Sprite::render();
  }

  if (!m_visible) {
    m_darkness->render();
  }
}

void Tile::tick(float dt) {
  if (m_map.at(m_row).at(m_column) == 1) {
    std::pair<float, float> coord = m_uvs[up()][right()][down()][left()];

    if (m_shadow) {
      m_shadow->setUV(coord.first, coord.second);
    }
    m_frame->setUV(coord.first, coord.second);
  }
}
