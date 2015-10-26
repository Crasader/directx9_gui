//font.cpp
//--------------------------------------------------------

#include "font.h"

//--------------------------------------------------------
//�������� �����
FONT::FONT(DXData *directx, int SizeFont,DWORD bold,bool italic,char* nameFont)
{
	m_directx = directx;

	TCHAR str[2];//������ ( ����� ���� ����� )
	str[1]=0;//���������� ����� ������
	BYTE c;//����� �������
    
	HDC hDC;
    hDC = CreateCompatibleDC( NULL );
    SetMapMode( hDC, MM_TEXT );

    HBITMAP hbmBitmap = NULL;
    HGDIOBJ hbmOld = NULL;

    // Prepare to create a bitmap
    DWORD*      pBitmapBits;
    BITMAPINFO bmi;
    ZeroMemory( &bmi.bmiHeader, sizeof(BITMAPINFOHEADER) );
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = SizeFont;
    bmi.bmiHeader.biHeight      = -SizeFont;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biBitCount    = 32;

    // Create a bitmap for the font
    hbmBitmap = CreateDIBSection( hDC, &bmi, DIB_RGB_COLORS,(void**)&pBitmapBits, NULL, 0 );

    SelectObject( hDC, hbmBitmap );
    
    // Set text properties
    SetTextColor( hDC, RGB(255,255,255) );
    SetBkColor(   hDC, 0x00000000 );
    SetTextAlign( hDC, TA_TOP );
	
	//������� ����
 	HFONT hfont=CreateFont(SizeFont,0,0,0,bold,italic,false,false,
			ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH,
			nameFont);//������ ��� �����

	if(hfont==NULL) goto fn;//���� ���� �� ������ ����� � �������
		//--------------
	//���������� ����
    SelectObject( hDC, hfont );
    //���������� �������������� �����
    SetTextColor( hDC, RGB(255,255,255) );
    SetBkColor(   hDC, 0x00000000 );
    SetTextAlign( hDC, TA_TOP );

    SIZE size;//��������� �������� ������� �������

	for( c =255; c >0; c-- )//����� ������� � �����
    {
  		//�������� �������� ��� ����� 
		m_directx->m_pD3DDevice->CreateTexture(SizeFont,SizeFont, 1,0,D3DFMT_A8R8G8B8,//������ ��������
                                      D3DPOOL_MANAGED, &texture[c], NULL );
		if(texture[c]==NULL)goto fn;
		//-----------------------------------

		str[0] = c;

		if(0==GetTextExtentPoint32( hDC, str, 1, &size ))goto fn;//����� ������� �������
			
		width[c] = (FLOAT)size.cx;//���������� ������� �������
		height = (FLOAT)size.cy;

		if(0==ExtTextOut( hDC, 0, 0, ETO_OPAQUE, NULL, str, 1, NULL ))goto fn;//����� ������� � ������

		D3DLOCKED_RECT rect;
		//������������� ��������
		texture[c]->LockRect( 0, &rect, 0, 0 );

		BYTE* pDstRow = (BYTE*)rect.pBits;//����� ��������
		DWORD* pDst16;
		BYTE bAlpha; // 4-bit measure of pixel intensity
		DWORD x, y;

		//��������� �� ������� � ��������
		for( y=0; y < (DWORD)SizeFont; y++ )
		{
			pDst16 = (DWORD*)pDstRow;//����� ���� � ���������
			for( x=0; x < (DWORD)SizeFont; x++ )
			{
				//����� ������� � �������
				bAlpha = (BYTE)((pBitmapBits[SizeFont*y + x] & 0xff) >> 4);
				//��������� �� �
				*pDst16++= D3DCOLOR_ARGB(bAlpha*14,255,255,255);//�������� ������
			}
			pDstRow += rect.Pitch;//��������� �� - Y
		}

		if(texture[c]) texture[c]->UnlockRect(0);//��������������
	}
	//������� ��������
fn: DeleteObject( hbmBitmap );
    DeleteObject( hfont );
    DeleteDC( hDC );
};
//����� ������
int FONT::print(float x,float y,DWORD color,char* s)
{
	if(s == NULL)
		return 0;

	byte ch;
	int start = (int)x;
	D3DXVECTOR2 vecScaling(1,1);  // �������
	D3DXVECTOR2 vecTrans(0,0);	  // Translation

	RECT rect;//��������� ����������� ��������������
	rect.left=0;
	rect.top=0;

	UINT len = (UINT)strlen(s);
	for(UINT i=0;i<len;++i)
	{
		ch=s[i];

		if(ch=='\n')
		{
			x = (float)start;
			y+=height;
			continue;
		}

        if(ch < 0 || ch > 255)continue;

		rect.right = (long)width[ch];
		rect.bottom = (long)height;

		// ���� ��������
		vecTrans.x = x;
		vecTrans.y = y;

		//����� �������
		m_directx->m_sprite->Draw(texture[ch],&rect,&vecScaling,NULL,0,&vecTrans,color);
		x+=rect.right;//���������� �� ������ �������
	}return (int)x-start;//�������� ����� ������
};
//����� ������ � �������������
void FONT::print(float x,float y,DWORD color,char* s,RECT clip)
{
	if(s == NULL)
		return;

	byte ch;
	int start = (int)x;
	D3DXVECTOR2 vecScaling(1,1);  // �������
	D3DXVECTOR2 vecTrans(0,0);	  // Translation

	RECT rect;//��������� ����������� ��������������
	rect.left=0;
	rect.top=0;

	UINT len = (UINT)strlen(s);
	for(UINT i=0;i<len;++i)
	{
		ch=s[i];

		if(ch=='\n')//��������� ����� ENTER
		{
			x = (float)start;
			y+=height;//��������� ����
			continue;
		}

        if(ch < 0 || ch > 255)continue;

		rect.right = (long)width[ch];
		rect.bottom = (long)height;

		int px=(int)x,py=(int)y,rx=0,ry=0,w=rect.right,h=rect.bottom;
		int c_x=clip.left,c_y=clip.top,c_w=clip.right,c_h=clip.bottom;
		//������������(�������� ��������� ������) ���������� ��������������
		if(px<c_x){ rx=rx+(c_x-px);w=w-(c_x-px);px=c_x;}
		if(py<c_y){ ry=ry+(c_y-py);h=h-(c_y-py);py=c_y;}
		if(px+w>c_x+c_w)w=c_w-(px-c_x);
		if(py+h>c_y+c_h)h=c_h-(py-c_y);
		//---------------------
		// ���� ��������
		vecTrans.x = (float)px;
		vecTrans.y = (float)py;

		rect.left=rx,rect.top=ry,rect.right=rx+w,rect.bottom=ry+h;
		//����� �������
		m_directx->m_sprite->Draw(texture[ch],&rect,&vecScaling,NULL,0,&vecTrans,color);
		x+=rect.right;//���������� �� ������ �������
	}
};
FONT::~FONT()
{
	/*height=NULL;
	for(int i=0;i<256;i++)
	{
		width[i]=NULL;
		_RELEASE_(texture[i]);
	}*/

	for(int  c =255; c >0; c-- )//����� ������� � �����
		_RELEASE_(texture[c]);
};

void FONT::vRelease()
{
	//height=NULL;
	for(int i=0; i<1; i++)
	{
		//width[i]=NULL;
		//_RELEASE_(texture[i]);
		if(texture[i])
		{
			//_RELEASE_(texture[i]);
		}
		//SafeExceptionRelease(&texture[i]);
	}

	for(int  c =255; c >0; c-- )//����� ������� � �����
		_RELEASE_(texture[c]);
}
//----------------------------------------
