
#pragma once

#ifdef _WIN32
  #include <windows.h>
#endif

namespace simplex {

  enum class keycode {
    UP = VK_UP,
    DOWN = VK_DOWN,
    LEFT = VK_LEFT,
    RIGHT = VK_RIGHT,
    // TODO: more keycodes
  };

}