cmake_minimum_required(VERSION 3.19)
project(donstu_math_funcs_view LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(donstu_math_funcs_view
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    donstu_funcs/funcline.h;
    donstu_funcs/functemplate.h
    donstu_funcs/funcfastosc.h

)

add_subdirectory(acana_dotplot/)

target_link_libraries(donstu_math_funcs_view
    PRIVATE
        Qt::Core
        Qt::Widgets
        acana_dotplot
)

include(GNUInstallDirs)

install(TARGETS donstu_math_funcs_view
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET donstu_math_funcs_view
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
