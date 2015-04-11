
#ifndef __REGISTRY_HPP__
#define __REGISTRY_HPP__

#include "Utility.hpp"
#include <map>

// =======================
// Template Class Registry
// =======================

template<class _K, class _X, class _C>
class Registry {
    
public:
    
    _X * Request(const _K & registry_key)
    {
        _X * rez;
        typename RegMap::iterator _Ptr = m_registry_map.find(registry_key);
        
        if (_Ptr != m_registry_map.end())
        {
            rez = (*_Ptr).second;
        }
        else
        {
            rez = 0;
        }
        
        return (rez);
    }
    
    void RegisterObject(const _K & registry_key, _X * const object)
    {
        std::pair<typename RegMap::iterator, bool> rez;
        rez = m_registry_map.insert(typename RegMap::value_type(registry_key, object));
        
        if (!rez.second)
        {
            throw std::runtime_error(std::string("Key Collision !"));
        }
    }
    
    _X * UnregisterObject(const _K & registry_key, bool delete_object)
    {
        _X * rez = 0;
        typename RegMap::iterator _Ptr = m_registry_map.find(registry_key);
        
        if (_Ptr != m_registry_map.end())
        {
            if (delete_object)
            {
                delete ((*_Ptr).second);
                (*_Ptr).second = 0;
            }
            
            rez = (*_Ptr).second;
            m_registry_map.erase(_Ptr);
        }
        
        return (rez);
    }
    
    void Clear()
    {
        if (!m_registry_map.empty())
        {
            typename RegMap::iterator _Ptr = m_registry_map.begin();
            typename RegMap::const_iterator _End = m_registry_map.end();
            
            while (_Ptr != _End)
            {
                delete ((*_Ptr).second);
                ++_Ptr;
            }
            
            m_registry_map.clear();
        }
    }
    
public:
    
    static _C * Instance()
    {
        if (m_instance == 0)
        {
            m_instance = new _C;
        }
        return (m_instance);
    }
    
    static void Kill()
    {
        if (m_instance)
        {
            delete m_instance;
            m_instance = 0;
        }
    }
    
private:
    
    typedef std::map<_K, _X *> RegMap;
    RegMap m_registry_map;
    static _C * m_instance;
    
protected:
    
    Registry() { }
    virtual ~Registry() { Clear(); }
};

template<class _K, class _X, class _C> _C * Registry<_K, _X, _C>::m_instance = 0;

#endif // __REGISTRY_HPP__
