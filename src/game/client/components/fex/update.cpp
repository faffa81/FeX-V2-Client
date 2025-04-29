#include <game/client/gameclient.h>
#include <game/client/components/fex/fexversion.h>

#include <engine/shared/json.h>

#include "update.h"
#include <string.h>
#include <tuple>

// Stole Taters Update Stuff
static constexpr const char *FXCLIENT_VER_URL = "https://faffa81.github.io/faffaSite/version.json";

void CUpdate::OnInit()
{
	FetchFXClientInfo();
}

void CUpdate::OnRender()
{
	if(m_pFXClientVerTask)
	{
		if(m_pFXClientVerTask->State() == EHttpState::DONE)
		{
			FinishFXClientInfo();
			ResetFXClientInfoTask();
		}
	}
}
void CUpdate::ResetFXClientInfoTask()
{
	if(m_pFXClientVerTask)
	{
		m_pFXClientVerTask->Abort();
		m_pFXClientVerTask = NULL;
	}
}

void CUpdate::FetchFXClientInfo()
{
	if(m_pFXClientVerTask && !m_pFXClientVerTask->Done())
		return;
	char aUrl[256];
	str_copy(aUrl, FXCLIENT_VER_URL);
	m_pFXClientVerTask = HttpGet(aUrl);
	m_pFXClientVerTask->Timeout(CTimeout{10000, 0, 500, 10});
	m_pFXClientVerTask->IpResolve(IPRESOLVE::V4);
	Http()->Run(m_pFXClientVerTask);
}

typedef std::tuple<int, int, int> FXVersion;
static const FXVersion gs_InvalidFXVersion = std::make_tuple(-1, -1, -1);

FXVersion ToFXVersion(char *pStr)
{
	int aVersion[3] = {0, 0, 0};
	const char *p = strtok(pStr, ".");

	for(int i = 0; i < 3 && p; ++i)
	{
		if(!str_isallnum(p))
			return gs_InvalidFXVersion;

		aVersion[i] = str_toint(p);
		p = strtok(NULL, ".");
	}

	if(p)
		return gs_InvalidFXVersion;

	return std::make_tuple(aVersion[0], aVersion[1], aVersion[2]);
}

void CUpdate::FinishFXClientInfo()
{
	json_value *pJson = m_pFXClientVerTask->ResultJson();
	if(!pJson)
		return;
	const json_value &Json = *pJson;
	const json_value &CurrentVersion = Json["version"];

	if(CurrentVersion.type == json_string)
	{
		char aNewVersionStr[64];
		str_copy(aNewVersionStr, CurrentVersion);
		char aCurVersionStr[64];
		str_copy(aCurVersionStr, FEX_RELEASE_VERSION);
		if(ToFXVersion(aNewVersionStr) > ToFXVersion(aCurVersionStr))
		{
			str_copy(m_aVersionStr, CurrentVersion);
		}
		else
		{
			m_aVersionStr[0] = '0';
			m_aVersionStr[1] = '\0';
		}
	}

	json_value_free(pJson);
}