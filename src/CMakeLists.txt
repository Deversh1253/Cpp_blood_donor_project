# list all sources here
set(SOURCES
    main.cpp
    DatabaseManager.cpp
    LoginDialog.cpp
    DonorDialog.cpp
    SearchDialog.cpp
    MainWindow.cpp
)

# list UI files for automatic moc/uic
set(UI_FILES
    ui/LoginDialog.ui
    ui/DonorDialog.ui
    ui/SearchDialog.ui
    ui/MainWindow.ui
)

qt_wrap_ui(UI_HEADERS ${UI_FILES})   # CHANGED for Qt6/CMake: auto-generation
add_executable(BloodLife ${SOURCES} ${UI_HEADERS})

target_link_libraries(BloodLife PRIVATE
    bloodlife_include
    Qt6::Widgets
    Qt6::Sql
)

target_compile_definitions(BloodLife PRIVATE QT_NO_KEYWORDS)
