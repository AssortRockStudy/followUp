#include <string>
#include "struct.h"
#include <Windows.h>


void SaveUserInfo()
{
	wchar_t szDir[256] = {};
	GetCurrentDirectory(256,szDir);
	wcscat_s(szDir, 256, L"\\UserInfo.txt");

	FILE* pFile = nullptr;
	//파일포인터를 채워줘야하기때문에 파일포인터포인터를 준다
	_wfopen_s(&pFile, szDir, L"wb");

	//저장시킬 유저의 수
	fwrite(&(g_user.iCurCount), 4, 1, pFile);

	for (int i = 0; i < g_user.iCurCount; ++i)
	{
		//[i]는 +i에 *을붙인것 포인터로 전달해야한다
		fwrite(g_user.pData+i, sizeof(User), 1, pFile);
	}

	fclose(pFile);
}

void LoadUserInfo()
{
	wchar_t szDir[256] = {};
	GetCurrentDirectory(256, szDir);
	wcscat_s(szDir, 256, L"\\UserInfo.txt");

	FILE* pFile = nullptr;
	errno_t err=_wfopen_s(&pFile, szDir, L"rb");

	//UserInfo.txt 파일이 존재하지 않는 경우
	//읽기 모드는 파일이 존재하지 않으면 fopen  이 실패한다.
	if (nullptr == pFile)
	{
		err;
		return;
	}
	int iCount = 0;
	fread(&iCount,sizeof(int),1,pFile);

	for(int i=0;i<iCount;++i)
	{
		User user = {};
		fread(&user, sizeof(user), 1, pFile);
		pushData(&g_user, user);
	}
	fclose(pFile);

	


}