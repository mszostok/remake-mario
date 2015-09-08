#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>

#include <string>
#include <memory>

using namespace std;

/* klasa wyj¹tków */
class fontNotFound : public exception {
	string _exceptionName;
public:
	fontNotFound(string name) : _exceptionName("Font not found: " + name) {};
	virtual const char* what() const throw() {
		return _exceptionName.c_str();
	}
};

class TextManager {

	ALLEGRO_FONT *font13;
	ALLEGRO_FONT *fontMario20;

public:
	TextManager(void);
	~TextManager(void);

	/* rysowanie tekstu */
	void drawText(int r, int g, int b, int x, int y, string text, int value = 0);
	void drawText(int x, int y, string text, int flag = ALLEGRO_ALIGN_LEFT, int value = 0);
	void drawTextInfo(int x, int y, string text, int flag = ALLEGRO_ALIGN_LEFT, int value = 0);
};



typedef std::shared_ptr < TextManager > TextManagerPtr;


#endif