set(wxWidgets_CONFIG_EXECUTABLE wx-config-gtk3)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})


add_executable(wxclip main.cc wxgui.cc appgui.cc popen2.cc cmd_history.cc actions.cc) 
#  actions.cc)
target_link_libraries(wxclip PUBLIC ${wxWidgets_LIBRARIES} itlib)

# target_compile_options(wxclip PRIVATE -Wall -Wextra -Wpedantic)

# add_executable(actions actions.cc)
# target_link_libraries(actions PUBLIC itlib)