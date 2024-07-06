QT       += core gui sql widgets pdfwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QTPLUGIN += QSQLMYSQL
unix {
    SOURCES +=     pdf_viewer/pdfviewer.cpp \
    pdf_viewer/pageselector.cpp \
    pdf_viewer/zoomselector.cpp

    HEADERS +=     pdf_viewer/pdfviewer.h \
    pdf_viewer/pageselector.h \
    pdf_viewer/zoomselector.h

    FORMS += pdf_viewer/pdfviewer.ui

}

win32 {
    SOURCES += pdf_viewer/pdfviewer_win.cpp \
    pdf_viewer/zoomselector_win.cpp \
    pdf_viewer/searchresultdelegate.cpp

    HEADERS +=     pdf_viewer/pdfviewer_win.h \
    pdf_viewer/zoomselector_win.h \
    pdf_viewer/searchresultdelegate.h

    FORMS += pdf_viewer/pdfviewer_win.ui
}
SOURCES += \
    app/global.cpp \
    queries/delqueries.cpp \
    queries/editqueries.cpp \
    queries/addqueries.cpp \
    queries/showtable.cpp \
    app/changepassword.cpp \
    app/settings.cpp \
    app/dataimport.cpp \
    app/dialogaddtables.cpp \
    app/dialogdeltables.cpp \
    app/dialogedittables.cpp \
    app/main.cpp \
    app/mainwindow.cpp \
    app/otables.cpp 



HEADERS += \
    app/global.h \
    queries/delqueries.h \
    queries/editqueries.h \
    queries/addqueries.h \
    queries/showtable.h \
    app/changepassword.h \
    app/settings.h \
    app/dataimport.h \
    app/dialogaddtables.h \
    app/dialogdeltables.h \
    app/dialogedittables.h \
    app/mainwindow.h \
    app/otables.h



FORMS += \
    app/changepassword.ui \
    app/dataimport.ui \
    app/dialogaddtables.ui \
    app/dialogdeltables.ui \
    app/dialogedittables.ui \
    app/mainwindow.ui \
    app/otables.ui \
    app/settings.ui

TRANSLATIONS += \
    language/Kursach_en_US.ts \
    language/Kursach_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:RC_FILE = file.rc

RESOURCES += \
    resource.qrc
