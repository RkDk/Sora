#include "FreeTypeContext.h"

void CFreeTypeContext::Init() {
    
    FT_Init_FreeType( &m_FTLib );

    
}

CFreeTypeContext::~CFreeTypeContext() {

    FT_Done_FreeType( m_FTLib );
    
}
