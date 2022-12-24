#include "complex_shapes.hpp"

SimpleMeshData make_clock()
{

	std::vector<SimpleMeshData> clock_meshes;

	// Shaft
	SimpleMeshData cube1 = make_cuboid(
		{ 0.2f, 8.0f, 2.0f },
		{ 0.5f, 0.3f, 0.0f },
		make_translation({ 1.0f,0.0f,0.0f })
	);
	clock_meshes.emplace_back(cube1);

	SimpleMeshData cube2 = make_cuboid(
		{ 0.2f, 8.0f, 2.0f },
		{ 0.5f, 0.3f, 0.0f },
		make_translation({ -1,0,0 })
	);
	clock_meshes.emplace_back(cube2);

	SimpleMeshData cube3 = make_cuboid(
		{ 2.2f, 8.f, 0.2f },
		{ .5f, .3f, .0f },
		make_translation({ 0.0f, 0.0f, -0.9f })
	);
	clock_meshes.emplace_back(cube3);

	//Top 
	SimpleMeshData cube4 = make_cuboid(
		{ 2.2f, 0.2f, 2.0f },
		{ 0.5f, 0.3f, 0.0f },
		make_translation({ 0.0f, -3.9f, 0.0f })
	);
	clock_meshes.emplace_back(cube4);

	//Bottom
	SimpleMeshData cube5 = make_cuboid(
		{ 2.2f, 0.2f, 2.f },
		{ 0.5f, 0.3f, 0.0f },
		make_translation({ 0.0f, 3.9f, 0.0f })
	);
	clock_meshes.emplace_back(cube5);

	//Base
	SimpleMeshData cube6 = make_cuboid(
		{ 3.2f, 2.f, 2.f },
		{ 0.5f, 0.3f, 0.0f },
		make_translation({ 0.0f, -4.0f, 0.0f })
	);
	clock_meshes.emplace_back(cube6);

	//clock legs
	SimpleMeshData cube7 = make_cuboid(
		{ 0.2f, 0.25f, 0.2f },
		{ 0.f, 0.f, 0.f },
		make_translation({ 1.25f, -5.0f, 0.75f })
	);
	clock_meshes.emplace_back(cube7);

	SimpleMeshData cube8 = make_cuboid(
		{ 0.2f, 0.25f, 0.2f },
		{ 0.f, 0.f, 0.f },
		make_translation({ -1.25f, -5.0f, -0.75f })
	);
	clock_meshes.emplace_back(cube8);

	SimpleMeshData cube9 = make_cuboid(
		{ 0.2f, 0.25f, 0.2f },
		{ 0.0f, 0.0f, 0.0f },
		make_translation({ -1.25f, -5.0f, 0.75f })
	);
	clock_meshes.emplace_back(cube9);

	SimpleMeshData cube10 = make_cuboid(
		{ 0.2f, 0.25f, 0.2f },
		{ 0.0f, 0.0f, 0.0f },
		make_translation({ 1.25f, -5.0f, -0.75f })
	);
	clock_meshes.emplace_back(cube10);

	// Scurting Front
	SimpleMeshData cube12 = make_cuboid(
		{ 2.8f, .05f, .05f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ 0.0f,-3.2f,1.0f })
	);
	clock_meshes.emplace_back(cube12);

	SimpleMeshData cube13 = make_cuboid(
		{ 2.8f, .05f, .05f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ 0.0f,-4.8f,1.0f })
	);
	clock_meshes.emplace_back(cube13);

	SimpleMeshData cube14 = make_cuboid(
		{ .05f, 1.645f, .05f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ 1.4f,-4.0f,1.0f })
	);
	clock_meshes.emplace_back(cube14);

	SimpleMeshData cube15 = make_cuboid(
		{ .05f, 1.645f, .05f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ -1.4f,-4.0f,1.0f })
	);
	clock_meshes.emplace_back(cube15);

	// Scurting Left
	SimpleMeshData cube16 = make_cuboid(
		{ .05f, .05f,1.645f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ -1.6f,-3.2f,0.0f})
	);
	clock_meshes.emplace_back(cube16);

	SimpleMeshData cube17 = make_cuboid(
		{ .05f, .05f, 1.645f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ -1.6f,-4.8f,0.0f })
	);
	clock_meshes.emplace_back(cube17);

	SimpleMeshData cube18 = make_cuboid(
		{ .05f, 1.645f, .05f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ -1.6f,-4.0f,-0.8f })
	);
	clock_meshes.emplace_back(cube18);
	SimpleMeshData cube19 = make_cuboid(
		{ .05f, 1.645f, .05f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ -1.6f,-4.0f,0.8f })
	);
	clock_meshes.emplace_back(cube19);

	// Scurting Right
	SimpleMeshData cube20 = make_cuboid(
		{ .05f, .05f,1.645f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ 1.6f,-3.2f,0.0f })
	);
	clock_meshes.emplace_back(cube20);

	SimpleMeshData cube21 = make_cuboid(
		{ .05f, .05f, 1.645f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ 1.6f,-4.8f,0.0f })
	);
	clock_meshes.emplace_back(cube21);

	SimpleMeshData cube22 = make_cuboid(
		{ .05f, 1.645f, .05f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ 1.6f,-4.0f,-0.8f })
	);
	clock_meshes.emplace_back(cube22);

	SimpleMeshData cube23 = make_cuboid(
		{ .05f, 1.645f, .05f },
		{ 0.6f, 0.2f, 0.f },
		make_translation({ 1.6f,-4.0f,0.8f })
	);
	clock_meshes.emplace_back(cube23);

	// Glass
	SimpleMeshData cube24 = make_cuboid(
		{ 1.81f, 7.f, 0.21f },
		{ .0f, .1f, .0f },
		make_translation({ 0, .5f, .85f }), 0.9f
	);
	clock_meshes.emplace_back(cube24);

	// Sloped Sides
	SimpleMeshData prism1 = make_triangular_prism({ 1.4f,8.0f,2.0f }, 0.5f, { .5f, .3f, .0f }, make_translation({-1.25,1.0f,0.0f }) * make_scaling(0.5f,1.0f,1.0f));
	SimpleMeshData prism2 = make_triangular_prism({ 1.4f,8.0f,2.0f }, 0.5f, { .5f, .3f, .0f }, make_rotation_y(deg2rad(180)) * make_translation({ -1.25f,1.0f,0.0f }) * make_scaling(0.5, 1.0f, 1.0f));
	clock_meshes.emplace_back(prism1);
	clock_meshes.emplace_back(prism2);

	//Clock Face
	auto cylinder1 = make_cylinder(true, 32, { 1.f, 1.f, 1.f }, make_translation({ 0.0f,5.0f,1.001f }) * make_rotation_z(3.141592f / 2.f) * make_scaling(1.2f, 1.2f, 0.2f) * make_rotation_y(deg2rad(90)));
	clock_meshes.emplace_back(cylinder1);

	auto cylinder3 = make_cylinder(true, 32, { .5f, .3f, .0f }, make_translation({ 0,5,1.00 }) * make_rotation_z(3.141592f / 2.f) * make_scaling(1.5f, 1.5f, 2.f) * make_rotation_y(deg2rad(90)));
	clock_meshes.emplace_back(cylinder3);

	auto cylinder4 = make_cylinder(true, 32, { .0f, .0f, .0f }, make_translation({ 0,5,1.20f }) * make_rotation_z(3.141592f / 2.f) * make_scaling(.1f, .1f, .1f) * make_rotation_y(deg2rad(90)));
	clock_meshes.emplace_back(cylinder4);


	SimpleMeshData cube25 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f })* make_rotation_y(deg2rad(90))* make_rotation_x(deg2rad(0))* make_translation({0, 0.8f, 0.f}), 1.f
	);
	clock_meshes.emplace_back(cube25);

	SimpleMeshData cube26 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f })* make_rotation_y(deg2rad(90))* make_rotation_x(deg2rad(30)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube26);

	SimpleMeshData cube27 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f })* make_rotation_y(deg2rad(90))* make_rotation_x(deg2rad(60)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube27);

	SimpleMeshData cube28 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f })* make_rotation_y(deg2rad(90))* make_rotation_x(deg2rad(90)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube28);

	SimpleMeshData cube29 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f })* make_rotation_y(deg2rad(90))* make_rotation_x(deg2rad(120)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube29);

	SimpleMeshData cube30 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f }) *make_rotation_y(deg2rad(90))* make_rotation_x(deg2rad(150))* make_translation({0, 0.8f, 0.f}), 1.f
	);
	clock_meshes.emplace_back(cube30);

	SimpleMeshData cube31 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f }) * make_rotation_x(deg2rad(180)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube31);

	SimpleMeshData cube32 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f }) * make_rotation_y(deg2rad(-90)) * make_rotation_x(deg2rad(30)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube32);

	SimpleMeshData cube33 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f }) * make_rotation_y(deg2rad(-90)) * make_rotation_x(deg2rad(60)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube33);

	SimpleMeshData cube34 = make_cuboid(
		{ .1f, .2f, 0.1f },
		{ .0f, .1f, .0f },
		make_translation({ 0, 5.f, 1.f }) * make_rotation_y(deg2rad(-90)) * make_rotation_x(deg2rad(90)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube34);

	SimpleMeshData cube35 = make_cuboid(
		{ 0.1f, 0.2f, 0.1f },
		{ 0.0f, 0.1f, 0.0f },
		make_translation({ 0.0f, 5.0f, 1.0f }) * make_rotation_y(deg2rad(-90)) * make_rotation_x(deg2rad(120)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube35);

	SimpleMeshData cube36 = make_cuboid(
		{ 0.1f, 0.2f, 0.1f },
		{ 0.0f, 0.1f, 0.0f },
		make_translation({ 0.0f, 5.0f, 1.0f }) * make_rotation_y(deg2rad(-90)) * make_rotation_x(deg2rad(150)) * make_translation({ 0, 0.8f, 0.f }), 1.f
	);
	clock_meshes.emplace_back(cube36);



	SimpleMeshData clock = merge_meshes(clock_meshes);

	return clock;
}

SimpleMeshData make_pendulum() {

	std::vector<SimpleMeshData> pendulum_meshes;

	auto cube = make_cuboid({ 0.2f, 5.5f, 0.1f },
		{ 0.9f, 0.9f,0.6f },
		make_translation({ 0.0f, 1.0f, 0.0f }));
	pendulum_meshes.emplace_back(cube);
	auto cylinder = make_cylinder(true, 32, { 0.9f, 0.9f,0.6f },
		make_translation({ 0,-2,.1f }) * make_rotation_z(3.141592f / 2.0f) * make_scaling(0.4f, 0.4f, 0.2f) * make_rotation_y(deg2rad(90)));
	pendulum_meshes.emplace_back(cylinder);

	SimpleMeshData pendulum = merge_meshes(pendulum_meshes);

	return pendulum;

}

SimpleMeshData make_house() {

	std::vector<SimpleMeshData> house_meshes;

	auto left_wall = make_cuboid({ 1.0f,15.0f,40.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ -20.0f, 0.0f, 0.0f }));
	house_meshes.emplace_back(left_wall);
	auto right_right_wall = make_cuboid({ 1.0f,15.0f,10.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ 20.0f, 0.0f, 15.0f }));
	house_meshes.emplace_back(right_right_wall);
	auto right_left_wall = make_cuboid({ 1.0f,15.0f,10.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ 20.0f, 0.0f,-15.0f }));
	house_meshes.emplace_back(right_left_wall);
	auto right_middle_top_wall = make_cuboid({ 1.0f,5.0f,20.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ 20.0f, 5.0f,0.0f }));
	house_meshes.emplace_back(right_middle_top_wall);
	auto right_middle_bottom_wall = make_cuboid({ 1.0f,5.0f,20.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ 20.0f, -5.0f,0.0f }));
	house_meshes.emplace_back(right_middle_bottom_wall);

	auto back_wall = make_cuboid({ 40.0f,15.0f,1.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ 0.0f, 0.0f, -19.5f }));
	house_meshes.emplace_back(back_wall);
	auto front_left_wall = make_cuboid({ 16.5f,15.0f,1.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ -12.0f, 0.0, 19.5f }));
	house_meshes.emplace_back(front_left_wall);
	auto front_right_wall = make_cuboid({ 16.5f,15.0f,1.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ 12.0f, 0.0f, 19.5f }));
	house_meshes.emplace_back(front_right_wall);
	auto front_middle_wall = make_cuboid({ 9.0f,5.0f,1.0f }, { 0.440f, 0.0308f, 0.433f }, make_translation({ 0.0f, 5.0f, 19.5f }));
	house_meshes.emplace_back(front_middle_wall);
	auto roof = make_triangular_prism({ 46.0f, 15.0f, 40.0f }, 1.0f, { 0.440f, 0.0308f, 0.433f }, make_translation({ 0.0f, 15.0f, 0.0f }));
	house_meshes.emplace_back(roof);
	auto door = make_cuboid({ 9.0f,10.0f,0.5f }, {1.0f,1.0f,1.0f }, make_translation({ 0.0f, -2.5f , 19.5f }) * make_translation({ -4.5f, 0.0f , 0.0f }) * make_rotation_y(1.3f) * make_translation({ 4.5f, 0.0f , 0.0f }));
	house_meshes.emplace_back(door);

	auto window = make_cuboid({ 1.0f,5.0f,20.0f }, { 1.0f,1.0f,1.0f }, make_translation({ 20.0f, 0.0f,0.0f }), 0.7f);
	house_meshes.emplace_back(window);

	SimpleMeshData house = merge_meshes(house_meshes);

	return house;
 
}

SimpleMeshData make_table() {

	std::vector<SimpleMeshData> table_meshes;

	auto top = make_cuboid({ 5.0f,0.5f,10.0f }, {0.2f,0.2f,0.2f});
	table_meshes.emplace_back(top);
	auto leg1 = make_cuboid({ 0.5f,4.0f,0.5f }, { 0.2f,0.2f,0.2f }, make_translation({ 2.0f,-2.0f,-4.5f }));
	table_meshes.emplace_back(leg1);
	auto leg2 = make_cuboid({ 0.5f,4.0f,0.5f }, { 0.2f,0.2f,0.2f }, make_translation({ 2.0f,-2.0f,4.5f }));
	table_meshes.emplace_back(leg2);
	auto leg3 = make_cuboid({ 0.5f,4.0f,0.5f }, { 0.2f,0.2f,0.2f }, make_translation({ -2.0f,-2.0f,-4.5f }));
	table_meshes.emplace_back(leg3);
	auto leg4 = make_cuboid({ 0.5f,4.0f,0.5f }, { 0.2f,0.2f,0.2f }, make_translation({ -2.0f,-2.0f,4.5f }));
	table_meshes.emplace_back(leg4);
	SimpleMeshData table = merge_meshes(table_meshes);

	return table;
}