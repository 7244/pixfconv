bool _pixfconv_st_f_BGRA_YUV420P(
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

  _pixfconv_BGRA_YUV420P_2x2(width, height, sstride, dstride, sdata, ddata);

  return 0;
}

bool _pixfconv_st_f_BGRA_NV12(
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

  _pixfconv_BGRA_NV12_2x2(width, height, sstride, dstride, sdata, ddata);

  return 0;
}

_pixfconv_st_convert_func_t _pixfconv_st_BGRA_getfmt(uint32_t dfmt){
  switch(dfmt){
    case PIXF_YUV420p:{
      return _pixfconv_st_f_BGRA_YUV420P;
    }
    case PIXF_YUVNV12:{
      return _pixfconv_st_f_BGRA_NV12;
    }
    default:{
      return 0;
    }
  }
}
