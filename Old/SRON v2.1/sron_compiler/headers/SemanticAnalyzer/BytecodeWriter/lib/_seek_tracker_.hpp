

#pragma once

#ifndef _SEEK_TCKR_H
#define _SEEK_TCKR_H

#include "_token_map_.hpp"

struct SeekTracker{


    long _position;

    // stores the flag before SeekTracker::_position
    flag_t _flag;

    inline SeekTracker(long __position, flag_t __flag) : _position(__position), _flag(__flag){}

};

#endif