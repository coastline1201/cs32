#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <list>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class Actor;
class Player;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir),jewelNum(0),levelComplete(false),bonus(1000)
	{
	}
    ~StudentWorld();
    
    virtual int init();
	

    virtual int move();
	

    virtual void cleanUp();
    
    Actor* getAnActor(int x,int y, Actor* self);
    
    int getJewel()
    {
        return jewelNum;
    }
    
    void decJewel()
    {
        jewelNum--;
    }
    
    
    void setLevelComplete()
    {
        levelComplete=true;
    }
    
    void addActor(Actor* p)
    {
        m_actor.push_back(p);
    }
    void addBullet(Actor *p)
    {
        m_actor.push_front(p);
    }
    void deleteActor(Actor* p);
    

private:
    list <Actor*> m_actor;
    Player* m_player;
    int jewelNum;
    bool levelComplete;
    int bonus;
    
    int LoadALevel();
    void setText();

};

#endif // STUDENTWORLD_H_
