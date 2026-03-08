#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushLoad_clicked()
{
    QString site_url = "http://localhost:3000/car";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {

        ui->textBrowserResults->clear();

        if (reply->error() != QNetworkReply::NoError) {
            ui->textBrowserResults->setText("Network error: " + reply->errorString());
            reply->deleteLater();
            return;
        }

        QByteArray response_data = reply->readAll();
        QJsonParseError parseError;
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            ui->textBrowserResults->setText("JSON parsing error: " + parseError.errorString());
            reply->deleteLater();
            return;
        }

        QJsonArray json_array = json_doc.array();
        QString resultString = "";

        foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            QString id = QString::number(json_obj["id"].toInt());
            QString brand = json_obj["brand"].toString();
            QString model = json_obj["model"].toString();
            resultString += "ID: " + id + " | Brand: " + brand + " | Model: " + model + "\n";
        }

        ui->textBrowserResults->setText(resultString);
        reply->deleteLater();
    });
}


void MainWindow::on_pushAdd_clicked()
{
    QJsonObject json;
    json.insert("brand", ui->lineBrand->text());
    json.insert("model", ui->lineModel->text());

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    QString site_url = "http://localhost:3000/car";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            ui->textBrowserResults->setText("Error: " + reply->errorString());
        } else {
            ui->textBrowserResults->setText("Car added\n" + reply->readAll());
        }
        reply->deleteLater();
    });
}


void MainWindow::on_pushUpdate_clicked()
{
    QString id = ui->lineID->text();
    QString site_url = "http://localhost:3000/car/" + id;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("brand", ui->lineBrand->text());
    json.insert("model", ui->lineModel->text());

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    QNetworkReply *reply = manager->put(request, jsonData);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            ui->textBrowserResults->setText("Error: " + reply->errorString());
        } else {
            ui->textBrowserResults->setText("Car updated\n" + reply->readAll());
        }
        reply->deleteLater();
    });
}


void MainWindow::on_pushDelete_clicked()
{
    QString id = ui->lineID->text();
    QString site_url = "http://localhost:3000/car/" + id;
    QNetworkRequest request((site_url));

    QNetworkReply *reply = manager->deleteResource(request);

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            ui->textBrowserResults->setText("Error: " + reply->errorString());
        } else {
            ui->textBrowserResults->setText("Car deleted\n" + reply->readAll());
        }
        reply->deleteLater();
    });
}

