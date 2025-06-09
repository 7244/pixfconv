bool _pixfconv_st_f_BGRX_YUV420P(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  if(EXPECT(width % 2, 0)){
    return 1;
  }
  if(EXPECT(height % 2, 0)){
    return 1;
  }
  _pixfconv_BGRX_YUV420P_2x2(width, height, sstride, dstride, sdata, ddata);
  return 0;
}

bool _pixfconv_st_f_BGRX_NV12(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  if(EXPECT(width % 2, 0)){
    return 1;
  }
  if(EXPECT(height % 2, 0)){
    return 1;
  }
  _pixfconv_BGRX_NV12_2x2(width, height, sstride, dstride, sdata, ddata);
  return 0;
}

bool _pixfconv_st_f_BGRX_BGRA(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  _pixfconv_BGRX_BGRA(width, height, sstride, dstride, sdata, ddata);
  return 0;
}

bool _pixfconv_st_f_BGRX_RGB24(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  _pixfconv_BGRX_RGB24(width, height, sstride, dstride, sdata, ddata);
  return 0;
}

bool _pixfconv_st_f_BGRX_YUV444_10BIT(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  _pixfconv_BGRX_YUV444_10BIT(width, height, sstride, dstride, sdata, ddata);
  return 0;
}

_pixfconv_st_convert_func_t _pixfconv_st_BGRX_getfmt(uint32_t dfmt){
  switch(dfmt){
    case PIXF_YUV420p:{
      return _pixfconv_st_f_BGRX_YUV420P;
    }
    case PIXF_YUVNV12:{
      return _pixfconv_st_f_BGRX_NV12;
    }
    case PIXF_BGRA:{
      return _pixfconv_st_f_BGRX_BGRA;
    }
    case PIXF_RGB24:{
      return _pixfconv_st_f_BGRX_RGB24;
    }
    case PIXF_YUV444_10BIT:{
      return _pixfconv_st_f_BGRX_YUV444_10BIT;
    }
    default:{
      return 0;
    }
  }
}