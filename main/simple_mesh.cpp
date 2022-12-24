#include "simple_mesh.hpp"

SimpleMeshData concatenate(SimpleMeshData aM, SimpleMeshData const& aN)
{
	aM.positions.insert(aM.positions.end(), aN.positions.begin(), aN.positions.end());
	aM.colors.insert(aM.colors.end(), aN.colors.begin(), aN.colors.end());
	aM.normals.insert(aM.normals.end(), aN.normals.begin(), aN.normals.end());
	aM.alphas.insert(aM.alphas.end(), aN.alphas.begin(), aN.alphas.end());
	aM.textures.insert(aM.textures.end(), aN.textures.begin(), aN.textures.end());

	return aM;
}

SimpleMeshData merge_meshes(std::vector<SimpleMeshData> const& meshes)
{
	SimpleMeshData result;

	// Determine the total number of vertices in all the meshes
	size_t totalVertices = 0;
	for (auto const& mesh : meshes)
	{
		totalVertices += mesh.positions.size();
	}

	// Allocate memory for the merged mesh
	result.positions.reserve(totalVertices);
	result.colors.reserve(totalVertices);
	result.normals.reserve(totalVertices);

	// Merge the meshes
	for (auto const& mesh : meshes)
	{
		result.positions.insert(result.positions.end(), mesh.positions.begin(), mesh.positions.end());
		result.colors.insert(result.colors.end(), mesh.colors.begin(), mesh.colors.end());
		result.normals.insert(result.normals.end(), mesh.normals.begin(), mesh.normals.end());
		result.alphas.insert(result.alphas.end(), mesh.alphas.begin(), mesh.alphas.end());
		result.textures.insert(result.textures.end(), mesh.textures.begin(), mesh.textures.end());

	}

	return result;
}



GLuint create_vao(SimpleMeshData const& aMeshData)
{
	//TODO: implement me

	GLuint positionVBO = 0;
	glGenBuffers(1, &positionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glBufferData(GL_ARRAY_BUFFER, aMeshData.positions.size() * sizeof(Vec3f), aMeshData.positions.data(), GL_STATIC_DRAW);

	GLuint colorVBO = 0;
	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, aMeshData.colors.size() * sizeof(Vec3f), aMeshData.colors.data(), GL_STATIC_DRAW);

	GLuint normalVBO = 0;
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, aMeshData.normals.size() * sizeof(Vec3f), aMeshData.normals.data(), GL_STATIC_DRAW);

	GLuint alphaVBO = 0;
	glGenBuffers(1, &alphaVBO);
	glBindBuffer(GL_ARRAY_BUFFER, alphaVBO);
	glBufferData(GL_ARRAY_BUFFER, aMeshData.normals.size() * sizeof(float), aMeshData.alphas.data(), GL_STATIC_DRAW);

	GLuint textureVBO = 0;
	glGenBuffers(1, &textureVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, aMeshData.textures.size() * sizeof(Vec2f), aMeshData.textures.data(), GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Specify attribute index 0
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// Specify attribute index 1
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glVertexAttribPointer(
		1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(1);

	// Specify attribute index 2
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// Specify attribute index 3
	glBindBuffer(GL_ARRAY_BUFFER, alphaVBO);
	glVertexAttribPointer( 3,	1, GL_FLOAT, GL_TRUE, 0, 0);
	glEnableVertexAttribArray(3);

	// Specify attribute index 4
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glVertexAttribPointer(
		4, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(4);

	// Reset state
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Clean up buffers
	// Note: these are not deleted fully, as the VAO holds a reference to them
	glDeleteBuffers(1, &positionVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &normalVBO);
	glDeleteBuffers(1, &alphaVBO);
	glDeleteBuffers(1, &textureVBO);


	// Reset state
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vao;
}

GLuint create_vao(std::vector<SimpleMeshData> const& meshes)
{
	// Determine the total number of vertices in all the meshes
	size_t totalVertices = 0;
	for (auto const& mesh : meshes)
	{
		totalVertices += mesh.positions.size();
	}

	// Create VBOs for positions and colors
	GLuint positionVBO = 0;
	glGenBuffers(1, &positionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glBufferData(GL_ARRAY_BUFFER, totalVertices * sizeof(Vec3f), nullptr, GL_STATIC_DRAW); 

	GLuint colorVBO = 0;
	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, totalVertices * sizeof(Vec3f), nullptr, GL_STATIC_DRAW); 

	GLuint normalVBO = 0;
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, totalVertices * sizeof(Vec3f), nullptr, GL_STATIC_DRAW); 

	GLuint alphaVBO = 0;
	glGenBuffers(1, &alphaVBO);
	glBindBuffer(GL_ARRAY_BUFFER, alphaVBO);
	glBufferData(GL_ARRAY_BUFFER, totalVertices * sizeof(float), nullptr, GL_STATIC_DRAW);

	GLuint textureVBO = 0;
	glGenBuffers(1, &textureVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, totalVertices * sizeof(Vec2f), nullptr, GL_STATIC_DRAW);

	// Copy data from each mesh into the VBOs
	size_t offset = 0;
	for (auto const& mesh : meshes)
	{
		// Copy position data
		glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vec3f), mesh.positions.size() * sizeof(Vec3f), mesh.positions.data());

		// Copy color data
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vec3f), mesh.colors.size() * sizeof(Vec3f), mesh.colors.data());

		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vec3f), mesh.normals.size() * sizeof(Vec3f), mesh.normals.data());

		glBindBuffer(GL_ARRAY_BUFFER, alphaVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), mesh.alphas.size() * sizeof(float), mesh.alphas.data());

		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vec2f), mesh.textures.size() * sizeof(float), mesh.textures.data());

		offset += mesh.positions.size();
	}

	// Create VAO
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Specify attribute index 0
	glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
	glVertexAttribPointer(
		0, // location = 0 in vertex shader
		3, GL_FLOAT, GL_FALSE, // 3 floats, not normalized to [0..1] (GL_FALSE)
		0, // stride = 0 indicates that there is no padding between inputs
		0 // data starts at offset 0 in the VBO.
	);
	glEnableVertexAttribArray(0);

	// Specify attribute index 1
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,	0, 0);
	glEnableVertexAttribArray(1);

	// Specify attribute index 2
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// Specify attribute index 2
	glBindBuffer(GL_ARRAY_BUFFER, alphaVBO);
	glVertexAttribPointer(
		3, 1, GL_FLOAT, GL_TRUE, 0, 0);
	glEnableVertexAttribArray(3);

	// Specify attribute index 2
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glVertexAttribPointer(	4,	2, GL_FLOAT, GL_FALSE,	0, 0 );
	glEnableVertexAttribArray(4);

	// Reset state
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Clean up buffers
	glDeleteBuffers(1, &positionVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &normalVBO);
	glDeleteBuffers(1, &alphaVBO);
	glDeleteBuffers(1, &textureVBO);

	return vao;
}
