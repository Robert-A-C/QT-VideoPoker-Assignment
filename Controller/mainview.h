///////////////////////////////////////////////////////////////////////
// File: mainview.h
// Author: Robert Carll
// This assignment represents my own work and is in accordance with the College Academic Policy
// Copyright (c) 2015 All Right Reserved by Robert Carll
// Contributors:
// Description:
// Date: May 2016
// Revisions:
//////////////////////////////////////////////////////////////////////

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <memory>
#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QSpacerItem>
#include <QLabel>
#include <QSignalMapper>

class videopokergame;

struct Card;
using CardPtr = std::shared_ptr<Card>;

namespace Ui {
    class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

    void showCards();   // shows the user cards
    void winCheck();    // checks for win

private slots:
    void drawCards();                   // draws cards
    void dealHands();                   // deals hands
    void MainView::onCardClick(int i);  // toggles cards

private:
    Ui::MainView *ui;
    std::unique_ptr<videopokergame> _videoPoker; // creates videopokergame
    std::vector<QPushButton*> _hand;             // vector for the hand
    QPushButton* _btnDraw;                       // draw button
    QPushButton* _btnDeal;                       // deal button

    QLabel* _logo;
    QLabel* _payoutTable;

    std::vector<bool> _selected;
};

#endif // MAINVIEW_H
