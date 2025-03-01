#include "Game.h"
#include "GameComponent.h"
#include "TriangleComponent.h"
Game::Game(LPCWSTR applicationName, long clientWidth, long clientHeight)
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	Display = new DisplayWin32(clientWidth, clientHeight, hInstance, applicationName);

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferCount = 2;
	swapDesc.BufferDesc.Width = clientWidth;
	swapDesc.BufferDesc.Height = clientHeight;
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = Display->hWnd;
	swapDesc.Windowed = true;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;


	D3D_FEATURE_LEVEL featureLevel[] = { D3D_FEATURE_LEVEL_11_1 };

	auto res = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapDesc,
		&swapChain,
		&device,
		nullptr,
		&context);

	if (FAILED(res))
	{
		// Well, that was unexpected
	}

	CreateBackBuffer();
}

void Game::CreateBackBuffer()
{
	auto res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backTex);	// __uuidof(ID3D11Texture2D)
	res = device->CreateRenderTargetView(backTex, nullptr, &rtv);
}

void Game::Initialize()
{
	for (GameComponent* comp : gameComponents)
	{
		comp->Initialize();
	}
}

void Game::Run()
{
	Initialize();
	prevTime = std::chrono::steady_clock::now();
	totalTime = 0;
	unsigned int frameCount = 0;

	isExitRequested = false;
	while (!isExitRequested) {
		MessageHandler();

		context->ClearState();
		

		auto	curTime = std::chrono::steady_clock::now();
		float	deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(curTime - prevTime).count() / 1000000.0f;
		prevTime = curTime;

		totalTime += deltaTime;
		frameCount++;

		if (totalTime > 1.0f) {
			float fps = frameCount / totalTime;

			totalTime -= 1.0f;

			WCHAR text[256];
			swprintf_s(text, TEXT("FPS: %f"), fps);
			SetWindowText(Display->hWnd, text);

			frameCount = 0;
		}

		context->OMSetRenderTargets(1, &rtv, nullptr);
		
		Draw();

		context->OMSetRenderTargets(0, nullptr, nullptr);
		
		swapChain->Present(1, /*DXGI_PRESENT_DO_NOT_WAIT*/ 0);
	}
	Exit();
}

void Game::Draw()
{
	float color[] = { 0.f, 0.f, 0.f, 1.0f };
	context->ClearRenderTargetView(rtv, color);

	for (GameComponent* comp : gameComponents)
	{
		comp->Draw();
	}
}

void Game::MessageHandler()
{
	MSG msg = {};
	// Handle the windows messages.
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If windows signals to end the application then exit out.
	if (msg.message == WM_QUIT) {
		isExitRequested = true;
	}

	if (msg.message == VK_LEFT)
	{
		for (GameComponent* comp : gameComponents)
		{
			std::cout << "left\n";
			comp->data.radius.x -= 100;
		}
	}
	else if (msg.message == VK_RIGHT)
	{
		for (GameComponent* comp : gameComponents)
		{
			comp->data.radius.x += 100;
		}
	}
}

void Game::DestroyResources()
{
	for (GameComponent* comp : gameComponents)
	{
		comp->DestroyResources();
	}
}

void Game::Exit()
{
	DestroyResources();
}
