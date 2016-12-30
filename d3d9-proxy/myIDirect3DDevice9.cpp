#include "StdAfx.h"
#include "myIDirect3DDevice9.h"


//FILE* pFile = fopen("hacklog.txt", "w");
//char buff[2048];
//
void DLOG(const char* szString)
{
	//fprintf(pFile, "%s\n", szString);
}

myIDirect3DDevice9::myIDirect3DDevice9(IDirect3DDevice9* pOriginal)
{
	// store the pointer to original object
	m_pIDirect3DDevice9 = pOriginal;
}

myIDirect3DDevice9::~myIDirect3DDevice9(void)
{
}

HRESULT myIDirect3DDevice9::QueryInterface (REFIID riid, void** ppvObj)
{
    // check if original dll can provide interface. then send *our* address
	*ppvObj = NULL;

	HRESULT hRes = m_pIDirect3DDevice9->QueryInterface(riid, ppvObj); 

	if (hRes == NOERROR)
	{
		*ppvObj = this;
	}
	
	return hRes;
}

ULONG myIDirect3DDevice9::AddRef(void)
{
    return(m_pIDirect3DDevice9->AddRef());
}

ULONG myIDirect3DDevice9::Release(void)
{
	// ATTENTION: This is a booby-trap ! Watch out !
	// If we create our own sprites, surfaces, etc. (thus increasing the ref counter
	// by external action), we need to delete that objects before calling the original
	// Release function	
	
	// global var
	extern myIDirect3DDevice9* gl_pmyIDirect3DDevice9;

    // release/delete own objects
    // .....
	
	// Calling original function now
	ULONG count = m_pIDirect3DDevice9->Release();
		
    // now, the Original Object has deleted itself, so do we here
	gl_pmyIDirect3DDevice9 = NULL;
	delete(this);  // destructor will be called automatically

	return (count);
}

HRESULT myIDirect3DDevice9::TestCooperativeLevel(void)
{
    return(m_pIDirect3DDevice9->TestCooperativeLevel());
}

UINT myIDirect3DDevice9::GetAvailableTextureMem(void)
{
    return(m_pIDirect3DDevice9->GetAvailableTextureMem());
}

HRESULT myIDirect3DDevice9::EvictManagedResources(void)
{
    return(m_pIDirect3DDevice9->EvictManagedResources());
}

HRESULT myIDirect3DDevice9::GetDirect3D(IDirect3D9** ppD3D9)
{
    return(m_pIDirect3DDevice9->GetDirect3D(ppD3D9));
}

HRESULT myIDirect3DDevice9::GetDeviceCaps(D3DCAPS9* pCaps)
{
    return(m_pIDirect3DDevice9->GetDeviceCaps(pCaps));
}

HRESULT myIDirect3DDevice9::GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode)
{
    return(m_pIDirect3DDevice9->GetDisplayMode(iSwapChain, pMode));
}

HRESULT myIDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
    return(m_pIDirect3DDevice9->GetCreationParameters(pParameters));
}

HRESULT myIDirect3DDevice9::SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap)
{
    return(m_pIDirect3DDevice9->SetCursorProperties(XHotSpot,YHotSpot,pCursorBitmap));
}

void    myIDirect3DDevice9::SetCursorPosition(int X,int Y,DWORD Flags)
{
    return(m_pIDirect3DDevice9->SetCursorPosition(X,Y,Flags));
}

BOOL    myIDirect3DDevice9::ShowCursor(BOOL bShow)
{
    return(m_pIDirect3DDevice9->ShowCursor(bShow));
}

HRESULT myIDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain)  
{
    return(m_pIDirect3DDevice9->CreateAdditionalSwapChain(pPresentationParameters,pSwapChain));
}

HRESULT myIDirect3DDevice9::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain)
{
    return(m_pIDirect3DDevice9->GetSwapChain(iSwapChain,pSwapChain));
}

UINT    myIDirect3DDevice9::GetNumberOfSwapChains(void)
{
    return(m_pIDirect3DDevice9->GetNumberOfSwapChains());
}

HRESULT myIDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return(m_pIDirect3DDevice9->Reset(pPresentationParameters));
}

HRESULT myIDirect3DDevice9::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
{
	// hook for hiding boot menus
	this->HideBootMenu();

	return (m_pIDirect3DDevice9->Present( pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion));
}

HRESULT myIDirect3DDevice9::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{
    return(m_pIDirect3DDevice9->GetBackBuffer(iSwapChain,iBackBuffer,Type,ppBackBuffer));
}

HRESULT myIDirect3DDevice9::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus)
{
    return(m_pIDirect3DDevice9->GetRasterStatus(iSwapChain,pRasterStatus));
}

HRESULT myIDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs)
{
    return(m_pIDirect3DDevice9->SetDialogBoxMode(bEnableDialogs));
}

void    myIDirect3DDevice9::SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp)
{
    return(m_pIDirect3DDevice9->SetGammaRamp(iSwapChain,Flags,pRamp));
}

void    myIDirect3DDevice9::GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp)
{
    return(m_pIDirect3DDevice9->GetGammaRamp(iSwapChain,pRamp));
}

HRESULT myIDirect3DDevice9::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateTexture(Width,Height,Levels,Usage,Format,Pool,ppTexture,pSharedHandle));
}

HRESULT myIDirect3DDevice9::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateVolumeTexture(Width,Height,Depth,Levels,Usage,Format,Pool,ppVolumeTexture,pSharedHandle));
}

HRESULT myIDirect3DDevice9::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateCubeTexture(EdgeLength,Levels,Usage,Format,Pool,ppCubeTexture,pSharedHandle));
}

HRESULT myIDirect3DDevice9::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateVertexBuffer(Length,Usage,FVF,Pool,ppVertexBuffer,pSharedHandle));
}

HRESULT myIDirect3DDevice9::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateIndexBuffer(Length,Usage,Format,Pool,ppIndexBuffer,pSharedHandle));
}

HRESULT myIDirect3DDevice9::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateRenderTarget(Width,Height,Format,MultiSample,MultisampleQuality,Lockable,ppSurface,pSharedHandle));
}

HRESULT myIDirect3DDevice9::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateDepthStencilSurface(Width,Height,Format,MultiSample,MultisampleQuality,Discard,ppSurface,pSharedHandle));
}

HRESULT myIDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint)
{
    return(m_pIDirect3DDevice9->UpdateSurface(pSourceSurface,pSourceRect,pDestinationSurface,pDestPoint));
}

HRESULT myIDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture)
{
    return(m_pIDirect3DDevice9->UpdateTexture(pSourceTexture,pDestinationTexture));
}

HRESULT myIDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface)
{
    return(m_pIDirect3DDevice9->GetRenderTargetData(pRenderTarget,pDestSurface));
}

HRESULT myIDirect3DDevice9::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface)
{
    return(m_pIDirect3DDevice9->GetFrontBufferData(iSwapChain,pDestSurface));
}

HRESULT myIDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
{
    return(m_pIDirect3DDevice9->StretchRect(pSourceSurface,pSourceRect,pDestSurface,pDestRect,Filter));
}

HRESULT myIDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color)
{
    return(m_pIDirect3DDevice9->ColorFill(pSurface,pRect,color));
}

HRESULT myIDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(m_pIDirect3DDevice9->CreateOffscreenPlainSurface(Width,Height,Format,Pool,ppSurface,pSharedHandle));
}

HRESULT myIDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget)
{
    return(m_pIDirect3DDevice9->SetRenderTarget(RenderTargetIndex,pRenderTarget));
}

HRESULT myIDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget)
{
    return(m_pIDirect3DDevice9->GetRenderTarget(RenderTargetIndex,ppRenderTarget));
}

HRESULT myIDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
    return(m_pIDirect3DDevice9->SetDepthStencilSurface(pNewZStencil));
}

HRESULT myIDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
    return(m_pIDirect3DDevice9->GetDepthStencilSurface(ppZStencilSurface));
}

HRESULT myIDirect3DDevice9::BeginScene(void)
{
    return(m_pIDirect3DDevice9->BeginScene());
}

HRESULT myIDirect3DDevice9::EndScene(void)
{
    return(m_pIDirect3DDevice9->EndScene());
}

HRESULT myIDirect3DDevice9::Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
{
    return(m_pIDirect3DDevice9->Clear(Count,pRects,Flags,Color,Z,Stencil));
}

HRESULT myIDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
    return(m_pIDirect3DDevice9->SetTransform(State,pMatrix));
}

HRESULT myIDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix)
{
    return(m_pIDirect3DDevice9->GetTransform(State,pMatrix));
}

HRESULT myIDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
    return(m_pIDirect3DDevice9->MultiplyTransform(State,pMatrix));
}

HRESULT myIDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	// Viewport no bezel hack
	if (pViewport->X == 213 && pViewport->Y == 120 && pViewport->Width == 853 && pViewport->Height == 480) {
		return D3D_OK;
	}
    return(m_pIDirect3DDevice9->SetViewport(pViewport));
}

HRESULT myIDirect3DDevice9::GetViewport(D3DVIEWPORT9* pViewport)
{
    return(m_pIDirect3DDevice9->GetViewport(pViewport));
}

HRESULT myIDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
    return(m_pIDirect3DDevice9->SetMaterial(pMaterial));
}

HRESULT myIDirect3DDevice9::GetMaterial(D3DMATERIAL9* pMaterial)
{
    return(m_pIDirect3DDevice9->GetMaterial(pMaterial));
}

HRESULT myIDirect3DDevice9::SetLight(DWORD Index,CONST D3DLIGHT9* pLight)
{
    return(m_pIDirect3DDevice9->SetLight(Index,pLight));
}

HRESULT myIDirect3DDevice9::GetLight(DWORD Index,D3DLIGHT9* pLight)
{
    return(m_pIDirect3DDevice9->GetLight(Index,pLight));
}

HRESULT myIDirect3DDevice9::LightEnable(DWORD Index,BOOL Enable)
{
    return(m_pIDirect3DDevice9->LightEnable(Index,Enable));
}

HRESULT myIDirect3DDevice9::GetLightEnable(DWORD Index,BOOL* pEnable)
{
    return(m_pIDirect3DDevice9->GetLightEnable(Index, pEnable));
}

HRESULT myIDirect3DDevice9::SetClipPlane(DWORD Index,CONST float* pPlane)
{
    return(m_pIDirect3DDevice9->SetClipPlane(Index, pPlane));
}

HRESULT myIDirect3DDevice9::GetClipPlane(DWORD Index,float* pPlane)
{
    return(m_pIDirect3DDevice9->GetClipPlane(Index,pPlane));
}

HRESULT myIDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State,DWORD Value)
{
    return(m_pIDirect3DDevice9->SetRenderState(State, Value));
}

HRESULT myIDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State,DWORD* pValue)
{
    return(m_pIDirect3DDevice9->GetRenderState(State, pValue));
}

HRESULT myIDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB)
{
    return(m_pIDirect3DDevice9->CreateStateBlock(Type,ppSB));
}

HRESULT myIDirect3DDevice9::BeginStateBlock(void)
{
    return(m_pIDirect3DDevice9->BeginStateBlock());
}

HRESULT myIDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
    return(m_pIDirect3DDevice9->EndStateBlock(ppSB));
}

HRESULT myIDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
    return(m_pIDirect3DDevice9->SetClipStatus(pClipStatus));
}

HRESULT myIDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
    return(m_pIDirect3DDevice9->GetClipStatus( pClipStatus));
}

HRESULT myIDirect3DDevice9::GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture)
{
    return(m_pIDirect3DDevice9->GetTexture(Stage,ppTexture));
}

HRESULT myIDirect3DDevice9::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)
{
    return(m_pIDirect3DDevice9->SetTexture(Stage,pTexture));
}

HRESULT myIDirect3DDevice9::GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue)
{
    return(m_pIDirect3DDevice9->GetTextureStageState(Stage,Type, pValue));
}

HRESULT myIDirect3DDevice9::SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value)
{
    return(m_pIDirect3DDevice9->SetTextureStageState(Stage,Type,Value));
}

HRESULT myIDirect3DDevice9::GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue)
{
    return(m_pIDirect3DDevice9->GetSamplerState(Sampler,Type, pValue));
}

HRESULT myIDirect3DDevice9::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value)
{
    return(m_pIDirect3DDevice9->SetSamplerState(Sampler,Type,Value));
}

HRESULT myIDirect3DDevice9::ValidateDevice(DWORD* pNumPasses)
{
    return(m_pIDirect3DDevice9->ValidateDevice( pNumPasses));
}

HRESULT myIDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries)
{
    return(m_pIDirect3DDevice9->SetPaletteEntries(PaletteNumber, pEntries));
}

HRESULT myIDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries)
{
    return(m_pIDirect3DDevice9->GetPaletteEntries(PaletteNumber, pEntries));
}

HRESULT myIDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber)
{
    return(m_pIDirect3DDevice9->SetCurrentTexturePalette(PaletteNumber));
}

HRESULT myIDirect3DDevice9::GetCurrentTexturePalette(UINT *PaletteNumber)
{
    return(m_pIDirect3DDevice9->GetCurrentTexturePalette(PaletteNumber));
}

HRESULT myIDirect3DDevice9::SetScissorRect(CONST RECT* pRect)
{
    return(m_pIDirect3DDevice9->SetScissorRect( pRect));
}

HRESULT myIDirect3DDevice9::GetScissorRect( RECT* pRect)
{
    return(m_pIDirect3DDevice9->GetScissorRect( pRect));
}

HRESULT myIDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware)
{
    return(m_pIDirect3DDevice9->SetSoftwareVertexProcessing(bSoftware));
}

BOOL    myIDirect3DDevice9::GetSoftwareVertexProcessing(void)
{
    return(m_pIDirect3DDevice9->GetSoftwareVertexProcessing());
}

HRESULT myIDirect3DDevice9::SetNPatchMode(float nSegments)
{
    return(m_pIDirect3DDevice9->SetNPatchMode(nSegments));
}

float   myIDirect3DDevice9::GetNPatchMode(void)
{
    return(m_pIDirect3DDevice9->GetNPatchMode());
}

HRESULT myIDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount)
{
    return(m_pIDirect3DDevice9->DrawPrimitive(PrimitiveType,StartVertex,PrimitiveCount));
}

HRESULT myIDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
    return(m_pIDirect3DDevice9->DrawIndexedPrimitive(PrimitiveType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount));
}

HRESULT myIDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
	unsigned int color = 0;
	int i = 0;

	// this variable is used to know what type and for which player we are drawing end stats text
	// (ate most pac-dots, etc)
	static char end_bg = 0;

	if (PrimitiveCount == 2 && VertexStreamZeroStride == 24) {
		color = ((unsigned int *)pVertexStreamZeroData)[3] & 0xFFFFFF00 >> 8;

		// some debug - tex[A-H] are used to find identification method of displayed thing to alter
		/*sprintf_s(buff, "P: x:%f y:%f z:%f texX:%f texY:%f color hex:%08x color int:%u texA:%u texB:%u texC:%u texD:%u texE:%u texF:%u texG:%u texH:%u",
			((float *)pVertexStreamZeroData)[0],
			((float *)pVertexStreamZeroData)[1],
			((float *)pVertexStreamZeroData)[2],
			((float *)pVertexStreamZeroData)[4],
			((float *)pVertexStreamZeroData)[5],
			((unsigned int *)pVertexStreamZeroData)[3] & 0xFFFFFF00 >> 8,
			((unsigned int *)pVertexStreamZeroData)[3] & 0xFFFFFF00 >> 8,
			(unsigned int)*(&pVertexStreamZeroData+32),
			(unsigned int)*(&pVertexStreamZeroData+36),
			(unsigned int)*(&pVertexStreamZeroData+40),
			(unsigned int)*(&pVertexStreamZeroData+44),
			(unsigned int)*(&pVertexStreamZeroData+48),
			(unsigned int)*(&pVertexStreamZeroData+52),
			(unsigned int)*(&pVertexStreamZeroData+56),
			(unsigned int)*(&pVertexStreamZeroData+60)
			);
		DLOG(buff); */

		// For each element to rotate, put it where a 180 degree Z rotation
		// would put him before doing the rotation
		// (because the rotation center is the window center)

		// Display viewport : 853x480
		// Viewport center : 426.5x240

		// SMALL TEXTs ==============================================

		// red text instructions (press start text)
		if (color == 16711680 && ((float *)pVertexStreamZeroData)[1] == 10.0f) {
//			DLOG("CASE 1 - red instructions text press start");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 534.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 440.0;
			}
		
		// blue text instructions (press start text)
		} else if (color == 56575 && ((float *)pVertexStreamZeroData)[1] == 10.0f) {
//			DLOG("CASE 2 - blue instructions text press start");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 534.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 440.0;
			}

		// PRESS START LOGOs ========================================

		// red press start big logo
		} else if (((float *)pVertexStreamZeroData)[0] == 85.5f &&
				   ((float *)pVertexStreamZeroData)[1] == 258.0f) {
//			DLOG("CASE 3 - red press start logo");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 427.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 220.0;
			}

		// blue press start big logo
		} else if (((float *)pVertexStreamZeroData)[0] == 512.5f &&
			       ((float *)pVertexStreamZeroData)[1] == 258.0f) {
//			DLOG("CASE 4 - blue press start logo");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 427.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 220.0;
			}

		// WIN LOGOs ==================================================

		// red WIN x390 y270
		} else if (((float *)pVertexStreamZeroData)[0] == 390.0f) {// &&
				// ((float *)pVertexStreamZeroData)[1] == 270.0f) {
//			DLOG("CASE 5 - red WIN logo");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 353.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 160.0;
			}

		// blue WIN X463 Y50
		} else if (((float *)pVertexStreamZeroData)[0] == 743.0f) {// &&
				// ((float *)pVertexStreamZeroData)[1] == 270.0f) {
//			DLOG("CASE 6 - blue WIN logo");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 353.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 160.0;
			}

		// WAIT TEXTs ==================================================

		// red WAIT FOR NEXT ROUND (&& PLEASE WAIT ?)
		} else if (((float *)pVertexStreamZeroData)[0] == 424) {// &&
				// ((float *)pVertexStreamZeroData)[1] == 40.0f) {
//			DLOG("CASE 7 - red WAIT FOR NEXT ROUND + PLEASE WAIT");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 517.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 432.0;
			}

		// blue WAIT FOR NEXT ROUND (&& PLEASE WAIT ?)
		} else if (((float *)pVertexStreamZeroData)[0] == 941.0f) {// &&
				// ((float *)pVertexStreamZeroData)[1] == 270.0f) {
//			DLOG("CASE 8 - blue WAIT FOR NEXT ROUND + PLEASE WAIT");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 517.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 432.0;
			}

		// [x] WIN TEXTs =============================================

		// red [x] WIN(s) text
		} else if (((float *)pVertexStreamZeroData)[1] == 78.0 &&
				   ((float *)pVertexStreamZeroData)[0] < 500.0f) {
//			DLOG("CASE 9 - red [x] WIN(s) text");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 353.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 388.0;
			}

		// blue [x] WIN(s) text
		} else if (((float *)pVertexStreamZeroData)[1] == 78.0f &&
				   ((float *)pVertexStreamZeroData)[0] > 500.0f) {
//			DLOG("CASE 10 - blue [x] WIN(s) text");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 353.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 388.0;
			}

		// END BGs ==================================================

		// red small end stats BG
		} else if (((float *)pVertexStreamZeroData)[0] == 51.0 &&
				   ((float *)pVertexStreamZeroData)[1] < 250.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 0.0f) {
//			DLOG("CASE 11 - red small end stats BG");
			end_bg = 4;
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 426.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 224.0;
			}

		// blue small end stats BG
		} else if (((float *)pVertexStreamZeroData)[0] == 477.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 250.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 0.0f) {
//			DLOG("CASE 12 - blue small end stats BG");
			end_bg = 3;
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 426.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 224.0;
			}

		// red winner end stats BG
		} else if (((float *)pVertexStreamZeroData)[0] == 14.0 &&
				   ((float *)pVertexStreamZeroData)[1] < 300.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 0.0f) {
//			DLOG("CASE 13 - red winner end stats BG");
			end_bg = 8;
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 426.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 176.0;
			}

		// blue winner end stats BG
		} else if (((float *)pVertexStreamZeroData)[0] == 440.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 300.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 0.0f) {
//			DLOG("CASE 14 - blue winner end stats BG");
			end_bg = 7;
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 426.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 176.0;
			}

		// NO ROTATE BGs

		// yellow small end stats BG
		} else if (((float *)pVertexStreamZeroData)[0] == 51.0 &&
				   ((float *)pVertexStreamZeroData)[1] > 250.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 480.0f) {
//			DLOG("end_bg set to 1");
			end_bg = 1;
			goto exit;

		// pink small end stats BG
		} else if (((float *)pVertexStreamZeroData)[0] == 477.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 250.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 480.0f) {
//			DLOG("end_bg set to 2");
			end_bg = 2;
			goto exit;

		// yellow winner end stats BG
		} else if (((float *)pVertexStreamZeroData)[0] == 14.0 &&
				   ((float *)pVertexStreamZeroData)[1] > 300.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 480.0f) {
//			DLOG("end_bg set to 5");
			end_bg = 5;
			goto exit;

		// pink winner end stats BG
		} else if (((float *)pVertexStreamZeroData)[0] == 440.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 300.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 480.0f) {
//			DLOG("end_bg set to 6");
			end_bg = 6;
			goto exit;
			
		// END TEXTs ================================================
		// TODO : when cyan vs yellow, bug: no rotation on cyan
		// TEST red vs yellow

		// red small end stats TEXT
		} else if (//(unsigned int)*(&pVertexStreamZeroData+40) == 4261281277 &&
				   end_bg == 4 &&
				   ((float *)pVertexStreamZeroData)[2] == 0.8f &&
				   ((float *)pVertexStreamZeroData)[0] < 426.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 240.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 0.0f) {
//			DLOG("CASE 15 - red small end stats TEXT");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 426.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 224.0;
			}

		// blue small end stats TEXT
		} else if (//(unsigned int)*(&pVertexStreamZeroData+40) == 4261281277 &&
				   end_bg == 3 &&
				   ((float *)pVertexStreamZeroData)[2] == 0.8f &&
				   ((float *)pVertexStreamZeroData)[0] > 426.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 240.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 0.0f) {
//			DLOG("CASE 16 - blue small end stats TEXT");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 426.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 224.0;
			}

		// red winner end stats TEXT
		} else if (//(unsigned int)*(&pVertexStreamZeroData+40) == 4261281277 &&
				   end_bg == 8 &&
				   ((float *)pVertexStreamZeroData)[2] == 0.8f &&
				   ((float *)pVertexStreamZeroData)[0] < 426.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 240.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 0.0f) {
//			DLOG("CASE 17 - red winner end stats TEXT");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] += 426.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 176.0;
			}

		// blue winner end stats TEXT
		} else if (//(unsigned int)*(&pVertexStreamZeroData+40) == 4261281277 &&
				   end_bg == 7 &&
				   ((float *)pVertexStreamZeroData)[2] == 0.8f &&
				   ((float *)pVertexStreamZeroData)[0] > 426.0f &&
				   ((float *)pVertexStreamZeroData)[1] < 240.0f &&
				   ((float *)pVertexStreamZeroData)[1] > 0.0f) {
//			DLOG("CASE 18 - blue winner end stats TEXT");
			for (i = 0; i < 4; i++) {
				((float *)pVertexStreamZeroData)[0+6*i] -= 426.0;
				((float *)pVertexStreamZeroData)[1+6*i] += 176.0;
			}

		// skip rotation
		} else {
			goto exit;
		}

		// do the 180 degree Z rotation
		D3DXMATRIX dat;
		D3DXMATRIX rot;
		D3DXMatrixRotationZ(&rot, 3.141592920f);
		m_pIDirect3DDevice9->GetVertexShaderConstantF(0, (float *)&dat, 4);
		rot = rot * dat;
		m_pIDirect3DDevice9->SetVertexShaderConstantF(0, (const float *)&rot, 4);
	}

	exit:
	return(m_pIDirect3DDevice9->DrawPrimitiveUP(PrimitiveType,PrimitiveCount,pVertexStreamZeroData,VertexStreamZeroStride));
}

HRESULT myIDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
	unsigned int color = ((unsigned int *)pVertexStreamZeroData)[3] & 0xFFFFFF00 >> 8;
	
	// remove bezel during game
	if (NumVertices == 36 && PrimitiveCount == 18 && (unsigned int)*(&pVertexStreamZeroData+40) == 68) {
		return D3D_OK;

	// remove bezel during ingame title screens
	} else if (NumVertices == 36 && PrimitiveCount == 18 && (unsigned int)*(&pVertexStreamZeroData+32) == 1017511936u) {
		return D3D_OK;

	//- remove ingame menu background
	} else if (NumVertices == 36 && PrimitiveCount == 18 && (unsigned int)*(&pVertexStreamZeroData+32) == 52428) {
		return D3D_OK;

	//- remove ingame menu button text 1 and 4
	} else if (NumVertices == 36 && PrimitiveCount == 18 && color == 15461355) {
		return D3D_OK;

	//- remove ingame menu button text 2
	} else if (NumVertices == 28 && PrimitiveCount == 14 && color == 15461355) {
		return D3D_OK;

	//- remove ingame menu button text 3
	} else if (NumVertices == 60 && PrimitiveCount == 30 && color == 15461355) {
		return D3D_OK;

	//- remove ingame menu buttons A B X Y icons
	} else if (NumVertices == 4 && PrimitiveCount == 2 && (
			(unsigned int)*(&pVertexStreamZeroData+36) == 1104674816u ||
			(unsigned int)*(&pVertexStreamZeroData+36) == 1065005056u ||
			(unsigned int)*(&pVertexStreamZeroData+36) == 1050779648u)) {
		return D3D_OK;

	// create a file named skip_save_popup for the ahk script to check it and press A key (this is ugly)
	} else if (NumVertices == 36 && PrimitiveCount == 18 && (unsigned int)*(&pVertexStreamZeroData+36) == 1117519872u) {
		fclose(fopen("skip_save_popup", "w"));
		return D3D_OK;

	// remove "game saved" popup text
	} else if (color == 15461355 && NumVertices == 72 && PrimitiveCount == 36) {
		return D3D_OK;

	// remove "game saved" A button
	} else if (NumVertices == 4 && PrimitiveCount == 2 && (unsigned int)*(&pVertexStreamZeroData+36) == 1107558400u) {
		return D3D_OK;

	// remove "game saved" confirm text
	} else if (NumVertices == 364 && PrimitiveCount == 182) { // WTF DID YOU DO !?
		return D3D_OK;
	}

	return(m_pIDirect3DDevice9->DrawIndexedPrimitiveUP(PrimitiveType,MinVertexIndex,NumVertices,PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData,VertexStreamZeroStride));
}

HRESULT myIDirect3DDevice9::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags)
{
    return(m_pIDirect3DDevice9->ProcessVertices( SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags));
}

HRESULT myIDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
{
    return(m_pIDirect3DDevice9->CreateVertexDeclaration( pVertexElements,ppDecl));
}

HRESULT myIDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
    return(m_pIDirect3DDevice9->SetVertexDeclaration(pDecl));
}

HRESULT myIDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
    return(m_pIDirect3DDevice9->GetVertexDeclaration(ppDecl));
}

HRESULT myIDirect3DDevice9::SetFVF(DWORD FVF)
{
    return(m_pIDirect3DDevice9->SetFVF(FVF));
}

HRESULT myIDirect3DDevice9::GetFVF(DWORD* pFVF)
{
    return(m_pIDirect3DDevice9->GetFVF(pFVF));
}

HRESULT myIDirect3DDevice9::CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader)
{
    return(m_pIDirect3DDevice9->CreateVertexShader(pFunction,ppShader));
}

HRESULT myIDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader)
{
    return(m_pIDirect3DDevice9->SetVertexShader(pShader));
}

HRESULT myIDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
    return(m_pIDirect3DDevice9->GetVertexShader(ppShader));
}

HRESULT myIDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
    return(m_pIDirect3DDevice9->SetVertexShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT myIDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{
    return(m_pIDirect3DDevice9->GetVertexShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT myIDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{
    return(m_pIDirect3DDevice9->SetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT myIDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
    return(m_pIDirect3DDevice9->GetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT myIDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
    return(m_pIDirect3DDevice9->SetVertexShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT myIDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
    return(m_pIDirect3DDevice9->GetVertexShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT myIDirect3DDevice9::SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride)
{
    return(m_pIDirect3DDevice9->SetStreamSource(StreamNumber,pStreamData,OffsetInBytes,Stride));
}

HRESULT myIDirect3DDevice9::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride)
{
    return(m_pIDirect3DDevice9->GetStreamSource(StreamNumber,ppStreamData,OffsetInBytes,pStride));
}

HRESULT myIDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber,UINT Divider)
{
    return(m_pIDirect3DDevice9->SetStreamSourceFreq(StreamNumber,Divider));
}

HRESULT myIDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber,UINT* Divider)
{
    return(m_pIDirect3DDevice9->GetStreamSourceFreq(StreamNumber,Divider));
}

HRESULT myIDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
    return(m_pIDirect3DDevice9->SetIndices(pIndexData));
}

HRESULT myIDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
    return(m_pIDirect3DDevice9->GetIndices(ppIndexData));
}

HRESULT myIDirect3DDevice9::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader)
{
    return(m_pIDirect3DDevice9->CreatePixelShader(pFunction,ppShader));
}

HRESULT myIDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader)
{
    return(m_pIDirect3DDevice9->SetPixelShader(pShader));
}

HRESULT myIDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
    return(m_pIDirect3DDevice9->GetPixelShader(ppShader));
}

HRESULT myIDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
    return(m_pIDirect3DDevice9->SetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT myIDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{
    return(m_pIDirect3DDevice9->GetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT myIDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{
    return(m_pIDirect3DDevice9->SetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT myIDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
    return(m_pIDirect3DDevice9->GetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT myIDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
    return(m_pIDirect3DDevice9->SetPixelShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT myIDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
    return(m_pIDirect3DDevice9->GetPixelShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT myIDirect3DDevice9::DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
    return(m_pIDirect3DDevice9->DrawRectPatch(Handle,pNumSegs, pRectPatchInfo));
}

HRESULT myIDirect3DDevice9::DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
    return(m_pIDirect3DDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo));
}

HRESULT myIDirect3DDevice9::DeletePatch(UINT Handle)
{
    return(m_pIDirect3DDevice9->DeletePatch(Handle));
}

HRESULT myIDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery)
{
    return(m_pIDirect3DDevice9->CreateQuery(Type,ppQuery));
}

void myIDirect3DDevice9::HideBootMenu(void)
{
	static time_t limit = time(0) + 10;
	static bool loaded = false;
	static bool check = true;
	static LPDIRECT3DTEXTURE9 imagetex;
	static LPD3DXSPRITE sprite;
	static D3DXVECTOR3 imagepos;

	if (!loaded) {
		D3DXCreateTextureFromFile(m_pIDirect3DDevice9, "loading.png", &imagetex);
		D3DXCreateSprite(m_pIDirect3DDevice9, &sprite);
		imagepos.x=0.0f;
		imagepos.y=0.0f;
		imagepos.z=0.0f;
		loaded = true;
	}

	if (check && time(0) < limit) {
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(imagetex, NULL, NULL, &imagepos, 0xFFFFFFFF);
		sprite->End();
	} else {
		check = false;
	}
}


