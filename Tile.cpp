#include "Tile.h"



Tile::Tile(Context const& c, std::string textureName, int row, int column, std::vector<std::vector<int> > const& map): Sprite(c, textureName),
														       m_row(row),
														       m_column(column),
														       m_map(map) {
  m_frame->setSize(32, 32);
  //  setScale(2, 2);
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

  m_uvs[0][0][0][0] = std::make_pair(0.5, 0.75);
  m_uvs[1][1][1][1] = std::make_pair(0.75, 0.75);
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

void Tile::tick(float dt) {
  if (m_map.at(m_row).at(m_column) == 1) {
    std::pair<float, float> coord = m_uvs[up()][right()][down()][left()];

    m_frame->setUV(coord.first, coord.second);
  }
  else {
    m_frame->setUV(0.5, 0.75);
  }
}

