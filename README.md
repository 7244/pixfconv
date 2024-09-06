# pixfconv
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

pixfconv is pixel format convert library. Made for get better performance than ffmpeg's swscale.

## Features
- Fast.

### For usage look at [example](example)

### Building
1. If you are using c or cpp you can just directly include st or mt header and everything will work.
2. If you want to use pixfconv through another language, you can compile pixfconv ([check](pixfconv/compile/)) then load it from another language.

### Depends On
* st doesn't have dependence. mt requires a thread pool library.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
