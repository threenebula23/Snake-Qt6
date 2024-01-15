#pragma once

#include <QWidget>
#include <QKeyEvent>

class Snake : public QWidget {

  public:
      Snake(QWidget *parent = 0);

  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

  private:
      QImage dot;
      QImage dot2;
      QImage head;
      QImage apple;
      QImage antidote;

      static const int B_WIDTH = 300;
      static const int B_HEIGHT = 300;
      static const int DOT_SIZE = 10;
      static const int ALL_DOTS = 900;
      static const int RAND_POS = 29;
      static const int DELAY = 140;

      int timerId;
      int dots;
      int axit;
      int apple_x;
      int apple_y;
      int axit_x;
      int axit_y;

      int let_x[30];
      int let_y[30];

      int x[ALL_DOTS];
      int y[ALL_DOTS];

      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;
      bool inGame;

      void loadImages();
      void initGame();
      void locateApple();
      void locateAxit();
      void locateLet();
      void checkApple();
      void checkAxit();
      void checkLet();
      void checkCollision();
      void move();
      void doDrawing();
      void gameOver(QPainter &);

      enum Directions{
          left,right,up,down
      };

      Directions m_dir;
      Directions vector;
};
