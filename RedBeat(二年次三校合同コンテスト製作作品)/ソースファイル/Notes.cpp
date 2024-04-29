#include "Notes.h"

Notes::Notes(SpriteDesc desc)
{
	Vertex vtx[]=
	{
	{{-50.0f,-50.0f,0.0f},{0.0f,0.0f}} ,
	{{50.0f,-50.0f,0.0f},{1.0f,0.0f}} ,
	{{-50.0f,50.0f,0.0f},{0.0f,1.0f}} ,
	{{50.0f,50.0f,0.0f},{1.0f,1.0f}}
	};
	desc.pVtx = vtx;
	desc.pTexture ="Assets/Texture.png";
	CreateSprite(desc);

	
}

Notes::~Notes()
{

}
