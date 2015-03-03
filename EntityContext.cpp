#include "EntityContext.h"

void CEntityContext::LoadResources( std::string filename ) {

    std::ifstream resfile( filename );
    
    if( resfile.is_open() )
        Log::Log( "Opening resource file: " + filename );
    else
        Log::Log( "Failed to open non-existent resource file: " + filename );
    
    while( !resfile.eof() ) {
     
        std::string cmd( "" );
        resfile >> cmd;
        
        if( cmd == "TEXTURE" ) {
         
            std::string textureInput( "" );
            resfile >> textureInput;
            
            bool wildcardSearch = false;
            std::string path( "" );
            std::vector< std::string > fileList;

            int wcPos = textureInput.find( "*" );
            
            if( wcPos != std::string::npos ) {
                
                wildcardSearch = true;
                path = textureInput.substr( 0, wcPos - 1 );
                std::string extension = textureInput.substr( wcPos + 1 );
                
                FileUtil::FindFilesInDirectory( path, extension, fileList,  false );
                
            } else {
             
                path = textureInput;
                fileList.push_back( path );
                
            }
            
            for( int j = 0; j < fileList.size(); j++ ) {

                TextureFactory()->NewTexture( fileList[j] );
                
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
    
}