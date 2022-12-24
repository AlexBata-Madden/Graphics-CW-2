#include "loadobj.hpp"

#include <cstdio>
#include <cstddef>
#include <cstring>
#include <vector>

#include "../support/error.hpp"
#include <iostream>
#include <string>


//used opengl tutorial.org on object loading, tutorial #7
SimpleMeshData load_obj_file(char const* aPath, Vec3f aColor, float alpha) {
	
	std::vector< Vec3f > vertices, normals, temp_vertices, temp_normals;
	std::vector< Vec2f > textures, temp_texcoords;
	FILE * objectreader;
	objectreader = fopen(aPath, "r");
	//reads in the first letter/letters of the line
	//0 gets rid of warning for termination zero
	char line[16]= {0};
	int read = fscanf(objectreader, "%s", line);	
	// checks if the file is readable
		while (read==1) {		
			// checks what is the the was read in and choose the corresponding value vertex, normal, texture or face 
			if (strcmp(line, "v") == 0) {
				//creates a vertex and adds the coordinates to it
				Vec3f vertex={0.0f,0.0f,0.0f};
				auto temp = fscanf(objectreader, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				//add it to the list of vertices
				if (temp == 0) {
					break;
				}
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(line, "vt") == 0) {
				//get texture coordinates
				Vec2f text = { 0.0f,0.0f};
				auto temp = fscanf(objectreader, "%f %f\n", &text.x, &text.y);
				if (temp == 0) {
					break;
				}
				//add to list of texture coordiantes
				temp_texcoords.push_back(text);
			}
			else if (strcmp(line, "vn") == 0) {
				//gets the  normals
				Vec3f normal = { 0.0f,0.0f,0.0f };
				auto temp = fscanf(objectreader, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				if (temp == 0) {
					break;
				}
				//add its to the list of normals
				temp_normals.push_back(normal);

			}
			else if (strcmp(line, "f") == 0) {
				//each face is stored as v/n/t v/n/t v/n/t
				// therefore to read in a face we get 3 vertices, 3 normals and 3 texture coordinates
				int vertexIndex[3], textureIndex[3], normalIndex[3];
				auto temp = fscanf(objectreader, " %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &textureIndex[0], &normalIndex[0], &vertexIndex[1], &textureIndex[1], &normalIndex[1], &vertexIndex[2], &textureIndex[2], &normalIndex[2]);
				if (temp == 0) {
					break;
				}
				//in the file the vertex index starts from one and in the index it starts from 0 so minus 1.
				//temp vertices is the unique list of all vertices and we get the specific the vertices that face is referencing
				// then vertices is the order at which vertices appear and should be rendered in
				vertices.push_back(temp_vertices.at(vertexIndex[0]-1));
				vertices.push_back(temp_vertices.at(vertexIndex[1]-1));
				vertices.push_back(temp_vertices.at(vertexIndex[2]-1));
				textures.push_back(temp_texcoords.at(textureIndex[0]-1));
				textures.push_back(temp_texcoords.at(textureIndex[1]-1));
				textures.push_back(temp_texcoords.at(textureIndex[2]-1));
				normals.push_back(temp_normals.at(normalIndex[0] - 1));
				normals.push_back(temp_normals.at(normalIndex[1] - 1));
				normals.push_back(temp_normals.at(normalIndex[2] - 1));

			}
			//read the next line so it can be checked if it can be read
			 read = fscanf(objectreader, "%s", line);
		}
		SimpleMeshData obj;

		std::vector<Vec3f> col(vertices.size(), aColor);
		std::vector<float> alphas(vertices.size(), alpha);

		return SimpleMeshData{ std::move(vertices), std::move(col), std::move(normals), std::move(alphas), std::move(textures) };
		
	}
