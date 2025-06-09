// not fully tested functions

void _pixfconv_BGRX_YUV420P_2x2(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  const uint8_t *src = sdata[0];
  uint8_t *dst_y = ddata[0];
  uint8_t *dst_u = ddata[1];
  uint8_t *dst_v = ddata[2];
  
  for(uint32_t y = 0; y < height; y += 2) {
    const uint32_t *src_row1 = (const uint32_t*)(src + y * sstride[0]);
    const uint32_t *src_row2 = (const uint32_t*)(src + (y + 1) * sstride[0]);
    uint8_t *dst_y_row1 = dst_y + y * dstride[0];
    uint8_t *dst_y_row2 = dst_y + (y + 1) * dstride[0];
    uint8_t *dst_u_row = dst_u + (y >> 1) * dstride[1];
    uint8_t *dst_v_row = dst_v + (y >> 1) * dstride[2];
    
    for(uint32_t x = 0; x < width; x += 2) {
      uint32_t p00 = src_row1[x];    
      uint32_t p01 = src_row1[x + 1];
      uint32_t p10 = src_row2[x];    
      uint32_t p11 = src_row2[x + 1];
      
      uint8_t b00 = p00 & 0xFF, g00 = (p00 >> 8) & 0xFF, r00 = (p00 >> 16) & 0xFF;
      uint8_t b01 = p01 & 0xFF, g01 = (p01 >> 8) & 0xFF, r01 = (p01 >> 16) & 0xFF;
      uint8_t b10 = p10 & 0xFF, g10 = (p10 >> 8) & 0xFF, r10 = (p10 >> 16) & 0xFF;
      uint8_t b11 = p11 & 0xFF, g11 = (p11 >> 8) & 0xFF, r11 = (p11 >> 16) & 0xFF;
      
      dst_y_row1[x] = (uint8_t)((77 * r00 + 150 * g00 + 29 * b00) >> 8);
      dst_y_row1[x + 1] = (uint8_t)((77 * r01 + 150 * g01 + 29 * b01) >> 8);
      dst_y_row2[x] = (uint8_t)((77 * r10 + 150 * g10 + 29 * b10) >> 8);
      dst_y_row2[x + 1] = (uint8_t)((77 * r11 + 150 * g11 + 29 * b11) >> 8);
      
      uint16_t avg_r = (r00 + r01 + r10 + r11) >> 2;
      uint16_t avg_g = (g00 + g01 + g10 + g11) >> 2;
      uint16_t avg_b = (b00 + b01 + b10 + b11) >> 2;
      
      dst_u_row[x >> 1] = (uint8_t)(128 + ((-43 * avg_r - 85 * avg_g + 128 * avg_b) >> 8));
      dst_v_row[x >> 1] = (uint8_t)(128 + ((128 * avg_r - 107 * avg_g - 21 * avg_b) >> 8));
    }
  }
}

void _pixfconv_BGRX_NV12_2x2(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  const uint8_t *src = sdata[0];
  uint8_t *dst_y = ddata[0];
  uint8_t *dst_uv = ddata[1];
  
  for(uint32_t y = 0; y < height; y += 2) {
    const uint32_t *src_row1 = (const uint32_t*)(src + y * sstride[0]);
    const uint32_t *src_row2 = (const uint32_t*)(src + (y + 1) * sstride[0]);
    uint8_t *dst_y_row1 = dst_y + y * dstride[0];
    uint8_t *dst_y_row2 = dst_y + (y + 1) * dstride[0];
    uint8_t *dst_uv_row = dst_uv + (y >> 1) * dstride[1];
    
    for(uint32_t x = 0; x < width; x += 2) {
      uint32_t p00 = src_row1[x];
      uint32_t p01 = src_row1[x + 1];
      uint32_t p10 = src_row2[x];
      uint32_t p11 = src_row2[x + 1];
      
      uint8_t b00 = p00 & 0xFF, g00 = (p00 >> 8) & 0xFF, r00 = (p00 >> 16) & 0xFF;
      uint8_t b01 = p01 & 0xFF, g01 = (p01 >> 8) & 0xFF, r01 = (p01 >> 16) & 0xFF;
      uint8_t b10 = p10 & 0xFF, g10 = (p10 >> 8) & 0xFF, r10 = (p10 >> 16) & 0xFF;
      uint8_t b11 = p11 & 0xFF, g11 = (p11 >> 8) & 0xFF, r11 = (p11 >> 16) & 0xFF;
      
      dst_y_row1[x] = (uint8_t)((77 * r00 + 150 * g00 + 29 * b00) >> 8);
      dst_y_row1[x + 1] = (uint8_t)((77 * r01 + 150 * g01 + 29 * b01) >> 8);
      dst_y_row2[x] = (uint8_t)((77 * r10 + 150 * g10 + 29 * b10) >> 8);
      dst_y_row2[x + 1] = (uint8_t)((77 * r11 + 150 * g11 + 29 * b11) >> 8);
      
      uint16_t avg_r = (r00 + r01 + r10 + r11) >> 2;
      uint16_t avg_g = (g00 + g01 + g10 + g11) >> 2;
      uint16_t avg_b = (b00 + b01 + b10 + b11) >> 2;
      
      dst_uv_row[x] = (uint8_t)(128 + ((-43 * avg_r - 85 * avg_g + 128 * avg_b) >> 8)); // U
      dst_uv_row[x + 1] = (uint8_t)(128 + ((128 * avg_r - 107 * avg_g - 21 * avg_b) >> 8)); // V
    }
  }
}

void _pixfconv_BGRX_BGRA(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  const uint8_t *src = sdata[0];
  uint8_t *dst = ddata[0];
  
  for(uint32_t y = 0; y < height; y++) {
    const uint32_t *src_row = (const uint32_t*)(src + y * sstride[0]);
    uint32_t *dst_row = (uint32_t*)(dst + y * dstride[0]);
    
    for(uint32_t x = 0; x < width; x++) {
      uint32_t pixel = src_row[x];
      dst_row[x] = (pixel & 0x00FFFFFF) | 0xFF000000;
    }
  }
}

void _pixfconv_BGRX_RGB24(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  const uint8_t *src = sdata[0];
  uint8_t *dst = ddata[0];
  
  for(uint32_t y = 0; y < height; y++) {
    const uint32_t *src_row = (const uint32_t*)(src + y * sstride[0]);
    uint8_t *dst_row = dst + y * dstride[0];
    
    for(uint32_t x = 0; x < width; x++) {
      uint32_t pixel = src_row[x];
      uint8_t b = pixel & 0xFF;
      uint8_t g = (pixel >> 8) & 0xFF;
      uint8_t r = (pixel >> 16) & 0xFF;
      
      dst_row[x * 3] = r;
      dst_row[x * 3 + 1] = g;
      dst_row[x * 3 + 2] = b;
    }
  }
}

void _pixfconv_BGRX_YUV444_10BIT(
  uint32_t width,
  uint32_t height,
  const uint32_t *sstride,
  const uint32_t *dstride,
  const uint8_t *const *sdata,
  uint8_t *const *ddata
){
  const uint8_t *src = sdata[0];
  uint16_t *dst_y = (uint16_t*)ddata[0];
  uint16_t *dst_u = (uint16_t*)ddata[1];
  uint16_t *dst_v = (uint16_t*)ddata[2];
  
  for(uint32_t y = 0; y < height; y++) {
    const uint32_t *src_row = (const uint32_t*)(src + y * sstride[0]);
    uint16_t *dst_y_row = (uint16_t*)((uint8_t*)dst_y + y * dstride[0]);
    uint16_t *dst_u_row = (uint16_t*)((uint8_t*)dst_u + y * dstride[1]);
    uint16_t *dst_v_row = (uint16_t*)((uint8_t*)dst_v + y * dstride[2]);
    
    for(uint32_t x = 0; x < width; x++) {
      uint32_t pixel = src_row[x];
      uint8_t b = pixel & 0xFF;
      uint8_t g = (pixel >> 8) & 0xFF;
      uint8_t r = (pixel >> 16) & 0xFF;
      
      uint16_t y_val = (uint16_t)(((77 * r + 150 * g + 29 * b) >> 8) << 2);
      uint16_t u_val = (uint16_t)((128 + ((-43 * r - 85 * g + 128 * b) >> 8)) << 2);
      uint16_t v_val = (uint16_t)((128 + ((128 * r - 107 * g - 21 * b) >> 8)) << 2);
      
      dst_y_row[x] = y_val;
      dst_u_row[x] = u_val;
      dst_v_row[x] = v_val;
    }
  }
}