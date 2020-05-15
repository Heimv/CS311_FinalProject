/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *toolbarLayout;
    QLabel *statusLabel;
    QLineEdit *search;
    QComboBox *searchType;
    QVBoxLayout *tasksLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *title;
    QComboBox *importance;
    QDateEdit *dueDate;
    QDateTimeEdit *reminderDate;
    QPushButton *addTaskButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(827, 659);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        toolbarLayout = new QHBoxLayout();
        toolbarLayout->setSpacing(6);
        toolbarLayout->setObjectName(QString::fromUtf8("toolbarLayout"));
        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        toolbarLayout->addWidget(statusLabel);

        search = new QLineEdit(centralWidget);
        search->setObjectName(QString::fromUtf8("search"));
        search->setMaximumSize(QSize(16777215, 16777215));

        toolbarLayout->addWidget(search);

        searchType = new QComboBox(centralWidget);
        searchType->addItem(QString());
        searchType->addItem(QString());
        searchType->addItem(QString());
        searchType->addItem(QString());
        searchType->addItem(QString());
        searchType->addItem(QString());
        searchType->addItem(QString());
        searchType->setObjectName(QString::fromUtf8("searchType"));
        searchType->setMinimumSize(QSize(150, 0));
        searchType->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        toolbarLayout->addWidget(searchType);


        verticalLayout->addLayout(toolbarLayout);

        tasksLayout = new QVBoxLayout();
        tasksLayout->setSpacing(6);
        tasksLayout->setObjectName(QString::fromUtf8("tasksLayout"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(803, 0));
        tableWidget->setColumnCount(6);

        tasksLayout->addWidget(tableWidget);


        verticalLayout->addLayout(tasksLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        title = new QLineEdit(centralWidget);
        title->setObjectName(QString::fromUtf8("title"));

        horizontalLayout->addWidget(title);

        importance = new QComboBox(centralWidget);
        importance->addItem(QString());
        importance->addItem(QString());
        importance->addItem(QString());
        importance->addItem(QString());
        importance->setObjectName(QString::fromUtf8("importance"));
        importance->setMinimumSize(QSize(160, 0));

        horizontalLayout->addWidget(importance);

        dueDate = new QDateEdit(centralWidget);
        dueDate->setObjectName(QString::fromUtf8("dueDate"));
        dueDate->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        dueDate->setCalendarPopup(true);

        horizontalLayout->addWidget(dueDate);

        reminderDate = new QDateTimeEdit(centralWidget);
        reminderDate->setObjectName(QString::fromUtf8("reminderDate"));
        reminderDate->setCalendarPopup(true);

        horizontalLayout->addWidget(reminderDate);

        addTaskButton = new QPushButton(centralWidget);
        addTaskButton->setObjectName(QString::fromUtf8("addTaskButton"));

        horizontalLayout->addWidget(addTaskButton);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Todo", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status: 0 todo/0 done", nullptr));
        search->setPlaceholderText(QCoreApplication::translate("MainWindow", "search", nullptr));
        searchType->setItemText(0, QCoreApplication::translate("MainWindow", "ID", nullptr));
        searchType->setItemText(1, QCoreApplication::translate("MainWindow", "Done", nullptr));
        searchType->setItemText(2, QCoreApplication::translate("MainWindow", "Label", nullptr));
        searchType->setItemText(3, QCoreApplication::translate("MainWindow", "Importance", nullptr));
        searchType->setItemText(4, QCoreApplication::translate("MainWindow", "Due Date", nullptr));
        searchType->setItemText(5, QCoreApplication::translate("MainWindow", "Reminder Date", nullptr));
        searchType->setItemText(6, QString());

        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Done", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "label", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Importance", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Due date", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Reminder Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        importance->setItemText(0, QCoreApplication::translate("MainWindow", "Important", nullptr));
        importance->setItemText(1, QCoreApplication::translate("MainWindow", "Urgent", nullptr));
        importance->setItemText(2, QCoreApplication::translate("MainWindow", "Not important but urgent", nullptr));
        importance->setItemText(3, QCoreApplication::translate("MainWindow", "Not urgent but important", nullptr));

        addTaskButton->setText(QCoreApplication::translate("MainWindow", "Add task", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
