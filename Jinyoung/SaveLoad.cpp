#include <string>
#include "struct.h"
#include <Windows.h>


void SaveUserInfo()
{
	wchar_t szDir[256] = {};
	GetCurrentDirectory(256,szDir);
	wcscat_s(szDir, 256, L"\\UserInfo.txt");

	FILE* pFile = nullptr;
	//���������͸� ä������ϱ⶧���� ���������������͸� �ش�
	_wfopen_s(&pFile, szDir, L"wb");

	//�����ų ������ ��
	fwrite(&(g_user.iCurCount), 4, 1, pFile);

	for (int i = 0; i < g_user.iCurCount; ++i)
	{
		//[i]�� +i�� *�����ΰ� �����ͷ� �����ؾ��Ѵ�
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

	//UserInfo.txt ������ �������� �ʴ� ���
	//�б� ���� ������ �������� ������ fopen  �� �����Ѵ�.
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