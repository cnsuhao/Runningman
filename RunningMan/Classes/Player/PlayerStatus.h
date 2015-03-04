#ifndef __PLAYER_STATUS_H__
#define __PLAYER_STATUS_H__

#include "cocos2d.h"

class Player;

class PlayerStatus
{
public:
	virtual void Enter(Player* pplayer){}
	virtual void Execute(Player* pplayer, float dt){}
	virtual void Exit(Player* pplayer){}
};
//--------------------------------------------------------------
class Player_Run : public PlayerStatus
{
public:
	static Player_Run* Instance();

	void Enter(Player* pplayer);
	void Execute(Player* pplayer, float dt);
	void Exit(Player* pplayer);

private:
	static Player_Run* m_instance;
};
//--------------------------------------------------------------
class Player_Jump : public PlayerStatus
{
private:
	static Player_Jump* m_instance;

public:
    static Player_Jump* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);

    
};
//--------------------------------------------------------------
class Player_JumpDown : public PlayerStatus
{
private:
	static Player_JumpDown* m_instance;

public:
    static Player_JumpDown* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);  
};
//--------------------------------------------------------------
class Player_Fall : public PlayerStatus
{
private:
	static Player_Fall* m_instance;

public:
    static Player_Fall* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);

    
};
//--------------------------------------------------------------
class Player_Retreat : public PlayerStatus
{
private:
	static Player_Retreat* m_instance;

public:
    static Player_Retreat* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);

    
};
//--------------------------------------------------------------
class Player_Electric : public PlayerStatus
{
private:
	static Player_Electric* m_instance;

public:
    static Player_Electric* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);

    
};
//--------------------------------------------------------------
class Player_SpeedMax : public PlayerStatus
{
private:
	static Player_SpeedMax* m_instance;

public:
    static Player_SpeedMax* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);    
};
//--------------------------------------------------------------
class Player_Anger : public PlayerStatus
{
private:
	static Player_Anger* m_instance;

public:
    static Player_Anger* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);    
};
//--------------------------------------------------------------
class Player_Rush : public PlayerStatus
{
private:
	static Player_Rush* m_instance;

public:
    static Player_Rush* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);    
};
//--------------------------------------------------------------
class Player_Win : public PlayerStatus
{
private:
	static Player_Win* m_instance;

public:
    static Player_Win* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);    
};
//--------------------------------------------------------------
class Player_Lose : public PlayerStatus
{
private:
	static Player_Lose* m_instance;

public:
    static Player_Lose* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);    
};
//--------------------------------------------------------------
class Player_Stop : public PlayerStatus
{
private:
	static Player_Stop* m_instance;

public:
    static Player_Stop* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);    
};
//--------------------------------------------------------------
class Player_Fly : public PlayerStatus
{
private:
	static Player_Fly* m_instance;

public:
    static Player_Fly* Instance();

    void Enter(Player* pplayer);

    void Execute(Player* pplayer, float dt);

    void Exit(Player* pplayer);    
};
//--------------------------------------------------------------
//--------------------------------------------------------------

#endif //__PLAYER_STATUS_H__