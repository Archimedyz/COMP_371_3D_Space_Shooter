
// ===============================================================================================================
// -*- C++ -*-
//
// Utility.hpp - Common includes and definition for the application.
//
// Copyright (c) 2010 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#if defined (_MSC_VER)
#pragma warning (disable: 4996) // Disable the CRT lib deprecation warning.
#pragma warning (disable: 4290) // Exception specification ignored warning.
#pragma warning (disable: 4505) // Unreferenced local function removed.
#pragma warning (disable: 4201) // Nameless struct/union.
#endif

#if defined (_WIN32) && !defined (WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

// == External Modules ======

// System, C-ANSI Includes:
#ifdef _WIN32
#include <Windows.h>
#include <commdlg.h>
#endif
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// OpenGL Includes:
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

// Std C++ Includes:
#include <stdexcept>
#include <iostream>
#include <string>

// ==========================
// Info Log Class (Singleton)
// ==========================

class Log {
    
public:
    
    static Log& Instance();
    bool IsOpen() const;
    
    bool Open(const char * filename);
    void Close();
    void Flush();
    
public:
    
    Log& operator << (const std::string & text);
    Log& operator << (const char * text);
    
    Log& operator << (char ch);
    Log& operator << (const void * ptr);
    
    Log& operator << (short value);
    Log& operator << (unsigned short value);
    
    Log& operator << (int value);
    Log& operator << (unsigned int value);
    
    Log& operator << (float value);
    Log& operator << (double value);
    
private:
    
    Log();
    Log(const Log&) { }
    Log& operator = (const Log&) { return (*this); }
    ~Log();
    
    FILE * m_pFile;
    bool m_open_flag;
};

// ===================
// Memory Buffer Class
// ===================

class MemoryBuffer {
    
public:
    
    MemoryBuffer();
    MemoryBuffer(unsigned int size, bool self_release = true);
    ~MemoryBuffer();
    
    bool Allocate(unsigned int size, bool self_release = true);
    void * GetBufferPointer() const;
    
    char * ReadLine(char * buffer, unsigned int count);
    int ReadChar();
    
    int Seek(long offset, int origin);
    void Free();
    bool Eof() const;
    
private:
    
    unsigned int m_size;
    unsigned int m_position;
    
    void * m_stream;
    bool m_self_release;
    bool m_end_of_stream;
    
    // Disable copy for now...
    MemoryBuffer(const MemoryBuffer &) { }
    MemoryBuffer & operator = (const MemoryBuffer &) { return (*this); }
};

// ================
// Misc Definitions
// ================

#define LOG_INFO(x)    { Log::Instance() << x << '\n'; }
#define LOG_WARNING(x) { Log::Instance() << "WARNING: " << x << '\n'; std::cerr << x << std::endl; }
#define LOG_ERROR(x)   { Log::Instance() << "ERROR: "   << x << '\n'; std::cerr << x << std::endl; }

// Used in OpenFileDialog(...)
const int SAVE_FILE = 1;
const int OPEN_FILE = 2;

// =================
// Utility Functions
// =================

void glBegin2D(int window_width, int window_height);
void glEnd2D();
int glPrintf(int x, int y, const char * format, ...);

int CalcFPS();
unsigned char * LoadUncompressedTGA(const char * fileName, int & width, int & height, int & bytesPerPixel);
const char * OpenFileDialog(void * hwnd, int mode, const char * filter, const char * ext);

#endif // __UTILITY_HPP__
