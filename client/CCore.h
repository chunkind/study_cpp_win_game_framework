#pragma once

class CCore
{
public:
	static CCore* GetInst()
	{
		static CCore core;
		return &core;
	}

private:
	CCore();
	~CCore();
};