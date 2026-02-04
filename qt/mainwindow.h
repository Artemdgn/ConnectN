#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Grid.h"
#include "Player.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onColumnClicked(int column);

private:
    // Game objects
    Grid* grid;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    int connectN;
    int rows;
    int columns;
    int score1;
    int score2;
    int targetScore;
    bool gameOver;

    // UI elements
    QLabel* statusLabel;
    QLabel* scoreLabel;
    QLabel* boardCells[20][20];      // Max 20x20 board
    QPushButton* columnButtons[20];  // Max 20 columns

    // Methods
    void initializeUI();
    void updateBoard();
    void switchPlayer();
    void checkWin(int row, int column);
    void resetBoard();
};

#endif // MAINWINDOW_H
