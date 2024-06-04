QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DESTDIR = $$PWD/bin
include($$PWD/src/src.pri)
include($$PWD/lib/lib.pri)

