#include "lecture11_demo_custom_models.h"
#include "PaginatedGenesTableModel.h"
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include "PictureDelegate.h"

Lecture11_demo_custom_models::Lecture11_demo_custom_models(GeneService& s, QWidget *parent) : QMainWindow(parent), serv{ s }
{
	ui.setupUi(this);

	// create the model
	this->tableModel = std::make_unique<GenesTableModel>(this->serv);

	// set the model for the table view
	this->setupTableView();

	// set the model for the tree view
	this->setupTreeView();

	// set the model for the list view
	ui.genesListView->setModel(this->tableModel.get());

	// create and set the model for the paginated table view
	this->setupPaginatedTableView();

	// set the model for the table view, the one that should display images
	this->setupPictureTableView();
}

Lecture11_demo_custom_models::~Lecture11_demo_custom_models()
{
}

void Lecture11_demo_custom_models::setupTableView()
{
	// set the model
	ui.genesTableView->setModel(this->tableModel.get());

	//// create and set a QSortFilterProxyModel and enable sorting
	//QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel{};
	//proxyModel->setSourceModel(this->tableModel.get());
	//ui.genesTableView->setSortingEnabled(true);
	////ui.genesTableView->setAlternatingRowColors(true); // use this if the background role is not used !

	//// filtering
	//proxyModel->setFilterRegularExpression(QRegularExpression("Human", QRegularExpression::CaseInsensitiveOption));
	//proxyModel->setFilterKeyColumn(1);

	//ui.genesTableView->setModel(proxyModel);

	// force the columns to resize, according to the size of their contents
	ui.genesTableView->resizeColumnsToContents();
	// hide the vertical header
	ui.genesTableView->verticalHeader()->hide();

	// alternate row colours in the table view
	QPalette p = ui.genesTableView->palette();
	p.setColor(QPalette::Base, Qt::white);
	p.setColor(QPalette::AlternateBase, QColor("#D6FCDB")); // Odd rows
	ui.genesTableView->setPalette(p);

	ui.genesTableView->setAlternatingRowColors(true);
}

void Lecture11_demo_custom_models::setupTreeView()
{
	ui.genesTreeView->setModel(this->tableModel.get());

	// force the columns to resize, according to the size of their contents
	ui.genesTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void Lecture11_demo_custom_models::setupPaginatedTableView()
{
	PaginatedGenesTableModel* pagTableModel = new PaginatedGenesTableModel{ this->serv };
	ui.paginatedGenesTableView->setModel(pagTableModel);

	// force the columns to resize, according to the size of their contents
	ui.paginatedGenesTableView->resizeColumnsToContents();
	// hide the vertical header
	ui.paginatedGenesTableView->verticalHeader()->hide();
}

void Lecture11_demo_custom_models::setupPictureTableView()
{
	// set the model
	ui.picturesTableView->setModel(this->tableModel.get());

	// set the custom delegate
	ui.picturesTableView->setItemDelegate(new PictureDelegate{});

	// force the columns to resize, according to the size of their contents
	ui.picturesTableView->resizeColumnsToContents();
	ui.picturesTableView->resizeRowsToContents();
	// hide the vertical header
	ui.picturesTableView->verticalHeader()->hide();
}
