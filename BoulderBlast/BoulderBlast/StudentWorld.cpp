#include "StudentWorld.h"
#include <string>
#include "Level.h"
#include "GameConstants.h"
#include "Actor.h"
#include <sstream>
#include <iomanip>
GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
StudentWorld::~StudentWorld()
{
    list<Actor*>::iterator it;
    for (it=m_actor.begin(); it!=m_actor.end(); it++) {
        delete *it;
        m_actor.erase(it);
    }

}

 int StudentWorld::init()
{
    jewelNum=0;
    levelComplete=false;
    bonus=1000;
    int result=LoadALevel();
    if (result==-1 || getLevel()>=100)
        return GWSTATUS_PLAYER_WON;
    if (result==0)
        return GWSTATUS_CONTINUE_GAME;
    
    return GWSTATUS_LEVEL_ERROR;
    

}

int StudentWorld::move()
{
    setText();
    
    list<Actor*>::iterator it;
    for (it=m_actor.begin(); it!=m_actor.end(); it++) {
        (*it)->doSomething();
    }
    
    for (it=m_actor.begin(); it!=m_actor.end(); it++) {
        if ((*it)->isAlive()==false) {
            delete *it;
            m_actor.erase(it);
        }
    }
    
    if (bonus>0)
        bonus--;
    
    if (m_player->isAlive()==false)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }

    if (levelComplete)
    {
        increaseScore(bonus);
        return GWSTATUS_FINISHED_LEVEL;

    }
    
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it;
    for (it=m_actor.begin(); it!=m_actor.end(); it++) {
        delete *it;
        m_actor.erase(it);
    }
}


int StudentWorld::LoadALevel()
{
    char level=getLevel()+'0';
    string curLevel="level0";
    curLevel+=level;
    curLevel+=".dat";
    Level lev(assetDirectory());
    Level::LoadResult result=lev.loadLevel(curLevel);
    if (result == Level::load_fail_file_not_found)
        return -1;
    if (result == Level:: load_fail_bad_format)
        return -2;
    Actor* p;
    for (int x=0; x<VIEW_WIDTH; x++) {
        for (int y=0; y<VIEW_HEIGHT; y++) {
            Level::MazeEntry item=lev.getContentsOf(x, y);
            switch (item) {
                case Level::player:
                    //cout << "The player should be placed at "<< x<<", "<<y<<" in the maze\n";
                    m_player=new Player(IID_PLAYER,x,y,this);
                    m_player->setVisible(true);
                    m_actor.push_back(m_player);
                    break;
                case Level::wall:
                    //cout << "There should be a wall at "<<x<<", "<<y<<" in the maze\n";
                    p=new Wall(IID_WALL,x,y,this);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::boulder:
                    p=new Boulder(IID_BOULDER,x,y,this);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::hole:
                    p=new Hole(IID_HOLE,x,y,this);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::jewel:
                    p=new Jewel(IID_JEWEL,x,y,this);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    jewelNum++;
                    break;
                case Level::exit:
                    p=new Exit(IID_EXIT,x,y,this);
                    p->setVisible(false);
                    m_actor.push_back(p);
                    break;
                case Level::extra_life:
                    p=new ExtraLife(IID_EXTRA_LIFE,x,y,this);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::restore_health:
                    p=new RestoreHealth(IID_RESTORE_HEALTH,x,y,this);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::ammo:
                    p=new Ammo(IID_AMMO,x,y,this);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::horiz_snarlbot:
                    p=new SnarlBot(IID_SNARLBOT,x,y,this,Actor::right);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::vert_snarlbot:
                    p=new SnarlBot(IID_SNARLBOT,x,y,this,Actor::down);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::angry_kleptobot_factory:
                    p=new Factory(IID_ROBOT_FACTORY, x, y, this, true);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                case Level::kleptobot_factory:
                    p=new Factory(IID_ROBOT_FACTORY, x, y, this, false);
                    p->setVisible(true);
                    m_actor.push_back(p);
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
    
}

Actor* StudentWorld::getAnActor(int x, int y, Actor* self)
{
    list<Actor*>::iterator it;
    Actor* result=nullptr;
    for (it=m_actor.begin(); it!=m_actor.end(); it++)
    {
        if ((*it)->getX()==x && (*it)->getY()==y && *it!=self)
        {
            Agent* ap = dynamic_cast<Agent*>(*it);
            if (ap!=nullptr) {
                return *it;
            }
            else if ((*it)->stealable())
                result=*it;
            result=*it;
        }
        
    }
    return result;

}

void StudentWorld::setText()
{
    int score=getScore();
    int level=getLevel();
    int lives=getLives();
    int health=m_player->getHealth();
    health=health*5;
    int ammo=m_player->getAmmunition();
    ostringstream oss;
    oss.fill('0');
    oss<<"Score: "<<setw(7)<<score<<"  ";
    oss<<"Level: "<<setw(2)<<level<<"  ";
    oss.fill(' ');
    oss<<"Lives: "<<setw(2)<<lives<<"  ";
    oss<<"Health: "<<setw(3)<<health<<"%  ";
    oss<<"Ammo: "<<setw(3)<<ammo<<"  ";
    oss<<"Bonus: "<<setw(4)<<bonus;
    string s=oss.str();
    setGameStatText(s);
}

void StudentWorld::deleteActor(Actor* p)
{
    list<Actor*>::iterator it;
    for (it=m_actor.begin(); it!=m_actor.end(); it++) {
        if (*it==p)
            m_actor.erase(it);
    }

}