MESSAGE(STATUS "Using bundled Findlibdb.cmake...")

FIND_PATH( LIBZTSTRING_INCLUDE_DIR ztstring.h ./cstring)
FIND_LIBRARY(LIBZTSTRING_LIB_DIR ztstring  PATHS ./cstring )