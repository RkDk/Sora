#ifndef LEVELEDITOR_H_
#define LEVELEDITOR_H_

#include "Level.h"
#include "GameInput.h"
#include "DrawContext.h"
#include "Camera.h"

#define CAMERA_TRANSLATE_SPEED 500.0f
#define GRIDLINE_THICKNESS 2

class CLevelEditorTileMenu {
    
private:
    
    std::vector< CTextureImage * > m_pTiles;
    std::string m_Name;
    
public:
    
    void SetName( std::string name ) {
        m_Name = name;
    }
    
    void AddTile( CTextureImage * tile ) {
        m_pTiles.push_back( tile );
    }
    
    std::vector< CTextureImage * > & GetTiles() {
        return m_pTiles;
    }
    
    
};

class CLevelEditor {
    
private:
    
    boost::ptr_vector< CLevelEditorTileMenu > m_pTileMenus;
    
    Vector2< int > m_WindowSize;
    
    CCamera * m_pCamera;
    CLevel * m_pCurLevel;
    bool m_bEditorOn;
    int m_CurTileMenu;
    int m_CurTileIndex, m_SelectedTileIndex;
    long int m_LastSaveTime;
    
    CTextureImage * m_pPixel;
    
    void PlaceTile( int, int, int );
    
public:
    
    CLevelEditor();
    
    void SetWindowSize( int w, int h ) {
        m_WindowSize.Set( w, h );
    }
    
    void SetLevel( CLevel * level ) {
        
        m_pCurLevel = level;
    
    }
    
    void SetCamera( CCamera * pCamera ) {
        m_pCamera = pCamera;
    }
    
    bool IsOn() {
        
        return m_bEditorOn;
        
    }
    
    void Toggle() {
    
        m_bEditorOn = !m_bEditorOn;
        SDL_ShowCursor( ( m_bEditorOn )? 1 : 0 );
        
        if( m_pCamera ) {
            m_pCamera->SetCameraFixed( m_bEditorOn );
        }
        
    }
    
    void SetPixelImage( CTextureImage * pPixel ) {
        m_pPixel = pPixel;
    }
    
    void NewTileMenu( CTextureFactory * , std::string, std::string );
    
    void Input( CGameInput * , float );
    void Think();
    void Draw( CDrawContext * );

    
};

#endif
