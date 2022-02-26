#pragma once

#include "Arduino.h"

#define COLORS_IN_PALETTE 5

struct Color {
    uint8_t R;
    uint8_t G;
    uint8_t B;
};

struct Palette {
    Color A;
    Color B;
    Color C;
    Color D;
    Color E;
};

constexpr Color PALETTES[][5] = {{{13,42,46},    {45,93,99},     {30,122,143},   {20,126,150},   {36,123,140}},
                                {{121,135,27},  {181,112,0},    {186,129,43},   {237,135,33},   {250,105,72}},
                                {{17,212,127},  {98,179,101},   {74,224,212},   {25,250,239},   {169,209,206}},
                                {{6,106,207},   {2,97,240},     {24,113,245},   {80,222,153},   {121,163,189}},
                                {{46,2,2},      {110,13,13},    {145,71,31},    {163,75,11},    {163,143,41}},
                                {{143,163,70},  {196,147,33},   {232,171,16},   {201,166,91},   {247,215,7}},
                                {{186,19,86},   {186,48,99},    {125,53,219},   {209,43,181},   {227,79,222}},
                                {{8,158,86},    {9,219,177},    {37,204,179},   {106,247,111},  {53,233,240}},
                                {{199,107,42},  {237,81,33},    {237,124,19},   {235,116,80},   {237,176,107}},
                                {{22,74,186},   {83,61,153},    {133,70,179},   {141,95,184},   {183,28,255}},
                                {{46,4,199},    {152,5,237},    {192,101,194},  {174,108,212},  {243,190,247}},
                                {{145,84,15},   {122,78,48},    {121,176,58},   {201,143,85},   {245,168,24}},
                                {{78,191,63},   {141,158,63},   {186,189,108},  {146,240,141},  {225,255,156}},
                                {{163,0,52},    {153,96,135},   {207,23,191},   {201,62,190},   {207,122,191}},
                                {{74,122,10},   {41,173,29},    {69,156,61},    {84,247,20},    {139,245,10}},
                                {{24,77,8},     {105,95,22},    {84,176,58},    {146,199,2},    {214,145,41}}};