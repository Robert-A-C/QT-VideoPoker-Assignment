///////////////////////////////////////////////////////////////////////
// File: mainview.cpp
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#include "mainview.h"
#include "ui_mainview.h"
#include "../Model/videopokergame.h"
#include "../Model/Hand.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QSpacerItem>
#include <QLabel>
#include <memory>
#include <QSignalMapper>

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: green;");

    _videoPoker = std::unique_ptr<videopokergame>(new videopokergame()); // creates videopokergame instance

    auto vlMain = new QVBoxLayout(ui->centralWidget);   // main layout
    auto hlLogo = new QHBoxLayout();                    // logo layout
    auto hlTable = new QHBoxLayout();                   // score table layout
    auto glCards = new QGridLayout();                   // card layout
    auto hlButtons = new QHBoxLayout();                 // button layout

    _logo = new QLabel();                                                   // creates logo label
    _logo->setMaximumSize(600,100);                                         // sets max size
    _logo->setMinimumSize(600,100);                                         // sets min size
    _logo->setStyleSheet("Border-image:url(:/images/Media/banner.png)");    // adds image to the label

    QSpacerItem *spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed); // creates spacer

    hlLogo->addSpacerItem(spacer);      // add spacer
    hlLogo->addWidget(_logo);           // adds logo to layout
    hlLogo->addSpacerItem(spacer);      // add spacer

    vlMain->addLayout(hlLogo);          // add hl layout to main layout

    _payoutTable = new QLabel();                                                    // creates payout table logo
    _payoutTable->setMaximumSize(400,350);                                          // sets max size
    _payoutTable->setMinimumSize(400,350);                                          // sets min size
    _payoutTable->setStyleSheet("Border-image:url(:/images/Media/paysheet1.png)");  // adds payout image to payput table label

    hlTable->addSpacerItem(spacer);     // adds spacer
    hlTable->addWidget(_payoutTable);   // adds logo to layout
    hlTable->addSpacerItem(spacer);     // adds spacer

    vlMain->addLayout(hlTable); // adds table layout to the main layout

    QSignalMapper * signalMapper = new QSignalMapper(this);                         // creates a Qsignal Mapper
    auto mapSignal = static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map);

    QFont font;
    font.setBold(true);
    font.setPixelSize(15);

    for(int i = 0; i < 5; i++)
    {
        auto btn = new QPushButton();
        btn->setFont(font);
        btn->setMaximumSize(80,160);
        btn->setMinimumSize(80,160);
        btn->setEnabled(false);

        btn->setStyleSheet("Border-image:url(:/images/Media/cardback.png)"); // adds card back image;
        glCards->addWidget(btn, 0, i);

        connect(btn, &QPushButton::clicked, signalMapper, mapSignal);
        signalMapper->setMapping(btn, i);

        _hand.push_back(btn);
    }

    vlMain->addLayout(glCards); // adds the card layout to the main layout


    //connects signal mapper to on card click
    connect(signalMapper, static_cast<void (QSignalMapper::*)(int)>(&QSignalMapper::mapped), this, &MainView::onCardClick);

    _btnDraw = new QPushButton();
    _btnDraw->setText(QString("Draw"));
    _btnDraw->setMaximumSize(80,50);
    _btnDraw->setEnabled(false);
    connect(_btnDraw, &QPushButton::clicked, this, &MainView::drawCards); // connects button to on draw
    _btnDraw->setStyleSheet("background-color: red");

    _btnDeal = new QPushButton();
    _btnDeal->setText(QString("Deal"));
    _btnDeal->setMaximumSize(80,50);
    connect(_btnDeal, &QPushButton::clicked, this, &MainView::dealHands); // connects button to on deal
    _btnDeal->setStyleSheet("background-color: red");


    hlButtons->addWidget(_btnDraw);     // adds draw button to layout
    hlButtons->addWidget(_btnDeal);     // adds deal button to layout

    hlButtons->addSpacerItem(spacer);   // adds spacer

    vlMain->addLayout(hlButtons);       // adds button layout to main layout

    for(int i = 0; i < 5;i++)
    {
        _selected.push_back(false);
    }
}

MainView::~MainView()
{
    delete ui;
}

void MainView::onCardClick(int i) // toggles cards
{
    if(_selected.at(i) == false)
    {
         _hand.at(i)->setStyleSheet("Border-image:url(:/images/Media/cardfrontHold.png)");
         _selected.at(i) = true;
    }
    else
    {
        _hand.at(i)->setStyleSheet("Border-image:url(:/images/Media/cardfront.png)");
        _selected.at(i) = false;
    }
}

void MainView::drawCards() // draws new cards
{
    for(int i = 0; i < 5;i++)
    {
        _hand.at(i)->setEnabled(false);
        if( _selected.at(i) == false)
        {
            _videoPoker->newCards(i);
        }
    }
    _btnDraw->setEnabled(false);
    _btnDeal->setEnabled(true);

    for(int i = 0; i < 5;i++)
    {
        _selected.at(i) = false;
    }

    showCards();
    winCheck();
}

void MainView::dealHands() // deals hand
{
    for(int i = 0; i < 5;i++)
    {
         _hand.at(i)->setEnabled(true);
    }
    _videoPoker->newHand();

    _btnDraw->setEnabled(true);
    _btnDeal->setEnabled(false);

    showCards();
}

void MainView::showCards() // shows the user cards
{
    for(int i = 0; i < 5;i++)
    {
        _hand.at(i)->setStyleSheet("Border-image:url(:/images/Media/cardfront.png)");
        QString str = QString::fromStdString(_videoPoker->drawHand(i));
         _hand.at(i)->setText(str);
    }
}

void MainView::winCheck() // checks for win
{
    std::string outcome = _videoPoker->winCheck();
    QString qOutcome = QString::fromStdString(outcome);
    QMessageBox msg;
    msg.setText(qOutcome);
    msg.exec();
}
