#include <QtWidgets/QApplication>
#include "database/DatabaseManager.h"
#include "ui/LoginDialog.h"
#include "mainwindow.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 1. Initialize Database
    DatabaseManager& dbInfo = DatabaseManager::instance();
    if (!dbInfo.connectToDatabase()) {
        QMessageBox::critical(nullptr, "Database Error", "Could not connect to the database. Application will exit.");
        return -1;
    }

    // 2. Show Login Dialog
    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        // 3. If authenticated, start Main Window
        std::optional<User> user = login.getAuthenticatedUser();
        if (user) {
            MainWindow* window = new MainWindow(*user);
            window->show();
            return app.exec();
        }
    }

    return 0;
}
