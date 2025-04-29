#ifndef GAME_CLIENT_COMPONENTS_FEX_UPDATE_H
#define GAME_CLIENT_COMPONENTS_FEX_UPDATE_H
#include <game/client/component.h>
#include <engine/shared/http.h>
#include <memory>
#include <cstdint>

class CUpdate : public CComponent
{
public:
	std::shared_ptr<CHttpRequest> m_pFXClientVerTask = nullptr;
	void FetchFXClientInfo();
	void FinishFXClientInfo();
	void ResetFXClientInfoTask();

	char m_aVersionStr[10] = "0";
	virtual int Sizeof() const override { return sizeof(*this); }
	virtual void OnInit() override;
	virtual void OnRender() override;
};

#endif