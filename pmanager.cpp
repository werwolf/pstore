#include "pmanager.h"
#include "ui_pmanager.h"
#include <QMessageBox>

PManager::PManager(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::PManager)
{
    ui->setupUi(this);
//    ui->add_prod_type->setEnabled(false);
//    ui->save_prod_type->setEnabled(false);

//    ui->prod_type_name_ed->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z]{3,12}$"), 0));
    // :TODO protect from SQL injections

    ui->del_prod_type->setEnabled(false);
    selected_row = -1;

    type_items = new QList<QTreeWidgetItem *>();
    items = new QList<QTreeWidgetItem *>();

    db = EDBconnection::getInstance();

    ui->prod_types_table->setColumnWidth(1, 300);
    //
    ui->prod_treeWidget->hideColumn(4);
    updateProdList();
}

PManager::~PManager()
{
    delete ui;
}

void PManager::startP(void)
{
    updateProdTypesList();
    this->show();
}

void PManager::on_add_prod_type_clicked()
{
    QString name = ui->prod_type_name_ed->text();
    QString description = ui->prod_type_dscr_ed->toPlainText();
    if (!name.isEmpty() && !description.isEmpty()) {
        QString query = QString("INSERT INTO product_types (name, description) VALUES('%1', '%2')").arg(name).arg(description);
        EDBconnection::getInstance()->insert(query);
        qDebug()<<"execute: "<<query;
        updateProdTypesList();
    }
}

void PManager::updateProdTypesList(void)
{
    QTableWidgetItem *ptwi = 0;
    QList<QStringList> List = EDBconnection::getInstance()->get("SELECT name, description FROM product_types");

    if (!List.isEmpty()) {
        ui->prod_types_table->setRowCount(List.length());
        for (int i = 0; i < List.length(); ++i)
            for (int j = 0; j < List.at(0).length(); ++j) {
                ptwi = new QTableWidgetItem(List[i].at(j));
                ui->prod_types_table->setItem(i, j, ptwi);
            }
    } else {
        qDebug("List is empty");
    }
}

void PManager::updateProdList(void)
{
//    pt.description as prod_type_dscr,
    QString query = QString("SELECT pt.name as type_name, " \
                                            " p.title as product_title, p.description as prod_dscr," \
                                            " p.extra_charge as extra_charge, p.rating as rating, p.id as id" \
                                            " FROM products AS p INNER JOIN product_types AS pt" \
                                            " ON p.product_type_id=pt.id ORDER BY type_name");

    QList<QStringList> List = db->get(query);

    if (type_items->length() > 0) type_items->clear();
    if (items->length() > 0) items->clear();
    ui->prod_treeWidget->clear();
    ui->prod_type_cb->clear();
    type_items->append(new QTreeWidgetItem(ui->prod_treeWidget, QStringList(QObject::trUtf8("Add new"))));
    type_items->at(0)->setForeground(0, QBrush(QColor(0xFF, 0xAA, 0x00)));

    if (!List.isEmpty()) {
        for (int i=0; i < List.length(); ++i) {
            if (i == 0 || QString::compare(List.at(i).at(0), List.at(i-1).at(0), Qt::CaseSensitive) != 0) {
                type_items->append(new QTreeWidgetItem(ui->prod_treeWidget, QStringList(List[i][0])));
                type_items->at(type_items->length()-1)->setForeground(0, QBrush(QColor(0x00, 0x2E, 0xB8)));
                type_items->at(type_items->length()-1)->setBackgroundColor(0, QColor(0xCC, 0xD9, 0xD3, 150));
                type_items->at(type_items->length()-1)->setBackgroundColor(1, QColor(0xCC, 0xD9, 0xD3, 150));
                type_items->at(type_items->length()-1)->setBackgroundColor(2, QColor(0xCC, 0xD9, 0xD3, 150));
                type_items->at(type_items->length()-1)->setBackgroundColor(3, QColor(0xCC, 0xD9, 0xD3, 150));
            }

            QStringList tmpList;
            tmpList<<List[i][1]<<List[i][2]<<List[i][3]<<List[i][4]<<List[i][5];
            QTreeWidgetItem *temp_item = new QTreeWidgetItem(type_items->at(type_items->length() - 1), tmpList);
            items->append(temp_item);

            // public slots inherited from QTreeView  --  void QTreeView::expandAll () [slot]
            // Warning: if the model contains a large number of items, this function will take some time to execute.
            if (List.length() < 20) ui->prod_treeWidget->expandAll();
        }
    } else {
        qDebug("List is empty");
        return;
    }

    // select, click & focus 'add new' item
    ui->prod_treeWidget->setCurrentItem(ui->prod_treeWidget->topLevelItem(0));
    on_prod_treeWidget_itemClicked(ui->prod_treeWidget->currentItem(), 0);
    ui->prod_treeWidget->setFocus();
}

void PManager::on_prod_types_table_cellActivated(int row, int column)
{
    Q_UNUSED(column);
    selected_row = row;
    ui->prod_type_name_ed->setText(ui->prod_types_table->item(row, 0)->text());
    ui->prod_type_dscr_ed->setText(ui->prod_types_table->item(row, 1)->text());
//    ui->add_prod_type->setEnabled(false);
    ui->save_prod_type->setEnabled(true);
    ui->del_prod_type->setEnabled(true);
}

void PManager::on_save_prod_type_clicked()
{
    qDebug("save");
    QString new_name = ui->prod_type_name_ed->text();
    QString new_description = ui->prod_type_dscr_ed->toPlainText();

    QString name = ui->prod_types_table->item(selected_row, 0)->text();
    QString query = QString("UPDATE product_types SET name='%1', description='%2' WHERE name = '%3'")
            .arg(new_name).arg(new_description).arg(name);
    qDebug()<<query;
    EDBconnection::getInstance()->query(query);

    updateProdTypesList();
}

void PManager::on_del_prod_type_clicked()
{
    qDebug("delete");
    QString name = ui->prod_types_table->item(selected_row, 0)->text();
    QString query = QString("DELETE FROM product_types WHERE name = '%1'").arg(name);
    EDBconnection::getInstance()->query(query);
    ui->prod_type_name_ed->clear();
    ui->prod_type_dscr_ed->clear();
    updateProdTypesList();
}

void PManager::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0 : updateProdTypesList();  break;
    case 1 : updateProdList();  break;
    }
}

void PManager::on_prod_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    Q_UNUSED(column);
    ui->add_update_btn->setEnabled(true);
    ui->prod_type_cb->clear();

    if (item->parent() != 0) {
        // resource selected
        ui->prod_type_cb->addItem(item->parent()->text(0));
        ui->prod_title_le->setText(item->text(0));
        ui->prod_dscr_te->setText(item->text(1));
        ui->extra_charge_dsb->setValue(item->text(2).toDouble());
        ui->rating_dsb->setValue(item->text(3).toDouble());
        ui->add_update_btn->setText(trUtf8("Изменить"));
        ui->delete_btn->setEnabled(true);
        ui->prod_title_le->setReadOnly(true);
    } else {
        // resource type or 'Add New' selected
        ui->prod_title_le->clear();
        ui->prod_dscr_te->clear();
        ui->extra_charge_dsb->setValue(0.00);
        ui->rating_dsb->setValue(0.0);
        ui->delete_btn->setEnabled(false);
        ui->prod_title_le->setReadOnly(false);

        if (ui->prod_treeWidget->indexOfTopLevelItem(item) == 0) {
            // 'Add New' selected
            ui->add_update_btn->setText(trUtf8("Добавить"));

            QList<QStringList> List = db->get("SELECT name FROM product_types ORDER BY name");

            for (int i = 0; i < List.length(); ++i)  ui->prod_type_cb->addItem(List[i].at(0));

        } else {
            // resource type selected
            ui->add_update_btn->setEnabled(false);
        }
    }
}

void PManager::on_add_update_btn_clicked()
{
    // Add / Update resources info
    QString prod_type = EDBconnection::escape(ui->prod_type_cb->currentText());
    QString prod_title  = EDBconnection::escape(ui->prod_title_le->text());
    QString prod_dscr = db->escape(ui->prod_dscr_te->toPlainText());
    double extra_chrge = ui->extra_charge_dsb->value();
    double rating = ui->rating_dsb->value();

    if (prod_title.isEmpty()) return;

    if (ui->prod_treeWidget->currentItem()->parent() != 0) {
        qDebug("Update");

        // Update suppliers_resources
        QString query = QString("UPDATE products SET title = '%1', description = '%2', extra_charge = '%3', rating = '%4' WHERE id = '%5'")
                                .arg(prod_title).arg(prod_dscr).arg(extra_chrge).arg(rating).arg(ui->prod_treeWidget->currentItem()->text(4));
        db->query(query);

    } else if (ui->prod_treeWidget->indexOfTopLevelItem(ui->prod_treeWidget->currentItem()) == 0) {
        qDebug("Add new");

        // this resource type already exists
        QString query = QString("SELECT id FROM `product_types` WHERE name = '%1'").arg(prod_type);
        int prod_type_id = db->get(query)[0].at(0).toInt();

        qDebug()<<"prod_type_id :"<<prod_type_id;

        if (prod_type_id == -1) {
            qDebug("ERROR : (prod_type_id == -1)");
            return;
        }

        // Insert resource (UNIQUE)
        query = QString("INSERT INTO products(product_type_id, title, description, extra_charge, rating) VALUES('%1', '%2', '%3', '%4', '%5') ")
                                .arg(prod_type_id).arg(prod_title).arg(prod_dscr).arg(extra_chrge).arg(rating);
        int res_id = db->insert(query);

        if (res_id == -1) {
            // ERROR message
            QMessageBox::warning(0, "Warning", trUtf8("Ошибка при добавлении товара. \n" \
                                                      "Возможно товар с таким названием уже существует."));
            return;
        }
    }

    updateProdList();
}

void PManager::on_delete_btn_clicked()
{
    // Delete resources
    qDebug("delete");

    int result = QMessageBox::question( 0, trUtf8("Внимание"),
                                                                trUtf8("Вы действительно хотите удалить этот товар?"),
                                                                QMessageBox::Yes, QMessageBox::No );

    if (result == QMessageBox::Yes) {

        QString query = QString("DELETE FROM products WHERE id='%1'").arg(ui->prod_treeWidget->currentItem()->text(4));
        db->query(query);

        updateProdList();
    }
}

void PManager::updateSuppliersList(void)
{
    QList<QStringList> List = EDBconnection::getInstance()->get("SELECT name, description FROM product_types");

    if (!List.isEmpty()) {
        ui->prod_types_table->setRowCount(List.length());
        for (int i = 0; i < List.length(); ++i)
            for (int j = 0; j < List.at(0).length(); ++j)
                ui->->setItem(i, j, new QTableWidgetItem(List[i].at(j));
    } else {
        qDebug("List is empty");
    }
}
