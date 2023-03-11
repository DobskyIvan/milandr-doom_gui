// Вывод графических примитивов на LCD-экран

#include "graphics.h"

#include "lcd.h"

void LCD_PutPixel(u32 x, u32 y) {
  u32 shifted, page;
  u8 data;

  if ((x > MAX_X) | (y > MAX_Y)) return;

  SetCrystal((LCD_Crystal)(x / 64));
  x %= 64;

  page = y / 8;
  shifted = (1 << (y % 8));
  LCD_SET_PAGE(page);
  LCD_SET_ADDRESS(x);
  data = ReadLCD_Data();
  switch (CurrentMethod) {
    case MET_OR:
      data |= shifted;
      break;
    case MET_XOR:
      data ^= shifted;
      break;
  }
  LCD_SET_ADDRESS(x);
  WriteLCD_Data(data);
}

void LCD_SetPixel(u32 x, u32 y, bool c) {
  u32 shifted, page;
  u8 data;

  if ((x > MAX_X) | (y > MAX_Y)) return;

  SetCrystal((LCD_Crystal)(x / 64));
  x %= 64;

  page = y / 8;
  shifted = (1 << (y % 8));
  LCD_SET_PAGE(page);
  LCD_SET_ADDRESS(x);
  data = ReadLCD_Data();
  if (c) {
    // Set the pixel to 1
    data |= shifted;
  } else {
    // Set the pixel to 0
    data &= ~shifted;
  }
  LCD_SET_ADDRESS(x);
  WriteLCD_Data(data);
}

void LCD_Line(u32 x1, u32 y1, u32 x2, u32 y2) {
  s32 dx, dy, i1, i2, i, kx, ky;
  s32 d;
  s32 x, y;
  s32 flag;

  dy = y2 - y1;
  dx = x2 - x1;
  if (dx == 0 && dy == 0) {
    LCD_PutPixel(x1, y1);
    return;
  }

  flag = kx = ky = 1;

  if (dx < 0) {
    dx = -dx;
    kx = -1;
  } else if (dx == 0)
    kx = 0;

  if (dy < 0) {
    dy = -dy;
    ky = -1;
  }

  if (dx < dy) {
    flag = 0;
    d = dx;
    dx = dy;
    dy = d;
  }

  i1 = dy + dy;
  d = i1 - dx;
  i2 = d - dx;
  x = x1;
  y = y1;

  for (i = 0;; i++) {
    LCD_PutPixel(x, y);
    if (i >= dx) break;

    if (flag)
      x += kx;
    else
      y += ky;

    if (d < 0)
      d += i1;
    else {
      d += i2;
      if (flag)
        y += ky;
      else
        x += kx;
    }
  }
}

void LCD_Circle(u32 xc, u32 yc, u32 r) {
  s32 x, y, d;
  x = 0;
  y = r;
  d = 3 - 2 * r;
  while (x <= y) {
    LCD_PutPixel(xc + x, yc + y);
    LCD_PutPixel(xc + x, yc - y);
    LCD_PutPixel(xc - x, yc + y);
    LCD_PutPixel(xc - x, yc - y);
    LCD_PutPixel(xc + y, yc + x);
    LCD_PutPixel(xc + y, yc - x);
    LCD_PutPixel(xc - y, yc + x);
    LCD_PutPixel(xc - y, yc - x);
    if (d < 0)
      d += 4 * x + 6;
    else {
      d += 4 * (x - y) + 10;
      y--;
    }
    x++;
  }
}

void Buffer_Line(u32 x1, u32 y1, u32 x2, u32 y2, bool c) {
  s32 dx, dy, i1, i2, i, kx, ky;
  s32 d;
  s32 x, y;
  s32 flag;

  dy = y2 - y1;
  dx = x2 - x1;
  if (dx == 0 && dy == 0) {
    // LCD_SetPixel(x1, y1, c); // use buffer
    SetBufferPixel(x1, y1, c);
    return;
  }

  flag = kx = ky = 1;

  if (dx < 0) {
    dx = -dx;
    kx = -1;
  } else if (dx == 0)
    kx = 0;

  if (dy < 0) {
    dy = -dy;
    ky = -1;
  }

  if (dx < dy) {
    flag = 0;
    d = dx;
    dx = dy;
    dy = d;
  }

  i1 = dy + dy;
  d = i1 - dx;
  i2 = d - dx;
  x = x1;
  y = y1;

  for (i = 0;; i++) {
    // LCD_SetPixel(x, y, c); // use buffer
    SetBufferPixel(x, y, c);
    if (i >= dx) break;

    if (flag)
      x += kx;
    else
      y += ky;

    if (d < 0)
      d += i1;
    else {
      d += i2;
      if (flag)
        y += ky;
      else
        x += kx;
    }
  }
}

void Buffer_Circle(u32 xc, u32 yc, u32 r, bool c) {
  s32 x, y, d;
  x = 0;
  y = r;
  d = 3 - 2 * r;
  while (x <= y) {
    // LCD_SetPixel(xc + x, yc + y, c); // use buffer
    SetBufferPixel(xc + x, yc + y, c);
    SetBufferPixel(xc + x, yc - y, c);
    SetBufferPixel(xc - x, yc + y, c);
    SetBufferPixel(xc - x, yc - y, c);
    SetBufferPixel(xc + y, yc + x, c);
    SetBufferPixel(xc + y, yc - x, c);
    SetBufferPixel(xc - y, yc + x, c);
    SetBufferPixel(xc - y, yc - x, c);
    if (d < 0)
      d += 4 * x + 6;
    else {
      d += 4 * (x - y) + 10;
      y--;
    }
    x++;
  }
}
