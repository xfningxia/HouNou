
#include "DirectX.h"

//�����ĸ�GUI����󣬷ֱ�����ĸ�ҳ��
D3DGUIClass		*g_MainGUI = NULL;//������
D3DGUIClass		*g_StartGUI = NULL; //��Ϸ��ʼ����
D3DGUIClass		*g_LoadGUI = NULL; //��Ϸ���봰��
D3DGUIClass		*g_OptionGUI = NULL; //��Ϸ���ô���

int						g_MainGUIFontID = -1;						//  GUI����������ID
int						g_StartGUIFontID = -1;						//  GUI����������ID
int						g_LoadGUIFontID = -1;						//  GUI����������ID
int						g_OptionGUIFontID = -1;						//  GUI����������ID
int						g_currentGUI = GUI_MAIN_SCREEN;				//һ����ǰ��GUI��ʶ

bool GUI_Init()
{
	//--------------------------------------------------��GUIϵͳ��ش��롿-------------------------------------------------------

	// ����һЩGUIϵͳ
	g_MainGUI = new D3DGUIClass(g_pd3dDevice, WINDOW_WIDTH, WINDOW_HEIGHT); //���˵�ҳ��
	g_StartGUI = new D3DGUIClass(g_pd3dDevice, WINDOW_WIDTH, WINDOW_HEIGHT); //��ʼ����Ϸҳ��
	g_LoadGUI = new D3DGUIClass(g_pd3dDevice, WINDOW_WIDTH, WINDOW_HEIGHT); //������Ϸҳ��
	g_OptionGUI = new D3DGUIClass(g_pd3dDevice, WINDOW_WIDTH, WINDOW_HEIGHT); //����ҳ��

																			  // ���ĸ�ҳ��ֱ����ӱ���ͼ
	if (!g_MainGUI->AddBackground(L"GameMedia/maingui.jpg")) return false;
	if (!g_StartGUI->AddBackground(L"GameMedia/startgui.jpg")) return false;
	if (!g_LoadGUI->AddBackground(L"GameMedia/loadgui.jpg")) return false;
	if (!g_OptionGUI->AddBackground(L"GameMedia/optiongui.jpg")) return false;


	// �ֱ���ĸ�ҳ����������
	if (!g_MainGUI->CreateTextFont(L"΢���ź�", 28, &g_MainGUIFontID)) return false;
	if (!g_StartGUI->CreateTextFont(L"΢���ź�", 38, &g_StartGUIFontID)) return false;
	if (!g_LoadGUI->CreateTextFont(L"΢���ź�", 38, &g_LoadGUIFontID)) return false;
	if (!g_OptionGUI->CreateTextFont(L"΢���ź�", 38, &g_OptionGUIFontID)) return false;




	//---------------------------------�����˵�mainҳ����ص�ҳ�沼�ִ��롿---------------------------------
	// ���Ӿ�̬�ı���ҳ����
	if (!g_MainGUI->AddStaticText(STATIC_TEXT_ID, L"Version 0.1",
		1170, 735, D3DCOLOR_XRGB(55, 155, 255), g_MainGUIFontID)) return false;

	if (!g_MainGUI->AddStaticText(STATIC_TEXT_ID, L"�Ǻ�",
		500, 150, D3DCOLOR_XRGB(255, 255, 255), g_MainGUIFontID)) return false;


	// ����4����ť���ֱ��ǿ�ʼ��Ϸ��������ȣ�ѡ����˳���Ϸ��ÿ����ť��Ӧ3��ͼ
	if (!g_MainGUI->AddButton(BUTTON_START_ID, 650, 340, L"GameMedia\\startUp.png",
		L"GameMedia\\StartOver.png", L"GameMedia\\startDown.png")) return false;

	if (!g_MainGUI->AddButton(BUTTON_LOAD_ID, 650, 385, L"GameMedia\\loadUp.png",
		L"GameMedia\\loadOver.png", L"GameMedia\\loadDown.png")) return false;

	if (!g_MainGUI->AddButton(BUTTON_OPTION_ID, 650, 430, L"GameMedia\\optionsUp.png",
		L"GameMedia\\optionsOver.png", L"GameMedia\\optionsDown.png")) return false;

	if (!g_MainGUI->AddButton(BUTTON_QUIT_ID, 650, 475, L"GameMedia\\quitUp.png",
		L"GameMedia\\quitOver.png", L"GameMedia\\quitDown.png")) return false;


	//------------------------����ʼ����Ϸstartҳ����ص�ҳ�沼�ִ��롿------------------------
	// ���Ӱ�ť��ҳ����
	if (!g_StartGUI->AddButton(BUTTON_LEVEL_1_ID, 550, 380, L"GameMedia/level1Up.png", L"GameMedia/level1Over.png",
		L"GameMedia/level1Down.png")) return false;

	if (!g_StartGUI->AddButton(BUTTON_BACK_ID, 750, 350, L"GameMedia/backUp.png", L"GameMedia/backOver.png",
		L"GameMedia/backDown.png")) return false;


	//------------------------��������Ϸloadҳ����ص�ҳ�沼�ִ��롿------------------------
	//���Ӿ�̬�ı���ҳ����
	if (!g_LoadGUI->AddStaticText(STATIC_TEXT_ID, L"������load gameҳ��",
		411, 340, D3DCOLOR_XRGB(33, 255, 55), g_LoadGUIFontID)) return false;
	// ���Ӱ�ť��ҳ����
	if (!g_LoadGUI->AddButton(BUTTON_BACK_ID, 750, 400, L"GameMedia/backUp.png", L"GameMedia/backOver.png",
		L"GameMedia/backDown.png")) return false;


	//------------------------����Ϸ����optionҳ����ص�ҳ�沼�ִ��롿------------------------
	// ���Ӱ�ť��ҳ����
	if (!g_OptionGUI->AddButton(BUTTON_BACK_ID, 750, 450, L"GameMedia/backUp.png", L"GameMedia/backOver.png",
		L"GameMedia/backDown.png")) return false;
	//���Ӿ�̬�ı���ҳ����
	if (!g_OptionGUI->AddStaticText(STATIC_TEXT_ID, L"������Optionҳ��",
		540, 60, D3DCOLOR_XRGB(33, 55, 255), g_OptionGUIFontID)) return false;
}


//-----------------------------------��GUICallback( )������---------------------------------------
//	������GUIϵͳ�Ļص���������д��ť���º����ش�������
//--------------------------------------------------------------------------------------------------
void GUICallback(int id, int state)
{
	switch (id)
	{
	case BUTTON_START_ID:   //start game��ʼ��Ϸ��ť
		if (state == UGP_BUTTON_DOWN)
			g_currentGUI = GUI_START_SCREEN;
		break;

	case BUTTON_LOAD_ID:  //load game������Ϸ��ť
		if (state == UGP_BUTTON_DOWN)
			g_currentGUI = GUI_LOAD_SCREEN;
		break;

	case BUTTON_OPTION_ID: //option���ð�ť
		if (state == UGP_BUTTON_DOWN)
			g_currentGUI = GUI_OPTION_SCREEN;
		break;

	case BUTTON_BACK_ID: //back���ذ�ť
		if (state == UGP_BUTTON_DOWN)
			g_currentGUI = GUI_MAIN_SCREEN;
		break;

	case BUTTON_QUIT_ID://quit�˳���ť
		if (state == UGP_BUTTON_DOWN)
			PostQuitMessage(0);
		break;

	case BUTTON_LEVEL_1_ID:  //start game��ʼ��Ϸҳ���У�Level1��ť
							 //�ȼ�һ����Ϸ�����￪ʼд����
		break;
	}
}

void GUI_CleanUp()
{
	SAFE_DELETE(g_MainGUI);
	SAFE_DELETE(g_StartGUI);
	SAFE_DELETE(g_LoadGUI);
	SAFE_DELETE(g_OptionGUI);
}