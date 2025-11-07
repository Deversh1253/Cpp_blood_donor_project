#include <QApplication>
#include "GUIManager.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GUIManager w;
    w.show();
    return a.exec();
