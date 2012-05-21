#ifndef FONTPARSER_H__
#define FONTPARSER_H__

#include <vector>
#include <map>
#include <string>

struct SCharDescr {
SCharDescr() : srcX(0), srcY(0), srcW(0), srcH(0), xOff(0), yOff(0), xAdv(0), page(0) {}

  float srcX;
  float srcY;
  float srcW;
  float srcH;
  float xOff;
  float yOff;
  float xAdv;
  short page;
  unsigned int chnl;
  
  std::vector<int> kerning_pairs;
  
};

enum EFontTextEncoding {
  NONE,
  UTF8,
  UTF16
};

class Font {
 public:
  short font_height;
  short base;
  short scalew;
  short scaleh;
  int outline_thickness;
  
  SCharDescr def_char;
  bool has_outline;

  float scale;
  EFontTextEncoding encoding;

  std::map<int, SCharDescr*> chars;
  std::string fx_file;

  int load(std::string fontname);
  SCharDescr* getChar(int id);
  
 private:
  int skipWhiteSpace(const std::string& str, int start);
  int findEndOfToken(const std::string& str, int start);
  void interpretChar(const std::string& str, int start);
  void interpretCommon(const std::string& str, int start);
  void addChar(int id, int x, int y, int w, int h, int xOffset, int yOffset, int xadvance, int page, int chnl);
  void setCommonInfo(int fontHeight, int base, int scalew, int scaleh, int pages, bool ispacked);
  void interpretInfo(const std::string& str, int start);

  
};


#endif
