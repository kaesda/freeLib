#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWebEngineView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QSqlQuery>
#include <QtWidgets/QTreeWidgetItem>
#include <QBuffer>
#include "helpdialog.h"
#include <QMenu>
#include <QDropEvent>
#include <QDragEnterEvent>
#include "dropform.h"
#include <QTcpServer>
#include "opds_server.h"
#include "common.h"
#include <QSystemTrayIcon>
#include <QTimer>
#include "myapplicationclass.h"

namespace Ui {
class MainWindow;
}

struct Stag
{
    QPixmap pm;
    int id;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool error_quit;
    
private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trIcon;
    QToolButton *tbClear;
    void UpdateAuthor();
    void UpdateSeria();
    void UpdateJanre();
    DropForm *dropForm;
    QString last_search_symbol;
    //QMenu ContextBookMenu;
    qlonglong CurrentBookID,CurrentSeriaID;
//    QSqlDatabase dbase;
    void UpdateTags();
    QMenu TagMenu;
    QObject* current_list_for_tag;
    qlonglong current_list_id,stored_book;
    void SaveLibPosition();
    QList<Stag> tags_pic;
    QPixmap GetTag(int id);
    void update_list_pix(qlonglong id,int list,int tag_id);
    void uncheck_books(QList<qlonglong> list);
    opds_server opds;
    QToolButton *FirstButton;
    QToolButton *btn_Hash;
    void UpdateExportMenu();
    void DeleteDropForm();
//    void closeEvent(QCloseEvent *event);
protected:
    void showEvent(QShowEvent *ev);
    void resizeEvent(QResizeEvent * e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void leaveEvent(QEvent *e);
    APP_MODE mode;
    void closeEvent(QCloseEvent *event);
    void FillBookList(QSqlQuery &query);
    void CheckParent(QTreeWidgetItem* parent);
    void CheckChild(QTreeWidgetItem* parent);
    void FillCheckedBookList(QList<book_info> &list, QTreeWidgetItem* item=0, bool send_all=false, bool count_only=false, bool checked_only=false);
    void FillCheckedItemsBookList(QList<book_info> &list, QTreeWidgetItem* item, bool send_all,bool count_only);
    void ExportBookListBtn(bool Enable);
    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);
    void dragLeaveEvent(QDragLeaveEvent *);
    void dragMoveEvent(QDragMoveEvent *ev);
    void proc_path(QString path, QStringList *book_list);
    void MoveToJanre(qlonglong id);
    void FillLibrariesMenu();
    void SendMail();
    void SendToDevice();
    QTimer searchTimer;
    void changeEvent(QEvent *event);
private slots:
    void ShowDropForm();
    void TimerSearch();
    void TimerResetSearch();
    void ExportAction();
    void Add_Library();
    void CheckBooks();
    void EditBooks();
    void Settings();
    void searchCanged(QString str);
    void searchClear();
    void btnSearch();
    void btnAuthor();
    void btnSeries();
    void btnPageSearch();
    void DoSearch();
    void btnJanres();
    void SelectAuthor();
    void SelectBook();
    void SelectJanre();
    void SelectSeria();
    void itemChanged(QTreeWidgetItem*,int);
    void BookDblClick();
    void About();
    void LanguageChange();
    void StartSearch();
    void HelpDlg();
    void ContextMenu(QPoint point);
    void MoveToAuthor(qlonglong id=-1,QString FirstLetter="");
    void MoveToSeria(qlonglong id=-1,QString FirstLetter="");
    void tag_select(int index);
    void set_tag();
    void ChangingPort(int i);
    void ChangingLanguage(bool change_language=true);
    void ReviewLink(QUrl url);
    void SelectLibrary();
    void on_actionSwitch_to_convert_mode_triggered();
    //void on_actionSwitch_to_shelf_mode_triggered();
    void on_actionSwitch_to_library_mode_triggered();

    void on_btnSwitchToLib_clicked();

    void on_btnPreference_clicked();

    void on_splitter_splitterMoved(int pos, int index);

    void ChangingTrayIcon(int index=-1, int color=-1);

    void TrayMenuAction(QSystemTrayIcon::ActivationReason reson);

    void dockClicked();
    void MinimizeWindow();
public slots:
    void newLibWizard(bool AddLibOnly=true);
signals:
    void window_loaded();
};

#endif // MAINWINDOW_H