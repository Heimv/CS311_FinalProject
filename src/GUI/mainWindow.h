#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QCheckBox>
#include <QLabel>
#include <QMainWindow>
#include "../CSV/csvManager.h"
#include "../BinSearchSortTree/binstree.h"

namespace Ui {
class MainWindow;
}

/* Inherits from QMainWindow. Q_OBJECT macro must be first thing
 * declared to setup some Qt magic stuff. We also declare a
 * pointer to a MainWindow class, member variable 'ui', this
 * will allow us to interact with our UI components (buttons, text
 * entries, etc.) from C++, as Qt will set it up for us.
 *
 * We set up our slots here too, to hook signals to.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateStatus();
    void buildTable();
    void addTableEntry(const Elem_t*);
public slots:
    void search();
    void onSearchTypeChanged(int);
    void reorderTable(int);
    void addTask();
    void removeTask();
    void taskStatusChanged(int);

private:
    std::map<Elem_t::importance, string> importanceMap = {
            {Elem_t::URGENT_IMPORTANT, "Urgent and Important"} ,
            {Elem_t::URGENT_NOT_IMPORTANT, "Urgent and Not Important"},
            {Elem_t::NOT_URGENT_IMPORTANT, "Not Urgent but Important"},
            {Elem_t::NOT_URGENT_NOT_IMPORTANT, "Not Urgent and Not Important"},
            {Elem_t::UNDEFINED, ""}
    };
    Elem_t::importance toImportance(std::string);
    static bool toBool(std::string &);
    BST *tree;
    Elem_t::ElemType searchType;
    csvManager *csv;
    Ui::MainWindow *ui;
    /* QVector is Qt container class for dynamic arrays, like std::vector
     * but more Qt specific features
     */
};

#endif // MAINWINDOW_H
