#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DirectXTK.lib")

#include <windows.h>
#include <d3d11_2.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <SpriteFont.h>
#include <string>

#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"
#include "defines.h"
#include "LoadModel.h"
#include "DXInput.h"
#include "cameraclass.h"
#include "positionclass.h"
#include "debug_render.h"

using namespace DirectX;

//--------------------------------------------------------------------------------------
// Defines
//--------------------------------------------------------------------------------------
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------

// Setup our lighting parameters
//Diffuse Light
XMFLOAT4 ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);

XMFLOAT4 vLightDirs[2] =
{
	XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f),
	XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f),
};
XMFLOAT4 vLightColors[2] =
{
	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
	XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f),
};
XMFLOAT4 tempLightDir[2], tempLightColor[2];

//Point Light
XMFLOAT4 pointLight_Color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
XMFLOAT4 pointLight_Position = XMFLOAT4(0.0f, 0.0f, -1.0f, 0.0);
XMFLOAT3 pointLight_Attenuation = XMFLOAT3(0.0f, 0.5f, 0.0f);
float pointLight_Range = 100.0f;
//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
HINSTANCE               g_hInst = nullptr;
HWND                    g_hWnd = nullptr;
D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device*           g_pd3dDevice = nullptr;
ID3D11DeviceContext*    g_pImmediateContext = nullptr;
IDXGISwapChain*         g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;

ID3D11Texture2D*        g_pDepthStencil = nullptr;
ID3D11DepthStencilView* g_pDepthStencilView = nullptr;
ID3D11DepthStencilState*g_pDepthStencilState_enable = nullptr;
ID3D11DepthStencilState*g_pDepthStencilState_disable = nullptr;

ID3D11VertexShader*     g_pVertexShader = nullptr;
ID3D11PixelShader*      g_pPixelShader = nullptr;
ID3D11InputLayout*      g_pVertexLayout = nullptr;

ID3D11Buffer*           g_pVertexBuffer = nullptr;
ID3D11Buffer*           g_pIndexBuffer = nullptr;
ID3D11Buffer*           g_pConstantBuffer = nullptr;

ID3D11VertexShader*      g_pVertexShader_DR = nullptr;
ID3D11PixelShader*       g_pPixelShader_DR = nullptr;
ID3D11InputLayout*		g_pVertexLayout_DR = nullptr;
ID3D11Buffer*           g_pConstantBuffer_DR = nullptr;

ID3D11VertexShader*		g_pVertexShader_SkinnedAnimation = nullptr;
ID3D11PixelShader*		g_pPixelShader_SkinnedAnimation = nullptr;
ID3D11InputLayout*		g_pVertexLayout_SkinnedAnimation = nullptr;
ID3D11Buffer*			g_pConstantBuffer_SkinnedAnimation = nullptr;

//solid cube pixel shader
ID3D11PixelShader*      g_pPixelShaderSolid = nullptr;
ID3D11PixelShader*		g_pPixelShaderFont = nullptr;

//cube texture
ID3D11ShaderResourceView*	g_pCubesTexture = nullptr;
ID3D11SamplerState*			g_pCubeTexSamplerState = nullptr;
ID3D11SamplerState*			g_pTexSamplerState_Mirror = nullptr;

//Rener States
ID3D11RasterizerState*	g_pRS_WireFrame;
ID3D11RasterizerState*	g_pRS_Solid;

// Blending
ID3D11BlendState*		g_pBS_Transparency;
ID3D11BlendState*		g_pBS_Transparency_Font;
ID3D11RasterizerState*	g_pRS_CCWcullMode;
ID3D11RasterizerState*	g_pRS_CWcullMode;

//Timer Variables
float countsPerSecond = 0.0;
__int64 CounterStart = 0;

int frameCount = 0;
int fps = 0;

__int64 frameTimeOld = 0;
float frameTime;

//Font
std::unique_ptr<SpriteBatch> spriteBatch;
std::unique_ptr<SpriteFont> spriteFont;
LONG mouse_X, mouse_Y;

// global variables
HRESULT hr;
UINT width;
UINT height;
float t = 0.01f;

XMMATRIX                g_World;
XMMATRIX                g_View;
XMMATRIX                g_Projection;
XMVECTOR				g_camPos, g_camTar, g_camUp;


// Model - Idle / Mega character ///////////////////////////////////////////////////////
LoadModel				*g_pModel_Mage;
ID3D11Buffer			*g_pVertexBuffer_Mage;
ID3D11Buffer			*g_pIndexBuffer_Mage;
ID3D11ShaderResourceView*	g_pTexture_Mage = nullptr;
ID3D11ShaderResourceView*	g_pTexture_Bump_Mage = nullptr;
ID3D11ShaderResourceView*	g_pTexture_Specular_Mage = nullptr;
XMMATRIX				g_World_Mega;

// Keyboard ////////////////////////////////////////////////////////////////////////////
DXINPUT					*g_pDXInput;
bool isCursorShown = false;

// Camera //////////////////////////////////////////////////////////////////////////////
CameraClass				*g_pCamera;
PositionClass			*g_pPosition;
float					mouseDeltaX, mouseDeltaY;

// DEBUG RENDER ////////////////////////////////////////////////////////////////////////
DEBUG_RENDER			*g_pDebugRender_Grid;

	// Animation
	DEBUG_RENDER		*g_pDebugRender_Animation;
	DEBUG_RENDER		*g_pDebugRender_AnimationAxis;

	bool				g_isAnimationStart = false;

	XMMATRIX			g_World_Mega_Skeleton;
	float				g_tAnimation_Start, g_tAnimation_Now;
	float				g_animationSpeed = 1.0f;

	float				g_tSkinnedAnimation_Start, g_tSkinnedAnimation_Now;
	float				g_skinnedAnimationSpeed = 1.0f;

	XMMATRIX			*g_pInverseJointMatrix;

//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void Update(float time);
void Render(float time);
void StartTimer();
float GetTime();
float GetFrameTime();
void ProcessDXInput(float time);
void UpdateCamera();

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	if (FAILED(InitDevice()))
	{
		CleanupDevice();
		return 0;
	}

	g_pDXInput = new DXINPUT();
	if (!g_pDXInput->InitDirectInput(g_hWnd, g_hInst, width, height))
	{
		MessageBox(0, L"Scene Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			frameCount++;
			if (GetTime() > 1.0f)
			{
				fps = frameCount;
				frameCount = 0;
				StartTimer();
			}

			frameTime = GetFrameTime();

			g_pDXInput->DetectInput();
			Update(frameTime);
			Render(frameTime);
		}
	}

	CleanupDevice();

	return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = L"ForTheDreamOFGameDevelopment";
	wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	
	if (!RegisterClassEx(&wndClass))
		return E_FAIL;

	g_hInst = hInstance;
	RECT rc = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	
	g_hWnd = CreateWindow(L"ForTheDreamOfGameDevelopment", L"My Project",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		nullptr, nullptr, hInstance, nullptr);

	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
	hr = S_OK;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	width = rc.right - rc.left;
	height = rc.bottom - rc.top;

	//Describe our SwapChain Buffer
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = width;
	bufferDesc.Height = height;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//Describe our SwapChain
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = g_hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//Create our SwapChain
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &g_pSwapChain, &g_pd3dDevice, NULL, &g_pImmediateContext);
	if (FAILED(hr))
		return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return hr;

	hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	hr = g_pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &g_pDepthStencil);
	if (FAILED(hr))
		return hr;

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = depthStencilDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil, &depthStencilViewDesc, &g_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);

	D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
	// Clear the second depth stencil state before setting the parameters.
	ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

	// Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is 
	// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
	depthDisabledStencilDesc.DepthEnable = true;
	depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisabledStencilDesc.StencilEnable = true;
	depthDisabledStencilDesc.StencilReadMask = 0xFF;
	depthDisabledStencilDesc.StencilWriteMask = 0xFF;
	depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the state using the device.
	hr = g_pd3dDevice->CreateDepthStencilState(&depthDisabledStencilDesc, &g_pDepthStencilState_enable);
	if (FAILED(hr))
	{
		return hr;
	}
	depthDisabledStencilDesc.DepthEnable = false;
	hr = g_pd3dDevice->CreateDepthStencilState(&depthDisabledStencilDesc, &g_pDepthStencilState_disable);
	if (FAILED(hr))
	{
		return hr;
	}

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports(1, &vp);


	// Compile the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShaderFromFile(L"Effects.fx", "VS", "vs_4_0", &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
	// Create the vertex shader
	hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &g_pVertexShader);
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	//Debug Render Vertex Shader
	ID3DBlob* pVSBlob_DR = nullptr;
	hr = CompileShaderFromFile(L"DebugRenderShader.fx", "VS", "vs_4_0", &pVSBlob_DR);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
	hr = g_pd3dDevice->CreateVertexShader(pVSBlob_DR->GetBufferPointer(), pVSBlob_DR->GetBufferSize(), nullptr, &g_pVertexShader_DR);
	if (FAILED(hr))
	{
		pVSBlob_DR->Release();
		return hr;
	}

	//Skinned Animation Vertex Shader
	ID3DBlob* pVSBlob_SA = nullptr;
	hr = CompileShaderFromFile(L"SkinnedAnimationShader.fx", "VS", "vs_4_0", &pVSBlob_SA);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The Skinned Animation Shader FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
	hr = g_pd3dDevice->CreateVertexShader(pVSBlob_SA->GetBufferPointer(), pVSBlob_SA->GetBufferSize(), nullptr, &g_pVertexShader_SkinnedAnimation);
	if (FAILED(hr))
	{
		pVSBlob_SA->Release();
		return hr;
	}

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShaderFromFile(L"Effects.fx", "PS", "ps_4_0", &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}	
	// Create the pixel shader
	hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
	if (FAILED(hr))
	{
		pPSBlob->Release();
		return hr;
	}

	// Compile the debug render pixel shader
	ID3DBlob* pPSBlob_DR = nullptr;
	hr = CompileShaderFromFile(L"DebugRenderShader.fx", "PS", "ps_4_0", &pPSBlob_DR);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
	// Create the pixel shader
	hr = g_pd3dDevice->CreatePixelShader(pPSBlob_DR->GetBufferPointer(), pPSBlob_DR->GetBufferSize(), nullptr, &g_pPixelShader_DR);
	if (FAILED(hr))
	{
		pPSBlob_DR->Release();
		return hr;
	}

	// compile the skinned animation pixel shader
	ID3DBlob* pPSBlob_SA = nullptr;
	hr = CompileShaderFromFile(L"SkinnedAnimationShader.fx", "PS", "ps_4_0", &pPSBlob_SA);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The Skinned Animation FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
	hr = g_pd3dDevice->CreatePixelShader(pPSBlob_SA->GetBufferPointer(), pPSBlob_SA->GetBufferSize(), nullptr, &g_pPixelShader_SkinnedAnimation);
	if (FAILED(hr))
	{
		pPSBlob_SA->Release();
		return hr;
	}

	// compile the soild pixel shader
	ID3DBlob* pD2DPSBlob = nullptr;
	hr = CompileShaderFromFile(L"Effects.fx", "PSSolid", "ps_4_0", &pD2DPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
	hr = g_pd3dDevice->CreatePixelShader(pD2DPSBlob->GetBufferPointer(), pD2DPSBlob->GetBufferSize(), nullptr, &g_pPixelShaderSolid);
	if(FAILED(hr))
	{
		pD2DPSBlob->Release();
		return hr;
	}

	ID3DBlob* pPSBlob_Font = nullptr;
	hr = CompileShaderFromFile(L"Effects.fx", "PSFont", "ps_4_0", &pPSBlob_Font);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
	hr = g_pd3dDevice->CreatePixelShader(pPSBlob_Font->GetBufferPointer(), pPSBlob_Font->GetBufferSize(), nullptr, &g_pPixelShaderFont);
	if (FAILED(hr))
	{
		pPSBlob_Font->Release();
		return hr;
	}

	// Loading Models ////////////////////////////////////////////////////////////////////////////////
	/* load mage model */
	g_pModel_Mage = new LoadModel();
	if (!g_pModel_Mage)
	{
		return S_FALSE;
	}
	g_pModel_Mage->InitializeModel("./Resources/Fbx/Run.dat");

	D3D11_BUFFER_DESC vertexBufferDesc_mage;
	ZeroMemory(&vertexBufferDesc_mage, sizeof(vertexBufferDesc_mage));

	vertexBufferDesc_mage.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc_mage.ByteWidth = sizeof(SimpleVertex) * g_pModel_Mage->getNumOfVertices();
	vertexBufferDesc_mage.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc_mage.CPUAccessFlags = 0;
	vertexBufferDesc_mage.MiscFlags = 0;
	vertexBufferDesc_mage.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData_mage;
	ZeroMemory(&vertexBufferData_mage, sizeof(vertexBufferData_mage));
	vertexBufferData_mage.pSysMem = g_pModel_Mage->getModelContent();
	hr = g_pd3dDevice->CreateBuffer(&vertexBufferDesc_mage, &vertexBufferData_mage, &g_pVertexBuffer_Mage);
	if (FAILED(hr))
		return hr;

	D3D11_BUFFER_DESC indexBufferDesc_mage;
	ZeroMemory(&indexBufferDesc_mage, sizeof(indexBufferDesc_mage));

	indexBufferDesc_mage.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc_mage.ByteWidth = sizeof(unsigned long) * g_pModel_Mage->getNumOfIndices();
	indexBufferDesc_mage.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc_mage.CPUAccessFlags = 0;
	indexBufferDesc_mage.MiscFlags = 0;
	indexBufferDesc_mage.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData_mage;
	ZeroMemory(&indexBufferData_mage, sizeof(indexBufferData_mage));
	indexBufferData_mage.pSysMem = g_pModel_Mage->getModelIndices();
	hr = g_pd3dDevice->CreateBuffer(&indexBufferDesc_mage, &indexBufferData_mage, &g_pIndexBuffer_Mage);
	if (FAILED(hr))
		return hr;

	int numOfJointMatrix = (int)g_pModel_Mage->GetModelAnimationJoint().size();
	g_pInverseJointMatrix = new XMMATRIX[numOfJointMatrix];
	for (int i = 0; i < numOfJointMatrix; i++)
	{
		XMMATRIX temp;

		temp = XMMatrixSet((float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.x1, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.x2, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.x3, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.x4,
						   (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.y1, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.y2, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.y3, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.y4,
						   (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.z1, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.z2, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.z3, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.z4,
						   (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.w1, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.w2, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.w3, (float)g_pModel_Mage->GetModelAnimationJoint()[i].myMatrix.w4);

		g_pInverseJointMatrix[i] = XMMatrixInverse(&XMMatrixDeterminant(temp), temp);
	}

	/* load cube model */
	// Create vertex buffer
	SimpleVertex vertices[] =
	{
		// Front Face
		SimpleVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),

		// Back Face
		SimpleVertex(-1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f,  1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(-1.0f,  1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,-1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),

		// Top Face
		SimpleVertex(-1.0f, 1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(-1.0f, 1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f, 1.0f,  1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f, 1.0f, -1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),

		// Bottom Face
		SimpleVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(-1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),

		// Left Face
		SimpleVertex(-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,-1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),

		// Right Face
		SimpleVertex(1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
		SimpleVertex(1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
					0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f),
	};

	// Create index buffer
	WORD indices[] =
	{
		// Front Face
		0,  1,  2,
		0,  2,  3,

		// Back Face
		4,  5,  6,
		4,  6,  7,

		// Top Face
		8,  9, 10,
		8, 10, 11,

		// Bottom Face
		12, 13, 14,
		12, 14, 15,

		// Left Face
		16, 17, 18,
		16, 18, 19,

		// Right Face
		20, 21, 22,
		20, 22, 23
	};

	//Initialize Vertex Buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(SimpleVertex) * 24;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;
	hr = g_pd3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &g_pVertexBuffer);
	if (FAILED(hr))
		return hr;

	//Initialize Index Buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(WORD) * 36;        // 36 vertices needed for 12 triangles in a triangle list
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData;
	ZeroMemory(&indexBufferData, sizeof(indexBufferData));
	indexBufferData.pSysMem = indices;
	hr = g_pd3dDevice->CreateBuffer(&indexBufferDesc, &indexBufferData, &g_pIndexBuffer);
	if (FAILED(hr))
		return hr;

	g_pDebugRender_Grid = new DEBUG_RENDER;
	if (!g_pDebugRender_Grid)
	{
		return S_FALSE;
	}

	hr = g_pDebugRender_Grid->Initialize(g_pd3dDevice);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, L"Could not initialize the debug render object.", L"Error", MB_OK);
		return S_FALSE;
	}

	g_pDebugRender_Animation = new DEBUG_RENDER;
	if (!g_pDebugRender_Animation)
	{
		return S_FALSE;
	}
	hr = g_pDebugRender_Animation->Initialize(g_pd3dDevice);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, L"Could not initialize the debug render object.", L"Error", MB_OK);
		return S_FALSE;
	}

	g_pDebugRender_AnimationAxis = new DEBUG_RENDER;
	if (!g_pDebugRender_AnimationAxis)
	{
		return S_FALSE;
	}
	hr = g_pDebugRender_AnimationAxis->Initialize(g_pd3dDevice);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, L"Could not initialize the debug render object.", L"Error", MB_OK);
		return S_FALSE;
	}

	//Create Grids
#if 1
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -12.0f, 1.0f), XMVectorSet(-12.0f, 0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-11.0f, 0.0f, -12.0f, 1.0f), XMVectorSet(-11.0f, 0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-10.0f, 0.0f, -12.0f, 1.0f), XMVectorSet(-10.0f, 0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-9.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-9.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-8.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-8.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-7.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-7.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-6.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-6.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-5.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-5.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-4.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-4.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-3.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-3.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-2.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-2.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-1.0f,  0.0f, -12.0f, 1.0f), XMVectorSet(-1.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 0.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 0.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 1.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 1.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 2.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 2.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 3.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 3.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 4.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 4.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 5.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 5.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 6.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 6.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 7.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 7.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 8.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 8.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 9.0f,  0.0f, -12.0f, 1.0f), XMVectorSet( 9.0f,  0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 10.0f, 0.0f, -12.0f, 1.0f), XMVectorSet( 10.0f, 0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 11.0f, 0.0f, -12.0f, 1.0f), XMVectorSet( 11.0f, 0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet( 12.0f, 0.0f, -12.0f, 1.0f), XMVectorSet( 12.0f, 0.0f, 12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -12.0f, 1.0f), XMVectorSet(12.0f, 0.0f, -12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -11.0f, 1.0f), XMVectorSet(12.0f, 0.0f, -11.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -10.0f, 1.0f), XMVectorSet(12.0f, 0.0f, -10.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -9.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -9.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -8.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -8.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -7.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -7.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -6.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -6.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -5.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -5.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -4.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -4.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -3.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -3.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -2.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -2.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f, -1.0f,  1.0f), XMVectorSet(12.0f, 0.0f, -1.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  0.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  0.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  1.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  1.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  2.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  2.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  3.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  3.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  4.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  4.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  5.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  5.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  6.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  6.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  7.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  7.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  8.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  8.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  9.0f,  1.0f), XMVectorSet(12.0f, 0.0f,  9.0f,  1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  10.0f, 1.0f), XMVectorSet(12.0f, 0.0f,  10.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  11.0f, 1.0f), XMVectorSet(12.0f, 0.0f,  11.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
	g_pDebugRender_Grid->add_line(g_pd3dDevice, XMVectorSet(-12.0f, 0.0f,  12.0f, 1.0f), XMVectorSet(12.0f, 0.0f,  12.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f));
#endif

	//Initialize Joints and Axes info
	for (int i = 0; i < g_pModel_Mage->GetModelAnimationJoint().size(); i++)
	{
		float x, y, z, w;
		float px, py, pz, pw;

		x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f;
		px = 0.0f; py = 0.0f; pz = 0.0f; pw = 0.0f;

		int parentIndex = g_pModel_Mage->GetModelAnimationJoint()[i].mParentIndex;
		if (parentIndex != -1)
		{
			g_pDebugRender_Animation->add_line_animation(g_pd3dDevice, XMVectorSet(x, y, z, w), XMVectorSet(px, py, pz, pw), //coordinates
				XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f), (float)i, (float)parentIndex); //Colors
		}
		//else
		//{
		//	g_pDebugRender_Animation->add_line_animation(g_pd3dDevice, XMVectorSet(x, y, z, w), XMVectorSet(px, py, pz, pw), //coordinates
		//		XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f), (float)i, (float)i); //Colors
		//}

		g_pDebugRender_AnimationAxis->add_line_animation(g_pd3dDevice, XMVectorSet(x, y, z, w), XMVectorSet(x + 0.25f, y, z, w),
			XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f), (float)i, (float)i);
		g_pDebugRender_AnimationAxis->add_line_animation(g_pd3dDevice, XMVectorSet(x, y, z, w), XMVectorSet(x, y + 0.25f, z, w),
			XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f), (float)i, (float)i);
		g_pDebugRender_AnimationAxis->add_line_animation(g_pd3dDevice, XMVectorSet(x, y, z, w), XMVectorSet(x, y, z - 0.25f, w),
			XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f), (float)i, (float)i);
	}

	// Create the constant buffer
	D3D11_BUFFER_DESC constantBufferDesc;
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;
	hr = g_pd3dDevice->CreateBuffer(&constantBufferDesc, nullptr, &g_pConstantBuffer);
	if (FAILED(hr))
		return hr;

	// Create the debug render constant buffer
	D3D11_BUFFER_DESC constantBufferDesc_DR;
	constantBufferDesc_DR.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc_DR.ByteWidth = sizeof(ConstantBuffer_DR);
	constantBufferDesc_DR.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc_DR.CPUAccessFlags = 0;
	constantBufferDesc_DR.MiscFlags = 0;
	hr = g_pd3dDevice->CreateBuffer(&constantBufferDesc_DR, nullptr, &g_pConstantBuffer_DR);
	if (FAILED(hr))
		return hr;

	// Create the Skinned Animation constant buffer
	D3D11_BUFFER_DESC constantBufferDesc_SA;
	constantBufferDesc_SA.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc_SA.ByteWidth = sizeof(ConstantBuffer_SkinnedAnimation);
	constantBufferDesc_SA.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc_SA.CPUAccessFlags = 0;
	constantBufferDesc_SA.MiscFlags = 0;
	hr = g_pd3dDevice->CreateBuffer(&constantBufferDesc_SA, nullptr, &g_pConstantBuffer_SkinnedAnimation);
	if (FAILED(hr))
		return hr;

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "VERTEXCOLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 76, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(), &g_pVertexLayout);
	pVSBlob->Release();
	if (FAILED(hr))
		return hr;

	// Define debug render input layout
	D3D11_INPUT_ELEMENT_DESC layout_DR[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "JOINTINDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements_DR = ARRAYSIZE(layout_DR);

	// Create the input layout
	hr = g_pd3dDevice->CreateInputLayout(layout_DR, numElements_DR, pVSBlob_DR->GetBufferPointer(),
		pVSBlob_DR->GetBufferSize(), &g_pVertexLayout_DR);
	pVSBlob_DR->Release();
	if (FAILED(hr))
		return hr;

	// Define Skinned Animation input layout
	D3D11_INPUT_ELEMENT_DESC layout_SA[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "VERTEXCOLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 64, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 76, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		
		{ "JOINTINDEX", 0, DXGI_FORMAT_R32G32B32A32_SINT, 0, 88, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 104, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements_SA = ARRAYSIZE(layout_SA);

	// Create the input layout
	hr = g_pd3dDevice->CreateInputLayout(layout_SA, numElements_SA, pVSBlob_SA->GetBufferPointer(),
		pVSBlob_SA->GetBufferSize(), &g_pVertexLayout_SkinnedAnimation);
	pVSBlob_SA->Release();
	if (FAILED(hr))
		return hr;

	// Initialize Textures ////////////////////////////////////////////////////////////////////////////

	// Initialize the cube texture shader resource view
	//D3D11_BUFFER_DESC cubeTextureDesc = {};
	//hr = CreateDDSTextureFromFile(g_pd3dDevice, L"./Resources/braynzar.dds", nullptr, &g_pCubesTexture);
	//if (FAILED(hr))
	//	return hr;

	hr = CreateWICTextureFromFile(g_pd3dDevice, L"./Resources/Texture/redbox.jpg", nullptr, &g_pCubesTexture, 0);
	if (FAILED(hr))
		return hr;
	hr = CreateWICTextureFromFile(g_pd3dDevice, L"./Resources/Texture/PPG_3D_Player_D.png", nullptr, &g_pTexture_Mage, 0);
	if (FAILED(hr))
		return hr;
	hr = CreateWICTextureFromFile(g_pd3dDevice, L"./Resources/Texture/PPG_3D_Player_N.png", nullptr, &g_pTexture_Bump_Mage, 0);
	if (FAILED(hr))
		return hr;
	hr = CreateWICTextureFromFile(g_pd3dDevice, L"./Resources/Texture/PPG_3D_Player_spec.png", nullptr, &g_pTexture_Specular_Mage, 0);
	if (FAILED(hr))
		return hr;

	// Initialize the cube texture sampler state /////////////////////////////////////////////////////
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pCubeTexSamplerState);
	if (FAILED(hr))
		return hr;

	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;

	hr = g_pd3dDevice->CreateSamplerState(&sampDesc, &g_pTexSamplerState_Mirror);
	if (FAILED(hr))
		return hr;

	// Initialize the Rasterizer State buffers
	D3D11_RASTERIZER_DESC rsDesc;
	ZeroMemory(&rsDesc, sizeof(D3D11_RASTERIZER_DESC));
	rsDesc.FillMode = D3D11_FILL_WIREFRAME;
	rsDesc.CullMode = D3D11_CULL_NONE;
	hr = g_pd3dDevice->CreateRasterizerState(&rsDesc, &g_pRS_WireFrame);
	if (FAILED(hr))
		return hr;

	rsDesc.FillMode = D3D11_FILL_SOLID;
	hr = g_pd3dDevice->CreateRasterizerState(&rsDesc, &g_pRS_Solid);
	if (FAILED(hr))
		return hr;

	// Initialize Blend Variables (Buffers) //////////////////////////////////////////////////////////
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	D3D11_RENDER_TARGET_BLEND_DESC rtbDesc;
	rtbDesc.BlendEnable = true;
	rtbDesc.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbDesc.DestBlend = D3D11_BLEND_BLEND_FACTOR;
	rtbDesc.BlendOp = D3D11_BLEND_OP_ADD;
	rtbDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbDesc.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbDesc;

	g_pd3dDevice->CreateBlendState(&blendDesc, &g_pBS_Transparency);
	rtbDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	g_pd3dDevice->CreateBlendState(&blendDesc, &g_pBS_Transparency_Font);

	//Create the counter clockwise and clockwise culling states
	D3D11_RASTERIZER_DESC cmDesc;
	ZeroMemory(&cmDesc, sizeof(D3D11_RASTERIZER_DESC));

	cmDesc.FillMode = D3D11_FILL_SOLID;
	cmDesc.CullMode = D3D11_CULL_BACK;

	cmDesc.FrontCounterClockwise = true;
	hr = g_pd3dDevice->CreateRasterizerState(&cmDesc, &g_pRS_CCWcullMode);
	if (FAILED(hr))
		return hr;
	cmDesc.FrontCounterClockwise = false;
	hr = g_pd3dDevice->CreateRasterizerState(&cmDesc, &g_pRS_CWcullMode);
	if (FAILED(hr))
		return hr;

	//Initialize Font
	spriteBatch = std::make_unique<SpriteBatch>(g_pImmediateContext);
	spriteFont = std::make_unique<SpriteFont>(g_pd3dDevice, L"Resources\\Fonts\\TimesNewRoman_16.spritefont");

	//Initialize Camera
	g_pCamera = new CameraClass;
	if (!g_pCamera)
	{
		return S_FALSE;
	}

	g_camPos = XMVectorSet(0.0f, 0.0f, -8.0f, 0.0f);
	g_camTar = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	g_camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	g_pCamera->CreateProjectionMatrix(0.4f*3.14f, width / (FLOAT)height, 0.01f, 1000.0f);
	g_pCamera->SetPosition(&g_camPos);
	g_pCamera->SetLookAt(&g_camTar);
	g_pCamera->Update();

	g_View = *g_pCamera->GetViewMatrix();
	g_Projection = *g_pCamera->GetProjectionMatrix();

	g_pPosition = new PositionClass;
	if (!g_pPosition)
	{
		return S_FALSE;
	}

	mouseDeltaX = 0.0f;
	mouseDeltaY = 0.0f;

	// Initialize the world matrix /////////////////////////////////////////////////////////////////////
	g_World = XMMatrixIdentity();

	g_World_Mega = XMMatrixIdentity() * XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), XMConvertToRadians(180.0f)) * XMMatrixTranslation(0.0f, -2.5f, 0.0f);

	g_World_Mega_Skeleton = XMMatrixIdentity() * XMMatrixTranslation(5.0f, -2.5f, 0.0f);

	g_tAnimation_Now = 0.0f;		
	g_tAnimation_Start = (float)GetTickCount64();

	g_tSkinnedAnimation_Now = 0.0f;
	g_tSkinnedAnimation_Start = (float)GetTickCount64();

	return S_OK;
}

void StartTimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = float(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart = frequencyCount.QuadPart;
}

float GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return float(currentTime.QuadPart - CounterStart) / countsPerSecond;
}

float GetFrameTime()
{
	LARGE_INTEGER currentTime;
	__int64 tickCount;
	QueryPerformanceCounter(&currentTime);

	tickCount = currentTime.QuadPart - frameTimeOld;
	frameTimeOld = currentTime.QuadPart;

	if (tickCount < 0)
		tickCount = 0;

	return float(tickCount) / countsPerSecond;
}

void ProcessDXInput(float time)
{
	bool keyDown = false;

	if (g_pDXInput->IsKey_Esc_Pressed())
	{
		PostMessage(g_hWnd, WM_DESTROY, 0, 0);
	}

	if (mouse_X != g_pDXInput->GetMouseX())
	{
		mouse_X = g_pDXInput->GetMouseX();
	}
	if (mouse_Y != g_pDXInput->GetMouseY())
	{
		mouse_Y = g_pDXInput->GetMouseY();
	}

	mouseDeltaX = g_pDXInput->GetMouseDeltaX();
	mouseDeltaY = g_pDXInput->GetMouseDeltaY();

	g_pPosition->SetFrameTime(time);

	keyDown = g_pDXInput->IsKey_SPACE_Pressed();
	g_pPosition->GoUp(keyDown);

	keyDown = g_pDXInput->IsKey_LCTR_Pressed();
	g_pPosition->GoDown(keyDown);

	keyDown = g_pDXInput->IsKey_W_Pressed();
	g_pPosition->GoForward(keyDown);

	keyDown = g_pDXInput->IsKey_S_Pressed();
	g_pPosition->GoBack(keyDown);

	keyDown = g_pDXInput->IsKey_A_Pressed();
	g_pPosition->GoLeft(keyDown);

	keyDown = g_pDXInput->IsKey_D_Pressed();
	g_pPosition->GoRight(keyDown);

	keyDown = g_pDXInput->IsKey_Q_Pressed();
	g_pPosition->TurnLeft(keyDown);
	
	keyDown = g_pDXInput->IsKey_E_Pressed();
	g_pPosition->TurnRight(keyDown);
	
	keyDown = g_pDXInput->IsKey_R_Pressed();
	g_pPosition->LookUpward(keyDown);
	
	keyDown = g_pDXInput->IsKey_F_Pressed();
	g_pPosition->LookDownward(keyDown);

	// Mega Skeleton //
	keyDown = g_pDXInput->IsKey_NUMPAD_8_Pressed();
	if (keyDown)
	{
		g_World_Mega_Skeleton *= XMMatrixTranslation(0.0f, 0.0f, 0.01f);
	}

	keyDown = g_pDXInput->IsKey_NUMPAD_5_Pressed();
	if (keyDown)
	{
		g_World_Mega_Skeleton *= XMMatrixTranslation(0.0f, 0.0f, -0.01f);
	}

	if (g_pDXInput->IsKey_UP_Pressed())
	{
		g_animationSpeed += GetTime() * 0.001f;
		g_skinnedAnimationSpeed = g_animationSpeed;
		if (g_animationSpeed >= 2.0f)
		{
			g_animationSpeed = 2.0f;
			g_skinnedAnimationSpeed = 2.0f;
		}
	}
	if (g_pDXInput->IsKey_DOWN_Pressed())
	{
		g_animationSpeed -= GetTime() * 0.001f;
		g_skinnedAnimationSpeed = g_animationSpeed;
		if (g_animationSpeed < 0)
		{
			g_animationSpeed = 0;
			g_skinnedAnimationSpeed = 0;
		}
	}
}

void UpdateCamera()
{
	g_pCamera->Strafe(g_pPosition->GetRightSpeed() - g_pPosition->GetLeftSpeed());
	g_pCamera->MoveUp(g_pPosition->GetUpSpeed() - g_pPosition->GetDownSpeed());
	g_pCamera->MoveForward(g_pPosition->GetForwardSpeed() - g_pPosition->GetBackwardSpeed());
	g_pCamera->Pitch((float)XMConvertToRadians(g_pPosition->GetLookdownSpeed() - g_pPosition->GetLookupSpeed() + mouseDeltaY * 0.1f));
	g_pCamera->Yaw((float)XMConvertToRadians(g_pPosition->GetRightTurnSpeed() - g_pPosition->GetLeftTurnSpeed() + mouseDeltaX * 0.1f));

	g_pCamera->Update();
	g_View = *g_pCamera->GetViewMatrix();
	g_Projection = *g_pCamera->GetProjectionMatrix();
}

//--------------------------------------------------------------------------------------
// Render the frame
//--------------------------------------------------------------------------------------
void Update(float time)
{
	ProcessDXInput(time);
	UpdateCamera();

	t += 1.0f * time;
	if (t > 6.28f)
		t = 0.0f;

	// Reset the tempLight color and direction
	for (int i = 0; i < 2; i++)
	{
		tempLightDir[i] = vLightDirs[i];
		tempLightColor[i] = vLightColors[i];
	}

	// Rotate the second light around the origin
	XMMATRIX mRotate = XMMatrixRotationY(-2.0f * t);
	XMVECTOR vLightDir = XMLoadFloat4(&tempLightDir[1]);
	vLightDir = XMVector3Transform(vLightDir, mRotate);
	XMStoreFloat4(&tempLightDir[1], vLightDir);
}

void Render(float frameTime)
{
	// Clear the back buffer
	float color[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, color);
	// Clear the depth buffer to 1.0 (max depth)
	g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	//Reset the blend state
	g_pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);


	g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer_Mage, &stride, &offset);
	// Set index buffer
	g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer_Mage, DXGI_FORMAT_R32_UINT, 0);
	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Render the character
	ConstantBuffer cb1;
	cb1.mWorld = XMMatrixTranspose(g_World_Mega);
	cb1.mView = XMMatrixTranspose(g_View);
	cb1.mProjection = XMMatrixTranspose(g_Projection);

	cb1.ambient = ambient;
	cb1.vLightDir[0] = tempLightDir[0];
	cb1.vLightDir[1] = tempLightDir[1];
	cb1.vLightColor[0] = tempLightColor[0];
	cb1.vLightColor[1] = tempLightColor[1];
	cb1.vOutputColor = XMFLOAT4(0, 0, 0, 0);
	
	cb1.vPointLightPos = pointLight_Position;
	cb1.vPointLightColor = pointLight_Color;
	cb1.vPointLightAttenuation = pointLight_Attenuation;
	cb1.PointLightRange = pointLight_Range;
	cb1.mapControl = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f);
	XMStoreFloat4(&cb1.cameraPosition, *g_pCamera->GetPosition());
	cb1.specularColor = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.2f);
	cb1.specularPower = 128.0f;

	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb1, 0, 0);

	g_pImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader, nullptr, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer);

	g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTexture_Mage);
	g_pImmediateContext->PSSetShaderResources(1, 1, &g_pTexture_Bump_Mage);
	g_pImmediateContext->PSSetShaderResources(2, 1, &g_pTexture_Specular_Mage);

	g_pImmediateContext->PSSetSamplers(0, 1, &g_pCubeTexSamplerState);
	g_pImmediateContext->PSSetSamplers(1, 1, &g_pTexSamplerState_Mirror);

	g_pImmediateContext->RSSetState(g_pRS_Solid);
	g_pImmediateContext->DrawIndexed(g_pModel_Mage->getNumOfIndices(), 0, 0);

	// Render Debug Render lines ////////////////////////////////////////////////////////////////
	g_pImmediateContext->IASetInputLayout(g_pVertexLayout_DR);
	// Gird //
#if 1
	g_pDebugRender_Grid->Render(g_pImmediateContext);
	ConstantBuffer_DR constantBuffer_Grid;
	constantBuffer_Grid.mWorld = XMMatrixTranspose(XMMatrixTranslation(0.0f, -2.5f, 0.0f));
	constantBuffer_Grid.mView = XMMatrixTranspose(g_View);
	constantBuffer_Grid.mProjection = XMMatrixTranspose(g_Projection);
	constantBuffer_Grid.hasAnimation = 0.0f;

	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer_DR, 0, nullptr, &constantBuffer_Grid, 0, 0);
	g_pImmediateContext->VSSetShader(g_pVertexShader_DR, nullptr, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader_DR, nullptr, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer_DR);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer_DR);
	g_pImmediateContext->RSSetState(g_pRS_Solid);
	
	g_pImmediateContext->DrawIndexed(g_pDebugRender_Grid->GetNumOfPoints(), 0, 0);
#endif
	// Joints //
#if 1
	g_pDebugRender_Animation->Render(g_pImmediateContext);
	
	ConstantBuffer_DR constantBuffer_Joints;
	constantBuffer_Joints.mWorld = XMMatrixTranspose(g_World_Mega_Skeleton);
	constantBuffer_Joints.mView = XMMatrixTranspose(g_View);
	constantBuffer_Joints.mProjection = XMMatrixTranspose(g_Projection);
	constantBuffer_Joints.hasAnimation = 1.0f;

	//g_tAnimation_Now += GetFrameTime() * 1000; //Get duration between frames in ms
	g_tAnimation_Now = (float)GetTickCount64();


	int lhsFrameIndex = 0;
	int rhsFrameIndex = 0;
	float finalRatio = 0.0f;
	float duration = (g_tAnimation_Now - g_tAnimation_Start) * g_animationSpeed;
	//if finish animation, reset the timer
	if(duration >= g_pModel_Mage->GetModelAnimationClip()->duration || 
		(duration / g_pModel_Mage->GetModelAnimationClip()->duration) >= g_pModel_Mage->GetModelAnimationClip()->frame[g_pModel_Mage->GetModelAnimationClip()->frame.size() -1].time)
	{
		//708 ms - animation time
		//16 frames (16 frames + 1 frame bindpose)
		g_tAnimation_Start = (float)GetTickCount64();
		duration = 0.0f;
		lhsFrameIndex = 0;
		rhsFrameIndex = 1;
	}
	else
	{
		for (int i = 0; i < g_pModel_Mage->GetModelAnimationClip()->frame.size(); i++)
		{
			if (duration / g_pModel_Mage->GetModelAnimationClip()->duration >= g_pModel_Mage->GetModelAnimationClip()->frame[i].time)
			{
				lhsFrameIndex = i;
				rhsFrameIndex = i + 1;
			}
			else
			{
				break;
			}
		}
	}

	float lhsTimeStamp = (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].time;
	float rhsTimeStamp = (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].time;

	finalRatio = (duration - (lhsTimeStamp * (float)g_pModel_Mage->GetModelAnimationClip()->duration)) /
				 (rhsTimeStamp * (float)g_pModel_Mage->GetModelAnimationClip()->duration - lhsTimeStamp * (float)g_pModel_Mage->GetModelAnimationClip()->duration);

	for (int i = 0; i < NUM_JOINTS; i++)
	{
		XMMATRIX temp;

		XMVECTOR lineX, lineY, lineZ, lineW;
#if 1
		lineX = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x4),
							finalRatio);
		lineY = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y4),
							finalRatio);
		lineZ = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z4),
							finalRatio);
		lineW = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w4),
							finalRatio);
#endif
#if 0
		lineX = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x4),
							1.0f);
		lineY = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y4),
							1.0f);
		lineZ = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z4),
							1.0f);
		lineW = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w4),
							1.0f);
#endif
		
		temp = XMMatrixSet(XMVectorGetX(lineX), XMVectorGetY(lineX), XMVectorGetZ(lineX), XMVectorGetW(lineX),
						   XMVectorGetX(lineY), XMVectorGetY(lineY), XMVectorGetZ(lineY), XMVectorGetW(lineY),
						   XMVectorGetX(lineZ), XMVectorGetY(lineZ), XMVectorGetZ(lineZ), XMVectorGetW(lineZ),
						   XMVectorGetX(lineW), XMVectorGetY(lineW), XMVectorGetZ(lineW), XMVectorGetW(lineW));

		constantBuffer_Joints.translateMatrix[i] = XMMatrixTranspose(temp);
	}

	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer_DR, 0, nullptr, &constantBuffer_Joints, 0, 0);
	g_pImmediateContext->VSSetShader(g_pVertexShader_DR, nullptr, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader_DR, nullptr, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer_DR);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer_DR);
	g_pImmediateContext->RSSetState(g_pRS_Solid);

	g_pImmediateContext->DrawIndexed(g_pDebugRender_Animation->GetNumOfPoints(), 0, 0);
#endif
	// Axes //
#if 1
	g_pDebugRender_AnimationAxis->Render(g_pImmediateContext);
	ConstantBuffer_DR constantBuffer_Axes;
	constantBuffer_Axes.mWorld = XMMatrixTranspose(g_World_Mega_Skeleton);
	constantBuffer_Axes.mView = XMMatrixTranspose(g_View);
	constantBuffer_Axes.mProjection = XMMatrixTranspose(g_Projection);
	constantBuffer_Axes.hasAnimation = 1.0f;
	
	for (int i = 0; i < NUM_JOINTS; i++)
	{
		XMMATRIX temp;
		XMVECTOR lineX, lineY, lineZ, lineW;
#if 1
		lineX = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x4),
							finalRatio);
		lineY = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y4),
							finalRatio);
		lineZ = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z4),
							finalRatio);
		lineW = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w4),
							finalRatio);
#endif
#if 0
		lineX = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x4),
							1.0f);
		lineY = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y4),
							1.0f);
		lineZ = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z4),
							1.0f);
		lineW = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w4),
							1.0f);
#endif
		
		temp = XMMatrixSet(XMVectorGetX(lineX), XMVectorGetY(lineX), XMVectorGetZ(lineX), XMVectorGetW(lineX),
						   XMVectorGetX(lineY), XMVectorGetY(lineY), XMVectorGetZ(lineY), XMVectorGetW(lineY),
						   XMVectorGetX(lineZ), XMVectorGetY(lineZ), XMVectorGetZ(lineZ), XMVectorGetW(lineZ),
						   XMVectorGetX(lineW), XMVectorGetY(lineW), XMVectorGetZ(lineW), XMVectorGetW(lineW));
		constantBuffer_Axes.translateMatrix[i] = XMMatrixTranspose(temp);
	}
	
	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer_DR, 0, nullptr, &constantBuffer_Axes, 0, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer_DR);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer_DR);
	g_pImmediateContext->VSSetShader(g_pVertexShader_DR, nullptr, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader_DR, nullptr, 0);
	g_pImmediateContext->RSSetState(g_pRS_Solid);
	
	g_pImmediateContext->DrawIndexed(g_pDebugRender_AnimationAxis->GetNumOfPoints(), 0, 0);
#endif


	// Render Skinned Animation /////////////////////////////////////////////////////////////////
	// Render the character
	g_pImmediateContext->IASetInputLayout(g_pVertexLayout_SkinnedAnimation);
	stride = sizeof(SimpleVertex);
	offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer_Mage, &stride, &offset);
	// Set index buffer
	g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer_Mage, DXGI_FORMAT_R32_UINT, 0);
	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ConstantBuffer_SkinnedAnimation ConstantBuffer_SkinnedAnimation;
	ConstantBuffer_SkinnedAnimation.mWorld = XMMatrixTranspose(g_World_Mega_Skeleton * XMMatrixTranslation(5.0f, 0.0f, 0.0f));
	ConstantBuffer_SkinnedAnimation.mView = XMMatrixTranspose(g_View);
	ConstantBuffer_SkinnedAnimation.mProjection = XMMatrixTranspose(g_Projection);

	ConstantBuffer_SkinnedAnimation.ambient = ambient;
	ConstantBuffer_SkinnedAnimation.vLightDir[0] = tempLightDir[0];
	ConstantBuffer_SkinnedAnimation.vLightDir[1] = tempLightDir[1];
	ConstantBuffer_SkinnedAnimation.vLightColor[0] = tempLightColor[0];
	ConstantBuffer_SkinnedAnimation.vLightColor[1] = tempLightColor[1];
	ConstantBuffer_SkinnedAnimation.vOutputColor = XMFLOAT4(0, 0, 0, 0);

	ConstantBuffer_SkinnedAnimation.vPointLightPos = pointLight_Position;
	ConstantBuffer_SkinnedAnimation.vPointLightColor = pointLight_Color;
	ConstantBuffer_SkinnedAnimation.vPointLightAttenuation = pointLight_Attenuation;
	ConstantBuffer_SkinnedAnimation.PointLightRange = pointLight_Range;
	ConstantBuffer_SkinnedAnimation.mapControl = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.0f);
	XMStoreFloat4(&ConstantBuffer_SkinnedAnimation.cameraPosition, *g_pCamera->GetPosition());
	ConstantBuffer_SkinnedAnimation.specularColor = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.2f);
	ConstantBuffer_SkinnedAnimation.specularPower = 128.0f;

	g_tSkinnedAnimation_Now = (float)GetTickCount64();

	for (int i = 0; i < NUM_JOINTS; i++)
	{
		XMMATRIX temp;

		XMVECTOR lineX, lineY, lineZ, lineW;
#if 1
		lineX = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].x4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].x4),
							finalRatio);
		lineY = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].y4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].y4),
							finalRatio);
		lineZ = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].z4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].z4),
							finalRatio);
		lineW = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[lhsFrameIndex].translateMatrx[i].w4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[rhsFrameIndex].translateMatrx[i].w4),
							finalRatio);
#endif
#if 0
		lineX = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].x4),
							1.0f);
		lineY = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].y4),
							1.0f);
		lineZ = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].z4),
							1.0f);
		lineW = XMVectorLerp(XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w4),
							 XMVectorSet((float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w1, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w2, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w3, 
										 (float)g_pModel_Mage->GetModelAnimationClip()->frame[1].translateMatrx[i].w4),
							1.0f);
#endif
		
		temp = XMMatrixSet(XMVectorGetX(lineX), XMVectorGetY(lineX), XMVectorGetZ(lineX), XMVectorGetW(lineX),
						   XMVectorGetX(lineY), XMVectorGetY(lineY), XMVectorGetZ(lineY), XMVectorGetW(lineY),
						   XMVectorGetX(lineZ), XMVectorGetY(lineZ), XMVectorGetZ(lineZ), XMVectorGetW(lineZ),
						   XMVectorGetX(lineW), XMVectorGetY(lineW), XMVectorGetZ(lineW), XMVectorGetW(lineW));

		temp = XMMatrixMultiply(g_pInverseJointMatrix[i], temp);

		ConstantBuffer_SkinnedAnimation.translateMatrix[i] = XMMatrixTranspose(temp);
	}

	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer_SkinnedAnimation, 0, nullptr, &ConstantBuffer_SkinnedAnimation, 0, 0);


	g_pImmediateContext->VSSetShader(g_pVertexShader_SkinnedAnimation, nullptr, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader_SkinnedAnimation, nullptr, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer_SkinnedAnimation);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer_SkinnedAnimation);

	g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTexture_Mage);
	g_pImmediateContext->PSSetShaderResources(1, 1, &g_pTexture_Bump_Mage);
	g_pImmediateContext->PSSetShaderResources(2, 1, &g_pTexture_Specular_Mage);

	g_pImmediateContext->PSSetSamplers(0, 1, &g_pCubeTexSamplerState);
	g_pImmediateContext->PSSetSamplers(1, 1, &g_pTexSamplerState_Mirror);


	g_pImmediateContext->RSSetState(g_pRS_Solid);
	g_pImmediateContext->DrawIndexed(g_pModel_Mage->getNumOfIndices(), 0, 0);

	// Render each light ////////////////////////////////////////////////////////////////////////
	g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
	// White light //
#if 0
	stride = sizeof(SimpleVertex);
	offset = 0;
	g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
	// Set index buffer
	g_pImmediateContext->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	// Set primitive topology
	g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	ConstantBuffer cb2;
	cb2.mWorld = XMMatrixTranspose(g_World);
	cb2.mView = XMMatrixTranspose(g_View);
	cb2.mProjection = XMMatrixTranspose(g_Projection);
	cb2.vOutputColor = XMFLOAT4(0, 0, 0, 0);
	cb2.mapControl = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	
	XMMATRIX mLight = XMMatrixTranslationFromVector(5.0f * XMLoadFloat4(&tempLightDir[0]));
	XMMATRIX mLightScale = XMMatrixScaling(0.2f, 0.2f, 0.2f);
	mLight = mLightScale * mLight;
	
	// Update the world variable to reflect the current light
	cb2.mWorld = XMMatrixTranspose(mLight);
	XMMATRIX R = XMMatrixRotationY(t*3.0f);
	cb2.mWorld *= R;
	cb2.vOutputColor = tempLightColor[0];
	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb2, 0, 0);
	
	g_pImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShaderSolid, nullptr, 0);

	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer);

	g_pImmediateContext->PSSetShaderResources(0, 1, &g_pCubesTexture);
	g_pImmediateContext->PSSetSamplers(0, 1, &g_pCubeTexSamplerState);
	g_pImmediateContext->PSSetSamplers(1, 1, &g_pTexSamplerState_Mirror);
	
	g_pImmediateContext->RSSetState(g_pRS_Solid);
	g_pImmediateContext->DrawIndexed(36, 0, 0);
#endif
	//transparent cube (Red light) //
#if 0
	ConstantBuffer cb3;
	cb3.mWorld = XMMatrixTranspose(g_World);
	cb3.mView = XMMatrixTranspose(g_View);
	cb3.mProjection = XMMatrixTranspose(g_Projection);
	cb3.vOutputColor = XMFLOAT4(0.0f, 0.0, 0.0f, 0.0f);
	
	// Update the world variable to reflect the current light
	mLight = XMMatrixTranslationFromVector(3.0f * XMLoadFloat4(&tempLightDir[1]));
	mLightScale = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	mLight = mLightScale * mLight;
	
	cb3.mWorld = XMMatrixTranspose(mLight);
	R = XMMatrixRotationY(t*3.0f);
	cb3.mWorld *= R;
	
	cb3.ambient = ambient;
	cb3.vLightDir[0] = tempLightDir[0];
	cb3.vLightDir[1] = tempLightDir[1];
	cb3.vLightColor[0] = tempLightColor[0];
	cb3.vLightColor[1] = tempLightColor[1];
	cb3.vOutputColor = tempLightColor[1];
	cb3.mapControl = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	
	g_pImmediateContext->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb3, 0, 0);
	
	g_pImmediateContext->VSSetShader(g_pVertexShader, nullptr, 0);
	g_pImmediateContext->PSSetShader(g_pPixelShader, nullptr, 0);
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pConstantBuffer);
	g_pImmediateContext->PSSetShaderResources(0, 1, &g_pCubesTexture);
	g_pImmediateContext->PSSetSamplers(0, 1, &g_pCubeTexSamplerState);
	g_pImmediateContext->PSSetSamplers(1, 1, &g_pTexSamplerState_Mirror);
	
	float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
	g_pImmediateContext->OMSetBlendState(g_pBS_Transparency, blendFactor, 0xffffffff);
	
	g_pImmediateContext->RSSetState(g_pRS_CCWcullMode);
	g_pImmediateContext->DrawIndexed(36, 0, 0);
	g_pImmediateContext->RSSetState(g_pRS_CWcullMode);
	g_pImmediateContext->DrawIndexed(36, 0, 0);
	g_pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);
#endif

	//Draw Text//////////////////////////////////////////////////////////////////////////////////////
#if 1
	g_pImmediateContext->OMSetDepthStencilState(g_pDepthStencilState_disable, 1);
	spriteBatch->Begin();

	std::wstring fpsStr = L"FPS: " + std::to_wstring(fps);
	const wchar_t* fpsW = fpsStr.c_str();
	spriteFont->DrawString(spriteBatch.get(), fpsW, XMFLOAT2(0, 0), Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));

	std::wstring mousePos = L"MousePos: " + std::to_wstring(mouse_X) + L"," + std::to_wstring(mouse_Y);
	const wchar_t* mousePosW = mousePos.c_str();
	spriteFont->DrawString(spriteBatch.get(), mousePosW, XMFLOAT2(0, 25), Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));

	std::wstring animeStr;
	const wchar_t* animeStrW;
	animeStr = L"Animation Speed: " + std::to_wstring(g_animationSpeed);
	animeStrW = animeStr.c_str();
	spriteFont->DrawString(spriteBatch.get(), animeStrW, XMFLOAT2(0, 50), Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));
	animeStr = L"Animation Ratio: " + std::to_wstring(finalRatio);
	animeStrW = animeStr.c_str();
	spriteFont->DrawString(spriteBatch.get(), animeStrW, XMFLOAT2(0, 75), Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));
	animeStr = L"LHS frame index: " + std::to_wstring(lhsFrameIndex);
	animeStrW = animeStr.c_str();
	spriteFont->DrawString(spriteBatch.get(), animeStrW, XMFLOAT2(0, 100), Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));
	animeStr = L"RHS frame index: " + std::to_wstring(rhsFrameIndex);
	animeStrW = animeStr.c_str();
	spriteFont->DrawString(spriteBatch.get(), animeStrW, XMFLOAT2(0, 125), Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f));

	spriteBatch->End();
	g_pImmediateContext->OMSetDepthStencilState(g_pDepthStencilState_enable, 1);
#endif

	// Present our back buffer to our front buffer
	g_pSwapChain->Present(0, 0);

}

void CleanupDevice()
{
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	if (g_pConstantBuffer) g_pConstantBuffer->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pIndexBuffer) g_pIndexBuffer->Release();
	if (g_pVertexLayout) g_pVertexLayout->Release();
	if (g_pVertexShader) g_pVertexShader->Release();
	if (g_pPixelShaderSolid) g_pPixelShaderSolid->Release();
	if (g_pPixelShader) g_pPixelShader->Release();
	if (g_pDepthStencil) g_pDepthStencil->Release();
	if (g_pDepthStencilView) g_pDepthStencilView->Release();
	if (g_pDepthStencilState_enable) g_pDepthStencilState_enable->Release();
	if (g_pDepthStencilState_disable) g_pDepthStencilState_disable->Release();
	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();

	if (g_pCubesTexture) g_pCubesTexture->Release();
	if (g_pCubeTexSamplerState) g_pCubeTexSamplerState->Release();
	if (g_pTexSamplerState_Mirror) g_pTexSamplerState_Mirror->Release();

	if (g_pRS_WireFrame) g_pRS_WireFrame->Release();
	if (g_pRS_Solid) g_pRS_Solid->Release();

	if (g_pBS_Transparency) g_pBS_Transparency->Release();
	if (g_pBS_Transparency_Font) g_pBS_Transparency_Font->Release();
	if (g_pRS_CCWcullMode) g_pRS_CCWcullMode->Release();
	if (g_pRS_CWcullMode) g_pRS_CWcullMode->Release();

	if (g_pPixelShaderFont) g_pPixelShaderFont->Release();

	if (g_pModel_Mage) g_pModel_Mage->Release();
	if (g_pVertexBuffer_Mage) g_pVertexBuffer_Mage->Release();
	if(g_pIndexBuffer_Mage) g_pIndexBuffer_Mage->Release();
	if (g_pTexture_Mage) g_pTexture_Mage->Release();
	if (g_pTexture_Bump_Mage) g_pTexture_Bump_Mage->Release();
	if (g_pTexture_Specular_Mage) g_pTexture_Specular_Mage->Release();

	if (g_pDXInput) g_pDXInput->Release();

	if (g_pCamera)
	{
		delete g_pCamera;
		g_pCamera = 0;
	}
	if (g_pPosition)
	{
		delete g_pPosition;
		g_pPosition = 0;
	}

	if (g_pDebugRender_Grid)
	{
		g_pDebugRender_Grid->Shutdown();
		delete g_pDebugRender_Grid;
		g_pDebugRender_Grid = 0;
	}
	if (g_pDebugRender_Animation)
	{
		g_pDebugRender_Animation->Shutdown();
		delete g_pDebugRender_Animation;
		g_pDebugRender_Animation = 0;
	}
	if (g_pDebugRender_AnimationAxis)
	{
		g_pDebugRender_AnimationAxis->Shutdown();
		delete g_pDebugRender_AnimationAxis;
		g_pDebugRender_AnimationAxis = 0;
	}

	if (g_pVertexShader_DR) g_pVertexShader_DR->Release();
	if (g_pPixelShader_DR) g_pPixelShader_DR->Release();
	if (g_pConstantBuffer_DR) g_pConstantBuffer_DR->Release();
	if (g_pVertexLayout_DR) g_pVertexLayout_DR->Release();

	if (g_pVertexShader_SkinnedAnimation) g_pVertexShader_SkinnedAnimation->Release();
	if (g_pPixelShader_SkinnedAnimation) g_pPixelShader_SkinnedAnimation->Release();
	if (g_pConstantBuffer_SkinnedAnimation) g_pConstantBuffer_SkinnedAnimation->Release();
	if (g_pVertexLayout_SkinnedAnimation) g_pVertexLayout_SkinnedAnimation->Release();
}
