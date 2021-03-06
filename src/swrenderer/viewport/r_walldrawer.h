
#pragma once

#include "r_drawerargs.h"

struct FSWColormap;
struct FLightNode;

namespace swrenderer
{
	class RenderThread;
	
	class WallDrawerArgs : public DrawerArgs
	{
	public:
		void SetStyle(bool masked, bool additive, fixed_t alpha);
		void SetDest(int x, int y);
		void SetCount(int count) { dc_count = count; }
		void SetTexture(const uint8_t *pixels, const uint8_t *pixels2, int height)
		{
			dc_source = pixels;
			dc_source2 = pixels2;
			dc_textureheight = height;
		}
		void SetTextureFracBits(int bits) { dc_wall_fracbits = bits; }
		void SetTextureUPos(uint32_t pos) { dc_texturefracx = pos; }
		void SetTextureVPos(fixed_t pos) { dc_texturefrac = pos; }
		void SetTextureVStep(fixed_t step) { dc_iscale = step; }

		bool IsMaskedDrawer() const;

		void DrawColumn(RenderThread *thread);

		uint8_t *Dest() const { return dc_dest; }
		int DestY() const { return dc_dest_y; }
		int Count() const { return dc_count; }

		uint32_t *SrcBlend() const { return dc_srcblend; }
		uint32_t *DestBlend() const { return dc_destblend; }
		fixed_t SrcAlpha() const { return dc_srcalpha; }
		fixed_t DestAlpha() const { return dc_destalpha; }

		uint32_t TextureUPos() const { return dc_texturefracx; }
		fixed_t TextureVPos() const { return dc_texturefrac; }
		fixed_t TextureVStep() const { return dc_iscale; }

		const uint8_t *TexturePixels() const { return dc_source; }
		const uint8_t *TexturePixels2() const { return dc_source2; }
		uint32_t TextureHeight() const { return dc_textureheight; }

		int TextureFracBits() const { return dc_wall_fracbits; }

		FVector3 dc_normal;
		FVector3 dc_viewpos;
		FVector3 dc_viewpos_step;
		DrawerLight *dc_lights = nullptr;
		int dc_num_lights = 0;

	private:
		uint8_t *dc_dest = nullptr;
		int dc_dest_y = 0;
		int dc_count;
		
		fixed_t dc_iscale;
		fixed_t dc_texturefrac;
		uint32_t dc_texturefracx;
		uint32_t dc_textureheight;
		const uint8_t *dc_source;
		const uint8_t *dc_source2;
		int dc_wall_fracbits;
		
		uint32_t *dc_srcblend;
		uint32_t *dc_destblend;
		fixed_t dc_srcalpha;
		fixed_t dc_destalpha;

		typedef void(SWPixelFormatDrawers::*WallDrawerFunc)(const WallDrawerArgs &args);
		WallDrawerFunc wallfunc = nullptr;
	};
}
