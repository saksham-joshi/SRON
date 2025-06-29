

#pragma once

#ifndef _SEEK_TCKR_H
#define _SEEK_TCKR_H

#include "_token_map_.hpp"

struct SeekTracker{


    BytecodePos_t _position;

    // stores the flag before SeekTracker::_position
    Flag_t _flag;

    inline SeekTracker(BytecodePos_t __position, Flag_t __flag) : _position(__position), _flag(__flag){}

};

#endif