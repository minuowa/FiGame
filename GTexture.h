#pragma once
#include "GResourceManager.h"
class GTexture
{
public:
	GTexture();
	~GTexture();

	bool createFromFile ( const char* name );

	inline IDirect3DTexture9* getTexture();

	void set(int stage);
	void destory();
	int width() const;
	int height() const;
public:
	uString	mFileName;
protected:
	u32 mWidth;
	u32 mHeight;
protected:
	IDirect3DTexture9*	mD3DTexture;
};

inline IDirect3DTexture9* GTexture::getTexture()
{
	return mD3DTexture;
}