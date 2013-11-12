/********************************************************************************
** Form generated from reading UI file 'WSChat.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WSCHAT_H
#define UI_WSCHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WSChat
{
public:
    QWidget *centralWidget;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QPushButton *enterButton;
    QLabel *infoLabel;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *WSChat)
    {
        if (WSChat->objectName().isEmpty())
            WSChat->setObjectName(QStringLiteral("WSChat"));
        WSChat->resize(600, 450);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WSChat->sizePolicy().hasHeightForWidth());
        WSChat->setSizePolicy(sizePolicy);
        WSChat->setMinimumSize(QSize(300, 250));
        centralWidget = new QWidget(WSChat);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 281, 91));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy1);
        textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 110, 221, 111));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy2);
        textEdit->setMinimumSize(QSize(200, 0));
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setAcceptRichText(true);
        enterButton = new QPushButton(centralWidget);
        enterButton->setObjectName(QStringLiteral("enterButton"));
        enterButton->setEnabled(true);
        enterButton->setGeometry(QRect(240, 110, 50, 115));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(enterButton->sizePolicy().hasHeightForWidth());
        enterButton->setSizePolicy(sizePolicy3);
        enterButton->setMaximumSize(QSize(16777215, 16777215));
        infoLabel = new QLabel(centralWidget);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        infoLabel->setGeometry(QRect(10, 230, 250, 16));
        sizePolicy2.setHeightForWidth(infoLabel->sizePolicy().hasHeightForWidth());
        infoLabel->setSizePolicy(sizePolicy2);
        infoLabel->setMinimumSize(QSize(250, 0));
        WSChat->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WSChat);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 20));
        WSChat->setMenuBar(menuBar);

        retranslateUi(WSChat);

        QMetaObject::connectSlotsByName(WSChat);
    } // setupUi

    void retranslateUi(QMainWindow *WSChat)
    {
        WSChat->setWindowTitle(QApplication::translate("WSChat", "WSChat", 0));
        enterButton->setText(QApplication::translate("WSChat", "Enter", 0));
        infoLabel->setText(QApplication::translate("WSChat", "hello", 0));
    } // retranslateUi

};

namespace Ui {
    class WSChat: public Ui_WSChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WSCHAT_H
