#include "Font.h"
#include <cstdio>
#include <stdlib.h>
#include <iostream>

int Font::load(std::string fontname) {
  std::string path = "../assets/fonts/" + fontname + ".fnt";
  FILE* f = fopen(path.c_str(), "r");
  std::string line;
  
  while (!feof(f)) {
    line = "";
    line.reserve(256);

    while (!feof(f)) {
      char ch;
      if (fread(&ch, 1, 1, f)) {
	if (ch != '\n') {
	  line += ch;
	}
	else {
	  break;
	}
      }
    }

    int pos = skipWhiteSpace(line, 0);
    
    int pos2 = findEndOfToken(line, pos);
    std::string token = line.substr(pos, pos2 - pos);
      
    if (token == "info") {
      interpretInfo(line, pos2);
    }
    else if (token == "common") {
      interpretCommon(line, pos2);
    }
    else if (token == "char") {
      interpretChar(line, pos2);
    }
    
  }

  fclose(f);
  return 0;

}

SCharDescr* Font::getChar(int id) {
  std::map<int, SCharDescr*>::iterator it = chars.find(id);
  if (it == chars.end()) {
    return 0;
  }

  return it->second;
}

int Font::skipWhiteSpace(const std::string& str, int start) {
  int n = start;
  while (n < str.size()) {
    char ch = str[n];
    if (ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n') {
      break;
    }
    ++n;
  }

  return n;
}

int Font::findEndOfToken(const std::string& str, int start) {
  int n = start;
  if (str[n] == '"') {
    n++;
    while (n < str.size()) {
      char ch = str[n];
      if (ch == '"') {
	++n;
	break;
      }
      ++n;
    }
  }
  else {
    while (n < str.size()) {
      char ch = str[n];
      if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '=') {
	break;
      }
      ++n;
    }
  }

  return n;
}


void Font::interpretChar(const std::string& str, int start) {
  int id = 0;
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
  int xoffset = 0;
  int yoffset = 0;
  int xadvance = 0;
  int page = 0;
  int chnl = 0;

  int pos, pos2 = start;
  while (true) {
    pos = skipWhiteSpace(str, pos2);
    pos2 = findEndOfToken(str, pos);
    
    std::string token = str.substr(pos, pos2 - pos);

    pos = skipWhiteSpace(str, pos2);
    if (pos == str.size() || str[pos] != '=') {
      break;
    }

    pos = skipWhiteSpace(str, pos + 1);
    pos2 = findEndOfToken(str, pos);

    std::string value = str.substr(pos, pos2 - pos);

    if (token == "id") {
      id = strtol(value.c_str(), 0, 10);
    }
    else if (token == "x") {
      x = strtol(value.c_str(), 0, 10);
    }
    else if (token == "y") {
      y = strtol(value.c_str(), 0, 10);
    }
    else if (token == "width") {
      width = strtol(value.c_str(), 0, 10);
    }
    else if (token == "height") {
      height = strtol(value.c_str(), 0, 10);
    }
    else if (token == "xoffset") {
      xoffset = strtol(value.c_str(), 0, 10);
    }
    else if (token == "yoffset") {
      yoffset = strtol(value.c_str(), 0, 10);
    }
    else if (token == "xadvance") {
      xadvance = strtol(value.c_str(), 0, 10);
    }
    else if (token == "page") {
      page = strtol(value.c_str(), 0, 10);
    }
    else if (token == "chnl") {
      chnl = strtol(value.c_str(), 0, 10);
    }

    if (pos == str.size()) {
      break;
    }
  }

  addChar(id, x, y, width, height, xoffset, yoffset, xadvance, page, chnl);
}

void Font::interpretInfo(const std::string& str, int start) {
  int outline_thickness;

  int pos, pos2 = start;
  while (true) {
    pos = skipWhiteSpace(str, pos2);
    pos2 = findEndOfToken(str, pos);
    
    std::string token = str.substr(pos, pos2 - pos);
    

    pos = skipWhiteSpace(str, pos2);
    if (pos == str.size() || str[pos] != '=') {
      break;
    }

    pos = skipWhiteSpace(str, pos + 1);
    pos2 = findEndOfToken(str, pos);

    std::string value = str.substr(pos, pos2 - pos);

    if (token == "outline") {
      outline_thickness = (short)strtol(value.c_str(), 0, 10);
    }
    if (pos == str.size()) {
      break;
    }
  }

  this->outline_thickness = outline_thickness;
}

void Font::interpretCommon(const std::string& str, int start) {
  int fontheight;
  int base;
  int scalew;
  int scaleh;
  int pages;
  int packed;

  int pos, pos2 = start;
  while (true) {
    pos = skipWhiteSpace(str, pos2);
    pos2 = findEndOfToken(str, pos);
    
    std::string token = str.substr(pos, pos2 - pos);
    pos = skipWhiteSpace(str, pos2);
    if (pos == str.size() || str[pos] != '=') {
      break;
    }

    pos = skipWhiteSpace(str, pos + 1);
    pos2 = findEndOfToken(str, pos);
    
    std::string value = str.substr(pos, pos2 - pos);

    if (token == "lineHeight") {
      fontheight = (short)strtol(value.c_str(), 0, 10);
    }
    else if (token == "base") {
      base = (short)strtol(value.c_str(), 0, 10);
    }
    else if (token == "scaleW") {
      scalew = (short)strtol(value.c_str(), 0, 10);
    }
    else if (token == "scaleH") {
      scaleh = (short)strtol(value.c_str(), 0, 10);
    }
    else if (token == "pages") {
      pages = strtol(value.c_str(), 0, 10);
    }
    else if (token == "packed") {
      packed = strtol(value.c_str(), 0, 10);
    }

    if (pos == str.size()) {
      break;
    }
  }

  setCommonInfo(fontheight, base, scalew, scaleh, pages, packed);
  
}

void Font::setCommonInfo(int fontheight, int base, int scalew, int scaleh, int pages, bool ispacked) {
  this->font_height = font_height;
  this->base = base;
  this->scalew = scalew;
  this->scaleh = scaleh;

  if (ispacked && outline_thickness) {
    this->has_outline = true;
  }
}


void Font::addChar(int id, int x, int y, int w, int h, int xoffset, int yoffset, int xadvance, int page, int chnl) {
  if (chnl == 1) {
    chnl = 0x00010000; // blue channel
  }
  else if (chnl == 2) {
    chnl = 0x00000100; // green channel 
  }
  else if (chnl == 4) {
    chnl = 0x00000001; // red channel
  }
  else if (chnl == 8) {
    chnl = 0x01000000;
  }
  else {
    chnl = 0;
  }

  if (id >= 0) {
    SCharDescr *ch = new SCharDescr;
    ch->srcX = x;
    ch->srcY = y;
    ch->srcW = w;
    ch->srcH = h;
    ch->xOff = xoffset;
    ch->yOff = yoffset;
    ch->xAdv = xadvance;
    ch->page = page;
    ch->chnl = chnl;
    
    chars.insert(std::make_pair(id, ch));
  }

  if (id == -1) {
    def_char.srcX = x;
    def_char.srcY = y;
    def_char.srcW = w;
    def_char.srcH = h;
    def_char.xOff = xoffset;
    def_char.yOff = yoffset;
    def_char.xAdv = xadvance;
    def_char.page = page;
    def_char.chnl = chnl;
  }
}

