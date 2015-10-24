#include "../include/Graphics.hpp"

Graphics::Graphics(int winWidth, int winHeight, const char* winTitle) {
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  window = SDL_CreateWindow(winTitle, 100, 100, winWidth, winHeight, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  m_screen = SDL_GetWindowSurface(window);

  setBgColor(14,14,14);

  camera.x = 0;
  camera.y = 0;
  camera.w = winWidth;
  camera.h = winHeight;
}

Graphics::~Graphics() {
  TTF_Quit();
  SDL_Quit();
}

void Graphics::drawChar(SDL_Surface* charBitmap, SpriteBase* player, SDL_Rect* cam) {
  drawSprite(charBitmap,player->getCurrentFrame().x,  player->getCurrentFrame().y,
      player->getX()-cam->x,		player->getY()-cam->y,
      player->getCurrentFrame().w,  player->getCurrentFrame().h);

}

void Graphics::drawChar(SDL_Surface* charBitmap, SpriteBase* player) {
  drawSprite(charBitmap,player->getCurrentFrame().x,  player->getCurrentFrame().y,
      player->getX(),				player->getY(),
      player->getCurrentFrame().w,  player->getCurrentFrame().h);

}

void Graphics::drawBox(SDL_Rect* box, int color) {
  SDL_FillRect(m_screen, box, color);
}

void Graphics::drawMenu(TextMenu* menu) {
  int font_size = 16;
  // get the background
  SDL_Rect* menubox = menu->getContainer();
  // draw it
  drawBox(menubox,0xAFAFAF);
  // get the options for drawing
  std::vector<TextMenuItem> options = menu->getCurrentOptions();
  // draw each of the options
  if (menu->selected_huh) {
    for (unsigned int i = 0; i<options.size(); i++) {
      // displacement
      int delta_y = i*font_size;
      // if its selected display it
      if (options[i].getTitle() == menu->getSelected()->getTitle()) {
        displayCursor(menubox->x-5, menubox->y+delta_y);
      }
      // draw text
      drawText(options[i].getTitle(),16,menubox->x+10,menubox->y+delta_y, 255,255,0,0,0,0);
    }
  }else {
    for (unsigned int i = 0; i<options.size(); i++) {
      int delta_y = i*font_size;
      // draw text
      drawText(options[i].getTitle(),16,menubox->x+10,menubox->y+delta_y, 255,255,0,0,0,0);
    }
  }
}

void Graphics::drawMenu(TextMenu* menu, int padding) {
  int font_size = 16;
  // get the background
  SDL_Rect* menubox = menu->getContainer();
  // draw it
  // drawBox(menubox,0xAFAFAF); // meh i dont know about this fix here
  // I needed top-padding but
  // use the same container for
  // the bg and text. [-___-]
  // get the options for drawing
  std::vector<TextMenuItem> options = menu->getCurrentOptions();
  // draw each of the options
  if (menu->selected_huh) {
    for (unsigned int i = 0; i<options.size(); i++) {
      // displacement for padding
      int delta_y = i*(font_size+padding);
      // if its selected display cursor
      if (options[i].getTitle() == menu->getSelected()->getTitle()) {
        displayCursor(menubox->x-5, menubox->y+delta_y);
      }
      // draw text
      drawText(options[i].getTitle(),font_size,
          menubox->x+10, menubox->y+delta_y,
          255,255,0,0,0,0);
    }
  }else {
    for (unsigned int i = 0; i<options.size(); i++) {
      int delta_y = i*(font_size+padding);
      // draw text
      drawText(options[i].getTitle(),font_size,menubox->x+10,menubox->y+delta_y, 255,255,0,0,0,0);
    }
  }
}

void Graphics::displayCursor(int x, int y) {
  SDL_Rect* box =  new SDL_Rect();
  box->x = x;
  box->y = y;
  box->w = 5;
  box->h = 5;
  drawBox(box,0xfd7d00);
  delete box;
}

// currently padding is done blind, its something like 75+font_size(16)-1
void Graphics::drawCharPane(TextMenu* CharMenu, std::vector<NPC*> avatars, std::vector<Toon*> party, SDL_Surface* avatarBitmap) {
  if ((avatars.size() < 1) || (avatars.size() > 3))  {
    std::cout << "avatar vector sucks\n";
    std::cout << avatars.size() << "\n";
    throw "avatar vector is incorrectly sized";
  }

  if (avatars.size() != party.size()) {
    std::cout << "party and avatars are mismatched";
    throw "party and avatars are mismatched";
  }

  SDL_Rect* ah1 = new SDL_Rect();
  SDL_Rect* am1 = new SDL_Rect();
  for (unsigned int i=0; i<avatars.size(); ++i) {
    drawChar(avatarBitmap, avatars[i]);

    ah1->x = 20;
    ah1->y = 200 + (i*90);
    if (party[i]->health != 100)
      ah1->w = (int)(((double)party[i]->health / (double)party[i]->total_health)*100); // (current_health/total_health)*100
    else
      ah1->w = 100;
    ah1->h = 5;

    am1->x = 20;
    am1->y = 206 + (i*90);
    if (party[i]->mana != 100)
      am1->w = (int)(((double)party[i]->mana / (double)party[i]->total_mana)*100); // same but mana
    else
      am1->w = 100;
    am1->h = 5;

    drawBox(ah1,0x00FF00); // health
    drawBox(am1,0x0000FF); // mana
  }
  delete ah1;
  delete am1;

  drawMenu(CharMenu, 75);
}

void Graphics::drawInventory(Inventory &inventory) {
  std::vector<std::string> list = inventory.list();
  int ctr = 1;
  for(std::vector<std::string>::const_iterator i = list.begin(); i != list.end(); ++i) {
    // draw text string size x y fr fg fb, br, bh, bb
    drawText(*i,15,350,100+20*ctr,255,255,ctr*20,0,0,0);
    ctr++;
  }
}

SDL_Surface* Graphics::loadBitmap(const char* bitmapFileName, int transR, int transG, int transB) {
  SDL_Surface* bitmap = SDL_LoadBMP(bitmapFileName);
  SDL_SetColorKey(bitmap, SDL_TRUE, SDL_MapRGB(bitmap->format, transR, transG, transB)); // SDL_RLEACCEL - compresses, keys, uncompresses
  return bitmap;
}

void Graphics::closeBitmap(SDL_Surface* bitmap) {
  SDL_FreeSurface(bitmap);
}

// bookend drawing routines
void Graphics::beginScene() {
  SDL_FillRect(m_screen, NULL, SDL_MapRGB(m_screen->format, m_bgR, m_bgG, m_bgB));
}

void Graphics::endScene() {
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, m_screen);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
  SDL_DestroyTexture(texture);
}

void Graphics::drawSprite(SDL_Surface* imageSurface,
    int srcX, int srcY,
    int dstX, int dstY,
    int wdth, int hght) {
  SDL_Rect srcRect;
  srcRect.x = srcX;
  srcRect.y = srcY;
  srcRect.w = wdth;
  srcRect.h = hght;

  SDL_Rect dstRect;
  dstRect.x = dstX;
  dstRect.y = dstY;
  dstRect.w = wdth;
  dstRect.h = hght;

  SDL_BlitSurface(imageSurface, &srcRect, m_screen, &dstRect);
}

SDL_Surface* Graphics::scaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height) {
  if(!Surface || !Width || !Height)
    return 0;

  SDL_Surface *_ret = SDL_CreateRGBSurface(Surface->flags, Width, Height, Surface->format->BitsPerPixel,
      Surface->format->Rmask, Surface->format->Gmask, Surface->format->Bmask, Surface->format->Amask);

  double 	_stretch_factor_x = (static_cast<double>(Width)  / static_cast<double>(Surface->w)),
          _stretch_factor_y = (static_cast<double>(Height) / static_cast<double>(Surface->h));

  for(Sint32 y = 0; y < Surface->h; y++)
    for(Sint32 x = 0; x < Surface->w; x++)
      for(Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
        for(Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)
          DrawPixel(_ret, static_cast<Sint32>(_stretch_factor_x * x) + o_x,
              static_cast<Sint32>(_stretch_factor_y * y) + o_y, ReadPixel(Surface, x, y));

  return _ret;
}

Uint32 Graphics::ReadPixel(SDL_Surface *surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
    case 1:
      return *p;
      break;

    case 2:
      return *(Uint16 *)p;
      break;

    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
      break;

    case 4:
      return *(Uint32 *)p;
      break;

    default:
      return 0;       /* shouldn't happen, but avoids warnings */
  }
}

void Graphics::DrawPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to set */
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
    case 1:
      *p = pixel;
      break;

    case 2:
      *(Uint16 *)p = pixel;
      break;

    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;

    case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

void Graphics::drawText(const char* string, int size,
    int x, int y,
    int frR, int frG, int frB,
    int bR, int bG, int bB) {


  // this and close font could probably be abstracted
  TTF_Font* font = TTF_OpenFont("build/CBM-64.TTF", size);
  if (!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    return;
  }

  SDL_Color fgColor = { static_cast<Uint8>(frR), static_cast<Uint8>(frG), static_cast<Uint8>(frB) };
  SDL_Color bgColor = { static_cast<Uint8>(bR), static_cast<Uint8>(bG), static_cast<Uint8>(bB) };

  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, string, fgColor, bgColor);
  SDL_Rect textLocation = { static_cast<Sint16>(x), static_cast<Sint16>(y), 0, 0 };
  SDL_BlitSurface(textSurface, NULL, m_screen, &textLocation);
  SDL_FreeSurface(textSurface);
  TTF_CloseFont(font);
}


void Graphics::drawText(std::string string, int size,
    int x, int y,
    int frR, int frG, int frB,
    int bR, int bG, int bB) {

  const char * c = string.c_str();

  SDL_Color fgColor = { static_cast<Uint8>(frR), static_cast<Uint8>(frG), static_cast<Uint8>(frB) };
  SDL_Color bgColor = { static_cast<Uint8>(bR), static_cast<Uint8>(bG), static_cast<Uint8>(bB) };

  // this and close font could probably be abstracted fixme
  TTF_Font* font = TTF_OpenFont("build/CBM-64.TTF", size);

  if (!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    return;
  }

  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, c, fgColor, bgColor);
  SDL_Rect textLocation = { static_cast<Sint16>(x), static_cast<Sint16>(y), 0, 0 };
  SDL_BlitSurface(textSurface, NULL, m_screen, &textLocation);
  SDL_FreeSurface(textSurface);
  TTF_CloseFont(font);
}

void Graphics::drawSpeech(std::string speech, int x, int y) {
  int offsetx = 100;
  int offsety = 100;

  if (speech.length()<=20) {
    drawText(speech,18,x-offsetx,y-offsety,255,255,255,0,0,0);
  } else {

    std::vector<std::string> lines = makeLines(getWords(speech));

    for (unsigned int z=0;z<lines.size();z++) {
      drawText(lines[z],18,x-offsetx,y-offsety+(z*18),255,255,255,0,0,0);
    }
  }
}

std::vector<std::string> Graphics::makeLines(std::vector<std::string> words) {
  std::vector<std::string> out;
  int length=0;
  std::string line = "";
  for (unsigned int q=0;q<words.size();q++) {
    line = line + words[q];
    length += words[q].length() + 1;
    if (length > 20 ) { // 20 is kind of a magic number here :: line_length
      length = 0;
      out.push_back(line);
      line = "";
    }else {
      line +=  " ";
    }
  }
  out.push_back(line);
  return out;
}

std::vector<std::string> Graphics::getWords(std::string text) {
  std::istringstream iss(text);
  std::string token;
  std::vector<std::string> x;
  while(getline(iss, token, ' '))
  {
    x.push_back(token);
  }
  return x;
}

// kind of deprecated atm fixme
void Graphics::drawTilemap(SDL_Surface* tileImage, std::vector<SDL_Rect> config, std::vector<int> tilemap) {
  int height=0;
  int width=0;

  for (int q=0;q<196;q++) {
    int i = tilemap[q];
    SDL_Rect clip = config[i];

    drawSprite(tileImage, config[i].x,config[i].y,width,height,config[i].w,config[i].h);

    width+=50;
    if (width%700==0 ) {
      height+=50;
      width=0;
    }
    if (height%700==0) {
      height=0;
    }

  }
}

std::vector<SDL_Rect> Graphics::createTileset(SDL_Surface* tileImage, int tileWidth, int tileHeight) {
  std::vector<SDL_Rect> config;
  for (int i=0; i<tileImage->w;i+=tileWidth) {
    for (int j=0; j<tileImage->h; j+=tileHeight) {
      SDL_Rect temp;
      temp.x = i;
      temp.y = j;
      temp.w = tileWidth;
      temp.h = tileHeight;
      config.push_back(temp);
    }
  }
  return config;
}

void Graphics::setCameraX(int charX, int LEVEL_WIDTH) {
  //Center the camera over the dot
  camera.x = ( charX + 25 ) - SCREEN_WIDTH / 2;

  //Keep the camera in bounds.
  if( camera.x < 0 )
  {
    camera.x = 0;
  }
  if( camera.x > LEVEL_WIDTH - camera.w )
  {
    camera.x = LEVEL_WIDTH - camera.w;
  }
}

void Graphics::setCameraY(int charY, int LEVEL_HEIGHT) {

  //Center the camera over the dot
  camera.y = ( charY + 25 ) - SCREEN_HEIGHT / 2;

  //Keep the camera in bounds.
  if ( camera.y < 0 ) {
    camera.y = 0;
  }

  if ( camera.y > LEVEL_HEIGHT - camera.h ) {
    camera.y = LEVEL_HEIGHT - camera.h;
  }

}

SDL_Rect Graphics::getCamera() {
  return camera;
}

void Graphics::drawTiles(SDL_Surface* tileImage, std::vector<Tile*> tiles, std::vector<SDL_Rect> tileset) {
  for (unsigned int i=0;i<tiles.size();i++) {
    Tile* tile = tiles.at(i);
    SDL_Rect box = tile->getBox();
    // this could be more secure with size checking for something
    // really sprite clipping could be handled better
    SDL_Rect box2 = tileset.at(tile->getType());
    if( check_collision( camera, box ) == true ) {
      // one of these needs to be the config x / y from type
      // expand type to include this rect
      drawSprite(tileImage, box2.x, box2.y, box.x - camera.x, box.y - camera.y, 80, 80);
    }
  }
}

void Graphics::setBgColor(int r, int g, int b) {
  m_bgR = r;
  m_bgB = g;
  m_bgG = b;
}
