include(FetchContent)

######################
###  Fetch: itlib  ###
######################
set(ITLIB_VERSION v1.0.8)

FetchContent_Declare(itlib
GIT_REPOSITORY https://github.com/liturri/itlib.git
GIT_TAG        "${ITLIB_VERSION}"
)

add_subdirectory(itlib)

