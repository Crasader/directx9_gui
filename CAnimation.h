#include <vector>
#include <stack>
#include "DXData.h"

using namespace std;


/* ������ ( begin ) */
#define ANIM_OK					0  /* */ 
#define ERR_TYPE_WAS_CREATED	-1 /* ��� ��� ���� */
#define ERR_TEXTURE_LOAD		-2 /* �������� � ��������� �������� */
#define ERR_ID_NOT_ARRAY		-3 /* ID ������� �� ������� ������� */
#define ERR_TYPE_NOT_FIND		(-4) /* �� ������ �������� ��� */
/* ������ ( end ) */


/* iFlagsAnimation */
#define ANIM_QUANT_ONE 0x00000001  /* ����������� ���� ��� */
#define ANIM_QUANT_INF 0x00000010  /* ����������� ����� ��� */
#define ANIM_FORWARD   0x00000100  /* ����������� ����� */
#define ANIM_BACK      0x00001000  /* ����������� ����� */
#define ANIM_NO_ANIM   0x00010000  /* �� ����������� */
#define ANIM_DELETE    0x00100000  /* ����� �������� ������� */


/* iFlagsCadr */
#define CADR_BEG	   -1 /* ��������� ���� */
#define CADR_END	   -2 /* ��������� ���� */
#define CADR_NEXT	   -3 /* ���� ���� */
#define CADR_PREV	   -4 /* ���� ���� */

/* ������� ( begin ) */
#define ANIM_CADR_END_WAS  1 /* �������� ���� ��� ��������� */
#define ANIM_CADR_BEG_WAS  2 /* ��������� ���� ��� ��������� */
/* ������� ( end ) */


struct stType
{
	stType()
	{
		iDelayAnim = 100;
		pTexture = NULL;
		rect_draw = NULL;
		iQuantCadrs = 0;
		iQuantTextureFiles = 0;

		//ID = -1;  // �� ������ ��� �����
		bDeleted = false;
		bFewFiles = false;
	};

	bool bDeleted;
	bool bFewFiles; // ��������� ������ ??
	int ID;
	char name[50];  // ��� ����
	int iDelayAnim;  // �������� ����� �������
	
	int iQuantCadrs;
	int iQuantTextureFiles;
	LPDIRECT3DTEXTURE9 *pTexture;
	RECT *rect_draw; // ����� ����� �������� ( ���� � ����� �������� ��������� ������ )
	
	// ��� VectorRot
	int iCadrWidth;
	int iCadrHeight;
};

struct stObject
{
	stObject()
	{
		iNumCadr = 0;
		iNumFile = 0;
		iBegTimeAnim = 0;
		bDeleted = false;

		vectorScale = D3DXVECTOR2(1.0f, 1.0f);
		vectorRot = D3DXVECTOR2(0.0f, 0.0f);
		fAngle = 0;

		bRender = true;
		name[0] = '\0';

		iPriority = 0;
	};

	bool bDeleted;
	int ID;		// ID ������ �������
	int IDType;  // ID ���� � �������� ����������� ������
	
	char name[50];
	D3DXVECTOR2 vectorPos;
	D3DXVECTOR2 vectorScale;
	D3DXVECTOR2 vectorRot; // ������ ��������
	float fAngle; // ���� ��������

	int iNumCadr;
	int iNumFile;
	int iBegTimeAnim;

	int iFlagsAnimation; // ��� ����������� (���� ���, ����)
	bool bRender;  // �������� �� ?

	int iPriority; // ��������� ���������
};



class CAnimation
{
	private:
		DXData *m_directx;
		int m_iQuantType; // ���������� ����������������� �����
		int m_iQuantObject; // ���������� ����������������� ��������
		int m_iSizeArrayType;  // ������ �������
		int m_iSizeArrayObject;
		
		int  m_iSizeArrayRender;  // ������ ������� ���������
		bool m_bRestAssumeArrayRender;  //  ����� �� ������������� ������� ������� ���������
		int *m_piIndexRender;  // ������� ������� ���������
		LPDIRECT3DTEXTURE9 m_lpRenderTexture;

		vector<stType> m_stType;
		vector<stObject> m_stObject;

		stack <int, vector<int> > m_stackFreeIndexObjects;  //  ���� �������� ��������� ������� ��������

	public:
		CAnimation();
		~CAnimation();

		void vSetDirectX(DXData *directX)
		{
			m_directx = directX;
			m_directx->m_pD3DDevice->CreateTexture(m_directx->m_d3dpp.BackBufferWidth,
														m_directx->m_d3dpp.BackBufferHeight,
														1,
														D3DUSAGE_RENDERTARGET,
														D3DFMT_A8R8G8B8,
														D3DPOOL_DEFAULT, 
														&m_lpRenderTexture,0);
			/*
			D3DXCreateTexture(m_directx->m_pD3DDevice,
						1024,
						1024,
						D3DUSAGE_RENDERTARGET,
						0,
						D3DFMT_A8R8G8B8,
						D3DPOOL_MANAGED, // D3DPOOL_MANAGED
						&m_lpRenderTexture);
			*/
		};

		int iAddType(char *pcType, char *pcFiles, int iQuantFiles);
		int iAddType(char *pcType, char *pcFile, int iQuantCadr, int iSizeCadrX, int iSizeCadrY);
		bool bDeleteType(char *cType);
		//int  inline iGetTypeID(char *pcType);


		int iAddObject(char *pcNameObject, char *pcType, D3DXVECTOR2 vectorPos, int iFlagsAnimation);
		bool bDeleteObject(char *pcNameObject, int ID);  // ����� ���������� �� ID ��� �����
		void vSetObjectPos(char *pcNameObject, int ID, D3DXVECTOR2 vectorPos);  // ����� ���������� �� ID ��� �����
		void vSetObjectScale(char *pcNameObject, int ID, D3DXVECTOR2 vectorScale);  // ����� ���������� �� ID ��� �����
		void vSetObjectAngle(char *pcNameObject, int ID, float fAngle);  // ����� ���������� �� ID ��� �����
		int iSetObjectCadr(char *pcNameObject, int ID, int iFlagsOrCadr);  // ����� ���������� �� ID ��� �����
		bool bSetObjectPriority(char *pcNameObject, int ID, int iPriority);  // ���������� ��������� ����������



		void vRender(); // ������
		void vDraw();   // ������������� (�������, ...)



		int iGetSizeArrayObject()
		{
			return m_iSizeArrayObject;
		};
		int iGetQuantObject()
		{
			return m_iQuantObject;
		};
		int iGetQuantType()
		{
			return m_iQuantType;
		};
		int iGetSizeArrayType()
		{
			return m_iSizeArrayType;
		};
};