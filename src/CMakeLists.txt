set(wxWidgets_CONFIG_EXECUTABLE wx-config-gtk3)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})


add_executable(wxclip main.cc wxgui.cc appgui.cc popen2.cc system.cc cmd_history.cc)
target_link_libraries(wxclip PRIVATE ${wxWidgets_LIBRARIES})
# target_compile_options(wxclip PRIVATE -Wall -Wextra -Wpedantic)
