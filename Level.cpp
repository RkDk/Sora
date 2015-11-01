#include "Level.h"

void CLevel::Load( std::string path, CTextureFactory * pTextureFactory ) {
    
    /*
    
        LEVEL FORMAT 
        A very crude level format.
     
        TEXTURELIST
        <#> <Texture Path>
        ENDTEXTURELIST
        TEXTUREMAP
        <#Texture> <x> <y> (flag) (flag) (...) END
        ENDTEXTUREMAP
    */
    
    if( !Util::DoesFileExist( path ) ) {
        
        Log::Error( "Attempted to load non-existent level: " + path );
        
    } else {
        
        Log::Log( "Loading level file: " + path );
        
        std::unordered_map< int, std::string > textureList;
        std::unordered_map< int, Vector3< int > > textureOffset;
        std::unordered_map< int, Vector4< float > > textureCoord;
        std::unordered_map< int, CTextureImage * > textureData;
        
        std::ifstream levelFile( path );
        
        while( !levelFile.eof() ) {
        
            std::string line( "" );
            std::getline( levelFile, line );
            
            if( line == "TEXTURELIST" ) {
                
                //Grab all the textures and load them from the texture factory
                while( 1 ) {
                    
                    std::getline( levelFile, line );
               
                    if( line != "ENDTEXTURELIST" && !levelFile.eof() ) {
                       
                        std::istringstream isstream( line );
                    
                        if( line != "ENDTEXTURELIST" ) {
                        
                            int texID;
                            std::string texPath;

                            isstream >> texID >> texPath;
                            textureList.emplace( texID, texPath );
                            
                            CTextureImage * image = pTextureFactory->GetObjectContent( texPath );
                            
                            if( image ) {
                                
                                textureData.emplace( texID, image );
                                
                            }
                            
                        }
                    } else
                        break;
                }
                
                Vector2< int > packedTextureSize( 0, 0 );
                
                //Determine the appropriate size of the packed texture and record the offset/width/height of each texture in the packed texture
                for( auto iter : textureData ) {
                    
                    CTextureImage * image = iter.second;
                    int width, height;
                    
                    image->GetFrameSize( 0, &width, &height );
                    
                    textureOffset.emplace( iter.first, Vector3< int >( packedTextureSize.GetX(), width, height ) );
                    packedTextureSize.SetX( packedTextureSize.GetX() + width );
                    
                    if( height > packedTextureSize.GetY() )
                        packedTextureSize.SetY( height );
                    
                }
                
                packedTextureSize.Set( Util::RoundToPower( packedTextureSize.GetX(), 2 ), Util::RoundToPower( packedTextureSize.GetY(), 2 ) );
                
                m_LevelTextureSheet.InitPixels( packedTextureSize.GetX(), packedTextureSize.GetY() );
                
                //Determine the s,t,m,n coordinates of the texture (for GLSL rendering)
                for( auto iter : textureOffset ) {
                    
                    textureCoord.emplace( iter.first, Vector4< float >( ( float )iter.second.GetX() / ( float )packedTextureSize.GetX(), 0.0f, ( ( float )( iter.second.GetX() + iter.second.GetY() ) ) / ( float )packedTextureSize.GetX(), ( ( float )iter.second.GetZ() / ( float )packedTextureSize.GetY() ) ) );
                    
                }
                
                
                //Render to the packed texture
                for( auto iter : textureData ) {
                    
                    Vector3< int > & offset = textureOffset[iter.first];
                    m_LevelTextureSheet.AddPixelData( iter.second->GetFrame( 0 ).GetPixelData(), offset.GetX(), 0, offset.GetY(), offset.GetZ() );
                    
                }
                
                m_LevelTextureSheet.CreateGLTexture();
                
            } else if( line == "TEXTUREMAP" ) {
                
                while( 1 ) {
                    
                    std::getline( levelFile, line );
                    
                    if( line != "ENDTEXTUREMAP" && !levelFile.eof() ) {
                    
                        std::istringstream isstream( line );
                        
                        int texID;
                        float tX, tY;
                        
                        isstream >> texID >> tX >> tY;
                        
                        CLevelTile * newTile = new CLevelTile;
                        Vector4< float > & c = textureCoord[texID];
                        
                        newTile->x = tX * TEXTURE_RENDER_WIDTH;
                        newTile->y = tY * TEXTURE_RENDER_HEIGHT;
                        
                        newTile->w = TEXTURE_RENDER_WIDTH;
                        newTile->h = TEXTURE_RENDER_HEIGHT;
                       
                        
                        newTile->s = c.GetX();
                        newTile->t = c.GetY();
                        newTile->m = c.GetZ();
                        newTile->n = c.GetW();

                        m_vTiles.push_back( newTile );
                        
                    } else
                        break;
                        
                    
                }
                
            }
            
        }
        
        Log::Log( "Successfully loaded level" );
        levelFile.close();
        
    }
    
    
}

void CLevel::Draw( CDrawContext * pDrawContext ) {
    
    pDrawContext->SetTexture( m_LevelTextureSheet.GetTexture() );
    pDrawContext->SetDrawColor( 1.0f, 1.0f, 1.0f, 1.0f );

    BOOST_FOREACH( CLevelTile & t, m_vTiles ) {
        pDrawContext->StartDraw();
            pDrawContext->SetPos( t.x, t.y );
            pDrawContext->SetScale( t.w, t.h );
            pDrawContext->SetTexCoord( t.s, t.t, t.m, t.t, t.m, t.n, t.s, t.n );
        pDrawContext->EndDraw();
        
    }

}