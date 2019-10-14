#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T11:27:55
#
#-------------------------------------------------

QT       -= core gui

TARGET = z80asm
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    DataBlock.cpp \
    EscapedBinary.cpp \
    Instruction.cpp \
    Program.cpp

HEADERS += \
    BinaryBlock.h \
    DataBlock.h \
    DataDeclarationExceptions.h \
    EscapedBinary.h \
    Exceptions.h \
    Immediate.h \
    Instruction.h \
    InstructionExceptions.h \
    InstructionTable.h \
    Program.h \
    ProgramException.h \
    StringUtilities.h \
    SymbolExceptions.h \
    SymbolTable.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
