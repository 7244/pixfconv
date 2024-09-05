import ctypes

rx = 512
ry = 512

lib = ctypes.CDLL("pixfconv_st.so")
lib.pixfconv_st_convert.argtypes = (
  ctypes.c_int,
  ctypes.c_int,
  ctypes.c_int,
  ctypes.c_int,
  ctypes.POINTER(ctypes.c_int),
  ctypes.POINTER(ctypes.c_int),
  ctypes.POINTER(ctypes.POINTER(ctypes.c_char)),
  ctypes.POINTER(ctypes.POINTER(ctypes.c_char))
)
lib.pixfconv_st_convert.restype = ctypes.c_bool

if __name__ == '__main__':
  bgrx_array = (ctypes.c_char * (rx * ry * 4))()
  for x in range(rx):
    for y in range(ry):
      bgrx_array[(y * rx + x) * 4 + 0] = int(x / 2)
      bgrx_array[(y * rx + x) * 4 + 1] = int(y / 2)
      bgrx_array[(y * rx + x) * 4 + 2] = 0
      bgrx_array[(y * rx + x) * 4 + 3] = 0

  yuv_array0 = (ctypes.c_char * (rx * ry))()
  yuv_array1 = (ctypes.c_char * (int(rx / 2) * int(ry / 2)))()
  yuv_array2 = (ctypes.c_char * (int(rx / 2) * int(ry / 2)))()

  sstride = (ctypes.c_int * 4)(*[rx * 4, 0, 0, 0])
  dstride = (ctypes.c_int * 4)(*[rx, int(rx / 2), int(rx / 2), 0])

  sdata = (ctypes.POINTER(ctypes.c_char) * 4)(*[bgrx_array, None, None, None])
  ddata = (ctypes.POINTER(ctypes.c_char) * 4)(*[yuv_array0, yuv_array1, yuv_array2, None])

  result = lib.pixfconv_st_convert(
    3, # PIXF_BGRA
    0, # PIXF_YUV420p
    rx,
    ry,
    sstride,
    dstride,
    sdata,
    ddata
  )
  if result != 0:
    __abort()

  with open("yuv420p", "wb") as out:
    out.write(yuv_array0)
    out.write(yuv_array1)
    out.write(yuv_array2)
