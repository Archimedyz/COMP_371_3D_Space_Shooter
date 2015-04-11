
#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

// == External Modules ======

#include "Utility.hpp"
#include "Registry.hpp"

// ===============
// Texture2D Class
// ===============

class Texture2D {
    
public:
    
    // Create a texture from an image file
    Texture2D(const std::string & filename);
    
    // Check if the texture creation failed.
    bool Fail() const;
    
    // Bind the texture to a geometry.
    void Bind(unsigned int texUnit = 0) const;
    
    // Get the OpneGL handle to the texture.
    int GetHandle() const;
    
    // Get the name of the file that originated this texture.
    const std::string & Name() const;
    
    ~Texture2D();
    
private:
    
    // Disable copy and assignment.
    Texture2D();
    Texture2D(const Texture2D &) { }
    Texture2D & operator = (const Texture2D &) { return (*this); }
    
    bool m_fail_flag;
    unsigned int m_handle;
    std::string m_file_name;
};

// ===================================
// Texture2D Manager Class (Singleton)
// ===================================

class Texture2DManager
: public Registry<std::string, Texture2D, Texture2DManager> {
    
public:
    
    friend class Registry<std::string, Texture2D, Texture2DManager>;
    
    Texture2D * LoadFromFile(const std::string & filename)
    {
        Texture2D * pTex = Request(filename);
        
        if (pTex == 0)
        {
            pTex = new Texture2D(filename);
            
            if (pTex->Fail())
            {
                if (pTex)
                {
                    delete pTex;
                    pTex = 0;
                }
                
                std::string msg("Unable To Load The Texture: "); msg.append(filename);
                throw std::runtime_error(msg);
            }
            else
            {
                RegisterObject(filename, pTex);
            }
        }
        
        return (pTex);
    }
    
    void Unload(const std::string & filename)
    {
        UnregisterObject(filename, true);
    }
};

#endif // __TEXTURE_HPP__
