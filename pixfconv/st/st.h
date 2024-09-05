#pragma once

#include "../internal/_include_all.h"

typedef bool (*_pixfconv_st_convert_func_t)(
  uint32_t x,
  uint32_t y,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
);

#include "internal/RGB24.h"
#include "internal/BGRA.h"
#include "internal/YUV420P.h"

_pixfconv_st_convert_func_t _pixfconv_st_getfmt(uint32_t sfmt, uint32_t dfmt){
  switch(sfmt){
    case PIXF_RGB24:{
      return _pixfconv_st_RGB24_getfmt(dfmt);
    }
    case PIXF_BGRA:{
      return _pixfconv_st_BGRA_getfmt(dfmt);
    }
    case PIXF_YUV420p:{
      return _pixfconv_st_YUV420P_getfmt(dfmt);
    }
    default:{
      return 0;
    }
  }
}

bool pixfconv_st_convert(
  uint32_t sfmt,
  uint32_t dfmt,
  uint32_t x,
  uint32_t y,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  _pixfconv_st_convert_func_t convert_func = _pixfconv_st_getfmt(sfmt, dfmt);
  if(!convert_func){
    return 1;
  }
  return convert_func(x, y, sstride, dstride, sdata, ddata);
}
