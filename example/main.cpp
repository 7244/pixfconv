#include <WITCH/WITCH.h>

#include <pixfconv/st/st.h>

#include <vector>
#include <fstream>

constexpr uint32_t rx = 512;
constexpr uint32_t ry = 512;

int main(){
  std::vector<uint8_t> bgrx_array(rx * ry * 4);
  for(auto x = rx; x--;){
    for(auto y = ry; y--;){
      bgrx_array[(y * rx + x) * 4 + 0] = x / 2;
      bgrx_array[(y * rx + x) * 4 + 1] = y / 2;
      bgrx_array[(y * rx + x) * 4 + 2] = 0;
      bgrx_array[(y * rx + x) * 4 + 3] = 0;
    }
  }

  std::vector<uint8_t> yuv_array0(rx * ry);
  std::vector<uint8_t> yuv_array1(rx / 2 * ry / 2);
  std::vector<uint8_t> yuv_array2(rx / 2 * ry / 2);

  uint32_t sstride[] = {rx * 4, 0, 0, 0};
  uint32_t dstride[] = {rx, rx / 2, rx / 2, 0};

  const uint8_t *const sdata[] = {bgrx_array.data(), NULL, NULL, NULL};
  uint8_t *const ddata[] = {yuv_array0.data(), yuv_array1.data(), yuv_array2.data(), NULL};

  auto result = pixfconv_st_convert(
    3, // PIXF_BGRA
    0, // PIXF_YUV420p
    rx,
    ry,
    sstride,
    dstride,
    sdata,
    ddata
  );
  if(result != 0){
    __abort();
  }

  std::ofstream out("yuv420p");
  out.write((const char *)yuv_array0.data(), yuv_array0.size());
  out.write((const char *)yuv_array1.data(), yuv_array1.size());
  out.write((const char *)yuv_array2.data(), yuv_array2.size());
}
