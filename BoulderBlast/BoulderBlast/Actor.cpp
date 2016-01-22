#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include  <cstdlib>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void Agent::fire()
{
    int x=getX();
    int y=getY();
    getProposedLocation(x, y, getDirection());
    Actor* p=new Bullet(IID_BULLET, x, y, getWorld(), getDirection());
    p->setVisible(true);
    getWorld()->addBullet(p);
}

void Player::attacked()
{
    damage();
    if (getHealth()<=0) {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
    getWorld()->playSound(SOUND_PLAYER_IMPACT);

}

void Player::doSomething()
{
    
    if (!isAlive())
        return;
    int ch;
    int proposedX, proposedY;
    Direction proposedDir;
    if (getWorld()->getKey(ch)) {
        switch (ch) {
            case KEY_PRESS_LEFT:
                proposedX=getX()-1;
                proposedY=getY();
                proposedDir=left;
                break;
            case KEY_PRESS_RIGHT:
                proposedX=getX()+1;
                proposedY=getY();
                proposedDir=right;
                break;
            case KEY_PRESS_UP:
                proposedX=getX();
                proposedY=getY()+1;
                proposedDir=up;
                break;
            case KEY_PRESS_DOWN:
                proposedX=getX();
                proposedY=getY()-1;
                proposedDir=down;
                break;
            case KEY_PRESS_ESCAPE:
                setDead();
                return;
            case KEY_PRESS_SPACE:
                if (m_ammunition>0)
                {
                   fire();
                   m_ammunition--;
                getWorld()->playSound(SOUND_PLAYER_FIRE);

                }
                return;
            
            default:
                return;
        }
        setDirection(proposedDir);
        Actor* ap=getWorld()->getAnActor(proposedX,proposedY, this);
        
        if (ap==nullptr)
            moveTo(proposedX, proposedY);
        else
        {
            Boulder* bp = dynamic_cast<Boulder*>(ap);
            if (bp!=nullptr)
            {
                if (bp->pushed(proposedDir))
                    moveTo(proposedX, proposedY);
            }
            else if (!ap->block())
                moveTo(proposedX, proposedY);

        }
    }
    return;
}


bool Boulder::pushed(Direction dir)
{
    
    int proposedX=getX();
    int proposedY=getY();
    getProposedLocation(proposedX, proposedY, dir);
    Actor* ap=getWorld()->getAnActor(proposedX,proposedY, this);
    Hole* hp = dynamic_cast<Hole*>(ap);

    if (ap==nullptr || hp!=nullptr)
    {
        moveTo(proposedX, proposedY);
        return true;
    }
    return false;

}

void Boulder::attacked()
{
    damage();
    if (getHealth()<=0) {
        setDead();
    }
    return;

}

void Hole::doSomething()
{
    if (!isAlive())
    return;
    Actor* ap=getWorld()->getAnActor(getX(),getY(), this);
    Boulder* bp = dynamic_cast<Boulder*>(ap);
    if (bp!=nullptr)
    {
        setDead();
        ap->setDead();
    }
    return;
}

void Bullet::doSomething()
{
    if (!isAlive())
        return;
    
    Actor* ap=getWorld()->getAnActor(getX(),getY(), this);
    Agent* agp = dynamic_cast<Agent*>(ap);
    if (ap!=nullptr && ap->destroyBullet())
    {
        if (agp!=nullptr)
            agp->attacked();
        setDead();
    }
    else
    {
        int proposedX=getX();
        int proposedY=getY();
        getProposedLocation(proposedX, proposedY, getDirection());
        moveTo(proposedX, proposedY);
        ap=getWorld()->getAnActor(getX(),getY(), this);
        agp = dynamic_cast<Agent*>(ap);
        if (ap!=nullptr && ap->destroyBullet())
        {
            if (agp!=nullptr)
                agp->attacked();
            setDead();
        }

    }
    
    return;

}

void Jewel::doSomething()
{
    if (!isAlive())
        return;
    Actor* ap=getWorld()->getAnActor(getX(),getY(), this);
    Player* pp = dynamic_cast<Player*>(ap);
    if (pp!=nullptr)
    {
        getWorld()->increaseScore(50);
        getWorld()->decJewel();
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);

    }
    return;

}

void Exit::doSomething()
{
    if(getWorld()->getJewel()==0)
    {
        setVisible(true);
        getWorld()->playSound(SOUND_REVEAL_EXIT);
        getWorld()->decJewel();
    }
    Actor* ap=getWorld()->getAnActor(getX(),getY(), this);
    Player* pp = dynamic_cast<Player*>(ap);
    if (pp!=nullptr && getWorld()->getJewel()==-1)
    {
        getWorld()->increaseScore(2000);
        getWorld()->setLevelComplete();
        getWorld()->playSound(SOUND_FINISHED_LEVEL);

    }
    return;

}

void ExtraLife::doSomething()
{
    
    if (!isAlive())
        return;
    Actor* ap=getWorld()->getAnActor(getX(),getY(), this);
    Player* pp = dynamic_cast<Player*>(ap);
    if (pp!=nullptr)
    {
        getWorld()->increaseScore(1000);
        getWorld()->incLives();
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);

    }
    return;
}

void RestoreHealth::doSomething()
{
    if (!isAlive())
        return;
    Actor* ap=getWorld()->getAnActor(getX(),getY(), this);
    Player* pp = dynamic_cast<Player*>(ap);
    if (pp!=nullptr)
    {
        getWorld()->increaseScore(500);
        pp->restoreHealth();
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);

    }
    return;

}

void Ammo::doSomething()
{
    if (!isAlive())
        return;
    Actor* ap=getWorld()->getAnActor(getX(),getY(), this);
    Player* pp = dynamic_cast<Player*>(ap);
    if (pp!=nullptr)
    {
        getWorld()->increaseScore(100);
        pp->addAmmunition();
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);

    }
    return;

}

Robot::Robot(int imageID, int startX, int startY, StudentWorld* World, Direction dir, int health)
:Agent(imageID, startX, startY, World, dir, health)
{
    m_tick=(28-getWorld()->getLevel())/4;
    if (m_tick < 3)
        m_tick = 3;
}

bool Robot::attack()
{
    Actor* ap=nullptr;
    int x=getX();
    int y=getY();
    Direction dir=getDirection();
    
    while (ap==nullptr || !ap->block()) {
        getProposedLocation(x, y, dir);
        ap=getWorld()->getAnActor(x,y, this);
        
    }
    Player* pp = dynamic_cast<Player*>(ap);
    
    if (pp!=nullptr) {
        fire();
        getWorld()->playSound(SOUND_ENEMY_FIRE);
        return true;
    }
    return false;

}

bool Robot::moveOneStep()
{
    int x=getX();
    int y=getY();
    Direction dir=getDirection();
    Actor* ap;
    getProposedLocation(x, y, dir);
    ap=getWorld()->getAnActor(x,y, this);
    if (ap==nullptr || !ap->block() ) {
        moveTo(x, y);
        return true;
    }
    return false;

}


void SnarlBot::doSomething()
{
    if (!isAlive() || !tick())
        return;
    if (attack())
        return;
    if (moveOneStep())
        return;
    else
        turnAround();

    return;
}

void SnarlBot::attacked()
{
    damage();
    if (getHealth()<=0) {
        setDead();
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(100);
    }
    getWorld()->playSound(SOUND_ROBOT_IMPACT);

}

void Factory::doSomething()
{
    Actor* ap;
    int num=0;
    for (int x=max(0,getX()-3); x<min(VIEW_WIDTH,getX()+3); x++) {
        for (int y=max(0,getY()-3); y<min(VIEW_HEIGHT,getY()+3); y++) {
            ap=getWorld()->getAnActor(x,y, this);
            KleptoBot* kp = dynamic_cast<KleptoBot*>(ap);
            if (kp!=nullptr)
                num++;
        }

    }
    ap=getWorld()->getAnActor(getX(),getY(), this);
    //KleptoBot* kp = dynamic_cast<KleptoBot*>(ap);

    if (num<3 && ap==nullptr && rand()%50==0) {
        Actor* p;
        if (m_angry)
        {
             p=new AngryKleptoBot(IID_KLEPTOBOT, getX(),getY(),getWorld());
        }
        else
        {
             p=new KleptoBot(IID_KLEPTOBOT, getX(),getY(),getWorld());
        }
        p->setVisible(true);
        getWorld()->addActor(p);
        getWorld()->playSound(SOUND_ROBOT_BORN);

    }
}

KleptoBot::KleptoBot(int imageID, int startX, int startY, StudentWorld* World,Direction dir,int health)
:Robot(imageID, startX, startY, World, dir, health)
{
    m_distance=rand()%6+1;
    m_goodie=nullptr;
}

bool KleptoBot::steal()
{
    Actor* ap=getWorld()->getAnActor(getX(),getY(), this);
    if (ap!=nullptr && ap->stealable() && rand()%10==0) {
        m_goodie=ap;
        ap->setVisible(false);
        getWorld()->deleteActor(ap);
        getWorld()->playSound(SOUND_ROBOT_MUNCH);
        return true;
    }
    return false;

}

void KleptoBot::ConsiderDirection()
{
    m_distance=rand()%6+1;
    int ran=rand()%4;
    int x,y;
    Direction d=Direction(ran+1);
    Actor* ap;
    for (int i=0; i<3; i++)
    {
        x=getX();
        y=getY();
        getProposedLocation(x, y, d);
        ap=getWorld()->getAnActor(x,y, this);
        if (ap==nullptr || !(ap->block() ) )
        {
            moveTo(x, y);
            m_distance--;
            setDirection(d);
            return;
        }
        ran=(ran+1)%4;
        d=Direction(ran+1);
    }
    setDirection(d);
    return;

}

void KleptoBot::action()
{
    if (steal())
        return;
    if (m_distance>0)
    {
        if (moveOneStep())
        {
            m_distance--;
            return;
        }
    }
    ConsiderDirection();
    return;

}

void KleptoBot::doSomething()
{
    if (!isAlive() || !tick())
        return;
    action();
    return;
}

void KleptoBot::attacked()
{
    damage();
    if (getHealth()<=0) {
        setDead();
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(10);
        dropGoodie();
        }
    getWorld()->playSound(SOUND_ROBOT_IMPACT);
}

void KleptoBot::dropGoodie()
{
    if (m_goodie!=nullptr) {
        m_goodie->moveTo(getX(), getY());
        m_goodie->setVisible(true);
        getWorld()->addActor(m_goodie);
    }
}

void AngryKleptoBot::doSomething()
{
    if (!isAlive() || !tick())
        return;
    if (attack())
        return;
    action();
    return;

}

void AngryKleptoBot::attacked()
{
    damage();
    if (getHealth()<=0) {
        setDead();
        getWorld()->playSound(SOUND_ROBOT_DIE);
        getWorld()->increaseScore(20);
        dropGoodie();
    }
    getWorld()->playSound(SOUND_ROBOT_IMPACT);

}

void Actor::getProposedLocation(int& x, int& y, const Direction& dir)
{
    switch (dir) {
        case left:
            x=x-1;
            return ;
        case right:
            x=x+1;
            return ;
        case up:
            y=y+1;
            return ;
        case down:
            y=y-1;
            return ;
        default:
            return ;
    }

}

bool Robot::tick()
{
    if (m_tick==0) {
        m_tick=(28-getWorld()->getLevel())/4;
        if (m_tick < 3)
            m_tick = 3;
        return true;
    }
    else
    {
        m_tick--;
        return false;
    }
}

void Robot::turnAround()
{
    switch (getDirection()) {
        case left:
            setDirection(right);
            break;
        case right:
            setDirection(left);
            break;
        case up:
            setDirection(down);
            break;
        case down:
            setDirection(up);
            break;
        default:
            break;
    }
}