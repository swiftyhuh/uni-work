#include "MyModel.h"
#include <QFont>
#include <QColor>

MyModel::MyModel(Service& serv): serv{serv}
{
}

int MyModel::rowCount(const QModelIndex& parent) const
{
	return this->serv.getSize();
}

int MyModel::columnCount(const QModelIndex& parent) const
{
	return 2;
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int col = index.column();

	Product p = this->serv.getAll()[row];

	if (role == Qt::DisplayRole) {
		switch (col) {
		case 0:
			return QString::fromStdString(p.getName());
		case 1:
			return QString::number(p.getPrice());
		}
	}

	if (role == Qt::FontRole) {
		QFont font{ "Verdana", 20 };
		if (col == 0)
			return font;
	}

	if (role == Qt::ForegroundRole)
	{
		QColor colour{ 0, 0, 255 };
		if (col == 1)
			return colour;
	}

	return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		switch (section) {
		case 0:
			return "Name";
		case 1:
			return "Price";
		}
	}

	return QVariant();
}

double MyModel::getTotal() const
{
	return this->serv.getTotal();
}

void MyModel::addProduct(const std::string& name, double price) {
	int size = this->serv.getSize();
	this->beginInsertRows(QModelIndex{}, size, size);
	this->serv.addProduct(name, price);
	this->endInsertRows();

	emit updateTotalSignal();
}

