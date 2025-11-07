QT += widgets sql core gui
CONFIG += c++17

# Your sources
SOURCES += main.cpp \
           GUIManager.cpp \
           DatabaseManager.cpp \
           Admin.cpp \
           Donor.cpp \
           Hospital.cpp \
           Search.cpp \
           SearchLog.cpp \
           Analytics.cpp \
           ... (rest)

HEADERS += GUIManager.h \
           DatabaseManager.h \
           Admin.h \
           Donor.h \
           Search.h \
           SearchLog.h \
           Analytics.h \
           ...

# Link MySQL client (system dependent)
LIBS += -lmysqlclient
