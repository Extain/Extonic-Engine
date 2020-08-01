#pragma once
#include <cstdint>
#include <string>

class Window {
public:

	Window(std::string title, uint32_t width, uint32_t height);

	virtual uint32_t getWidth() { return _width; }
	virtual uint32_t getHeight() { return _height; }
	virtual long getWindowHandle() { return windowHandle; }
private:
	std::string title;
	uint32_t _width;
	uint32_t _height;
	long windowHandle;
};
