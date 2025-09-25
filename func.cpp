#include "pch.h"
#include "func.h"
#include "CEventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeAIState(AI* _pAI, MON_STATE _eNextState)
{
	tEvent evn = { };
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)_pAI;
	evn.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GetInst()->AddEvent(evn);
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	// Animation 의 이름을 저장한다.
	// 아래처럼 하면 5글자 미만은 출력되도 그 이상은 힙메모리에 저장되서 주소값이 출력된다.
	//fwrite(&_str, sizeof(wstring), 1, _pFile); // wstring은 백터와 비슷해서 동적으로 크기 변경이 된다.
	// 데이터 직렬화: 주소가 가르치는 데이터를 가서 일렬로 정렬한다.
	const wchar_t* pStrName = _str.c_str(); // 주소
	size_t iLen = _str.length(); // 길이

	// 문자 길이 저장
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	// 문자열 저장
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);
	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	_str = szBuff;
}
