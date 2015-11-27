#include "Level.h"

void CLevel::Save( std::string path ) {
    
    std::stringstream newMapData;
    auto numTextures = m_textureList.size();
    newMapData << "TEXTURELIST\n";
    for( int j = 1; j <= numTextures; j++ ) {
        newMapData << j << " " << m_textureList[j] << "\n";
    }
    newMapData << "ENDTEXTURELIST\n";
    
    newMapData << "TEXTUREMAP\n";
    for( auto iter : m_textureInfoList ) {
        newMapData << iter.textureListIndex << " " << iter.worldPos.GetX() << " " << iter.worldPos.GetY() << "\n";
    }
    newMapData << "ENDTEXTUREMAP\n";

    Log::Log( "Saving map: "  + path );

    std::ofstream mapFile( path );
    mapFile.write( newMapData.str().c_str(), newMapData.str().length() );
    mapFile.close();
    
}

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

        std::ifstream levelFile( path );
        m_LastTextureKey = -1;
        
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
                            m_textureList.emplace( texID, texPath );
                            
                            if( texID > m_LastTextureKey )
                                m_LastTextureKey = texID;
                            
                            CTextureImage * image = pTextureFactory->GetObjectContent( texPath );
                            
                            if( image ) {
                                
                                m_textureData.emplace( texID, image );
                                
                            }
                            
                        }
                    } else
                        break;
                }
                
                CreatePackedTexture();
                
                
            } else if( line == "TEXTUREMAP" ) {
                
                while( 1 ) {
                    
                    std::getline( levelFile, line );
                    
                    if( line != "ENDTEXTUREMAP" && !levelFile.eof() ) {
                    
                        std::istringstream isstream( line );
                        
                        int texID;
                        float tX, tY;
                        
                        isstream >> texID >> tX >> tY;
                        
                        CTextureInfo texInfo( texID, tX, tY );
                        m_textureInfoList.push_back( texInfo );
                        
                        CreateNewTile( texID, tX * TEXTURE_RENDER_WIDTH, tY * TEXTURE_RENDER_HEIGHT );
     
                        
                    } else
                        break;
                        
                    
                }
                
            }
            
        }
        
        Log::Log( "Successfully loaded level" );
        levelFile.close();
        
    }
    
    
}

void CLevel::RemoveTileAt( int x, int y ) {
    
    for( boost::ptr_vector< CLevelTile >::iterator iter = m_vTiles.begin(); iter != m_vTiles.end(); ) {
        
        float x2 = ( *iter ).w + ( *iter ).x;
        float y2 = ( *iter ).h + ( *iter ).y;
        bool erase = false;
        
        if( x > ( *iter ).x && y > ( *iter ).y ) {
            
            if( x < x2 && y < y2 ) {
                
                iter = m_vTiles.erase( iter );
                erase = true;
                
            }
            
        }
        
        if( !erase )
            iter++;
        
    }
    
}

void CLevel::CreateNewTile( int texID, int x, int y ) {
    
    CLevelTile * newTile = new CLevelTile;
    Vector4< float > & c = m_textureCoord[texID];
    
    newTile->texID = texID;
    
    newTile->x = x;
    newTile->y = y;
    
    newTile->w = TEXTURE_RENDER_WIDTH;
    newTile->h = TEXTURE_RENDER_HEIGHT;
    
    
    newTile->s = c.GetX();
    newTile->t = c.GetY();
    newTile->m = c.GetZ();
    newTile->n = c.GetW();
    
    m_vTiles.push_back( newTile );
    
}

bool CLevel::HasLevelTexture( std::string texture ) {
 
    for( auto iter : m_textureList ) {
        if( iter.second == texture )
            return true;
    }
    
    return false;
    
}

void CLevel::AddLevelTexture( std::string texture, CTextureImage * image ) {

    int texID = -1;
    
    for( auto iter : m_textureList ) {
        if( iter.second == texture ) {
            texID = iter.first;
            break;
        }
    }
    
    if( texID < 0 ) {
        
        int newTexID = m_LastTextureKey + 1;
        
        for( int j = 1; j <= m_LastTextureKey; j++ ) {
            
            if( m_textureList.find( j ) == m_textureList.end() ) {
                
                newTexID = j;
                break;
                
            }
            
        }
        
        m_textureList.emplace( newTexID, texture );
        m_textureData.emplace( newTexID, image );
        
        if( newTexID > m_LastTextureKey )
            m_LastTextureKey = newTexID;
        
        
    }
    
}

int CLevel::GetLevelTextureCount( std::string texture ) {
    
    int c = 0;
    int texID = -1;
    
    for( auto iter : m_textureList ) {
        if( iter.second == texture ) {
            texID = iter.first;
            break;
        }
    }
    
    for( auto iter : m_vTiles ) {
        if( iter.texID == texID )
            c++;
    }
    
    return c;
    
}

void CLevel::RemoveLevelTexture( std::string texture ) {

    int texID = -1;
    
    for( auto iter : m_textureList ) {
        if( iter.second == texture ) {
            texID = iter.first;
            break;
        }
    }
    
    if( texID >= 0 ) {
        
        m_textureList.erase( texID );
        m_textureCoord.erase( texID );
        m_textureData.erase( texID );
        
    }
    
}

void CLevel::SetTileAt( std::string path, int x, int y ) {

    int texID = -1;
    
    for( auto iter : m_textureList ) {
        
        if( iter.second == path ) {
            
            texID = iter.first;
            break;
            
        }

    }
    
    if( texID >= 0 ) {
        
        CreateNewTile( texID, x, y );
        
    }
    
}

void CLevel::UpdatePackedTextureCoords() {
    
    for( int j = 0; j < m_vTiles.size(); j++ ) {
        
        int texID = m_vTiles[j].texID;
        Vector4< float > & c = m_textureCoord[texID];
        
        m_vTiles[j].s = c.GetX();
        m_vTiles[j].t = c.GetY();
        m_vTiles[j].m = c.GetZ();
        m_vTiles[j].n = c.GetW();
        
        
    }
    
}

void CLevel::CreatePackedTexture() {
  
    std::unordered_map< int, Vector3< int > > textureOffset;
    Vector2< int > packedTextureSize( 0, 0 );
    
    m_textureCoord.clear();
    
    //Determine the appropriate size of the packed texture and record the offset/width/height of each texture in the packed texture
    for( auto iter : m_textureData ) {
        
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
        
        m_textureCoord.emplace( iter.first, Vector4< float >( ( float )iter.second.GetX() / ( float )packedTextureSize.GetX(), 0.0f, ( ( float )( iter.second.GetX() + iter.second.GetY() ) ) / ( float )packedTextureSize.GetX(), ( ( float )iter.second.GetZ() / ( float )packedTextureSize.GetY() ) ) );
        
    }
    
    
    //Render to the packed texture
    for( auto iter : m_textureData ) {

        Vector3< int > & offset = textureOffset[iter.first];
        m_LevelTextureSheet.AddPixelData( iter.second->GetFrame( 0 ).GetPixelData(), offset.GetX(), 0, offset.GetY(), offset.GetZ() );
        
    }
    
    m_LevelTextureSheet.CreateGLTexture();
    
    
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