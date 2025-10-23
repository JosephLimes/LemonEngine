#ifndef _LevelTracker
#define _LevelTracker

class PlayerTank;

class LevelTracker
{
private:
	LevelTracker();
	LevelTracker(const LevelTracker&) = delete;
	LevelTracker operator = (const LevelTracker&) = delete;
	~LevelTracker() = default;

	static LevelTracker*	m_pInstance;
	static LevelTracker&	Instance();

private:
	PlayerTank*				m_pPlayer;
	int						m_numEnemies;
	bool					m_onBossLevel;

public:
	static void				Terminate();
	static void				Initialize(PlayerTank* pPlayer, bool onBossLevel) { Instance().privInitialize(pPlayer, onBossLevel); };

	static PlayerTank*		GetPlayer() { return Instance().privGetPlayer(); };
	static void				SetPlayer(PlayerTank* pPlayer) { Instance().privSetPlayer(pPlayer); };
	static void				EnemyDestroyed() { Instance().privEnemyDestroyed(); };
	static void				BossDestroyed() { Instance().privBossDestroyed(); };
	static void				TransitionLevel() { Instance().privTransitionLevel(); };

private:
	void					privInitialize(PlayerTank* pPlayer, bool onBossLevel);
	PlayerTank*				privGetPlayer();
	void					privSetPlayer(PlayerTank* pPlayer);
	void					privEnemyDestroyed();
	void					privBossDestroyed();
	void					privTransitionLevel();
};

#endif _LevelTracker