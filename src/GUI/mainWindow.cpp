#include "mainWindow.h"
#include "../../ui/ui_mainWindow.h"
#include <QDebug>
#include <QInputDialog>

/* Constructor. Initializer list here calls superclass
 * constructor with any parent widget passed along, default
 * none. We also initialize the private member variable
 * 'ui' using initializer list. It is declared in header
 * as a private member var, a pointer.
 *
 * Signals are messages sent by an object. Slots are just
 * functions that receive signals. Slot/Signals must have
 * have same function signatures to work.
 *
 * We use connect() function to set up a signal/slot connection:
 * connect(sender, &Sender::signalName, receiver, &Receiver::slotName);
 */
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        tree(new BST),
        ui(new Ui::MainWindow) {
    csv = new csvManager(tree);
    // need to call this to init all widgets used in the
    // mainWindow.ui design file.
    ui->setupUi(this);

    ui->dueDate->setDate(QDate::currentDate());
    ui->reminderDate->setDate(QDate::currentDate());
    ui->reminderDate->setTime(QTime::currentTime());
    ui->tableWidget->setColumnWidth(0, 50);
    ui->tableWidget->setColumnWidth(2, 100);
    ui->tableWidget->setColumnWidth(3, 100);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 100);
    ui->tableWidget->setColumnWidth(1, ui->tableWidget->width() - 525);

    // Setup a connection using signal/slot mechanism, to call
    // addTask() function when our add task button clicked signal is emitted.
    connect(ui->search, &QLineEdit::returnPressed, this, &MainWindow::search);
    connect(ui->search, &QLineEdit::textChanged, this, &MainWindow::search);
    connect(ui->searchType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onSearchTypeChanged);
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::reorderTable);
    connect(ui->title, &QLineEdit::returnPressed, this, &MainWindow::addTask);
    connect(ui->addTaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);
    // Call our method
    buildTable();
}

MainWindow::~MainWindow() {
    // Clean up the pointer
    delete ui;
}

void MainWindow::reorderTable(int column) {
    switch (column) {
        case 0:
            tree->setType(Elem_t::DONE, true);
            break;
        case 1:
            tree->setType(Elem_t::TITLE, true);
            break;
        case 2:
            tree->setType(Elem_t::IMPORTANCE, true);
            break;
        case 3:
            tree->setType(Elem_t::DUEDATE, true);
            break;
        case 4:
            tree->setType(Elem_t::REMINDERDATE, true);
            break;
        default:
            return;
    }
    buildTable();
}

void MainWindow::addTableEntry(const Elem_t *elem) {
    QCheckBox *checkBox = new QCheckBox();
    checkBox->setChecked(elem->Done);
    QLabel *label = new QLabel(QString(elem->Title.c_str()));
    label->setAlignment(Qt::AlignCenter);
    QLabel *importance = new QLabel(importanceMap[elem->Importance].c_str());
    importance->setAlignment(Qt::AlignCenter);
    QLabel *dueDate = new QLabel(elem->DueDate.toString());
    dueDate->setAlignment(Qt::AlignCenter);
    QLabel *reminderDate = new QLabel(elem->ReminderDate.toString());
    reminderDate->setAlignment(Qt::AlignCenter);
    QPushButton *deleteTask = new QPushButton("delete");

    const int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);
    ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString(std::to_string(elem->Id).c_str())));
    ui->tableWidget->setCellWidget(row, 0, checkBox);
    ui->tableWidget->setCellWidget(row, 1, label);
    ui->tableWidget->setCellWidget(row, 2, importance);
    ui->tableWidget->setCellWidget(row, 3, dueDate);
    ui->tableWidget->setCellWidget(row, 4, reminderDate);
    ui->tableWidget->setCellWidget(row, 5, deleteTask);
    connect(deleteTask, &QPushButton::clicked, this, &MainWindow::removeTask);
    connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::taskStatusChanged);
    ui->title->clear();
}

void MainWindow::buildTable() {
    std::vector<Elem_t *> *tmp = tree->getOrderdNodes();

    ui->tableWidget->setRowCount(0);
    cout << tmp << endl;
    for (const Elem_t *elem : *tmp) {
        cout << "adding: " << elem->Title << " with Id: " << elem->Id << " to the table" << endl;
        addTableEntry(elem);
    }
    updateStatus();
    csv->writeFile();
}


/* Slot function for adding task */
void MainWindow::addTask() {
    // Static blocking function that display dialog to get task name.
    if (ui->title->text().isEmpty())
        return;
    tree->InsertVertex(
            new Elem_t(
                    false,
                    Elem_t::importance::URGENT_IMPORTANT,
                    ui->title->text().toStdString(),
                    ui->importance->currentText().toStdString(),
                    ui->dueDate->date(),
                    ui->reminderDate->dateTime(),
                    tree
            )
    );
    buildTable();
}

void MainWindow::removeTask() {
    Elem_t::ElemType type = tree->getType();
    Elem_t *elem = new Elem_t(ui->tableWidget->verticalHeaderItem(ui->tableWidget->currentRow())->text().toInt(), tree);

    tree->setType(Elem_t::ElemType::ID, false);
    tree->DeleteVertex(elem);
    tree->setType(type, true);
    buildTable();
}

void MainWindow::taskStatusChanged(int state) {
    Elem_t::ElemType type = tree->getType();
    Elem_t *elem = nullptr;
    Elem_t *tmp = new Elem_t(ui->tableWidget->verticalHeaderItem(ui->tableWidget->currentRow())->text().toInt(), tree);

    tree->setType(Elem_t::ElemType::ID, false);
    elem = tree->Search(tmp);
    if (state == Qt::CheckState::Checked && elem != nullptr) {
        qDebug() << "task done";
        elem->Done = true;
    } else if (state == Qt::CheckState::Unchecked && elem != nullptr) {
        qDebug() << "task is not finished";
        elem->Done = true;
    }
    tree->setType(type, false);
    updateStatus();
    csv->writeFile();
}

void MainWindow::onSearchTypeChanged(int type) {
    switch (type) {
        case 0:
            searchType = Elem_t::ID;
            break;
        case 1:
            searchType = Elem_t::DONE;
            break;
        case 2:
            searchType = Elem_t::TITLE;
            break;
        case 3:
            searchType = Elem_t::DUEDATE;
            break;
        case 4:
            searchType = Elem_t::REMINDERDATE;
            break;
        default:
            searchType = Elem_t::ID;
    }
}

Elem_t::importance MainWindow::toImportance(std::string imp) {
    return std::find_if(
            importanceMap.begin(),
            importanceMap.end(),
            [imp](const std::pair<Elem_t::importance, std::string > &t) -> bool {
                return t.second.find(imp);
            })->first;
}

bool MainWindow::toBool(std::string &str) {
    return str == "Done" || str == "done" || str == "true" || str == "1";
}

void MainWindow::search() {
    Elem_t::ElemType tmp = tree->getType();
    std::vector<Elem_t *> *results = nullptr;
    std::string toSearch = ui->search->text().toStdString();

    if (toSearch.empty()) {
        return buildTable();
    }
    tree->setType(searchType, true);
    switch (searchType) {
        case Elem_t::ID:
            try {
                stoi(toSearch);
                results = tree->Search(stoi(toSearch));
            } catch (std::exception &e) {
            }
            break;
        case Elem_t::IMPORTANCE:
            results = tree->Search(toImportance(toSearch));
            break;
        case Elem_t::DONE:
            results = tree->Search(toBool(toSearch));
            break;
        case Elem_t::TITLE:
        case Elem_t::DUEDATE:
        case Elem_t::REMINDERDATE:
            results = tree->Search(toSearch);
            break;
    }
    if (results != nullptr) {
        ui->tableWidget->setRowCount(0);
        for (Elem_t *elem: *results) {
            addTableEntry(elem);
        }
    }
    tree->setType(tmp, true);
}

void MainWindow::updateStatus() {
    int completedCount = 0;
    const QCheckBox *checkBox;
    /* Using C++11 auto var feature here in for-loop to assign the
     * type and var name at each iteration of an iterable container.
     */
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        checkBox = dynamic_cast<const QCheckBox *>(ui->tableWidget->cellWidget(i, 0));
        if (checkBox->isChecked()) {
            completedCount++;
        }
    }
    int todoCount = ui->tableWidget->rowCount() - completedCount;

    ui->statusLabel->setText(
            QString("Status: %1 todo / %2 completed")
                    .arg(todoCount)
                    .arg(completedCount));
}
