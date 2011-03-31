#ifndef PMANAGER_H
#define PMANAGER_H

#include <QTabWidget>
#include <QTreeWidgetItem>
#include "edbconnection.h"

namespace Ui {
    class PManager;
}

class PManager : public QTabWidget
{
    Q_OBJECT

public:
    explicit PManager(QWidget *parent = 0);
    ~PManager();

public slots:
    void startP(void);

private slots:
    void on_add_prod_type_clicked();
//    void on_prod_type_dscr_ed_textChanged();
    void on_prod_types_table_cellActivated(int row, int column);
    void on_save_prod_type_clicked();
    void on_del_prod_type_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_prod_treeWidget_itemClicked(QTreeWidgetItem* item, int column);
    void on_add_update_btn_clicked();
    void on_delete_btn_clicked();
    void on_add_supplier_btn_clicked();
    void on_suppliers_types_table_cellClicked(int row, int column);
    void on_save_supplier_btn_clicked();
    void on_del_supplier_btn_clicked();
    void on_new_price_rec_btn_clicked();

private:
    Ui::PManager *ui;
    QList<QTreeWidgetItem *>* type_items;
    QList<QTreeWidgetItem *>* items;
    EDBconnection* db;

    // private methods
    int selected_row;
    void updateProdTypesList(void);
    void updateProdList(void);
    void updateSuppliersList(void);
    void updatePriceList(void);
};

#endif // PMANAGER_H
