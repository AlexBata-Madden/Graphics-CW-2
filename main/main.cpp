#include <glad.h>
#include <GLFW/glfw3.h>
#include <typeinfo>
#include <stdexcept>

#include <cstdio>
#include <cstdlib>
#include <stb_image.h>

#include <stdio.h>
#include <stdlib.h>
#include <stb_image_write.h>
#include <sstream>

#include "../support/error.hpp"
#include "../support/program.hpp"
#include "../support/checkpoint.hpp"
#include "../support/debug_output.hpp"

#include "../vmlib/vec4.hpp"
#include "../vmlib/mat44.hpp"

#include "defaults.hpp"
#include "simple_mesh.hpp"
#include "cone.hpp"
#include "cylinder.hpp"
#include "cuboid.hpp"
#include "camera.hpp"
#include "../vmlib/mat33.hpp"
#include <iostream>
#include "pyramid.hpp"
#include "complex_shapes.hpp"
#include "triangular_prism.hpp"
#include "loadobj.hpp"
#include "animation.hpp"


namespace
{
	constexpr char const* kWindowTitle = "COMP3811 - Coursework 2";
	
	constexpr float kPi_ = 3.1415926f;

	float kMouseSensitivity_ = 0.01f; // radians per pixel

	void glfw_callback_error_( int, char const* );

	void glfw_callback_key_( GLFWwindow*, int, int, int, int );

	void glfw_callback_motion_(GLFWwindow*, double, double);

	struct GLFWCleanupHelper
	{
		~GLFWCleanupHelper();
	};
	struct GLFWWindowDeleter
	{
		~GLFWWindowDeleter();
		GLFWwindow* window;
	};

	GLuint load_texture_2d(char const* aPath);

	void take_screenshot(GLFWwindow* window, const char* file_name);

}

animation animations = animation();


int main() try
{
	// Initialize GLFW
	if( GLFW_TRUE != glfwInit() )
	{
		char const* msg = nullptr;
		int ecode = glfwGetError( &msg );
		throw Error( "glfwInit() failed with '%s' (%d)", msg, ecode );
	}

	// Ensure that we call glfwTerminate() at the end of the program.
	GLFWCleanupHelper cleanupHelper;

	// Configure GLFW and create window
	glfwSetErrorCallback( &glfw_callback_error_ );

	glfwWindowHint( GLFW_SRGB_CAPABLE, GLFW_TRUE );
	glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );

	//glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	glfwWindowHint( GLFW_DEPTH_BITS, 24 );

#	if !defined(NDEBUG)
	// When building in debug mode, request an OpenGL debug context. This
	// enables additional debugging features. However, this can carry extra
	// overheads. We therefore do not do this for release builds.
	glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE );
#	endif // ~ !NDEBUG

	GLFWwindow* window = glfwCreateWindow(
		1280,
		720,
		kWindowTitle,
		nullptr, nullptr
	);

	if( !window )
	{
		char const* msg = nullptr;
		int ecode = glfwGetError( &msg );
		throw Error( "glfwCreateWindow() failed with '%s' (%d)", msg, ecode );
	}

	GLFWWindowDeleter windowDeleter{ window };

	// Set up camera
	Camera camera = Camera();

	glfwSetWindowUserPointer( window, &camera );

	glfwSetKeyCallback( window, &glfw_callback_key_ );

	glfwSetCursorPosCallback( window, &glfw_callback_motion_ );


	// Set up drawing stuff
	glfwMakeContextCurrent( window );
	glfwSwapInterval( 1 ); // V-Sync is on.

	// Initialize GLAD
	// This will load the OpenGL API. We mustn't make any OpenGL calls before this!
	if( !gladLoadGLLoader( (GLADloadproc)&glfwGetProcAddress ) )
		throw Error( "gladLoaDGLLoader() failed - cannot load GL API!" );

	std::printf( "RENDERER %s\n", glGetString( GL_RENDERER ) );
	std::printf( "VENDOR %s\n", glGetString( GL_VENDOR ) );
	std::printf( "VERSION %s\n", glGetString( GL_VERSION ) );
	std::printf( "SHADING_LANGUAGE_VERSION %s\n", glGetString( GL_SHADING_LANGUAGE_VERSION ) );

	// Ddebug output
#	if !defined(NDEBUG)
	setup_gl_debug_output();
#	endif // ~ !NDEBUG

	// Global GL state
	OGL_CHECKPOINT_ALWAYS();

	// Global GL setup 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	OGL_CHECKPOINT_ALWAYS();

	// Get actual framebuffer size.
	// This can be different from the window size, as standard window
	// decorations (title bar, borders, ...) may be included in the window size
	// but not be part of the drawable surface area.
	int iwidth, iheight;
	glfwGetFramebufferSize( window, &iwidth, &iheight );
	
	glViewport( 0, 0, iwidth, iheight );

	// Other initialization & loading
	OGL_CHECKPOINT_ALWAYS();
	
	// Load shader program
	ShaderProgram prog({
		{ GL_VERTEX_SHADER, "assets/default.vert" },
		{ GL_FRAGMENT_SHADER, "assets/default.frag" }
		});

	// Clock and Angle for animation
	auto last = Clock::now();
	float angle = 0.f;

	// Light Source positions

	//Create VAOs
	
	// Floor
	auto floor = make_cuboid({ 100.0f,0.01f,100.0f }, Vec3f{ 0.1f,0.1f,0.1f }, make_translation(Vec3f{ 0.0f,-0.0f,0.0f }), 1.0f, false);
	GLuint floor_vao = create_vao(floor);
	GLsizei floor_vertexCount = (GLsizei)floor.positions.size();

	// Table
	auto table = make_table();
	GLuint table_vao = create_vao(table);
	GLsizei table_vertexCount = (GLsizei)table.positions.size();

	// House
	auto house = make_house();
	GLuint house_vao = create_vao(house);
	GLsizei house_vertexCount = (GLsizei)house.positions.size();

	// Clock
	auto clock = make_clock();
	GLuint clock_vao = create_vao(clock);
	GLsizei clock_vertexCount = (GLsizei)clock.positions.size();

	// Pendulum
	auto pendulum = make_pendulum();
	GLuint pendulum_vao = create_vao(pendulum);
	GLsizei pendulum_vertexCount = (GLsizei)pendulum.positions.size();

	// Clock Handle
	SimpleMeshData clock_hand = make_cuboid(
		{ .05f, .8f, 0.05f },
		{ .0f, .1f, .0f }
	);
	GLuint clock_hand_vao = create_vao(clock_hand);
	GLsizei clock_hand_vertexCount = (GLsizei)clock_hand.positions.size();

	// High Spec Obj
	auto high_spec_cube = make_cuboid({ 1,1,1 }, Vec3f{ 0,1,0 }, make_translation(Vec3f{ 0.0f,0.0f,0.0f }));
	GLuint high_spec_cube_vao = create_vao(high_spec_cube);
	GLsizei high_spec_cube_vertexCount = (GLsizei)high_spec_cube.positions.size();

	// High diff Obj
	auto high_diff_cube = make_cuboid({ 1,1,1 }, Vec3f{ 0,1,0 }, make_translation(Vec3f{ 0.0f,0.0f,0.0f }));
	GLuint high_diff_cube_vao = create_vao(high_diff_cube);
	GLsizei high_diff_cube_vertexCount = (GLsizei)high_diff_cube.positions.size();

	// High emmissive Obj
	auto high_emmissive_cube = make_cuboid({ 1,1,1 }, Vec3f{ 0,1,0 }, make_translation(Vec3f{ 0.0f,0.0f,0.0f }));
	GLuint high_emmissive_cube_vao = create_vao(high_emmissive_cube);
	GLsizei high_emmissive_cube_vertexCount = (GLsizei)high_emmissive_cube.positions.size();

	// Bed
	auto bed = load_obj_file("assets/bed.obj", { 1.0f,1.0f,1.0f }, 1.f);
	GLuint bed_vao = create_vao(bed);
	GLsizei bed_vertexCount = (GLsizei)bed.positions.size();

	// Lamp
	auto lamp = load_obj_file("assets/lamp.obj", { 1.0f,1.0f,1.0f }, 1.f);
	GLuint lamp_vao = create_vao(lamp);
	GLsizei lamp_vertexCount = (GLsizei)lamp.positions.size();

	// Bed Table
	auto bed_table = load_obj_file("assets/bed_table.obj", { 1.0f,1.0f,1.0f }, 1.f);
	GLuint bed_table_vao = create_vao(bed_table);
	GLsizei bed_table_vertexCount = (GLsizei)bed_table.positions.size();

	auto street_light = load_obj_file("assets/streetlight.obj", { 1.0f,1.0f,1.0f }, 1.f);
	GLuint street_light_vao = create_vao(street_light);
	GLsizei street_light_vertexCount = (GLsizei)street_light.positions.size();

	OGL_CHECKPOINT_ALWAYS();
	
	// create textures
	GLuint texture1 =  load_texture_2d("assets/markus.png");
	GLuint texture2 = load_texture_2d("assets/wood.jpg");
	GLuint texture3 = load_texture_2d("assets/red_plastic.jpg");
	GLuint texture4 = load_texture_2d("assets/metal.jpg");
	// Light positions
	Vec3f Lightpos_0 = { 200.0f, 200.0f, 200.0f };
	Vec3f Lightpos_1 = { 200.0f, 200.0f, 200.0f };
	Vec3f Lightpos_2 = { 200.0f, 200.0f, 200.0f };

	double lastFrame = glfwGetTime();
	// Main loop
	while( !glfwWindowShouldClose( window ) )
	{
		// Let GLFW process events
		glfwPollEvents();
		
		// Check if window was resized.
		float fbwidth, fbheight;
		{
			int nwidth, nheight;
			glfwGetFramebufferSize( window, &nwidth, &nheight );

			fbwidth = float(nwidth);
			fbheight = float(nheight);

			if( 0 == nwidth || 0 == nheight )
			{
				// Window minimized? Pause until it is unminimized.
				// This is a bit of a hack.
				do
				{
					glfwWaitEvents();
					glfwGetFramebufferSize( window, &nwidth, &nheight );
				} while( 0 == nwidth || 0 == nheight );
			}

			glViewport( 0, 0, nwidth, nheight );
		}

		// Update camera state
		
		double currentFrame = glfwGetTime();
		double deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera.Update(float(deltaTime));

		// Create tranformation matrices
		Mat44f model2world = make_identity();
		Mat44f projection = make_perspective_projection(60.f * 3.1415926f / 180.f,fbwidth / (float)fbheight,0.1f, 200.0f);
		Mat44f projCameraWorld = projection  * camera.GetMatrix()  * model2world;
		Mat44f modelview = camera.GetMatrix() * model2world;
		Mat33f normalMatrix = mat44_to_mat33(transpose(invert(model2world)));

		// Draw scene
		OGL_CHECKPOINT_DEBUG();

		//TODO: draw frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(prog.programId());

		glUniform3f(5, camera.GetPostition().x, camera.GetPostition().y, camera.GetPostition().z);


		glUniform1f(40, 1.0f);
		glUniform1f(41, 0.0014f);
		glUniform1f(42, 0.000007f);

		//// Light 1
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniform3f(6, -20, 11, -20);
		glUniform3f(7, 1,1,1);
		glUniform3f(8, 1,1,1);
		glUniform3f(9, 7.f, 7.f, 7.f);
		glUniform3f(10, 1.00f, 1.0f, 1.0f);
		//1.00, 0.0527, 0.0200 red light
		
		// Light 2
		glUniform3f(11, 30.5f, 7.f, -7);
		glUniform3f(12, .20f, .2f, 0.2f);
		glUniform3f(13, 0.5f, .50f, 0.5f);
		glUniform3f(14, 7.0f, 7.0f, 7.0f);
		glUniform3f(15, sin(angle) + 1, cos(angle) + 1, -sin(angle) + 1);

		// Light 3
		glUniform3f(16, -20.0f,11.0f,20.0f);
		glUniform3f(17, 1.0f, 1.0f, 1);
		glUniform3f(18, 1.0f, 1.0f, 1);
		glUniform3f(19, 1.0f, 1.0f, 1.0f);
		glUniform3f(20, 1.00f, 0.0527f, 0.0200f);

		
		
		glUniform3f(30, 100.0f, 100.0f, 100.0f);//material spec
		glUniform3f(31, 1.0f, 1.0f, 1.f);//material diff
		glUniform3f(32, 1.f, 1.f, 1.f);//material ambient
		glUniform1f(33, 32.0f);//material shineness
		glUniform3f(34,0.0f,0.0f,0.0f);//material emissive
		
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);

		// Draw Floor
		glBindVertexArray(floor_vao);
		glDrawArrays(GL_TRIANGLES, 0, floor_vertexCount);

		glUniform3f(30, 1.0f, 1.0f, 1.0f);//material spec

		// Bed Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Draw Bed
		model2world = make_scaling(1.5, 1.5, 1.5) * make_translation({ 17,1.f,2 }) * make_rotation_y(deg2rad(-90));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(bed_vao);
		glDrawArrays(GL_TRIANGLES, 0, bed_vertexCount);

		// Lamp Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture3);

		// Draw Lamp
		model2world = make_scaling(1.5, 1.5, 1.5) * make_translation({ 20.75,2.2f,-4.5 });
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(lamp_vao);
		glDrawArrays(GL_TRIANGLES, 0, lamp_vertexCount);

		// Bed Table Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Draw Bed Table
		model2world = make_scaling(1.5, 1.5, 1.5) * make_translation({ 20.5,1.f,-4.25 }) * make_rotation_y(deg2rad(180));
		projCameraWorld = projection * camera.GetMatrix() * model2world ;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(bed_table_vao);
		glDrawArrays(GL_TRIANGLES, 0, bed_table_vertexCount);

		// Street Light Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture4);

		// Street Light 1
		model2world = make_translation({ -20,0.5f,25 }) * make_scaling(7, 6, 6) * make_rotation_y(deg2rad(180));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glBindVertexArray(street_light_vao);
		glDrawArrays(GL_TRIANGLES, 0, street_light_vertexCount);
		
		// Street Light 2
		model2world = make_translation({ -20.0f,0.5f,-25.0f }) * make_scaling(7.0f, 6.0f, 6.0f);
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glBindVertexArray(street_light_vao);
		glDrawArrays(GL_TRIANGLES, 0, street_light_vertexCount);

		auto const now = Clock::now();
		float dt = std::chrono::duration_cast<Secondsf>(now - last).count();
		last = now;

		// Animations
		if (!animations.GetPaused())
		{
			angle += dt * kPi_ * animations.GetSpeed();
			if (angle >= 2.f * kPi_)
				angle -= 2.f * kPi_;
		}

		// Draw Pendulum
		model2world = make_translation(Vec3f{ 0.0f,9.f,-17.5f }) * make_rotation_z(std::sin(angle) * 0.05f) * make_translation({ 0.0f,-3.75f,0.0f });
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(pendulum_vao);
		glDrawArrays(GL_TRIANGLES, 0, pendulum_vertexCount);

		// Draw Clock Hand
		model2world = make_translation(Vec3f{ 0.0f,10.1f,-16.5f }) * make_rotation_y(deg2rad(-90)) * make_rotation_x(angle) * make_translation({ 0.0f,0.4f,0.0f });
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(clock_hand_vao);
		glDrawArrays(GL_TRIANGLES, 0, clock_hand_vertexCount);

		// Draw Clock
		model2world = make_translation(Vec3f{ 0.0f,5.1f,-17.5f });
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(clock_vao);
		glDrawArrays(GL_TRIANGLES, 0, clock_vertexCount);

		// Draw High Specular Cube
		model2world = make_translation({-17,4.75,-20}) * make_identity() * make_rotation_y(deg2rad(30));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(high_spec_cube_vao);
		glDrawArrays(GL_TRIANGLES, 0, high_spec_cube_vertexCount);

		glUniform3f(30, 1,1,1);//material spec
		glUniform3f(31, 100,100,100.f);//material diff
		glUniform3f(32, 1.f,1.f,1.f);//material ambient
		glUniform1f(33, 32.0f);//material shineness
		glUniform3f(34, 0.f, .0f, .0f);//material emissiveness

		// Draw High Diffusion Cube
		model2world = make_translation({ -20,4.75,-20 }) * make_rotation_y(deg2rad(10));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(high_diff_cube_vao);
		glDrawArrays(GL_TRIANGLES, 0, high_diff_cube_vertexCount);

		glUniform3f(30, 1.0f, 1.0f, 1.0f);//material spec
		glUniform3f(31, 1.0f, 1.0f, 1.f);//material diff
		glUniform3f(32, 1.f, 1.f, 1.f);//material ambient
		glUniform1f(33, 32.0f);//material shineness
		glUniform3f(34, 10.0f, 10.0f, 10.0f);//material emissive

		// Draw High emmissive Cube 
		model2world = make_translation({ -23,4.75,-20 }) * make_rotation_y(deg2rad(-70));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glBindVertexArray(high_emmissive_cube_vao);
		glDrawArrays(GL_TRIANGLES, 0, high_emmissive_cube_vertexCount);

		glUniform3f(30, 100, 100, 100.f);//material spec
		glUniform3f(31, 1, 1, 1);//material diff
		glUniform3f(32, 1.f, 1.f, 1.f);//material ambient
		glUniform1f(33, 32.0f);//material shineness
		glUniform3f(34, 0.f, .0f, .0f);//material emissiveness

		// Draw High Specular Cube 2
		model2world = make_translation({ -17,4.75,20 }) * make_identity() * make_rotation_y(deg2rad(30));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(high_spec_cube_vao);
		glDrawArrays(GL_TRIANGLES, 0, high_spec_cube_vertexCount);

		glUniform3f(30, 1, 1, 1);//material spec
		glUniform3f(31, 100, 100, 100.f);//material diff
		glUniform3f(32, 1.f, 1.f, 1.f);//material ambient
		glUniform1f(33, 32.0f);//material shineness
		glUniform3f(34, 0.f, .0f, .0f);//material emissiveness

		// Draw High Diffusion Cube 2
		model2world = make_translation({ -20,4.75,20 }) * make_rotation_y(deg2rad(10));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		glBindVertexArray(high_diff_cube_vao);
		glDrawArrays(GL_TRIANGLES, 0, high_diff_cube_vertexCount);

		glUniform3f(30, 1.0f, 1.0f, 1.0f);//material spec
		glUniform3f(31, 1.0f, 1.0f, 1.f);//material diff
		glUniform3f(32, 1.f, 1.f, 1.f);//material ambient
		glUniform1f(33, 32.0f);//material shineness
		glUniform3f(34, 10.0f, 10.0f, 10.0f);//material emissive

		// Draw High emmissive Cube 2
		model2world = make_translation({ -23,4.75,20 }) * make_rotation_y(deg2rad(-70));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glBindVertexArray(high_emmissive_cube_vao);
		glDrawArrays(GL_TRIANGLES, 0, high_emmissive_cube_vertexCount);

		glUniform3f(30, 1.0f, 1.0f, 1.0f);//material spec
		glUniform3f(31, 1.0f, 1.0f, 1.f);//material diff
		glUniform3f(32, 1.f, 1.f, 1.f);//material ambient
		glUniform1f(33, 32.0f);//material shineness
		glUniform3f(34, 0.0f, 0.0f, 0.0f);//material emissive


		// Draw Table
		model2world = make_translation({ -20, 4, -20 }) * make_rotation_y(deg2rad(90));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glBindVertexArray(table_vao);
		glDrawArrays(GL_TRIANGLES, 0, table_vertexCount);

		// Draw Table 2
		model2world = make_translation({ -20.0f, 4.0f, 20.0f }) * make_rotation_y(deg2rad(90));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glBindVertexArray(table_vao);
		glDrawArrays(GL_TRIANGLES, 0, table_vertexCount);

		// Draw House
		model2world = make_scaling(0.7f, 1.0f, 0.7f) * make_translation({ 30.0f,7.5f,0.0f }) * make_rotation_y(deg2rad(-90));
		projCameraWorld = projection * camera.GetMatrix() * model2world;
		glUniformMatrix4fv(2, 1, GL_TRUE, model2world.v);
		glUniformMatrix4fv(0, 1, GL_TRUE, projCameraWorld.v);
		normalMatrix = mat44_to_mat33(transpose(invert(model2world)));
		glUniformMatrix3fv(1, 1, GL_TRUE, normalMatrix.v);
		glBindVertexArray(house_vao);
		glDrawArrays(GL_TRIANGLES, 0, house_vertexCount);

		OGL_CHECKPOINT_DEBUG();

		// Display results
		glfwSwapBuffers( window );
	}

	// Cleanup.
	//TODO: additional cleanup
	
	return 0;
}
catch( std::exception const& eErr )
{
	std::fprintf( stderr, "Top-level Exception (%s):\n", typeid(eErr).name() );
	std::fprintf( stderr, "%s\n", eErr.what() );
	std::fprintf( stderr, "Bye.\n" );
	return 1;
}


namespace
{
	void glfw_callback_error_( int aErrNum, char const* aErrDesc )
	{
		std::fprintf( stderr, "GLFW error: %s (%d)\n", aErrDesc, aErrNum );
	}

	void glfw_callback_key_(GLFWwindow* aWindow, int aKey, int, int aAction, int)
	{
		if (GLFW_KEY_ESCAPE == aKey && GLFW_PRESS == aAction)
		{
			glfwSetWindowShouldClose(aWindow, GLFW_TRUE);
			return;
		}

		if (GLFW_KEY_P == aKey && GLFW_PRESS == aAction)
		{
			animations.togglePause();
		}

		if (GLFW_KEY_LEFT_BRACKET == aKey && GLFW_PRESS == aAction)
		{
			animations.ChangeSpeed(-.1f);
		}

		if (GLFW_KEY_RIGHT_BRACKET == aKey && GLFW_PRESS == aAction)
		{
			animations.ChangeSpeed(.1f);
		}

		if (GLFW_KEY_PRINT_SCREEN == aKey && GLFW_PRESS == aAction)
		{
			time_t now = time(0);
			tm* ltm = localtime(&now);
			std::stringstream ss;
			ss << ltm->tm_year + 1900 << "_" << ltm->tm_mon + 1 << "_" << ltm->tm_mday << "_" << ltm->tm_hour << "_" << ltm->tm_min << "_" << ltm->tm_sec;
			std::string timestamp = ss.str();

			// Use the timestamp to generate a unique filename
			std::string filename = "screenshots/screenshot_" + timestamp + ".png";

			take_screenshot(aWindow, filename.c_str());
		}

		if (auto* camera = static_cast<Camera*>(glfwGetWindowUserPointer(aWindow)))
		{

			// Space toggles camera
			if (GLFW_KEY_SPACE == aKey && GLFW_PRESS == aAction)
			{
				camera->toggleCameraActive();

				if (camera->getCameraActive())
					glfwSetInputMode(aWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
				else
					glfwSetInputMode(aWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}



			// Camera controls if camera is active
			// actionForward, actionBackwards, actionLeft, actionRight, actionSlow, actionFast;

			if (camera->getCameraActive())
			{
				if (GLFW_KEY_W == aKey)
				{
					if (GLFW_PRESS == aAction)
						camera->togglemovingForward();
					else if (GLFW_RELEASE == aAction)
						camera->togglemovingForward();
				}
				else if (GLFW_KEY_S == aKey)
				{
					if (GLFW_PRESS == aAction)
						camera->togglemovingBack();
					else if (GLFW_RELEASE == aAction)
						camera->togglemovingBack();

				}
				else if (GLFW_KEY_A == aKey)
				{
					if (GLFW_PRESS == aAction)
						camera->togglemovingLeft();
					else if (GLFW_RELEASE == aAction)
						camera->togglemovingLeft();

				}
				else if (GLFW_KEY_D == aKey)
				{
					if (GLFW_PRESS == aAction)
						camera->togglemovingRight();
					else if (GLFW_RELEASE == aAction)
						camera->togglemovingRight();

				}
				else if (GLFW_KEY_LEFT_CONTROL == aKey)
				{
					if (GLFW_PRESS == aAction)
						camera->SetSpeed(20.f);
					else if (GLFW_RELEASE == aAction)
						camera->SetSpeed(10.f);

				}
				else if (GLFW_KEY_LEFT_SHIFT == aKey)
				{
					if (GLFW_PRESS == aAction)
						camera->SetSpeed(5.f);
					else if (GLFW_RELEASE == aAction)
						camera->SetSpeed(10.f);

				}
				else if (GLFW_KEY_Q == aKey)
				{
					if (GLFW_PRESS == aAction)
						camera->togglemovingUp();
					else if (GLFW_RELEASE == aAction)
						camera->togglemovingUp();

				}
				else if (GLFW_KEY_E == aKey)
				{
					if (GLFW_PRESS == aAction)
						camera->togglemovingDown();
					else if (GLFW_RELEASE == aAction)
						camera->togglemovingDown();

				}
			}
		}
	}

	void glfw_callback_motion_(GLFWwindow* aWindow, double aX, double aY)
	{
		if (auto* camera = static_cast<Camera*>(glfwGetWindowUserPointer(aWindow)))
		{
			camera->UpdateOrientation(aX, aY);
		}
	}

	void take_screenshot(GLFWwindow* window, const char* file_name)
	{

		// Get the width and height of the framebuffer
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		// Allocate memory for the pixels
		unsigned char* pixels = (unsigned char*)malloc(static_cast<size_t>(width) * height * 4);

		

		// Read the pixels from the framebuffer
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

		stbi_flip_vertically_on_write(true);

		// Write the pixels to a PNG file
		auto temp = stbi_write_png(file_name, width, height, 4, pixels, width * 4);

		if (temp == 0) {
			std::cout << "Error saving screenshot" << std::endl;
		}
		
		// Free the memory for the pixels
		free(pixels);
	}
	

	GLuint load_texture_2d(char const* aPath)
	{
		assert(aPath);

		stbi_set_flip_vertically_on_load(true);

		int w, h, channels;

		stbi_uc* ptr = stbi_load(aPath, &w, &h, &channels, 4);

		if (!ptr)
			throw Error("Unable to load image '%s'\n", aPath);

		GLuint tex = 0;

		glGenTextures(1, &tex);

		glBindTexture(GL_TEXTURE_2D, tex);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
		
		stbi_image_free(ptr);
		
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY, 6.f);

		return tex;
	}

	

}

namespace
{
	GLFWCleanupHelper::~GLFWCleanupHelper()
	{
		glfwTerminate();
	}

	GLFWWindowDeleter::~GLFWWindowDeleter()
	{
		if( window )
			glfwDestroyWindow( window );
	}
}

