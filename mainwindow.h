#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "modules/auth/User.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const User& user, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onMenuClicked(QListWidgetItem *item);
    void toggleTheme();

private:
    void setupUi();
    void setupSidebar();
    void createPages();

    User m_user;
    QWidget *m_centralWidget;
    QHBoxLayout *m_mainLayout;
    
    // Sidebar
    QWidget *m_sidebar;
    QVBoxLayout *m_sidebarLayout;
    QListWidget *m_menuList;
    QPushButton *m_themeToggleBtn;
    QLabel *m_userLabel;

    // Content
    QStackedWidget *m_contentStack;

    // Theme state
    bool m_isDarkTheme;
};

#endif // MAINWINDOW_H
