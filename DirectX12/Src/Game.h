#pragma once

/// <summary>
/// メイン関数で作成される全システムの核となるクラス
/// </summary>
class cGameSystem
{
public:
	cGameSystem();
	~cGameSystem();

	void Init();
	void RunLoop();
	void UnInit();
	
private:
	void SystemInit();
	void AppInit();

	void AppUnInit();
	void SystemUnInit();
};