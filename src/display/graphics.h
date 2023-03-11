// Вывод графических примитивов на LCD-экран

#ifndef __GL_H
#define __GL_H

#include "../types.h"

// old methods
void LCD_PutPixel(u32 x, u32 y);
void LCD_Line(u32 x1, u32 y1, u32 x2, u32 y2);
void LCD_Circle(u32 xc, u32 yc, u32 r);
void LCD_SetPixel(u32 x, u32 y, bool c);

// new methods
void Buffer_Line(u32 x1, u32 y1, u32 x2, u32 y2, bool c);
void Buffer_Circle(u32 xc, u32 yc, u32 r, bool c);

#endif /* __GL_H */
