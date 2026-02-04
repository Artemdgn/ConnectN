#include "MainWindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gameOver = false;
    score1 = 0;
    score2 = 0;

    // Ask user for settings
    rows = QInputDialog::getInt(this, "Setup", "Enter number of rows (default 6):", 6, 1, 20);
    columns = QInputDialog::getInt(this, "Setup", "Enter number of columns (default 7):", 7, 1, 20);
    connectN = QInputDialog::getInt(this, "Setup", "Enter how many in a row to win (default 4):", 4, 1, 20);
    targetScore = QInputDialog::getInt(this, "Setup", "Enter target score to win the game (default 10):", 10, 1, 100);

    // Create game objects
    grid = new Grid(rows, columns);
    player1 = new Player("Player 1", YELLOW);
    player2 = new Player("Player 2", RED);
    currentPlayer = player1;

    initializeUI();
}

MainWindow::~MainWindow()
{
    delete grid;
    delete player1;
    delete player2;
}

void MainWindow::initializeUI()
{
    // Window settings
    setWindowTitle("ConnectN");
    resize(columns * 70 + 40, rows * 70 + 200);

    // Central widget and main layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Score label
    scoreLabel = new QLabel(this);
    scoreLabel->setText("Player 1: 0  |  Player 2: 0  |  First to " + QString::number(targetScore) + " wins!");
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setStyleSheet("font-size: 16px; font-weight: bold; padding: 5px;");
    mainLayout->addWidget(scoreLabel);

    // Status label
    statusLabel = new QLabel(this);
    statusLabel->setText("Player 1's turn");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("font-size: 20px; padding: 5px; color: goldenrod; font-weight: bold;");
    mainLayout->addWidget(statusLabel);

    // Column buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    for(int col = 0; col < columns; col++) {
        columnButtons[col] = new QPushButton("▼", this);
        columnButtons[col]->setFixedSize(60, 35);
        columnButtons[col]->setStyleSheet(
            "QPushButton { font-size: 18px; background-color: #4a90d9; color: white; border-radius: 5px; border: none; }"
            "QPushButton:hover { background-color: #357abd; }"
            "QPushButton:pressed { background-color: #2a5f9e; }"
            );
        connect(columnButtons[col], &QPushButton::clicked, this, [this, col]() {
            onColumnClicked(col);
        });
        buttonLayout->addWidget(columnButtons[col]);
    }
    mainLayout->addLayout(buttonLayout);

    // Board grid
    QWidget* boardWidget = new QWidget(this);
    boardWidget->setStyleSheet("background-color: #1a3a5c; border-radius: 10px; padding: 8px;");
    QGridLayout* boardLayout = new QGridLayout(boardWidget);
    boardLayout->setSpacing(4);
    boardLayout->setContentsMargins(8, 8, 8, 8);

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            boardCells[row][col] = new QLabel(this);
            boardCells[row][col]->setFixedSize(60, 60);
            boardCells[row][col]->setStyleSheet(
                "background-color: white;"
                "border-radius: 30px;"
                );
            boardLayout->addWidget(boardCells[row][col], row, col);
        }
    }
    mainLayout->addWidget(boardWidget);

    setCentralWidget(centralWidget);
}

void MainWindow::onColumnClicked(int column)
{
    if(gameOver) return;

    int row = grid->placePiece(column, currentPlayer->getPieceColour());

    // Column is full
    if(row == -1) {
        statusLabel->setText("Column is full! Pick another!");
        statusLabel->setStyleSheet("font-size: 20px; padding: 5px; color: red; font-weight: bold;");
        return;
    }

    updateBoard();
    checkWin(row, column);
}

void MainWindow::updateBoard()
{
    vector<vector<int>> boardState = grid->getGrid();

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            if(boardState[row][col] == GridPosition::EMPTY) {
                boardCells[row][col]->setStyleSheet(
                    "background-color: white; border-radius: 30px;"
                    );
            }
            else if(boardState[row][col] == GridPosition::YELLOW) {
                boardCells[row][col]->setStyleSheet(
                    "background-color: #f0c030; border-radius: 30px;"
                    "border: 3px solid #d4a020;"
                    );
            }
            else if(boardState[row][col] == GridPosition::RED) {
                boardCells[row][col]->setStyleSheet(
                    "background-color: #e03030; border-radius: 30px;"
                    "border: 3px solid #b02020;"
                    );
            }
        }
    }
}

void MainWindow::checkWin(int row, int column)
{
    if(grid->checkWin(connectN, row, column, currentPlayer->getPieceColour())) {
        // Update score
        if(currentPlayer == player1) score1++;
        else score2++;

        scoreLabel->setText("Player 1: " + QString::number(score1) +
                            "  |  Player 2: " + QString::number(score2) +
                            "  |  First to " + QString::number(targetScore) + " wins!");

        // Check if someone won the whole game
        if(score1 >= targetScore || score2 >= targetScore) {
            gameOver = true;
            statusLabel->setText(currentPlayer->getName().c_str() + QString(" wins the GAME!!! 🎉"));
            statusLabel->setStyleSheet("font-size: 24px; padding: 5px; color: green; font-weight: bold;");

            // Disable all buttons
            for(int col = 0; col < columns; col++) {
                columnButtons[col]->setEnabled(false);
            }
        }
        else {
            // Won a round, reset board
            statusLabel->setText(currentPlayer->getName().c_str() + QString(" wins the round!"));
            statusLabel->setStyleSheet("font-size: 20px; padding: 5px; color: green; font-weight: bold;");
            QMessageBox::information(this, "Round Won", currentPlayer->getName().c_str() + QString(" wins the round!"));
            resetBoard();
            currentPlayer = player1;
            statusLabel->setText("Player 1's turn");
            statusLabel->setStyleSheet("font-size: 20px; padding: 5px; color: goldenrod; font-weight: bold;");
        }
    }
    else {
        switchPlayer();
    }
}

void MainWindow::switchPlayer()
{
    if(currentPlayer == player1) {
        currentPlayer = player2;
        statusLabel->setText("Player 2's turn");
        statusLabel->setStyleSheet("font-size: 20px; padding: 5px; color: red; font-weight: bold;");
    }
    else {
        currentPlayer = player1;
        statusLabel->setText("Player 1's turn");
        statusLabel->setStyleSheet("font-size: 20px; padding: 5px; color: goldenrod; font-weight: bold;");
    }
}

void MainWindow::resetBoard()
{
    grid->initializeGrid();
    updateBoard();
}
