#include "../include/Input.hpp"

Input::Input() {
  m_windowClosed = false;
  for (unsigned int i=0;i<323;i++) {
    m_keysHeld[i]=false;
  }
}

Input::~Input() {
  //delete m_keysHeld;
}

void Input::readInput() {
  if (SDL_PollEvent(&m_event)) {
    if (m_event.type == SDL_QUIT) {
      m_windowClosed = true;
    }
    if (m_event.type == SDL_KEYDOWN) {
      m_keysHeld[m_event.key.keysym.sym] = true;

      int in_vector = false;
      for(unsigned int i=0;i<ARROW_KEY_STACK.size();i++) {
        if (ARROW_KEY_STACK[i] == m_event.key.keysym.sym) {
          in_vector = true;
        }
      }
      if (!in_vector) {
        ARROW_KEY_STACK.push_back(m_event.key.keysym.sym);
      }
    }
    if (m_event.type == SDL_KEYUP) {
      m_keysHeld[m_event.key.keysym.sym] = false;

      for(unsigned int i=0;i<ARROW_KEY_STACK.size();i++) {
        if (ARROW_KEY_STACK[i] == m_event.key.keysym.sym) {
          ARROW_KEY_STACK.erase(ARROW_KEY_STACK.begin()+i);
        }
      }

    }
  }
}

bool* Input::getInput() {
  return m_keysHeld;
}

bool Input::windowClosed() {
  return m_windowClosed;
}
