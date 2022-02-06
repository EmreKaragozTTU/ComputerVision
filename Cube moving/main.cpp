#define GLM_SWIZZLE 

#include <SDL.h>
#include <Windows.h>
#include <gl\GL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include "Cube.h"

bool g_running = true;
SDL_Window* g_window = nullptr;
SDL_GLContext g_context = nullptr;
Cube g_cube;

const float tval = 0.1f;
const float rval = 1;

void ProcessEvent(SDL_Event e) {
	if (e.type == SDL_QUIT)
		g_running = false;

	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
			g_running = false;
			break;
		case SDLK_PAGEUP:
			g_cube.Translate(Vec3(0, 0, -tval));
			break;
		case SDLK_PAGEDOWN:
			g_cube.Translate(Vec3(0, 0, tval));
			break;
		case SDLK_LEFT:
			g_cube.Translate(Vec3(-tval, 0, 0));
			break;
		case SDLK_RIGHT:
			g_cube.Translate(Vec3(tval, 0, 0));
			break;
		case SDLK_UP:
			g_cube.Translate(Vec3(0, tval, 0));
			break;
		case SDLK_DOWN:
			g_cube.Translate(Vec3(0, -tval, 0));
			break;
		case SDLK_a:
			g_cube.Rotate(glm::radians(rval), Vec3(1, 0, 0));
			break;
		case SDLK_s:
			g_cube.Rotate(glm::radians(rval), Vec3(0, 1, 0));
			break;
		case SDLK_d:
			g_cube.Rotate(glm::radians(rval), Vec3(0, 0, 1));
			break;
		case SDLK_q:
			g_cube.Rotate(glm::radians(-rval), Vec3(1, 0, 0));
			break;
		case SDLK_w:
			g_cube.Rotate(glm::radians(-rval), Vec3(0, 1, 0));
			break;
		case SDLK_e:
			g_cube.Rotate(glm::radians(-rval), Vec3(0, 0, 1));
			break;
		case SDLK_m:
			g_cube.SwapTs();
		default:
			break;
		}
	}
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_cube.Draw();

	SDL_GL_SwapWindow(g_window);
}

void Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0) {
		g_running = false;
	}
	else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		g_window = SDL_CreateWindow("CV HW 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (g_window == nullptr) {
			g_running = false;
		}
		else {
			g_context = SDL_GL_CreateContext(g_window);
			if (g_context = nullptr) {
				g_running = false;
			}
			else {
				// Init gl
				SDL_GL_SetSwapInterval(1);
				
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glClearColor(0.f, 0.f, 0.f, 1.f);
			}
		}
	}
}

void Exit() {
	g_running = false;

	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

int main(int argc, char *argv[]) {
	Init();

	SDL_Event e;
	while (g_running) {

		while (SDL_PollEvent(&e)) {
			ProcessEvent(e);
		}

		Render();
	}

	Exit();
	return 0;
}
