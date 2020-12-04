QT += widgets

SOURCES += \
    main.cpp \
    src/connector/connector.cpp \
    src/interface/mainwindow.cpp \
    src/interface/widgets/commandline/commandline.cpp \
    src/interface/widgets/keyboard/keyboard.cpp \
    src/interface/widgets/pile/pile.cpp \
    src/interface/widgets/varsprogs/varsprogs.cpp \
    src/observer/observer.cpp \
    src/observer/subject.cpp \
    src/engine/expression/expression.cpp \
    src/engine/expression/expressionmanager.cpp \

FORMS += \
    src/interface/mainwindow.ui \
    src/interface/widgets/commandline/commandline.ui \
    src/interface/widgets/keyboard/keyboard.ui \
    src/interface/widgets/pile/pile.ui \
    src/interface/widgets/varsprogs/varsprogs.ui \

HEADERS += \
    src/connector/connector.h \
    src/engine/operator/operator.h \
    src/engine/exception/CompException.h \
    src/engine/expression/expression.h \
    src/engine/expression/expressionmanager.h \
    src/engine/stack/stack.h \
    src/interface/mainwindow.h \
    src/interface/widgets/commandline/commandline.h \
    src/interface/widgets/keyboard/keyboard.h \
    src/interface/widgets/pile/pile.h \
    src/interface/widgets/varsprogs/varsprogs.h \
    src/observer/observer.h \
    src/observer/subject.h
