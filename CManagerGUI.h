#ifndef _CMANAGER_GUI_H_
#define _CMANAGER_GUI_H_

#include "DXData.h"
#include "font.h"
#include <vector>

using namespace std;



#define  D3DFVF_GUI (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
struct stVertexGUI
{
	D3DXVECTOR3 vectorPos;
	DWORD color;
	float tu, tv;
};

// -------------- ��� �������� ---------
#define TYPE_SELECTION_COLOR_FONT 1
#define TYPE_SELECTION_SIZE_FONT  2
#define TYPE_SELECTION_FRAME      3

;
// ====================== structures (begin) ==================================================
enum enTypeElemGui {NOT_ELEM = -1, BUTTON, CHECK_BOX, STATIC_TEXT, IMAGE_BOX, MOUSE, GROUP, HSCROLL_BAR, VSCROLL_BAR, WINDOW_PANEL}; // ������������ ���� ����� ���������
enum enTypeWindowFill {FILL_NO = 0, FILL_REPEAT, FILL_SCALE}; /* ��� �������� ����������� ���� ������� 
															  ������������ (�� ��������, �������� � ��������, ��������������� ��� ������� ����)*/
enum enElemGuiState {ELEM_STATE_NOT = 0, ELEM_STATE_NORMAL, ELEM_STATE_SELECTED, ELEM_STATE_ON, ELEM_STATE_OFF}; // � ����� ��������� ��������� ������ ���� ������ ��� ����

struct stMouseInfoGUI
{
	stMouseInfoGUI()
	{
		//bDownLB = false;
		bLButtonClick = false;
		bLButtonDown = false;
	}
	POINT pointMousePos;  // ������� ����

	//bool bDownLB;
	bool bLButtonClick; // ��� �� ���� ����� ��������
	bool bLButtonDown; // ����� ������� ������
	POINT pointLBDownPos;   // ��� ���� ������ ����� �������
	POINT pointLBUpPos;	 // ��� ���� �������� ����� �������
};

struct stButton
{
	stButton()
	{
		textureButton = NULL;
		textureSelectionButton = NULL;
		pTextureRender = NULL;

		bEnable = true;
		bVisible = true;
		bSelectEnable = true;
		
		vectorScale = D3DXVECTOR2(1.0f, 1.0f);
		enState = ELEM_STATE_NOT;
	};

	LPDIRECT3DTEXTURE9 *pTextureRender; // ����� �������� ������� ���������� �������
	LPDIRECT3DTEXTURE9 textureButton; // ������� �������� ������
	LPDIRECT3DTEXTURE9 textureSelectionButton; // ������� �������� ������ � ��������� ����������

	char *pcButtonName; // ��� ������
	D3DXVECTOR2 vectorTrans;
	D3DXVECTOR2 vectorScale;
	RECT rectButton; // ������������� � ������� ��������� ������, �������� ��� ������� ������
	RECT rectForWindowMouse; // ��� ������� ������ � ����
	int iIDWindow; // ������ ���� �������� ����������� ������

	bool bSelectEnable; // ��������� ���������
	bool bEnable;   // �����������
	bool bVisible;  // ���������
	enElemGuiState enState;

	void (*pFuncExecute)(); // ��������� �� ������� ������� ���������� ��� �������
};

struct stCheckBox
{
	stCheckBox()
	{
		textureCheckBoxOFF = NULL;
		textureCheckBoxON = NULL;
		pTextureRender = NULL;

		bCheckBoxState = false;
		enState = ELEM_STATE_OFF;
		bEnable = true;
		bVisible = true;
		bRunFunc = true;
	};

	LPDIRECT3DTEXTURE9 *pTextureRender; // ����� �������� ������� ���������� �������
	LPDIRECT3DTEXTURE9 textureCheckBoxOFF; // ������� �������� checkBox = false
	LPDIRECT3DTEXTURE9 textureCheckBoxON; // ������� �������� checkBox = true

	char *pcCheckBoxName; // ��� checkBox
	D3DXVECTOR2 vectorTrans;
	RECT rectCheckBox; // ������������� � ������� �������� checkBox, �������� ��� ������� ������
	RECT rectForWindowMouse; // ��� ������� ������ � ����
	int iIDWindow; // ������ ���� �������� ����������� checkBox
	enElemGuiState enState;

	bool bCheckBoxState; // ������ ��������� � ������� ��������� (ON, OFF)
	bool bEnable;   // �����������
	bool bVisible;  // ���������
	bool bRunFunc; // ��������� ������� �� ����������

	void (*pFuncExecute)(bool bCheckBoxOn); // ��������� �� ������� ������� ���������� ��� �������, � bCheckBoxOn ������� ��������� ���������
};

struct stRadioButton
{
	stRadioButton()
	{
		textureRadioButtonOFF = NULL;
		textureRadioButtonON = NULL;
		pTextureRender = NULL;

		bRadioButtonState = false;
		enState = ELEM_STATE_OFF;
		bEnable = true;
		bVisible = true;

		vectorScale = D3DXVECTOR2(1.0f, 1.0f);
	};

	LPDIRECT3DTEXTURE9 *pTextureRender; // ����� �������� ������� ���������� �������
	LPDIRECT3DTEXTURE9 textureRadioButtonOFF; // ������� �������� checkBox = false
	LPDIRECT3DTEXTURE9 textureRadioButtonON; // ������� �������� checkBox = true

	char *pcRadioButtonName; // ��� RadioButton
	D3DXVECTOR2 vectorTrans;
	D3DXVECTOR2 vectorScale;
	RECT rectRadioButton; // ������������� � ������� �������� RadioButton, �������� ��� ������� ������
	RECT rectForWindowMouse; // ��� ������� ������ � ����
	int iIDWindow; // ������ ���� �������� ����������� RadioButton

	enElemGuiState enState;
	bool bRadioButtonState; // ������ ��������� � ������� ��������� (ON, OFF)
	bool bEnable;   // �����������
	bool bVisible;  // ���������

	void (*pFuncExecute)(bool bRadioButtonState); // ��������� �� ������� ������� ���������� ��� �������, � bRadioButtonState ������� ��������� ���������
};

struct stGroup
{
	stGroup()
	{
		m_iQuantRadioButton = 0;
		iCurIndexRadioButton = 0;
		bRunRadioButtonFunc = true;
	};

	int m_iQuantRadioButton;
	bool bRunRadioButtonFunc; // ��������� ������� RadioButton �� ����������
	vector<stRadioButton> m_stRadioButton;
	int iCurIndexRadioButton;   // ����� ���������� ������ ��������� false
};

struct stStaticText
{
	stStaticText()
	{
		textureStaticText = NULL;
		//pTextureRender = NULL;
		bVisible = true;
	};

	//LPDIRECT3DTEXTURE9 *pTextureRender; // ����� �������� ������� ���������� �������
	LPDIRECT3DTEXTURE9 textureStaticText; // ������� �������� StaticText
	
	char *text;
	D3DXVECTOR2 vectorTrans;
	int iIDWindow; // ������ ���� �������� ����������� �������
	bool bVisible;  // ���������
	int iFontSize; // ������ ������

	RECT rectStaticText;
};

struct stImageBox
{
	stImageBox()
	{
		textureImageBox = NULL;
		bVisible = true;

		bAnimEnable = false;
		iRateInSec = 1;
		dwLastUpdate = 0;
		iNumCurCadr = 0;
		iQuantCadr = 0;
	};

	//LPDIRECT3DTEXTURE9 *pTextureRender; // ����� �������� ������� ���������� �������
	LPDIRECT3DTEXTURE9 textureImageBox; // ������� �������� stImageBox

	D3DXVECTOR2 vectorTrans;
	D3DXVECTOR2 vectorScale;
	int iIDWindow; // ������ ���� �������� ����������� �������
	bool bVisible;  // ���������

	// ��� ������������ �����������
	bool bAnimEnable;  // ���������� �� ��������
	int iRateInSec; // ������� ������ � �������
	int iDelayFrame; // �������� ����� �������
	DWORD dwLastUpdate; // ���������� ���������� ����� �������
	int iNumCurCadr;  // ����� �������� �����
	int iQuantCadr; // ���������� ������
	RECT *pRectRender; // ����� ����� �������� ����������, ��� �������� ��������� �� ������ ����
	RECT rectFrameForWindow; // ����� �������� ��������
	stRECT m_stRectPos; // �������������� �������������
};

struct stSliderInfo  // ��������� ��������� � ���������� Slider'y �������
{
	stSliderInfo()
	{
		m_fMinValue = 0.0f;
		m_fCurValue = 0.0f;
		m_fMaxValue = 0.0f;

		m_fRaznizaMinMax = 0.0f;
		fDelta = 1.0f;
	};
	stSliderInfo(float fMinValue, float fCurValue, float fMaxValue, float delta)
	{
		m_fMinValue = fMinValue;
		m_fCurValue = fCurValue;
		m_fMaxValue = fMaxValue;

		m_fRaznizaMinMax = 0.0f;
		fDelta = delta;
	};

	float m_fMinValue;
	float m_fCurValue;
	float m_fMaxValue;
	
	float m_fRaznizaMinMax;  // ������� ����� min � max �� ������ => �������� ��������
	float fDelta; // ��������� ����������
};
struct stScrollBar
{
	stScrollBar()
	{
		textureSliderString = NULL;
		bEnable = true;
		bVisible = true;
		bSlider = false;
		bHorizontalSlider = true;

		iSliderStringWidth = 0;

		vectorScale.x = 1.0f;
		vectorScale.y = 1.0f;

		iDelayScroll = 70;
		dwLastUpdate = 0;

		iButtonSliderBegPosX = 0;
		iButtonSliderBegPosY = 0;
		iSliderButtonWidth = 0;

		fPixelInValue = 0.0f;
		bFollowMouse = false;
	};

	bool bSlider;
	bool bFollowMouse; // ��������� �� ������� �� �������� �����
	bool bHorizontalSlider; // �������������� ������� = true, ����� ��� ������������ �������
	D3DXVECTOR2 vectorTrans;
	D3DXVECTOR2 vectorScale; // ������� �������������� �� �������� ����� �������
	int iSliderStringWidth; // ������ �������������� �� �������� ����� �������
	int iSliderButtonWidth; // ������ �������
	float fPixelInValue;  // ����� ������� � ������� �������� ��������
	bool bEnable;   // �����������
	bool bVisible;  // ���������
	int iButtonSliderBegPosX;
	int iButtonSliderBegPosY;

	int iDelayScroll; // �������� ����� �����������
	DWORD dwLastUpdate; // ��������� ���������� ������� ����������

	stSliderInfo m_stSliderInfo; // ���������� ��� ������� (min, cur, max) �� ��������� ������ ����
	stButton buttonSlider; // ������� � �������� ������ �� ������� ������
	stButton buttonNext;
	stButton buttonPrev;
	
	LPDIRECT3DTEXTURE9 textureSliderString; // �������� �������������� �� �������� ����� �������

	void (*pFuncExecute)(stSliderInfo *pSliderInfo);
};

struct stGuiMouse
{
	stImageBox image;
};

struct stWindowPanel // �������� �������� ��� ������ ���� �� ��� �� �������� �� ������ (������� ��� ����)
{
	stWindowPanel()
	{
		textureRenderWindow = NULL;
		textureRenderFon = NULL;
		
		bVisible = true;

		m_iQuantImageBox = 0;
		m_iQuantButtons = 0;
		m_iQuantCheckBox = 0;
		m_iQuantStaticText = 0;
		m_iQuantGroup = 0;
	};

	LPDIRECT3DTEXTURE9 textureRenderWindow;  // ������� �������� ���� ( ��� ����������� �������� ���� ������������ )
	LPDIRECT3DTEXTURE9 textureRenderFon; // ���������� ��� �������� ���� � �������� ������� ����������� � ������������ ����������

	enTypeWindowFill typeWindowFill; // ��� �������� ������� ������������

	RECT RectWindow; // ������� � ������ ���� (��� �������)
	stRECT stRect;   // ������ ���� ������� ������� �������
	D3DXVECTOR2 vectorTransWindow;
	bool bVisible;


	// �������� ������� ����� � ���� ( ������, ����, ... )
	vector<stImageBox> m_stImageBox;
	vector<stButton> m_stButtons;
	vector<stCheckBox> m_stCheckBox;
	vector<stStaticText> m_stStaticText;
	vector<stGroup> m_stGroup;
	int m_iQuantImageBox;
	int m_iQuantButtons;
	int m_iQuantCheckBox;
	int m_iQuantStaticText;
	int m_iQuantGroup;
};

struct stHandleGui  // ��� ��������� � ��������, �������� Show, Hide
{
	stHandleGui()
	{
		typeElementGui = NOT_ELEM; // �� ��������� ������� ��� ��� ��������
		typeWindow = NOT_ELEM;
	};

	enTypeElemGui typeWindow;  // ��� ���� �������� ����������� �������
	int iIDWindow; // ������ ���� �������� ����������� �������

	enTypeElemGui typeElementGui;  // ��� ��������
	int iIndex;  // ������ ��������

	//int iIndexButton;
	//int iIndexCheckBox;
	//int iIndexWindow;
};
// ====================== structures ( end ) ==================================================



// ==================================  class CManagerGUI ( BEGIN ) ==================================
class CManagerGUI
{
	private:
		int i; // ��� ������
		int j; // ��� ������
		LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
		LPDIRECT3DINDEXBUFFER9  m_pIndexBuffer;
		LPDIRECT3DTEXTURE9 m_boxTexture;

		DXData *m_directx;

		D3DXMATRIX m_matWorld;
		D3DXMATRIX m_matView;
		D3DXMATRIX m_matProjection;
		D3DXMATRIX m_matRot;
		D3DXMATRIX m_matTrans;
		D3DXMATRIX m_matScale;

		// �������� ������
		int m_iSampleSoundID_MouseDown; // ��� ����� �������
		int m_iSampleSoundID_MouseOver; // ���� ��� ���������

		D3DCOLOR m_colorTextDefault;
		D3DCOLOR m_colorTextDefault_forRestore;  // ���� ������ ������� �������� � ������ ��� �������������
		D3DCOLOR m_colorFrameCheckBox; // ���� ����� CheckBox
		D3DCOLOR m_colorFrameRadioButton; // ���� ����� RadioButton
		//FONT *m_pFontDefault_s20; // ������ ������ 20
		//FONT *m_pFontDefault_s25; // ������ ������ 25

		int m_iCurNumMouse;  // ������� ����� �����
		bool m_bCreatedMouse; // ���� �� ������� ����

		vector<stWindowPanel> m_stWindowPanel;
		vector<stHandleGui> m_stHandleWindowRender; // ������ ��������� ���� (� ����� ������������������ ��������)
		//stHandleGui m_stHandleActiveWindow; // �������� � ������ ������ ����
		//stWindows m_stWindows;
		vector<stGuiMouse> m_stGuiMouse;
		vector<stGroup> m_stGroup;
		vector<stScrollBar> m_stHorizScrollBar; // �������������� ScrollBar
		vector<stScrollBar> m_stVertScrollBar; // ������������ ScrollBar
		vector<stButton> m_stButtons; // ������ �� ������������� �� ������ ����
		vector<stCheckBox> m_stCheckBox; // checkBox �� ������������� �� ������ ����
		vector<stRadioButton> m_stRadioButton; // RadioButton �� ������������� �� ������ ����
		vector<stStaticText> m_stStaticText; // StaticText �� ������������� �� ������ ����
		vector<stImageBox> m_stImageBox; // ImageBox �� ������������� �� ������ ����
		int m_iQuantWindowsPanel; // ���������� Panel ����
		int m_iQuantButtons; // ���������� ������
		int m_iQuantCheckBox; // ���������� checkBox
		int m_iQuantRadioButton; // ���������� RadioButton
		int m_iQuantStaticText; // ���������� StaticText
		int m_iQuantImageBox; // ���������� ImageBox
		int m_iQuantMouse; // ���������� �����
		int m_iQuantGroup; // ���������� ����
		int m_iQuantHorizScrollBar; // ���������� �������������� ScrollBar
		int m_iQuantVertScrollBar; // ���������� ������������ ScrollBar
	public:
		CManagerGUI();
		~CManagerGUI();

		void vBeginInit(DXData *directx);  // ������ � ����� ������������� ���� ������, ����, � ��� �����...
		void vEndInit();
		void vLoadSamples(char *pcSampleMouseDown, char *pcSampleMouseOver, int iSoundVolume);

		void vRender(); // ���������
		void vSetMatrix(); // ��������� ������� - �������� 2D ����

		void vCalculate(stMouseInfoGUI *mouseInfoGui); // �������� � ������� �����, ������� ������ ����
		inline bool bCalculateWindowPanels(stMouseInfoGUI *mouseInfoGui); // ��������� Panel window's
		bool bShow(stHandleGui *handleGui);  // �������� �������
		bool bHide(stHandleGui *handleGui);  // �������� �������
		bool bReplaceStaticText(stHandleGui *handleGui, char *newText); // �������� ������� � �������� StaticText
		bool bSetObjectPos(D3DXVECTOR2 pos, stHandleGui *handleGui);   // ������������� ������� ����� ����������
		void vSetCurTextColor(D3DCOLOR color);  // ������������� ������� ���� ������
		void vRestoreTextColor(); // �������������� ���� ������ ������� �������� � ������ ��-���������


		// �������� ������
		stHandleGui hCreateButton(stHandleGui *handleWindow, char *name, stRECT rectPos, void (*pFunc)(), bool bSelecEnable, int iTypeSelection);
		stHandleGui hCreateButton(stHandleGui *handleWindow, char *name, stRECT rectPos, void (*pFunc)(), bool bSelecEnable, int iTypeSelection, char *textureButtonName);
		stHandleGui hCreateButton(stHandleGui *handleWindow, char *name, stRECT rectPos, void (*pFunc)(), char *textureButtonName, char *textureButtonSelectName);

		// �������� checkBox
		stHandleGui hCreateCheckBox(stHandleGui *handleWindow, char *name, stRECT rectPos, void (*pFunc)(bool bCheckBoxOn));
		stHandleGui hCreateCheckBox(stHandleGui *handleWindow, char *name, stRECT rectPos, void (*pFunc)(bool bCheckBoxOn), char *textureNameCheckBoxOFF, char *textureNameCheckBoxON);

		// �������� ������ GroupRadioButton �  ������ RadioButton
		stHandleGui hCreateGroup(stHandleGui *handleWindow);
		void vCreateRadioButton(stHandleGui *handleGroup, char *name, stRECT rectPos, void (*pFunc)(bool bRadioButtonOn));
		void vCreateRadioButton(stHandleGui *handleGroup, char *name, stRECT rectPos, void (*pFunc)(bool bRadioButtonOn), char *textureNameRadioButtonOFF, char *textureNameRadioButtonON);


		// �������� �������� StaticText
		stHandleGui hCreateStaticText(stHandleGui *handleWindow, char *text, int iPosX, int iPosY, int iFontSize);

		// �������� ImageBox
		stHandleGui hCreateImageBox(stHandleGui *handleWindow, stRECT rectPos, char *textureNameImage);
		stHandleGui hCreateImageBox(stHandleGui *handleWindow, stRECT rectPos, stSIZE sizeCadr, int rateInSec, char *textureNameImage);

		// �������� ScrollBar
		stHandleGui hCreateHorizScrollBar(int iWindowID, stRECT rectPos, stSliderInfo info, void (*pFunc)(stSliderInfo *pSliderInfo), int iDelayButton, bool bSlider);
		stHandleGui hCreateHorizScrollBar(int iWindowID, stRECT rectPos, stSliderInfo info, void (*pFunc)(stSliderInfo *pSliderInfo), int iDelayButton, bool bSlider,
												char *pcNameTextureButtonSlider,
												char *pcNameTextureButtonSliderSelection,
												char *pcNameTextureButtonPrev,
												char *pcNameTextureButtonPrevSelection,
												char *pcNameTextureButtonNext,
												char *pcNameTextureButtonNextSelection,
												char *pcNameTextureSliderString);
		stHandleGui hCreateVertScrollBar(int iWindowID, stRECT rectPos, stSliderInfo info, void (*pFunc)(stSliderInfo *pSliderInfo), int iDelayButton, bool bSlider);
		stHandleGui hCreateVertScrollBar(int iWindowID, stRECT rectPos, stSliderInfo info, void (*pFunc)(stSliderInfo *pSliderInfo), int iDelayButton, bool bSlider,
												char *pcNameTextureButtonSlider,
												char *pcNameTextureButtonSliderSelection,
												char *pcNameTextureButtonPrev,
												char *pcNameTextureButtonPrevSelection,
												char *pcNameTextureButtonNext,
												char *pcNameTextureButtonNextSelection,
												char *pcNameTextureSliderString);
		bool bScrollBarOffsetCurValue(int iIndexScrollBar,bool bHoriz, float fDelta); // �������� �������� ��������


		// �������� ����
		stHandleGui hCreateWindowPanel(stRECT rectPos, char *nameTextureFon, enTypeWindowFill typeWindowFill);
		void vRefreshRectWindowPanel(int iIndexWindowPanel, stHandleGui *handleElem, LPDIRECT3DTEXTURE9 *texture);


		// �������� ����
		stHandleGui hCreateMouse(stSIZE sizeCursor, stSIZE sizeCadr, int rateInSec, char *textureNameImage);  // ������ ����
		bool bSetMouse(stHandleGui *handleMouse);  // ������������� ����
		void vShowMouse();  // �������� ������� ����
		void vHideMouse();  // �������� ������� ����



		//
		void vDrawBox2D(int x,int y,int w,int h,DWORD color);
		void vDrawRectangle(int x,int y,int w,int h,DWORD clr);
		void vDrawRectangle(int x,int y,int w,int h,DWORD clr1,DWORD clr2);
		void vDrawFrameRect(int x, int y, int w, int h, DWORD color_1,DWORD color_2, int widthFrame); // ������������� � �������� �����
		void vDrawButton(int x,int y,int w,int h,FONT* font,char* str,DWORD colorText);
};
// -----------------------------------  class CManagerGUI ( END ) -----------------------------------


// ==================================  class CButtonGUI ( BEGIN ) ==================================
#define BUTTON_GUI_STATE__PICK_OUT 1 // ������ ��������
#define BUTTON_GUI_STATE__PRESSED  2 // ������ ���� ������
#define BUTTON_GUI_STATE__JAMMED   3 // ������ ������

class CButtonGUI
{
	private:
		// ��� �������� ��������� � ��������� GUI
		int m_iIndexTextureButton;   // ������ �������� ������
		int m_iIndexTexturePickOut;  // ������ �������� ���������
		
		RECT m_rectButton;  // ������������� � ������� ��������� ������
	public:
		CButtonGUI();
		~CButtonGUI();
};
// -----------------------------------  class CButtonGUI ( END ) -----------------------------------
#endif // _CMANAGER_GUI_H_