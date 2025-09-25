#include "pch.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CResMgr.h"
#include "CPathMgr.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		++m_iCurFrm;

		if (m_vecFrm.size() <= m_iCurFrm)
		{
			m_iCurFrm = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos += m_vecFrm[m_iCurFrm].vOffset;

	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc // 출력할 DC
		, (int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f) // 출력할쪽의 좌상단 x 위치
		, (int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f) // 출력할쪽의 좌상단 y 위치
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x) // 가로 길이
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y) // 세로 길이
		, m_pTex->GetDC() // 붙여넣을 원본 DC
		, (int)(m_vecFrm[m_iCurFrm].vLT.x) // 붙여넣을 원본 DC의 좌상단 x 위치
		, (int)(m_vecFrm[m_iCurFrm].vLT.y) // 붙여넣을 원본 DC의 좌상단 y 위치
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x) // 가로 길이
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y) // 세로 길이
		, RGB(255, 0, 255) // 무시할 색상 :: 마젠타
	);
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize
	, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * (float)i;

		m_vecFrm.push_back(frm);
	}
}

void CAnimation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	// Animation 의 이름을 저장한다. (데이터 직렬화)
	SaveWString(m_strName, pFile);

	// Animation이 사용할 텍스쳐
	SaveWString(m_pTex->GetKey(), pFile);
	SaveWString(m_pTex->GetRelativePath(), pFile);

	// 프레임 개수
	size_t iFrameCount = m_vecFrm.size();
	fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	// 모든 프레임 정보
	fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);

	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// Animation 이름 읽기
	LoadWString(m_strName, pFile);

	// 텍스쳐
	wstring strTexKey, strTexPath;
	LoadWString(strTexKey, pFile);
	LoadWString(strTexPath, pFile);
	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);

	// 프레임 개수
	size_t iFrameCount = 0;
	fread(&iFrameCount, sizeof(size_t), 1, pFile);

	// 모든 프레임 정보
	m_vecFrm.resize(iFrameCount);
	fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);

	fclose(pFile);
}