#include "LevelEditor.h"

CLevelEditor::CLevelEditor() {
    
    m_pCurLevel = nullptr;
    m_bEditorOn = false;
    m_CurTileIndex = -1;
    m_SelectedTileIndex = -1;
    m_CurTileMenu = 0;
    
}

void CLevelEditor::NewTileMenu( CTextureFactory * pTextureFactory, std::string name, std::string directory ) {
    
    CLevelEditorTileMenu * pTileMenu = new CLevelEditorTileMenu;
    std::vector< std::string > fileList;
    
    pTileMenu->SetName( name );
    
    FileUtil::FindFilesInDirectory( directory, ".png", fileList, false );
    
    for( auto iter : fileList ) {
        CTextureImage * pTile = pTextureFactory->GetObjectContent( directory + iter );
        pTileMenu->AddTile( pTile );
    }
    
    m_pTileMenus.push_back( pTileMenu );
    
}

void CLevelEditor::PlaceTile( int tileIndex, int x, int y ) {
    
    if( m_pCurLevel ) {
        
        std::vector< CTextureImage * > & tiles = m_pTileMenus[m_CurTileMenu].GetTiles();
        std::string tilePath = tiles[tileIndex]->GetPath();
        
        if( !m_pCurLevel->HasLevelTexture( tilePath ) ) {
            
            m_pCurLevel->AddLevelTexture( tilePath, tiles[tileIndex] );
            m_pCurLevel->CreatePackedTexture();
            m_pCurLevel->UpdatePackedTextureCoords();
            
        }
        
        m_pCurLevel->SetTileAt( tilePath, x, y );
        
            
    }
    
}

void CLevelEditor::Input( CGameInput * pGameInput ) {
    
    if( !m_bEditorOn || !m_pCurLevel )
        return;
    
    int mx, my;
    auto mouseState = SDL_GetMouseState( &mx, &my );
    
    if( mouseState & SDL_BUTTON( SDL_BUTTON_LEFT ) ) {
        
        if( m_CurTileIndex > -1  ) {
            
            m_SelectedTileIndex = m_CurTileIndex;
        
        } else if( m_SelectedTileIndex > -1 ) {
            
            int tX = mx / TEXTURE_RENDER_WIDTH;
            int tY = my / TEXTURE_RENDER_HEIGHT;
            int x = tX * TEXTURE_RENDER_WIDTH;
            int y = tY * TEXTURE_RENDER_HEIGHT;
            
            m_pCurLevel->RemoveTileAt( mx, my );
            PlaceTile( m_SelectedTileIndex, x, y );
                
        }
            
    }
    
}

void CLevelEditor::Think() {
    
    if( !m_bEditorOn || !m_pCurLevel )
        return;

}

void CLevelEditor::Draw( CDrawContext * pDrawContext ) {
    
    if( !m_bEditorOn || !m_pCurLevel )
        return;
    
    int mx, my;
    SDL_GetMouseState( &mx, &my );
    
    int tileX = mx / TEXTURE_RENDER_WIDTH;
    int tileY = my / TEXTURE_RENDER_HEIGHT;
    
    pDrawContext->DrawMaterial( *m_pPixel, tileX * TEXTURE_RENDER_WIDTH, tileY * TEXTURE_RENDER_HEIGHT, TEXTURE_RENDER_WIDTH, TEXTURE_RENDER_HEIGHT, 0.5f, 0.5f, 1.0f, 0.5f );

    
    int numLinesHoriz = m_WindowSize.GetX() / TEXTURE_RENDER_WIDTH;
    int numLinesVert = m_WindowSize.GetY() / TEXTURE_RENDER_HEIGHT;
    
    for( int j = 0; j < numLinesHoriz; j++ )
        pDrawContext->DrawMaterial( *m_pPixel, j * TEXTURE_RENDER_WIDTH, 0, GRIDLINE_THICKNESS, m_WindowSize.GetY(), 1.0f, 1.0f, 1.0f, 1.0f );

    for( int j = 0; j < numLinesVert; j++ )
        pDrawContext->DrawMaterial( *m_pPixel, 0, j * TEXTURE_RENDER_HEIGHT, m_WindowSize.GetX(), GRIDLINE_THICKNESS, 1.0f, 1.0f, 1.0f, 1.0f );
    
    if( m_CurTileMenu < m_pTileMenus.size() ) {
        
        
        std::vector< CTextureImage * > pTiles = m_pTileMenus[m_CurTileMenu].GetTiles();
        int numTilesInMenu = pTiles.size();
        const int tileMenuNumColumns = 3;
        int tileMenuNumRows = ( ( float ) numTilesInMenu / ( float )tileMenuNumColumns + .5f );
        int curTileIndex = 0;
        
        int tileMenuWidth = tileMenuNumColumns * TEXTURE_RENDER_WIDTH;
        int tileMenuHeight = tileMenuNumRows * TEXTURE_RENDER_HEIGHT;
        
        pDrawContext->DrawMaterial( *m_pPixel, 0, 0, tileMenuWidth, tileMenuHeight, 0.5f, 0.5f, 1.0f, 0.2f );
        
        for( int y = 0; y < tileMenuNumRows; y++ ) {
            for( int x = 0; x < tileMenuNumColumns; x++ ) {
                pDrawContext->DrawMaterial( *pTiles[curTileIndex], x * TEXTURE_RENDER_WIDTH, y * TEXTURE_RENDER_HEIGHT, TEXTURE_RENDER_WIDTH, TEXTURE_RENDER_HEIGHT, 1.0f, 1.0f, 1.0f, 1.0f );
                if( curTileIndex == m_SelectedTileIndex ) {
                    pDrawContext->DrawMaterial( *m_pPixel, x * TEXTURE_RENDER_WIDTH, y * TEXTURE_RENDER_HEIGHT, TEXTURE_RENDER_WIDTH, TEXTURE_RENDER_HEIGHT, 1.0f, 0.0f, 1.0f, 0.2f );
                }
                if( ++curTileIndex >= numTilesInMenu )
                    break;
            }
        }
        
        m_CurTileIndex = -1;
        
        if( mx < tileMenuWidth && my < tileMenuHeight ) {
            
            m_CurTileIndex = tileX + tileY * tileMenuNumColumns;
            pDrawContext->DrawMaterial( *m_pPixel, tileX * TEXTURE_RENDER_WIDTH, tileY * TEXTURE_RENDER_HEIGHT, TEXTURE_RENDER_WIDTH, TEXTURE_RENDER_HEIGHT, 1.0f, 1.0f, 1.0f, 0.3f );
        
        }
        
    }
    
}