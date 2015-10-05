#include "EntityContext.h"

void CEntityContext::InitAllShaders() {
    
    int numShaders = m_pGraphicsContext->GetShaderCount();
    
    int width, height;
    m_pGraphicsContext->GetWindowSize( &width, &height );
    
    for( int j = 0; j < numShaders; j++ ) {
    
        int id = m_pGraphicsContext->GetShaderIDFromIndex( j );
        
        m_pDrawContext->UseShaderProgram( id );
        
        m_pDrawContext->Calculate2DProjectionMatrix( width, height );
        
        CMatrix< float > viewMat;
        viewMat.Identity();
        m_pDrawContext->UpdateViewMatrix( &viewMat );
        
    }
    
}

void CEntityContext::LoadResources( std::string filename ) {

    std::ifstream resfile( filename );
    
    if( resfile.is_open() ) {
        
    
        Log::Log( "Opening resource file: " + filename );
    
        while( !resfile.eof() ) {
            
            std::string cmd( "" );
            resfile >> cmd;
            
            bool isTexture = false, isSound = false;
            
            if( cmd == "TEXTURE" )
                isTexture = true;
            
            if( cmd == "SOUND" )
                isSound = true;
            
            if( isTexture || isSound ) {
                
                std::string fileInput( "" );
                resfile >> fileInput;
                
                bool wildcardSearch = false;
                std::string path( "" );
                std::vector< std::string > fileList;
                
                int wcPos = fileInput.find( "*" );
                
                if( wcPos != std::string::npos ) {
                    
                    wildcardSearch = true;
                    path = fileInput.substr( 0, wcPos - 1 );
                    std::string extension = fileInput.substr( wcPos + 1 );
                    
                    FileUtil::FindFilesInDirectory( path, extension, fileList,  false, true );
                    
                } else {
                    
                    path = fileInput;
                    fileList.push_back( path );
                    
                }
                
                for( int j = 0; j < fileList.size(); j++ ) {
                    
                    if( isTexture )
                        TextureFactory()->NewTexture( fileList[j] );
                    else
                        SoundFactory()->NewSound( fileList[j] );
                    
                    
                }
                
                
            }
            
            if( cmd == "FONT" ) {
                
                std::string fontInput( "" );
                int fontSize = 0;
                
                resfile >> fontInput >> fontSize;
                
                FontFactory()->NewFont( fontInput, fontSize );
                
            }
            
        }

        
        resfile.close();
        
    } else
        Log::Log( "Failed to open non-existent resource file: " + filename );


}