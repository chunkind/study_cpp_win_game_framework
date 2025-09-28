#pragma once

class CCore
{
public:
	// 정적변수로 싱글톤을 만들면 내가 해제를 신경쓰지 않아도 된다.
	// 프로그램 꺼질때 자동 해제된다.
	// 반대로 해제 되지 않아서 메모리에서 지울수가 없다.
	static CCore* GetInst()
	{
		static CCore core; // 데이터 영역에 core를 만든거다.
		return &core; // core라는 정적 변수는 해당 메서드에서만 접근 가능해도 데이터 영역에주소값은 접근 가능하다.
	}

private:
	CCore();
	~CCore();
};