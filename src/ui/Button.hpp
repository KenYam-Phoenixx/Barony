//! @file Button.hpp

#pragma once

#include "../main.hpp"
#include "Widget.hpp"
#include "Font.hpp"

class Frame;

static inline bool rectContainsPoint(SDL_Rect r, int x, int y) {
	return x >= r.x && y >= r.y && x < r.x + r.w && y < r.y + r.h;
}

//! A Button lives in a Frame and can have scripted actions or a native callback.
class Button : public Widget {
public:
	Button();
	Button(Frame& _parent);
	Button(const Button&) = delete;
	Button(Button&&) = delete;
	virtual ~Button() = default;

	Button& operator=(const Button&) = delete;
	Button& operator=(Button&&) = delete;

	//! the result of the button process
	struct result_t {
		bool highlighted;				//!< was highlighted this frame
		bool pressed;					//!< was pressed this frame
		bool clicked;					//!< was activated this frame
		Uint32 highlightTime;			//!< time since button was highlighted
		const char* tooltip = nullptr;	//!< button tooltip to be displayed
	};

	//! button style
	enum style_t {
		STYLE_NORMAL,
		STYLE_TOGGLE,
		STYLE_CHECKBOX,
		STYLE_DROPDOWN,
		STYLE_MAX
	};

	//! text justification
	enum justify_t {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		CENTER,
		JUSTIFY_TYPE_LENGTH
	};

	//! draws the button
	//! @param renderer the renderer object used to draw the button
	//! @param _size size and position of button's parent frame
	//! @param _actualSize offset into the parent frame space (scroll)
	//! @param selectedWidget the currently selected widget, if any
	void draw(SDL_Rect _size, SDL_Rect _actualSize, Widget* selectedWidget);

	//! handles button clicks, etc.
	//! @param _size size and position of button's parent frame
	//! @param _actualSize offset into the parent frame space (scroll)
	//! @param usable true if another object doesn't have the mouse's attention, false otherwise
	//! @return resultant state of the button after processing
	result_t process(SDL_Rect _size, SDL_Rect _actualSize, const bool usable);

	//! activates the button
	virtual void activate() override;

	virtual type_t              getType() const override { return WIDGET_BUTTON; }
	const char*					getText() const { return text.c_str(); }
	const char*					getFont() const { return font.c_str(); }
	int							getBorder() const { return border; }
	const SDL_Rect&				getSize() const { return size; }
	int							getStyle() const { return style; }
	void						(*getCallback() const)(Button&) { return callback; }
	const int					getHJustify() const { return static_cast<int>(hjustify); }
	const int					getVJustify() const { return static_cast<int>(vjustify); }
	const char*					getBackground() const { return background.c_str(); }
	const char*					getBackgroundActivated() const { return backgroundActivated.c_str(); }

	void	setBorder(int _border) { border = _border; }
	void	setPos(int x, int y) { size.x = x; size.y = y; }
	void	setSize(SDL_Rect _size) { size = _size; }
	void	setColor(const Uint32& _color) { color = _color; }
	void	setTextColor(const Uint32& _color) { textColor = _color; }
	void	setTextHighlightColor(const Uint32& _color) { textHighlightColor = _color; }
	void	setBorderColor(const Uint32& _color) { borderColor = _color; }
	void	setHighlightColor(const Uint32& _color) { highlightColor = _color; }
	void	setText(const char* _text) { text = _text; }
	void	setFont(const char* _font) { font = _font; }
	void	setIcon(const char* _icon);
	void	setTooltip(const char* _tooltip) { tooltip = _tooltip; }
	void	setStyle(int _style) { style = static_cast<style_t>(_style); }
	void	setCallback(void (*const fn)(Button&)) { callback = fn; }
	void	setBackground(const char* image) { background = image; }
	void	setBackgroundActivated(const char* image) { backgroundActivated = image; }
	void	setJustify(const int _justify) { hjustify = vjustify = static_cast<justify_t>(_justify); }
	void	setHJustify(const int _justify) { hjustify = static_cast<justify_t>(_justify); }
	void	setVJustify(const int _justify) { vjustify = static_cast<justify_t>(_justify); }

private:
	void (*callback)(Button&) = nullptr;			//!< native callback for clicking
	std::string background;							//!< background image
	std::string backgroundActivated;				//!< background image when activated
	std::string text;								//!< button text, if any
	std::string font = Font::defaultFont;			//!< button font
	std::string icon;								//!< icon, if any (supersedes text content)
	std::string tooltip;							//!< if empty, button has no tooltip; otherwise, it does
	int border = 2;									//!< size of the button border in pixels
	SDL_Rect size;									//!< size and position of the button within its parent frame
	Uint32 color;									//!< the button's color
	Uint32 highlightColor;							//!< color used when the button is selected/highlighted
	Uint32 textColor;								//!< text color
	Uint32 textHighlightColor;						//!< text color used when the button is selected/highlighted
	Uint32 borderColor;								//!< (optional) border color
	style_t style = STYLE_NORMAL;					//!< button style
	justify_t hjustify = CENTER;					//!< horizontal text justification
	justify_t vjustify = CENTER;					//!< vertical text justification
};