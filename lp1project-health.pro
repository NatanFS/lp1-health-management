# Nome do projeto
TEMPLATE = app
TARGET = lp1project-health
INCLUDEPATH += .

# Arquivos fonte
SOURCES += \
    main.cpp \
    mainwindow.cpp

# Arquivos cabeçalho
HEADERS += \
    mainwindow.h

# Arquivos de interface
FORMS += \
    mainwindow.ui

# Adicionar bibliotecas Qt necessárias
QT += core gui widgets charts
