#ifndef __GEOMETORY_H__
#define __GEOMETORY_H__

void InitGeometory(float screenWidth, float screenHeight);
void UninitGeometory();

void GeometoryColor(float r, float g, float b, float a);
void DrawLine(float startX, float startY, float endX, float endY);
void DrawRect(float centerX, float centerY, float width, float height);
void DrawCircle(float centerX, float centerY, float radius);

#endif // __GEOMETORY_H__