include(FetchContent)

######################
###  Fetch: itlib  ###
######################
set(ITLIB_VERSION v1.0.3) # 2.5.15.x

FetchContent_Declare(itlib
GIT_REPOSITORY https://github.com/liturri/itlib.git
GIT_TAG        "${ITLIB_VERSION}"
)

add_subdirectory(itlib)

