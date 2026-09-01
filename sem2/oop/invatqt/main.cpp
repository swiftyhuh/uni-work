#include "Repository.h"
#include "Services.h"
#include "WatchList.h"
#include "gui.h" // Your GUI class
#include <QApplication> // Required for Qt application

int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Create the application object

    // Initialize your application services
    Repository repo("tutorials.txt");
    CSVWatchList csv_watch_list("watchlist.csv");
    HTMLWatchList html_watch_list("watchlist.html");
    Services csv_service(repo, &csv_watch_list);
    Services html_service(repo, &html_watch_list);

    // Create and show your main GUI window
    GUI gui(csv_service, html_service);
    gui.show(); // Show the main window

    return app.exec(); // Start the Qt event loop
}
