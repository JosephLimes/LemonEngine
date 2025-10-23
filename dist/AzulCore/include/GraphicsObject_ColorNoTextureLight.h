#ifndef GRAPHICS_OBJECT_COLOR_NO_TEXTURE_LIGHT_H
#define GRAPHICS_OBJECT_COLOR_NO_TEXTURE_LIGHT_H

#include "GraphicsObject.h"


class GraphicsObject_ColorNoTextureLight :public GraphicsObject
{
public:
	GraphicsObject_ColorNoTextureLight(Model *model, ShaderObject *pShaderObj, Vect &LightColor, Vect &LightPos);
	~GraphicsObject_ColorNoTextureLight();

	void SetColor(const Vect& col) { *(this->pselectedColor) = col; }
	void SetLightPos(const Vect& LightPos) { *(this->pLightPos) = LightPos; }
	void SetLightCol(const Vect& LightColor) { *(this->pLightColor) = LightColor; }

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;	
	virtual void privDraw() override;
	virtual void privRestoreState() override;

public:
// data:  place uniform instancing here
	Vect *pLightColor;
	Vect *pLightPos;

	Vect* pselectedColor;

	GraphicsObject_ColorNoTextureLight() = delete;

};
#endif