

High Level Description

The class hierarchy is as follows:
Actor
  Agent
    Player
    Boulder
    Robot
      SnarlBot
      KleptoBot
        AngryKletoBot
  Wall
  Hole
  Bullet
  Jewel
  Exit
  ExtraLife
  RestoreHealth
  Ammo
  Factory

The Agent class serves as a base class for some classes with similar features. Though Boulder is normally not considered as an “agent”, it shares some feature with Robot and Player, like it can move and can be hit. Thus I put it in the Agent class. I will introduce the public member functions of these classes one by one, ignoring constructors and destructors, whose purposes are obvious.

Actor:
virtual void doSomething()
The doSomething() function in Actor class does nothing, it serves for objects like Wall and Boulder that actually does nothing by itself. It is virtual so that other class can define their own action.

StudentWorld* getWorld()
It returns the StudentWorld that create the Actor. It is used when an Actor need to access
or inform the StudentWord.

virtual bool block()
Return if the Actor blocks the Player or Robot. By default, it is false. It is virtual to allow some actors to define it true.

bool isAlive()
Return if the Actor is currently alive.

void setDead()
Set the Actor to dead.

virtual bool destroyBullet()
Return if the Actor can destroy a bullet when it is in the same square as a  bullet. By default, it is false. It is virtual to allow some actors to define it true.

virtual bool stealable()
Return if the Actor can be stolen by KleptoBot. By default, it is false. It is virtual to allow some actors to define it true.

Agent:
void restoreHealth()
Restore Agent’s health to 100%. it is only used by Player. It is called  when the Player gets a RestoreHealth goodie.

int getHealth()
Return The Agent’s hit point.

virtual bool destroyBullet()
An agent can destroy a bullet, so return true.

void damage()
Decrement the Agent’s health by 2 points.

virtual bool block()
An agent can block a Player or a Robot, so return true.

virtual void attacked()=0;
Pure virtual function. Allow its subclass to define its own way when attacked by a bullet.


Player:
virtual void doSomething()
Do things as specified during a tick, controlled by keyboard, like move, push, pick up things or fire.

int getAmmunition()
Return the ammunition the Player owns.

void addAmmunition()
Add ammunition by 20. It is called  when the Player gets a Ammo goodie.

void decAmmunition()
Decrement the ammunition by 1 when Player fire a bullet.

virtual void attacked()
React when Player is attacked as specified.

Boulder
bool pushed()
React when a Boulder is pushed by the Player as specified. If it can be pushed, return true, otherwise false.

virtual void attacked()
React when the Boulder is attacked as specified.

Robot
bool attack()
Define the way Robot attack Player. SnarlBot and AngryKleptoBot attack Player in the same way, so it is not virtual. If it successfully fire to the Player, return true, otherwise, return false.

SnarlBot
virtual void doSomething()
Do things as specified during a tick, like walk straightly or turn around or attack the player.

virtual void attacked()
React when the Boulder is attacked as specified.


KleptoBot
virtual void doSomething()
Do things as specified during a tick, including move randomly, pick up goodies, etc.

virtual void attacked()
React when the Boulder is attacked as specified.


AngryKleptoBot
virtual void doSomething()
Do things as specified during a tick, including move randomly, pick up goodies, attack the player, etc.

virtual void attacked()
React when the Boulder is attacked as specified.


Wall
virtual bool block()
A wall can block a Player or a Robot, so return true.

virtual bool destroyBullet()
A wall can destroy a bullet, so return true.


Hole
virtual void doSomething()
Do things as specified during a tick. Swallow a boulder if there is one on the same square.

virtual bool block()
A wall can block a Player or a Robot, so return true.

Bullet
virtual void doSomething()
Do things as specified during a tick, keep moving straightly or hit a target.

Jewel
virtual void doSomething()
Do things as specified during a tick, waiting for player to pick up.

Exit
virtual void doSomething()
Do things as specified during a tick, keep track of the jewel number in the game, reveal itself when needed.

ExtraLife
virtual void doSomething()
Do things as specified during a tick,waiting for player to pick up.

virtual bool stealable()
An ExtraLife goodie can be stollen by a KleptoBot, so return true.

RestoreLife
virtual void doSomething()
Do things as specified during a tick,waiting for player to pick up.

virtual bool stealable()
An RestoreLife goodie can be stollen by a KleptoBot, so return true.

Ammo
virtual void doSomething()
Do things as specified during a tick, waiting for player to pick up.

virtual bool stealable()
An Ammo goodie can be stollen by a KleptoBot, so return true.

Factory
virtual void doSomething()
Do things as specified during a tick, count the KleptoBot number in the specified region and produce KleptoBot by chance.

virtual bool block()
A wall can block a Player or a Robot, so return true.

virtual bool destroyBullet()
A wall can destroy a bullet, so return true.


Tests
By playing the game, I can easily test the classes. There is no need to test the superclasses that do not directly relate to an object in the game, since if the derived class behave correctly, the superclass must be implemented correctly.
Testing the Player, it can walk around the maze properly according to direction keys hit on keyboard. It fires a bullet when hit space. it can pick up items and push boulders. When it is hit by bullet, its health is reduced. When the health is zero. it dies.
The boulder can be pushed to a hole or empty square. When it is hit for 5 times, it dies.
SnarlBot walks either vertically or horizontally, and fires when Player is in its sight. When it is hit for 5 times, it dies.
KleptoBot walks randomly as designed. It might pick up a goodie and drop it when dead. When it is hit for 3 times, it dies.
AngryKleptoBot also walks randomly as designed. It fires when Player is in its sight. It might pick up a goodie and drop it when dead. When it is hit for 4 times, it dies.
The wall stands still. It stops any item including player, robots, boulder and bullets.
The Hole also stands still. It stops player, robots, but bullets can fly through. When a boulder is on it, the hole disappears with the boulder.
A bullet keeps flying after it is created. It can damage player, robots and boulder.
A jewel is still. Player can pick it up.
Exit is invisible until jewels are all picked up.
The ExtraLife, RestoreHealth and Ammo goodie are still. Player can pick it up or let KleptoBot to pick it.
A factory stands still. It stops any item including player, robots, boulder and bullets. It creates KleptoBot as designed.

