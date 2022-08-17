#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
//#include "imgui_plot.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl2.h"
#include <chrono>

//#include "imgui_plot.h"
//#include "TrashTheCache.h"
////#include "imgui_internal.h"
//
//int ex1Samples{ 100000000 };
//int ex2Samples{ 100000000 };
//int ex3Samples{ 100000000 };
//ImGui::PlotConfig config;
//ImGui::PlotConfig config2;
//ImGui::PlotConfig config3;
//TrashTheCache g_Trash{};
//
//enum class ExType
//{
//	TypeInt = 0,
//	TypeGO3D = 1,
//	TypeGO3DAlt = 2
//};

//void UpdatePlot(ExType type, ImGui::PlotConfig& cf);

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void cycle::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void cycle::Renderer::Render() const
{
	//const auto& color = GetBackgroundColor();
	//SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
	//RenderImGuiWindows();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_Renderer);
}

void cycle::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void cycle::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void cycle::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

//void cycle::Renderer::RenderImGuiWindows() const
//{
//	//First ImGui window
//	ImGui::Begin("Exercise 1");
//	//ImGui::SetWindowPos(ImVec2(10.f, 20.f));
//	//ImGui::SetWindowSize(ImVec2(400.f, 300.f));
//	ImGui::Text("Exercise 1");
//	ImGui::InputInt("Samples", &ex1Samples, 10000, 100);
//	if (ImGui::Button("Trash that ex1 cache!"))
//	{
//		UpdatePlot(ExType::TypeInt, config);
//	}
//	ImGui::Plot("Ex1", config);
//	ImGui::End();
//
//	//Second ImGui window
//	ImGui::Begin("Exercise 2 & 3");
//	//ImGui::SetWindowPos(ImVec2(10.f, 20.f));
//	//ImGui::SetWindowSize(ImVec2(400.f, 300.f));
//	ImGui::Text("Exercise 2");
//	ImGui::InputInt("Samples", &ex2Samples, 10000, 100);
//	if (ImGui::Button("Trash that ex2 cache!"))
//	{
//		UpdatePlot(ExType::TypeGO3D, config2);
//	}
//	ImGui::Plot("Ex2", config2);
//	ImGui::Text("Exercise 3");
//	ImGui::InputInt("Samples", &ex3Samples, 10000, 100);
//	if (ImGui::Button("Trash that ex3 cache!"))
//	{
//		UpdatePlot(ExType::TypeGO3DAlt, config3);
//	}
//	ImGui::Plot("Ex3", config3);
//	ImGui::End();
//}
//
//void UpdatePlot(ExType type, ImGui::PlotConfig& cf)
//{
//	std::vector<float> vec{};
//	static float y_data[11]{};
//	static float x_data[11]{ 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
//	switch (type)
//	{
//	case ExType::TypeInt:
//		vec = g_Trash.Exercise1(ex1Samples);
//		for (int iter = 0; iter < vec.size(); ++iter)
//		{
//			y_data[iter] = vec[iter];
//		}
//		break;
//	case ExType::TypeGO3D:
//		vec = g_Trash.Exercise2(ex2Samples);
//		for (int iter = 0; iter < vec.size(); ++iter)
//		{
//			y_data[iter] = vec[iter];
//		}
//		break;
//	case ExType::TypeGO3DAlt:
//		vec = g_Trash.Exercise3(ex3Samples);
//		for (int iter = 0; iter < vec.size(); ++iter)
//		{
//			y_data[iter] = vec[iter];
//		}
//		break;
//	default:
//		return;
//	}
//	cf.values.xs = x_data;
//	cf.values.ys = y_data;
//	cf.values.count = 12;
//	cf.scale.min = 0;
//	cf.scale.max = 200;
//	cf.tooltip.show = true;
//	cf.tooltip.format = "x=%.2f, y=%.2f";
//	cf.grid_x.show = true;
//	cf.grid_y.show = true;
//	cf.frame_size = ImVec2(300, 150);
//	cf.line_thickness = 2.f;
//}