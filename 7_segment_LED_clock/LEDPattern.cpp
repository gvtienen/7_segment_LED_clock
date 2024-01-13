/*
   7-segment-LED-clock: https://github.com/gvtienen/7_segment_LED_clock
   Copyright (C) 2023 Geert Vantienen

   This file is part of 7-segment-LED-clock:
   7-segment-LED-clock is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "LEDPattern.h"

const int max_rows = 9;
const int max_columns = 25;
uint32_t colormatrix[max_rows][max_columns];


typedef enum
{
    Color_DarkGreen=0x006400,
    Color_Red=0xFF0000,
    Color_White=0xFFFFFF
} Colors;


// digit_id : 1-4, segment: a-g, lednb: 1-3
uint32_t get_matrix_color(int digit_id, char segment, int lednb)
{ 
  int row = 0;
  int col = 0;
  switch(segment)
  {
    case 'a' : row = 0; col += lednb; break;
    case 'b' : row = 0 + lednb; col += 4; break;
    case 'c' : row = 4 + lednb; col += 4; break;
    case 'd' : row = 8; col += lednb; break;
    case 'e' : row = 4 + lednb; break;
    case 'f' : row = 0 + lednb; break;
    case 'g' : row = 4; col += lednb;  break;
  }
  switch(digit_id)
  {
    case 1 : break;
    case 2 : col += 6; break;
    case 3 : col += 14; break;
    case 4 : col += 20; break;
  }
  return colormatrix[row][col];
}

// dot_id : 1-2
uint32_t get_matrix_dots_color(int dot_id)
{
  if (dot_id == 1)
    return colormatrix[2][12];
  else
    return colormatrix[6][12];
}

void initColorMatrix_hline()
{
  for (int y=0; y<max_rows; y++)
    for (int x=0; x<max_columns; x++)
      if (y==0)
        colormatrix[y][x] = Color_White;
      else
        colormatrix[y][x] = Color_Red;
}

void setNextColorMatrixIteration_hline()
{
  static int white_row = 0;
  for (int x=0; x<max_columns; x++)
    colormatrix[white_row][x] = Color_Red;
  if (++white_row >= max_rows)
    white_row = 0;
  for (int x=0; x<max_columns; x++)
    colormatrix[white_row][x] = Color_White;
}

void initColorMatrix_vline()
{
  for (int y=0; y<max_rows; y++)
    for (int x=0; x<max_columns; x++)
      if (x==0)
        colormatrix[y][x] = Color_White;
      else
        colormatrix[y][x] = Color_Red;
}

void setNextColorMatrixIteration_vline()
{
  static int white_col = 0;
  for (int y=0; y<max_rows; y++)
    colormatrix[y][white_col] = Color_Red;
  if (++white_col >= max_columns)
    white_col = 0;
  for (int y=0; y<max_rows; y++)
    colormatrix[y][white_col] = Color_White;
}

void initColorMatrix_raining_code()
{
  for (int y=0; y<max_rows; y++)
    for (int x=0; x<max_columns; x++)
        colormatrix[y][x] = Color_DarkGreen;
}

void setNextColorMatrixIteration_raining_code()
{
  const int max_drops = 9;
  int drop_xpos[max_drops] = {0, 4, 6, 10, 14, 18, 20, 24};
  static int drops[max_drops] = {-1};
  for (int x=0; x<max_drops; x++)
  {
    int pos = drops[x];
    if (pos == -1) // There is no drop going on
    {
      if (random(5) == 1) // 1 out of 5
        drops[x] = 0;
    }
    else
    {
      if (++pos < max_rows)
        drops[x] = pos;
      else
        drops[x] = -1; // Finished // TODO need to update the tail as well !
    }
  }
  for (int x=0; x<max_drops; x++)
  {
    int xpos = drop_xpos[x];
    int pos = drops[x];
    if (pos == -1)
    {
      colormatrix[max_rows-1][xpos] = Color_DarkGreen;
    }
    else
    {
      colormatrix[pos][xpos] = Color_White;
      if (pos >= 1)
        colormatrix[pos-1][xpos] = Color_DarkGreen; 
    }
  }
}


void initColorMatrix(ColorPattern pattern)
{
  switch(pattern)
  {
    case ColorPattern::hline: initColorMatrix_hline(); break;
    case ColorPattern::vline: initColorMatrix_vline(); break;
    case ColorPattern::matrix: initColorMatrix_raining_code(); break;

    default: break;
  }
}

void setNextColorMatrixIteration(ColorPattern pattern)
{
  switch(pattern)
  {
    case ColorPattern::hline: setNextColorMatrixIteration_hline(); break;
    case ColorPattern::vline: setNextColorMatrixIteration_vline(); break;
    case ColorPattern::rainbow: ; break;
    case ColorPattern::matrix: setNextColorMatrixIteration_raining_code(); break;
    default: break;
  }
}

