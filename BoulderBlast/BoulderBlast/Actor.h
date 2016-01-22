#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor:public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :GraphObject(imageID, startX, startY, dir),m_world(World),m_alive(true)
    {}
    virtual ~Actor(){}
    virtual void doSomething()
    {
        return;
    }
    StudentWorld* getWorld()
    {
        return m_world;
    }
    virtual bool block()
    {
        return false;
    }
    
    bool isAlive()
    {
        return m_alive;
    }
    
    void setDead()
    {
        m_alive=false;
    }
    
    
    virtual bool destroyBullet()
    {
        return 0;
    }
    virtual bool stealable()
    {
        return false;
    }
    
protected:
    void getProposedLocation(int& x, int& y, const Direction& dir);
private:
    StudentWorld* m_world;
    bool m_alive;

};

class Agent:public Actor
{
public:
    Agent(int imageID, int startX, int startY, StudentWorld* World, Direction dir,int health)
    :Actor(imageID, startX, startY, World, dir),m_health(health)
    {}
    virtual ~Agent(){}
    void restoreHealth()
    {
        m_health=20;
    }
    int getHealth()
    {
        return m_health;
    }
    virtual bool destroyBullet()
    {
        return true;
    }
    void damage()
    {
        m_health-=2;
    }
    bool block()
    {
        return true;
    }
    virtual void attacked()=0;
protected:
    void fire();

private:
    int m_health;
};

class Player:public Agent
{
public:
    Player(int imageID, int startX, int startY, StudentWorld* World, Direction dir = right)
    :Agent(imageID, startX, startY, World, dir,20),m_ammunition(20)
    {}
    ~Player(){}
    virtual void doSomething();
    int getAmmunition()
    {
        return m_ammunition;
    }
    void addAmmunition()
    {
        m_ammunition+=20;
    }
    void decAmmunition()
    {
        m_ammunition--;
    }
    virtual void attacked();
private:
    int m_ammunition;

};

class Wall:public Actor
{
public:
    Wall(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :Actor(imageID, startX, startY, World, dir)
    {}
    bool block()
    {
        return true;
    }
    virtual bool destroyBullet()
    {
        return 1;
    }

};

class Boulder: public Agent
{
public:
    Boulder(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :Agent(imageID, startX, startY, World, dir,10)
    {}
    bool pushed(Direction dir);
    
    virtual void attacked();

    private:

};

class Hole:public Actor
{
public:
    Hole(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :Actor(imageID, startX, startY, World, dir)
    {}
    virtual void doSomething();
    bool block()
    {
        return true;
    }
};

class Bullet:public Actor
{
public:
    Bullet(int imageID, int startX, int startY, StudentWorld* World, Direction dir)
    :Actor(imageID, startX, startY, World, dir)
    {}
    virtual void doSomething();
    
};

class Jewel:public Actor
{
public:
    Jewel(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :Actor(imageID, startX, startY, World, dir)
    {}
    
    virtual void doSomething();
    
};

class Exit:public Actor
{
public:
    Exit(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :Actor(imageID, startX, startY, World, dir)
    {}
    virtual void doSomething();
};

class ExtraLife:public Actor
{
public:

    ExtraLife(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :Actor(imageID, startX, startY, World, dir)
    {}
    virtual void doSomething();
        virtual bool stealable()
    {
        return true;
    }


};

class RestoreHealth:public Actor
{
public:

    RestoreHealth(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :Actor(imageID, startX, startY, World, dir)
    {}
    virtual void doSomething();
        virtual bool stealable()
    {
        return true;
    }
    
};

class Ammo:public Actor
{
public:
    Ammo(int imageID, int startX, int startY, StudentWorld* World, Direction dir = none)
    :Actor(imageID, startX, startY, World, dir)
    {}
    virtual void doSomething();
        virtual bool stealable()
    {
        return true;
    }
    
};

class Robot:public Agent
{
public:
    Robot(int imageID, int startX, int startY, StudentWorld* World, Direction dir, int health);
    virtual ~Robot(){}
    bool attack();
protected:
    bool moveOneStep();
    bool tick();
    void turnAround();
   private:
    int m_tick;
    
    
};

class SnarlBot: public Robot
{
public:
    SnarlBot(int imageID, int startX, int startY, StudentWorld* World, Direction dir)
    :Robot(imageID, startX, startY, World, dir, 10)
    {}
    virtual void doSomething();
    virtual void attacked();

};

class Factory:public Actor
{
public:
    
    Factory(int imageID, int startX, int startY, StudentWorld* World, bool angry, Direction dir = none)
    :Actor(imageID, startX, startY, World, dir),m_angry(angry)
    {}
    virtual void doSomething();
    bool block()
    {
        return true;
    }
    virtual bool destroyBullet()
    {
        return 1;
    }
private:
    bool m_angry;

};

class KleptoBot : public Robot
{
public:
    KleptoBot(int imageID, int startX, int startY, StudentWorld* World, Direction dir=right, int health=5);
    virtual void attacked();

    virtual void doSomething();
protected:
    bool steal();
    void dropGoodie();
    void ConsiderDirection();
    void action();
private:
    int m_distance;
    Actor* m_goodie;

};

class AngryKleptoBot : public KleptoBot
{
public:
    AngryKleptoBot(int imageID, int startX,int startY,StudentWorld* World, Direction dir=right,int health=8)
    :KleptoBot(imageID, startX, startY, World, dir, 8)
    {}
    virtual void doSomething();
    virtual void attacked();

    
};


#endif // ACTOR_H_
