#include <QPainter>
#include <QTime>
#include <QFontMetrics>
#include "Snake.h"

Snake::Snake(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:black;");
    m_dir=Directions::right;
    axit = 130;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    loadImages();
    initGame();
}

void Snake::loadImages() {

    dot.load("dot.png");
    dot2.load("dot2.png");
    head.load("head.png");
    apple.load("apple.png");
    antidote.load("antidote.png");
}

void Snake::initGame() {

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 90 - z * 10;
        y[z] = 140;
    }
    locateLet();
    locateApple();
    locateAxit();

    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doDrawing();
}

void Snake::doDrawing() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);
        qp.drawImage(axit_x,axit_y,antidote);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            }
            else{
            if(100-(100/dots-1)*z>axit)
            {
                qp.drawImage(x[z], y[z], dot2);
            }
            else
            {
                qp.drawImage(x[z], y[z], dot);
            }
            }
        }
        for (int i =0;i<30;i++)
        {
            qp.setBrush(Qt::gray);
            qp.drawRect(let_x[i],let_y[i],10,10);
        }

    } else {

        gameOver(qp);
    }
}

void Snake::gameOver(QPainter &qp) {

    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.lineWidth();

    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

void Snake::checkApple() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
        axit+=30;
        locateApple();
    }
}

void Snake::checkAxit()
{
    if ((x[0] == axit_x) && (y[0] == axit_y)) {

        axit+=85;
        if(axit > 130){axit=axit -(axit-130);}
        locateAxit();
    }
}

void Snake::checkLet()
{
    for(int i =0;i<30;i++)
    {
        if ((x[0] == let_x[i]) && (y[0] == let_y[i]))
            inGame = false;
    }
}

void Snake::move() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    switch (vector) {
    case Directions::left:
        x[0] -= DOT_SIZE;
        break;
    case Directions::right:
        x[0] += DOT_SIZE;
        break;
    case Directions::up:
        y[0] -= DOT_SIZE;
        break;
    case Directions::down:
        y[0] += DOT_SIZE;
        break;
    }

}

void Snake::checkCollision() {

    for (int z = dots; z > 0; z--) {

        if ((z > 3) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

void Snake::locateApple() {

    QTime time = QTime::currentTime();
    srand((uint) time.msec());
    int r = rand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = rand() % RAND_POS;
    apple_y = (r * DOT_SIZE);

    for (int i = 0; i < dots; i++) {
        if((apple_x == x[i]) && (apple_y == y[i]))
        {
            r = rand() % RAND_POS;
            apple_x = (r * DOT_SIZE);

            r = rand() % RAND_POS;
            apple_y = (r * DOT_SIZE);
        }
    }

    for (int i = 0; i < 30; i++) {
        if((apple_x == let_x[i]) && (apple_y == let_y[i]))
        {
            let_x[i]=500;
            let_y[i]=500;
        }
    }

}

void Snake::locateAxit()
{

    int r = rand() % RAND_POS;
    axit_x = (r * DOT_SIZE);

    r = rand() % RAND_POS;
    axit_y = (r * DOT_SIZE);
    for (int i = 0; i < dots; i++) {
        if((axit_x == x[i]) && (axit_y == y[i]))
        {
            r = rand() % RAND_POS;
            axit_x = (r * DOT_SIZE);

            r = rand() % RAND_POS;
            axit_y = (r * DOT_SIZE);
        }
    }

    for (int i = 0; i < 30; i++) {
        if((axit_x == let_x[i]) && (axit_y == let_y[i]))
        {
            let_x[i]=500;
            let_y[i]=500;
        }
    }
}

void Snake::locateLet()
{
    QTime time = QTime::currentTime();
    srand((uint) time.msec());

    int h=0;
    for(int i=0;i<6;i++)
    {
        for(int g=0;g<2;g++)
        {
            let_x[h]= ((rand() % 4) +1 )*10 + 50*i;
            let_y[h]= ((rand() % 4) +1 )*10 + 50*g;
            h++;
        }
    }
    for(int i=0;i<6;i++)
    {
        for(int g=5;g>3;g--)
        {
            let_x[h]= ((rand() % 4) +1)*10 + 50*i;
            let_y[h]= ((rand() % 4) +1)*10 + 50*g;
            h++;
        }
    }
    let_x[24]= ((rand() % 4) +1)*10 + 50*0;
    let_y[24]= ((rand() % 4) +1)*10 + 50*2;

    let_x[25]= ((rand() % 4) +1)*10 + 50*0;
    let_y[25]= ((rand() % 4) +1)*10 + 50*3;

    let_x[26]= ((rand() % 4) +1)*10 + 50*4;
    let_y[26]= ((rand() % 4) +1)*10 + 50*2;

    let_x[27]= ((rand() % 4) +1)*10 + 50*4;
    let_y[27]= ((rand() % 4) +1)*10 + 50*3;

    let_x[28]= ((rand() % 4) +1)*10 + 50*5;
    let_y[28]= ((rand() % 4) +1)*10 + 50*2;

    let_x[29]= ((rand() % 4) +1)*10 + 50*5;
    let_y[29]= ((rand() % 4) +1)*10 + 50*3;



}

void Snake::timerEvent(QTimerEvent *e) {

    Q_UNUSED(e);

    if (inGame) {
        vector = m_dir;
        axit-=2;
        if (axit<0) {inGame=false;}
        checkApple();
        checkAxit();
        checkLet();
        checkCollision();
        move();
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_Left) && (vector != Directions::right)) {
        m_dir = Directions::left;
    }

    if ((key == Qt::Key_Right) && (vector != Directions::left)) {
        m_dir = Directions::right;
    }

    if ((key == Qt::Key_Up) && (vector != Directions::down)) {
        m_dir = Directions::up;
    }

    if ((key == Qt::Key_Down) && (vector != Directions::up)) {
        m_dir = Directions::down;
    }

    QWidget::keyPressEvent(e);
}
