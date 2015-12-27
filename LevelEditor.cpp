#include "LevelEditor.h"

CLevelEditor::CLevelEditor() {
    
    m_pCurLevel = nullptr;
    m_pCamera = nullptr;
    m_bEditorOn = false;
    m_CurTileIndex = -1;
    m_SelectedTileIndex = -1;
    m_CurTileMenu = 0;
    m_LastSaveTime = -5000;
    
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

void CLevelEditor::Input( CGameInput * pGameInput, float dps ) {
    
    if( !m_bEditorOn || !m_pCurLevel )
        return;
    
    int mx, my;
    auto mouseState = SDL_GetMouseState( &mx, &my );
    
    
    Vector2< float > cameraTranslate;
    
    if( m_pCamera ) {
        
        cameraTranslate = m_pCamera->GetTranslate();
        
    }
    
    int tX = ( mx - cameraTranslate.GetX() ) / TEXTURE_RENDER_WIDTH;
    int tY = ( my - cameraTranslate.GetY() ) / TEXTURE_RENDER_HEIGHT;
    
    if( mx - cameraTranslate.GetX() < 0 )
        tX--;
    
    if( my - cameraTranslate.GetY() < 0 )
        tY--;
    
    int x = tX * TEXTURE_RENDER_WIDTH;
    int y = tY * TEXTURE_RENDER_HEIGHT;

    
    if( mouseState & SDL_BUTTON( SDL_BUTTON_LEFT ) ) {
        
        if( m_CurTileIndex > -1  ) {
            
            m_SelectedTileIndex = m_CurTileIndex;
        
        } else if( m_SelectedTileIndex > -1 ) {
            
            m_pCurLevel->RemoveTileAt( mx - cameraTranslate.GetX(), my - cameraTranslate.GetY() );
            PlaceTile( m_SelectedTileIndex, x, y );
                
        }
            
    }
    
    if( m_pCamera ) {
    
        if( pGameInput->KeyDown( SDL_SCANCODE_UP ) ) {
         
            m_pCamera->Translate( 0.0f, -CAMERA_TRANSLATE_SPEED * dps );
            
        }

        if( pGameInput->KeyDown( SDL_SCANCODE_DOWN ) ) {
            
            m_pCamera->Translate( 0.0f, CAMERA_TRANSLATE_SPEED * dps );
            
        }
      
        if( pGameInput->KeyDown( SDL_SCANCODE_LEFT ) ) {
            
            m_pCamera->Translate( -CAMERA_TRANSLATE_SPEED * dps, 0.0f );
            
        }
        
        if( pGameInput->KeyDown( SDL_SCANCODE_RIGHT ) ) {
            
            m_pCamera->Translate( CAMERA_TRANSLATE_SPEED * dps, 0.0f );
            
        }

    }
    
    
    if( pGameInput->KeyDown( SDL_SCANCODE_1 ) ) {
        
        if( m_SelectedTileIndex > -1 ) {
            
            m_pCurLevel->RemoveTileAt( mx - cameraTranslate.GetX(), my - cameraTranslate.GetY() );
            PlaceTile( m_SelectedTileIndex, x, y );
        
        }
        
    }
    
    if( pGameInput->KeyDown( SDL_SCANCODE_3 ) ) {
        
        
        m_pCurLevel->RemoveTileAt( mx - cameraTranslate.GetX(), my - cameraTranslate.GetY() );

        
    }
    
    if( pGameInput->ShiftMod() && pGameInput->KeyDownOnce( SDLK_0 ) ) {
        
        if( m_pCurLevel ) {
            
            m_LastSaveTime = SDL_GetTicks();
            m_pCurLevel->Save( m_pCurLevel->GetPath() );
        
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
    
    Vector2< float > cameraTranslate;
    
    if( m_pCamera ) {
     
        cameraTranslate = m_pCamera->GetTranslate();
    
    }
    
    float gridOffsetX = cameraTranslate.GetX() - ( ( int )( cameraTranslate.GetX() / TEXTURE_RENDER_WIDTH ) * TEXTURE_RENDER_WIDTH );
    float gridOffsetY = cameraTranslate.GetY() - ( ( int )( cameraTranslate.GetY() / TEXTURE_RENDER_HEIGHT ) * TEXTURE_RENDER_HEIGHT );
    
    int selectedTileX = mx / TEXTURE_RENDER_WIDTH_EDITOR;
    int selectedTileY = my / TEXTURE_RENDER_HEIGHT_EDITOR;
    
    int tileX = ( mx - gridOffsetX ) / TEXTURE_RENDER_WIDTH;
    int tileY = ( my - gridOffsetY ) / TEXTURE_RENDER_HEIGHT;
    
    pDrawContext->DrawMaterial( *m_pPixel, tileX * TEXTURE_RENDER_WIDTH + gridOffsetX, tileY * TEXTURE_RENDER_HEIGHT + gridOffsetY, TEXTURE_RENDER_WIDTH, TEXTURE_RENDER_HEIGHT, 0.5f, 0.5f, 1.0f, 0.5f );

    
    int numLinesHoriz = m_WindowSize.GetX() / TEXTURE_RENDER_WIDTH;
    int numLinesVert = m_WindowSize.GetY() / TEXTURE_RENDER_HEIGHT;
    
    for( int j = 0; j < numLinesHoriz + 1; j++ )
        pDrawContext->DrawMaterial( *m_pPixel, j * TEXTURE_RENDER_WIDTH + gridOffsetX, gridOffsetY - TEXTURE_RENDER_HEIGHT, GRIDLINE_THICKNESS, m_WindowSize.GetY() + TEXTURE_RENDER_HEIGHT * 2, 1.0f, 1.0f, 1.0f, 1.0f );

    for( int j = 0; j < numLinesVert + 1; j++ )
        pDrawContext->DrawMaterial( *m_pPixel, gridOffsetX - TEXTURE_RENDER_WIDTH, j * TEXTURE_RENDER_HEIGHT + gridOffsetY, m_WindowSize.GetX() + TEXTURE_RENDER_WIDTH * 2, GRIDLINE_THICKNESS, 1.0f, 1.0f, 1.0f, 1.0f );
    
    if( m_CurTileMenu < m_pTileMenus.size() ) {
        
        
        std::vector< CTextureImage * > pTiles = m_pTileMenus[m_CurTileMenu].GetTiles();
        int numTilesInMenu = pTiles.size();
        const int tileMenuNumColumns = 3;
        int tileMenuNumRows = ( ( float ) numTilesInMenu / ( float )tileMenuNumColumns + .99f );
        int curTileIndex = 0;
        
        int tileMenuWidth = tileMenuNumColumns * TEXTURE_RENDER_WIDTH_EDITOR;
        int tileMenuHeight = tileMenuNumRows * TEXTURE_RENDER_HEIGHT_EDITOR;
        
        pDrawContext->DrawMaterial( *m_pPixel, 0, 0, tileMenuWidth, tileMenuHeight, 0.5f, 0.5f, 1.0f, 0.2f );
        
        for( int y = 0; y < tileMenuNumRows; y++ ) {
            for( int x = 0; x < tileMenuNumColumns; x++ ) {
                pDrawContext->DrawMaterial( *pTiles[curTileIndex], x * TEXTURE_RENDER_WIDTH_EDITOR, y * TEXTURE_RENDER_HEIGHT_EDITOR, TEXTURE_RENDER_WIDTH_EDITOR, TEXTURE_RENDER_HEIGHT_EDITOR, 1.0f, 1.0f, 1.0f, 1.0f );
                if( curTileIndex == m_SelectedTileIndex ) {
                    pDrawContext->DrawMaterial( *m_pPixel, x * TEXTURE_RENDER_WIDTH_EDITOR, y * TEXTURE_RENDER_HEIGHT_EDITOR, TEXTURE_RENDER_WIDTH_EDITOR, TEXTURE_RENDER_HEIGHT_EDITOR, 1.0f, 0.0f, 1.0f, 0.2f );
                }
                if( ++curTileIndex >= numTilesInMenu )
                    break;
            }
        }
        
        m_CurTileIndex = -1;
        
        if( mx < tileMenuWidth && my < tileMenuHeight ) {
            
            m_CurTileIndex = selectedTileX + selectedTileY * tileMenuNumColumns;
            pDrawContext->DrawMaterial( *m_pPixel, selectedTileX * TEXTURE_RENDER_WIDTH_EDITOR, selectedTileY * TEXTURE_RENDER_HEIGHT_EDITOR, TEXTURE_RENDER_WIDTH_EDITOR, TEXTURE_RENDER_HEIGHT_EDITOR, 1.0f, 1.0f, 1.0f, 0.3f );
        
        }
        
    }
    
    if( SDL_GetTicks() - m_LastSaveTime < 1000 ) {
        
        pDrawContext->DrawMaterial( *m_pPixel, 0.0f, 0.0f, m_WindowSize.GetX(), m_WindowSize.GetY() * .1f, 0.0f, 1.0f, 0.0f, 0.5f );
        
    }
    
}