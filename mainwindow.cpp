#include "mainwindow.h"
#include "ui/Dashboard.h"
#include "ui/student/StudentPortal.h"
#include "ui/academic/AcademicSystem.h"
#include <QHeaderView>
#include <QApplication>

MainWindow::MainWindow(const User& user, QWidget *parent)
    : QMainWindow(parent), m_user(user), m_isDarkTheme(false)
{
    setupUi();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    setMinimumSize(1200, 800);
    setWindowTitle("University SIS - " + m_user.fullName);

    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_mainLayout = new QHBoxLayout(m_centralWidget);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    setupSidebar();

    // Content Area
    m_contentStack = new QStackedWidget(this);
    m_contentStack->setStyleSheet("background-color: #f7fafc;");
    m_mainLayout->addWidget(m_contentStack);

    createPages();
}

void MainWindow::setupSidebar() {
    // Modern Light Sidebar
    m_sidebar = new QWidget(this);
    m_sidebar->setFixedWidth(280);
    // Pure white sidebar with subtle border
    m_sidebar->setStyleSheet("background-color: #ffffff; border-right: 1px solid #e2e8f0;");

    m_sidebarLayout = new QVBoxLayout(m_sidebar);
    m_sidebarLayout->setContentsMargins(0, 0, 0, 0);
    m_sidebarLayout->setSpacing(0);

    // App Logo/Title
    QLabel *logoLabel = new QLabel("University SIS", m_sidebar);
    logoLabel->setFixedHeight(80);
    logoLabel->setAlignment(Qt::AlignCenter);
    // Dark almost black text for contrast
    logoLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #1a1a1a; border-bottom: 1px solid #e2e8f0;");
    m_sidebarLayout->addWidget(logoLabel);

    // Menu
    m_menuList = new QListWidget(m_sidebar);
    m_menuList->setFrameShape(QFrame::NoFrame);
    // List styling: Black text, light gray hover/select
    // List styling: Black text, light gray hover/select
    m_menuList->setStyleSheet(R"(
        QListWidget { background-color: transparent; outline: none; border: none; }
        QListWidget::item { 
            height: 50px; 
            padding-left: 20px; 
            font-size: 16px; 
            color: #000000; 
            border-left: 4px solid transparent; 
        }
        QListWidget::item:selected { 
            background-color: #e9ecef; 
            color: #000000;
            border-left-color: #000000; 
            font-weight: bold;
        }
        QListWidget::item:hover { 
            background-color: #f1f3f5; 
            color: #000000;
        }
    )");
    
    // Add items based on Role
    auto addItem = [this](const QString& name, const QString& icon) {
        QListWidgetItem *item = new QListWidgetItem(name, m_menuList);
        // In real app, setIcon(QIcon(icon));
        item->setData(Qt::UserRole, name);
    };

    addItem("Dashboard", "");
    
    if (m_user.role == UserRole::Admin || m_user.role == UserRole::Faculty) {
        addItem("Student Portal", "");
        addItem("Academic System", "");
    }
    
    if (m_user.role == UserRole::Student) {
        addItem("My Courses", "");
        addItem("My Grades", "");
    }
    
    if (m_user.role == UserRole::Admin || m_user.role == UserRole::Finance) {
        addItem("Finance System", "");
    }

    addItem("Profile", "");

    connect(m_menuList, &QListWidget::itemClicked, this, &MainWindow::onMenuClicked);
    m_sidebarLayout->addWidget(m_menuList);
    
    m_sidebarLayout->addStretch();

    // User Profile Small View at bottom
    QWidget *userWidget = new QWidget(m_sidebar);
    userWidget->setFixedHeight(80);
    userWidget->setStyleSheet("background-color: #f8fafc; border-top: 1px solid #e2e8f0;");
    QHBoxLayout *userLayout = new QHBoxLayout(userWidget);
    
    QWidget *avatar = new QWidget();
    avatar->setFixedSize(40, 40);
    avatar->setStyleSheet("background-color: #000000; border-radius: 20px;"); // Black avatar
    
    QLabel *userName = new QLabel(m_user.username, userWidget);
    userName->setStyleSheet("font-weight: bold; color: #000000; padding-left: 10px; font-size: 14px;");
    
    userLayout->addWidget(avatar);
    userLayout->addWidget(userName);
    
    m_sidebarLayout->addWidget(userWidget);

    m_mainLayout->addWidget(m_sidebar);
}

void MainWindow::createPages() {
    // 0: Dashboard
    m_contentStack->addWidget(new Dashboard(m_user, this));

    // 1: Student Portal
    m_contentStack->addWidget(new StudentPortal(this));
    
    // 2: Academic System
    m_contentStack->addWidget(new AcademicSystem(this));
}

void MainWindow::onMenuClicked(QListWidgetItem *item) {
    QString pageName = item->data(Qt::UserRole).toString();
    
    if (pageName == "Dashboard") {
        m_contentStack->setCurrentIndex(0);
    } else if (pageName == "Student Portal") {
        m_contentStack->setCurrentIndex(1);
    } else if (pageName == "Academic System") {
        m_contentStack->setCurrentIndex(2);
    }
}

void MainWindow::toggleTheme() {
    m_isDarkTheme = !m_isDarkTheme;
    // Apply QSS for dark/light mode
    QString bg = m_isDarkTheme ? "#1a202c" : "#f7fafc";
    QString text = m_isDarkTheme ? "#ffffff" : "#000000";
    // ... complete theme logic
}
