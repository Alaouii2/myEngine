#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderable2d.h"
#include "src/graphics/simple2drenderer.h"

#include "src/graphics/static_sprite.h"

int main()
{
	using namespace myEngine;
	using namespace graphics;
	using namespace maths;

	Window window("myEngine", 960, 540);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
	
	StaticSprite sprite(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;

	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
	

	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();
		window.update();
	}
	return 0;
}