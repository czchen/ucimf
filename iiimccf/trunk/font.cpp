#include "graphdev.h"
#include "font.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Font* Font::_instance = 0;

Font* Font::getInstance()
{
  if ( _instance == 0 )
  {
    _instance = new Font;
  }
  return _instance;
}

Font::Font()
{
  font_path = getenv("UCIMF_FONTPATH");

  FT_Init_FreeType( &library ); 
  FT_New_Face( library, font_path, 0, &face);

  /* get font size info */
  font_width=16;
  font_height=16;
  
  //FT_Set_Char_Size( face, font_width*64 , font_height*64, 0, 0 );
  FT_Set_Pixel_Sizes( face, font_width, font_height);
  //FT_Select_Charmap( face, FT_ENCODING_UNICODE );

  if( face->available_sizes !=0 ) // stand for the pcf font.
  {
    FT_Set_Charmap( face, face->charmaps[0] );

    int fh = face->available_sizes->height;
    int fw = face->available_sizes->width;
    if( fh == 0 )
    {
      font_height = fw;
    }
    else
    {
      font_height = fh;
    }
    
    if( fw == 0 )
    {
      font_width = fh;
    }
    else
    {
      font_width = fw;
    }
  }
  
}

Font::~Font()
{
  FT_Done_Face(face);
  FT_Done_FreeType(library);
}

int Font::Height()
{
  return font_height;
}

int Font::Width()
{
  return font_width;
}

void Font::render( int code, CharBitMap& charbitmap )
{
  FT_Error error;
  FT_ULong charcode = static_cast<FT_ULong>(code);
  /*
  cout.setf(ios_base::hex, ios_base::basefield );
  cout << "charcode: [" << charcode << "] in UTF-16" << endl;
  cout.setf(ios_base::dec, ios_base::basefield );
  */
  
  int glyph_index = FT_Get_Char_Index( face, charcode );
  FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
  FT_Render_Glyph( face->glyph, FT_RENDER_MODE_MONO );
  
  FT_Bitmap bmap=face->glyph->bitmap;


  cerr << "rows:" << bmap.rows << endl;
  cerr << "width:" << bmap.width << endl;
  cerr << "pitch:" << bmap.pitch << endl << endl;

  charbitmap.h = bmap.rows;
  charbitmap.w = bmap.width;
  charbitmap.wBytes = bmap.pitch;
  int total_size = bmap.rows * bmap.pitch;
  charbitmap.pBuf = new char[ total_size ];
  memcpy( charbitmap.pBuf, bmap.buffer, total_size );
  charbitmap.isMulti8 = (bmap.width % 8) ? false : true;
}


int Font::length( int code )
{
  FT_ULong charcode = static_cast<FT_ULong>(code);

  int glyph_index = FT_Get_Char_Index( face, charcode );
  FT_Load_Glyph( face, glyph_index, FT_LOAD_DEFAULT );
  FT_Render_Glyph( face->glyph, FT_RENDER_MODE_MONO );
  
  int result = face->glyph->bitmap.width;
  
  return result;
}
