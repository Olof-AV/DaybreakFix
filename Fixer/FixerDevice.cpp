#include "FixerDevice.h"
#pragma comment(lib, "d3d9.lib")

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::QueryInterface(REFIID riid, void** ppvObj)
{
    return m_pDevice->QueryInterface(riid, ppvObj);
}

STDMETHODIMP_(ULONG __stdcall) FixerDevice::AddRef()
{
    return m_pDevice->AddRef();
}

STDMETHODIMP_(ULONG __stdcall) FixerDevice::Release()
{
    return m_pDevice->Release();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::TestCooperativeLevel()
{
    return m_pDevice->TestCooperativeLevel();
}

STDMETHODIMP_(UINT __stdcall) FixerDevice::GetAvailableTextureMem()
{
    return m_pDevice->GetAvailableTextureMem();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::EvictManagedResources()
{
    return m_pDevice->EvictManagedResources();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetDirect3D(IDirect3D9** ppD3D9)
{
    return m_pDevice->GetDirect3D(ppD3D9);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetDeviceCaps(D3DCAPS9* pCaps)
{
    return m_pDevice->GetDeviceCaps(pCaps);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
    return m_pDevice->GetDisplayMode(iSwapChain, pMode);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
    return m_pDevice->GetCreationParameters(pParameters);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
    return m_pDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

STDMETHODIMP_(void __stdcall) FixerDevice::SetCursorPosition(int X, int Y, DWORD Flags)
{
    m_pDevice->SetCursorPosition(X, Y, Flags);
}

STDMETHODIMP_(BOOL __stdcall) FixerDevice::ShowCursor(BOOL bShow)
{
    return m_pDevice->ShowCursor(bShow);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
    return m_pDevice->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
    return m_pDevice->GetSwapChain(iSwapChain, pSwapChain);
}

STDMETHODIMP_(UINT __stdcall) FixerDevice::GetNumberOfSwapChains()
{
    return m_pDevice->GetNumberOfSwapChains();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return m_pDevice->Reset(pPresentationParameters);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::Present(const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
    return m_pDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
    return m_pDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
    return m_pDevice->GetRasterStatus(iSwapChain, pRasterStatus);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetDialogBoxMode(BOOL bEnableDialogs)
{
    return m_pDevice->SetDialogBoxMode(bEnableDialogs);
}

STDMETHODIMP_(void __stdcall) FixerDevice::SetGammaRamp(UINT iSwapChain, DWORD Flags, const D3DGAMMARAMP* pRamp)
{
    m_pDevice->SetGammaRamp(iSwapChain, Flags, pRamp);
}

STDMETHODIMP_(void __stdcall) FixerDevice::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
    m_pDevice->GetGammaRamp(iSwapChain, pRamp);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
    if (Width == 1024 && Height == 1024 && Format == D3DFMT_L16) // Incorrect shadowmap creation detected?
    {
        Usage = D3DUSAGE_DEPTHSTENCIL; // The texture is going to be used as a shadowmap, make sure that the Usage reflects that.
        Format = D3DFMT_D16; // L16 is inappropriate for shadowmaps (luminance only), use a proper depth format instead.
    }

    return m_pDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
    return m_pDevice->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
    return m_pDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
    return m_pDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
    return m_pDevice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
    return m_pDevice->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
    return m_pDevice->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::UpdateSurface(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, const POINT* pDestPoint)
{
    return m_pDevice->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
    return m_pDevice->UpdateTexture(pSourceTexture, pDestinationTexture);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
    return m_pDevice->GetRenderTargetData(pRenderTarget, pDestSurface);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
    return m_pDevice->GetFrontBufferData(iSwapChain, pDestSurface);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::StretchRect(IDirect3DSurface9* pSourceSurface, const RECT* pSourceRect, IDirect3DSurface9* pDestSurface, const RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
    return m_pDevice->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::ColorFill(IDirect3DSurface9* pSurface, const RECT* pRect, D3DCOLOR color)
{
    return m_pDevice->ColorFill(pSurface, pRect, color);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
    return m_pDevice->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
    return m_pDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
    return m_pDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
    return m_pDevice->SetDepthStencilSurface(pNewZStencil);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
    return m_pDevice->GetDepthStencilSurface(ppZStencilSurface);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::BeginScene()
{
    return m_pDevice->BeginScene();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::EndScene()
{
    return m_pDevice->EndScene();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::Clear(DWORD Count, const D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
    return m_pDevice->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
{
    return m_pDevice->SetTransform(State, pMatrix);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
    return m_pDevice->GetTransform(State, pMatrix);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::MultiplyTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX* pMatrix)
{
    return m_pDevice->MultiplyTransform(State, pMatrix);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetViewport(const D3DVIEWPORT9* pViewport)
{
    return m_pDevice->SetViewport(pViewport);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetViewport(D3DVIEWPORT9* pViewport)
{
    return m_pDevice->GetViewport(pViewport);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetMaterial(const D3DMATERIAL9* pMaterial)
{
    return m_pDevice->SetMaterial(pMaterial);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetMaterial(D3DMATERIAL9* pMaterial)
{
    return m_pDevice->GetMaterial(pMaterial);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetLight(DWORD Index, const D3DLIGHT9* pLight)
{
    return m_pDevice->SetLight(Index, pLight);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetLight(DWORD Index, D3DLIGHT9* pLight)
{
    return m_pDevice->GetLight(Index, pLight);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::LightEnable(DWORD Index, BOOL Enable)
{
    return m_pDevice->LightEnable(Index, Enable);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetLightEnable(DWORD Index, BOOL* pEnable)
{
    return m_pDevice->GetLightEnable(Index, pEnable);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetClipPlane(DWORD Index, const float* pPlane)
{
    return m_pDevice->SetClipPlane(Index, pPlane);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetClipPlane(DWORD Index, float* pPlane)
{
    return m_pDevice->GetClipPlane(Index, pPlane);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
    return m_pDevice->SetRenderState(State, Value);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
    return m_pDevice->GetRenderState(State, pValue);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
    return m_pDevice->CreateStateBlock(Type, ppSB);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::BeginStateBlock()
{
    return m_pDevice->BeginStateBlock();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
    return m_pDevice->EndStateBlock(ppSB);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetClipStatus(const D3DCLIPSTATUS9* pClipStatus)
{
    return m_pDevice->SetClipStatus(pClipStatus);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
    return m_pDevice->GetClipStatus(pClipStatus);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
    return m_pDevice->GetTexture(Stage, ppTexture);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
    return m_pDevice->SetTexture(Stage, pTexture);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
    return m_pDevice->GetTextureStageState(Stage, Type, pValue);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
    return m_pDevice->SetTextureStageState(Stage, Type, Value);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
    return m_pDevice->GetSamplerState(Sampler, Type, pValue);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
    return m_pDevice->SetSamplerState(Sampler, Type, Value);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::ValidateDevice(DWORD* pNumPasses)
{
    return m_pDevice->ValidateDevice(pNumPasses);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY* pEntries)
{
    return m_pDevice->SetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
    return m_pDevice->GetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetCurrentTexturePalette(UINT PaletteNumber)
{
    return m_pDevice->SetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetCurrentTexturePalette(UINT* PaletteNumber)
{
    return m_pDevice->GetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetScissorRect(const RECT* pRect)
{
    return m_pDevice->SetScissorRect(pRect);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetScissorRect(RECT* pRect)
{
    return m_pDevice->GetScissorRect(pRect);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetSoftwareVertexProcessing(BOOL bSoftware)
{
    return m_pDevice->SetSoftwareVertexProcessing(bSoftware);
}

STDMETHODIMP_(BOOL __stdcall) FixerDevice::GetSoftwareVertexProcessing()
{
    return m_pDevice->GetSoftwareVertexProcessing();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetNPatchMode(float nSegments)
{
    return m_pDevice->SetNPatchMode(nSegments);
}

STDMETHODIMP_(float __stdcall) FixerDevice::GetNPatchMode()
{
    return m_pDevice->GetNPatchMode();
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
    return m_pDevice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
    return m_pDevice->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    return m_pDevice->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, const void* pIndexData, D3DFORMAT IndexDataFormat, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
    return m_pDevice->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
    return m_pDevice->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateVertexDeclaration(const D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
    return m_pDevice->CreateVertexDeclaration(pVertexElements, ppDecl);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
    return m_pDevice->SetVertexDeclaration(pDecl);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
    return m_pDevice->GetVertexDeclaration(ppDecl);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetFVF(DWORD FVF)
{
    return m_pDevice->SetFVF(FVF);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetFVF(DWORD* pFVF)
{
    return m_pDevice->GetFVF(pFVF);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateVertexShader(const DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
    return m_pDevice->CreateVertexShader(pFunction, ppShader);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetVertexShader(IDirect3DVertexShader9* pShader)
{
    return m_pDevice->SetVertexShader(pShader);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
    return m_pDevice->GetVertexShader(ppShader);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetVertexShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount)
{
    return m_pDevice->SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
    return m_pDevice->GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetVertexShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount)
{
    return m_pDevice->SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
    return m_pDevice->GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetVertexShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount)
{
    return m_pDevice->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
    return m_pDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
    return m_pDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride)
{
    return m_pDevice->GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetStreamSourceFreq(UINT StreamNumber, UINT Setting)
{
    return m_pDevice->SetStreamSourceFreq(StreamNumber, Setting);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetStreamSourceFreq(UINT StreamNumber, UINT* pSetting)
{
    return m_pDevice->GetStreamSourceFreq(StreamNumber, pSetting);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
    return m_pDevice->SetIndices(pIndexData);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
    return m_pDevice->GetIndices(ppIndexData);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreatePixelShader(const DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
    return m_pDevice->CreatePixelShader(pFunction, ppShader);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetPixelShader(IDirect3DPixelShader9* pShader)
{
    return m_pDevice->SetPixelShader(pShader);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
    return m_pDevice->GetPixelShader(ppShader);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetPixelShaderConstantF(UINT StartRegister, const float* pConstantData, UINT Vector4fCount)
{
    return m_pDevice->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
    return m_pDevice->GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetPixelShaderConstantI(UINT StartRegister, const int* pConstantData, UINT Vector4iCount)
{
    return m_pDevice->SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
    return m_pDevice->GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::SetPixelShaderConstantB(UINT StartRegister, const BOOL* pConstantData, UINT BoolCount)
{
    return m_pDevice->SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
    return m_pDevice->GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::DrawRectPatch(UINT Handle, const float* pNumSegs, const D3DRECTPATCH_INFO* pRectPatchInfo)
{
    return m_pDevice->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::DrawTriPatch(UINT Handle, const float* pNumSegs, const D3DTRIPATCH_INFO* pTriPatchInfo)
{
    return m_pDevice->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::DeletePatch(UINT Handle)
{
    return m_pDevice->DeletePatch(Handle);
}

STDMETHODIMP_(HRESULT __stdcall) FixerDevice::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
    return m_pDevice->CreateQuery(Type, ppQuery);
}
